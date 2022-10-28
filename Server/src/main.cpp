#include "M5Battery.h"
#include "M5Clock.h"
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <M5StickCPlus.h>
#include <Preferences.h>
#include <SPIFFS.h>
#include <WiFi.h>

#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

#define HTTP_PORT 80
#define FORMAT_SPIFFS_IF_FAILED true

enum { NORMAL, SELECT, COUNT } state = NORMAL;

AsyncWebServer server(HTTP_PORT);
AsyncWebSocket ws("/ws");
Preferences preferences;
LGFX lcd;

M5Clock cl;
M5Battery bat(190, 12, 3);

const char *ssid = "ESP32-AP";
const char *password = "password";
const IPAddress ip(192, 168, 1, 1);
const IPAddress subnet(255, 255, 255, 0);

uint8_t count = 1;
uint8_t code = 0;
bool isRecieved = false;
bool isTimeout = false;

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len);
void broadcastJson(uint8_t code, String &timestamp, uint8_t _count = 1);

void setup() {
    M5.begin();
    Serial.begin(115200);
    delay(500);
    Serial.println();

    lcd.init();
    lcd.setRotation(1);
    M5.Axp.ScreenBreath(10);

    Wire1.beginTransmission(0x51);
    Wire1.write(0x00);
    Wire1.write(0x00);
    Wire1.write(0x00);
    Wire1.endTransmission();

    SPIFFS.begin(FORMAT_SPIFFS_IF_FAILED);
    preferences.begin("M5Bell", false);

    WiFi.softAP(ssid, password);
    delay(100);
    WiFi.softAPConfig(ip, ip, subnet);

    server.on("/api/log", HTTP_GET, [](AsyncWebServerRequest *request) {
        String timestamp =
            preferences.getString("timestamp", "----/--/-- --:--");
        request->send(200, "text/plain", timestamp);
    });

    server.on("/api/wifi", HTTP_GET, [](AsyncWebServerRequest *request) {
        String ssid = request->getParam("ssid")->value();
        String password = request->getParam("password")->value();
        cl.connectWiFi(ssid, password);
        request->send(200);
    });

    server.serveStatic("/", SPIFFS, "/www/").setDefaultFile("index.html");

    server.onNotFound([](AsyncWebServerRequest *server) {
        server->method() == HTTP_OPTIONS ? server->send(200)
                                         : server->send(404);
    });

    ws.onEvent(onEvent);
    server.addHandler(&ws);

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

    server.begin();
    Serial.println("Server started.");
}

void loop() {
    M5.update();
    M5.Beep.update();
    cl.update();

    if (isRecieved) {
        lcd.clear();
        isRecieved = false;
    }

    if (isTimeout) {
        lcd.setTextColor(RED);
        isTimeout = false;
    }

    switch (state) {
    case NORMAL: {
        bat.showBattery();
        bat.updateBattery();
        cl.printTime(20, 20, 150, 48);
        lcd.drawLine(10, 70, lcd.width() - 10, 70, WHITE);
        String timestamp =
            preferences.getString("timestamp", "----/--/-- --:--");
        lcd.setFont(&fonts::lgfxJapanGothic_20);
        lcd.setCursor(30, 80);
        lcd.print(timestamp);
        lcd.print("に");
        lcd.setCursor(20, 105);
        lcd.print("ボタンが押されました");
        delay(100);
    } break;
    case SELECT: {
        lcd.setFont(&fonts::lgfxJapanGothic_32);
        lcd.setCursor(10, 20);
        code == 0 ? lcd.setTextColor(GREEN) : lcd.setTextColor(WHITE);
        lcd.print("入室できます");
        lcd.setCursor(10, 52);
        code == 1 ? lcd.setTextColor(GREEN) : lcd.setTextColor(WHITE);
        lcd.print("入室できません");
        lcd.setCursor(10, 84);
        code == 2 ? lcd.setTextColor(GREEN) : lcd.setTextColor(WHITE);
        lcd.print("〇分後対応可能");
        if (M5.BtnA.wasReleased()) {
            M5.Beep.tone(3300, 100);
            code = (code > 1) ? 0 : code + 1;
            lcd.clear();
        }
        if (M5.BtnB.wasPressed()) {
            M5.Beep.tone(3300, 300);
            if (code == 2) {
                state = COUNT;
            } else {
                String timestamp = cl.getTimeStamp();
                broadcastJson(code, timestamp);
                state = NORMAL;
                code = 0;
            }
            lcd.clear();
        }
    } break;
    case COUNT: {
        lcd.setTextColor(WHITE);
        lcd.setCursor(10, 20);
        lcd.printf("%d分後に", count);
        lcd.setCursor(10, 52);
        lcd.print("入室できます");
        if (M5.BtnA.wasPressed()) {
            M5.Beep.tone(3300, 100);
            count++;
            lcd.clear();
        }
        if (M5.BtnA.pressedFor(1000)) {
            count++;
            delay(200);
            lcd.clear();
        }
        if (M5.BtnB.wasPressed()) {
            M5.Beep.tone(3300, 300);
            String timestamp = cl.getTimeStamp();
            broadcastJson(code, timestamp, count);
            state = NORMAL;
            code = 0;
            count = 1;
            lcd.clear();
        }
    } break;
    }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len) {
    switch (type) {
    case WS_EVT_CONNECT:
        Serial.println("[CONNECT] WebSocket connected");
        break;
    case WS_EVT_DISCONNECT:
        Serial.println("[DISCONNECT] WebSocket disconnected");
        break;
    case WS_EVT_DATA: {
        Serial.println("[RECIEVE] WebSocket recieved from client");
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len) {
            data[len] = 0;
            if (strcmp((char *)data, "request") == 0) {
                M5.Beep.tone(3300);
                delay(500);
                M5.Beep.mute();
                M5.Beep.tone(2600);
                delay(1000);
                M5.Beep.mute();
                state = SELECT;
                String timestamp = cl.getTimeStamp();
                broadcastJson(3, timestamp);
                preferences.putString("timestamp", timestamp);
            }
            if (strcmp((char *)data, "timeout") == 0) {
                M5.Beep.tone(3300, 300);
                code = 0;
                count = 1;
                state = NORMAL;
                isTimeout = true;
            }
            isRecieved = true;
        }
    } break;
    case WS_EVT_ERROR:
        Serial.println("[ERROR] WebSocket error");
        break;
    default:
        break;
    }
}

void broadcastJson(uint8_t code, String &timestamp, uint8_t count) {
    StaticJsonDocument<256> doc;
    doc["code"] = code;
    doc["timestamp"] = timestamp;
    doc["count"] = count;
    char data[256];
    size_t len = serializeJson(doc, data);
    ws.textAll(data, len);
}