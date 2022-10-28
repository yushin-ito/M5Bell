#include <M5StickCPlus.h>

class M5TextScroll {
  public:
    M5TextScroll(int32_t x, int32_t y, uint8_t scroll_pixel);
    void setBgColor(uint32_t color);
    void setTextColor(uint32_t color);
    void setText(const char *text);
    void showTextScroll();
    uint8_t getScrollCount();

  private:
    int32_t _x;
    int32_t _y;
    uint8_t _scroll_pixel;
    uint32_t _bg_color;
    uint32_t _text_color;
    int32_t cursor_x;
    char _text[256];
    size_t _text_len;
    size_t _text_pos;
    uint8_t scroll_count;
};