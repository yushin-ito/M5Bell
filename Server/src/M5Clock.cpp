#include "M5Clock.h"

extern LGFX lcd;
static LGFX_Sprite canvas(&lcd);

M5Clock::M5Clock() {
    _ssid = "";
    _password = "";
    _time_size = 0.9;
    _date_size = 0.9;
    _color = WHITE;
    _bg_color = BLACK;
}

void M5Clock::setColor(uint16_t color) { _color = color; }
void M5Clock::setBgColor(uint16_t bg_color) { _bg_color = bg_color; }
void M5Clock::setTimeSize(float time_size) { _time_size = time_size; }
void M5Clock::setDateSize(float date_size) { _date_size = date_size; }

void M5Clock::printTime(int32_t _time_pos_x, int32_t _time_pos_y,
                        uint16_t width, uint16_t height) {
    canvas.setTextSize(_time_size);
    canvas.setTextColor(_color);
    canvas.setTextWrap(false);
    canvas.setCursor(0, 0);
    canvas.createSprite(width, height);
    canvas.setFont(&Font7);
    canvas.printf("%02d:%02d", RTC_TimeStruct.Hours, RTC_TimeStruct.Minutes);
    canvas.setFont(&Font2);
    canvas.printf(" : %02d\n", RTC_TimeStruct.Seconds);
    canvas.pushSprite(_time_pos_x, _time_pos_y);
}

void M5Clock::printDate(int32_t _date_pos_x, int32_t _date_pos_y) {
    canvas.setTextSize(_date_size);
    canvas.setTextColor(_color);
    canvas.setFont(&Font0);
    canvas.setCursor(_date_pos_x, _date_pos_y);

    canvas.printf("Date: %04d.%02d.%02d %s\n", RTC_DateStruct.Year,
                  RTC_DateStruct.Month, RTC_DateStruct.Date,
                  wd[RTC_DateStruct.WeekDay]);
}

void M5Clock::connectWiFi(String &_ssid, String &_password) {
    size_t ssid_len = _ssid.length() + 1;
    char ssid[ssid_len];
    _ssid.toCharArray(ssid, ssid_len);

    size_t password_len = _password.length() + 1;
    char password[password_len];
    _password.toCharArray(password, password_len);

    if (WiFi.status() == WL_CONNECTED)
        WiFi.disconnect(true);
    delay(100);
    WiFi.begin(ssid, password);
    Serial.println("WiFi has successfully connected.");
}

void M5Clock::update() {
    M5.Rtc.GetTime(&RTC_TimeStruct);
    M5.Rtc.GetData(&RTC_DateStruct);
    if (WiFi.status() == WL_CONNECTED) {
        configTime(gmtOffset_sec, daylightOffset_sec, ntp_server);

        struct tm timeInfo;
        if (getLocalTime(&timeInfo)) {

            RTC_TimeTypeDef TimeStruct;
            TimeStruct.Hours = timeInfo.tm_hour;
            TimeStruct.Minutes = timeInfo.tm_min;
            TimeStruct.Seconds = timeInfo.tm_sec;
            M5.Rtc.SetTime(&TimeStruct);

            RTC_DateTypeDef DateStruct;
            DateStruct.WeekDay = timeInfo.tm_wday;
            DateStruct.Month = timeInfo.tm_mon + 1;
            DateStruct.Date = timeInfo.tm_mday;
            DateStruct.Year = timeInfo.tm_year + 1900;
            M5.Rtc.SetData(&DateStruct);
        }
    }
}

String M5Clock::getTimeStamp() {
    char timestamp[126];
    sprintf(timestamp, "%04d/%02d/%02d %02d:%02d", RTC_DateStruct.Year,
            RTC_DateStruct.Month, RTC_DateStruct.Date, RTC_TimeStruct.Hours,
            RTC_TimeStruct.Minutes, RTC_TimeStruct.Minutes);
    return String(timestamp);
}
