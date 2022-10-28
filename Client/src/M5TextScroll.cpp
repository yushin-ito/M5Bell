#include "M5TextScroll.h"
#define LGFX_AUTODETECT
#define LGFX_USE_V1
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>

extern LGFX lcd;
static LGFX_Sprite canvas(&lcd);

M5TextScroll::M5TextScroll(int32_t x, int32_t y, uint8_t scroll_pixel) {
    _x = x;
    _y = y;
    _bg_color = lcd.color888(0, 0, 0);
    _text_color = lcd.color888(255, 255, 255);
    _scroll_pixel = scroll_pixel;
    _text_pos = 0;
    scroll_count = 0;
}

void M5TextScroll::setBgColor(uint32_t color) { _bg_color = color; }
void M5TextScroll::setTextColor(uint32_t color) { _text_color = color; }

void M5TextScroll::setText(const char *text) {
    canvas.setTextWrap(false);
    canvas.setFont(&fonts::lgfxJapanGothic_40);
    size_t text_size = 40;
    scroll_count = 0;
    canvas.createSprite(lcd.width() + text_size, text_size);
    canvas.clear();
    strncpy(_text, text, 255);
    _text_len = sizeof(_text) / sizeof(_text[0]);
    _text_pos = 0;
    cursor_x = lcd.width();
}

void M5TextScroll::showTextScroll() {
    canvas.setTextColor(_text_color, _bg_color);
    cursor_x = canvas.getCursorX() - 1;
    if (cursor_x <= 0) {
        _text_pos = 0;
        cursor_x = lcd.width();
        scroll_count++;
    }

    canvas.setCursor(cursor_x, 0);
    canvas.scroll(-_scroll_pixel, 0);
    while (_text_pos < _text_len && cursor_x <= lcd.width()) {
        canvas.print(_text[_text_pos++]);
        cursor_x = canvas.getCursorX();
    }

    canvas.pushSprite(&lcd, _x, _y);
}

uint8_t M5TextScroll::getScrollCount() { return scroll_count; }