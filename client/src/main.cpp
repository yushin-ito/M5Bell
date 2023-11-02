#include "M5Battery.h"
#include "M5TextScroll.h"
#include <ArduinoJson.h>
#include <M5StickCPlus.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

enum STATE { YES, NO, WAIT };

LGFX lcd;
static LGFX_Sprite canvas(&lcd);

WebSocketsClient client;

StaticJsonDocument<64> doc;

M5TextScroll ts(0, lcd.height() / 2 + 50, 1);
M5Battery bat(190, 12, 3);

const char* ssid = "ESP32-AP";
const char* password = "password";

void onEvent(WStype_t type, uint8_t* payload, size_t length);
void onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info);

uint8_t code = 3;
uint8_t count = 0;
bool isRequest = false;

void setup() {
    M5.begin();
    Serial.begin(115200);
    delay(500);
    Serial.println();

    lcd.init();
    lcd.setRotation(1);
    M5.Axp.ScreenBreath(10);
    WiFi.onEvent(onDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

    WiFi.begin(ssid, password);
    Serial.print("WiFi connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nWiFi connected.");

    ts.setText("ボタンを押してください");

    client.begin("192.168.1.1", 80, "/ws");
    client.onEvent(onEvent);
    client.setReconnectInterval(5000);
}

void loop() {
    M5.update();
    M5.Beep.update();

    ts.showTextScroll();
    bat.showBattery();
    bat.updateBattery();

    if (M5.BtnA.wasPressed()) {
        M5.Beep.tone(3300);
        delay(400);
        M5.Beep.mute();
        M5.Beep.tone(2600);
        delay(800);
        M5.Beep.mute();
        ts.setText("しばらくお待ちください");
        client.sendTXT("request");
        isRequest = true;
    }

    switch (code) {
    case YES:
        ts.setText("入室してください");
        break;
    case NO: 
        ts.setText("現在対応できません");
        break;
    case WAIT: {
        char buffer[32];
        sprintf(buffer, "%d分後入室できます", count);
        ts.setText(buffer);
    } break;
    }

    if (code < 3) {
        M5.Beep.tone(3300, 500);
        isRequest = false;
        code = 3;
    }

    if (ts.getScrollCount() > 10) {
        ts.setText("ボタンを押してください");
        if (isRequest) {
            client.sendTXT("timeout");
            M5.Beep.tone(3300, 500);
            isRequest = false;
        }
    }

    client.loop();
}
void onEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
    case WStype_CONNECTED:
        Serial.println("[CONNECT] WebSocket connected");
        break;
    case WStype_DISCONNECTED:
        Serial.println("[DISCONNECT] WebSocket disconnected");
        break;
    case WStype_TEXT: {
        deserializeJson(doc, payload);
        code = doc["code"];
        count = doc["count"];
        Serial.print("[RECIEVE] WebSocket recieved status code: ");
        Serial.println(code);
    } break;
    default:
        break;
    }
}

void onDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.println("WiFi lost connection.");
    Serial.println("WiFi reconnecting...");
    WiFi.begin(ssid, password);
}