#include <M5StickCPlus.h>
#include <WiFi.h>

#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

class M5Clock {
  public:
    M5Clock();
    void printTime(int32_t _time_pos_x, int32_t _time_pos_y, uint16_t width,
                   uint16_t height);
    void printDate(int32_t _date_pos_x, int32_t _date_pos_y);
    void setColor(uint16_t color);
    void setBgColor(uint16_t bg_color);
    void setDateSize(float _date_size);
    void setTimeSize(float _time_size);
    void connectWiFi(String &_ssid, String &_password);
    void update();
    String getTimeStamp();

  private:
    const char *_ssid;
    const char *_password;
    const char *ntp_server = "ntp.jst.mfeed.ad.jp";
    const long gmtOffset_sec = 9 * 3600;
    const char *wd[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const int daylightOffset_sec = 0;
    RTC_DateTypeDef RTC_DateStruct;
    RTC_TimeTypeDef RTC_TimeStruct;
    float _date_size;
    float _time_size;
    uint16_t _color;
    uint16_t _bg_color;
    uint8_t min = 0;
};
