#include <M5StickCPlus.h>

class M5Battery {
  public:
    M5Battery(int32_t x, int32_t y, size_t size);
    void setBgColor(uint32_t color);
    void setBorderColor(uint32_t color);
    void showBattery();
    void deleteBattery();
    void updateBattery();
    uint8_t getBatteryPercent();
    bool isLowBattery();
    bool isUsingBattery();

  private:
    const float MAX_VOLTAGE = 4.2f;
    const float MIN_VOLTAGE = 3.0f;
    const uint8_t MAX_SIZE = 7;
    const uint8_t MIN_SIZE = 1;

    bool _flag = true;
    int32_t _x;
    int32_t _y;
    size_t _size;
    int32_t _width;
    int32_t _height;
    int32_t _top_width;
    uint32_t _bg_color;
    uint32_t _border_color;

    void drawBatteryShape();
    uint32_t getBatteryColor();
};