#include "M5Battery.h"
#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

extern LGFX lcd;
static LGFX_Sprite canvas(&lcd);

M5Battery::M5Battery(int32_t x, int32_t y, size_t size = 0) {

    _x = x;
    _y = y;

    if (MAX_SIZE < size) {
        _size = MAX_SIZE;
    } else if (size < MIN_SIZE) {
        _size = MIN_SIZE;
    } else {
        _size = size;
    }

    _width = 12 * _size;
    _height = 5 * _size;
    _top_width = 1 * _size;
    _bg_color = lcd.color888(0, 0, 0);
    _border_color = lcd.color888(255, 255, 255);
}

void M5Battery::setBgColor(uint32_t color) { _bg_color = color; }

void M5Battery::setBorderColor(uint32_t color) { _border_color = color; }

void M5Battery::showBattery() {
    _flag = true;
    drawBatteryShape();
    canvas.setColorDepth(16);
    canvas.createSprite(_width - 4, _height - 4);
}

void M5Battery::deleteBattery() {
    canvas.deleteSprite();
    canvas.createSprite(_width + _top_width, _height);
    canvas.fillSprite(_bg_color);
    canvas.pushSprite(_x, _y);
    canvas.deleteSprite();
    _flag = false;
}

void M5Battery::updateBattery() {
    if (!_flag) {
        return;
    }

    uint8_t percent = getBatteryPercent();

    canvas.fillRect(0, 0, _width - 4, _height - 4, _bg_color);

    int32_t fill_width = int32_t((_width - 4) * (percent / 100.0f));
    canvas.fillRect(0, 0, fill_width, _height - 4, getBatteryColor());

    canvas.pushSprite(_x + 2, _y + 2);
}

void M5Battery::drawBatteryShape() {
    canvas.setColorDepth(1);
    canvas.createSprite(_width + _top_width, _height);
    canvas.fillSprite(0);

    canvas.fillRect(0, 0, _width, _height, _border_color);
    canvas.fillRect(2, 2, _width - 4, _height - 4, 0);
    canvas.fillRect(_width, _top_width, _top_width, _height - (_top_width * 2),
                    _border_color);

    canvas.setBitmapColor(_border_color, 0);
    canvas.pushSprite(_x, _y, 0);
}

uint8_t M5Battery::getBatteryPercent() {
    float _voltage = M5.Axp.GetBatVoltage();
    float percent = (_voltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE);
    return roundf(percent * 100.0f);
}

uint32_t M5Battery::getBatteryColor() {
    uint32_t color = lcd.color888(255, 255, 255);
    if (isLowBattery()) {
        color = lcd.color888(255, 0, 0);
    } else if (!isUsingBattery()) {
        color = lcd.color888(0, 255, 0);
    }
    return color;
}

bool M5Battery::isLowBattery() {
    uint8_t _battery = M5.Axp.GetWarningLeve();
    if (_battery == 0) {
        return false;
    } else {
        return true;
    }
}

bool M5Battery::isUsingBattery() {
    float _battery = M5.Axp.GetBatCurrent();
    if (_battery < 0.0f) {
        return true;
    } else {
        return false;
    }
}