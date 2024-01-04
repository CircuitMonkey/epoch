#include "slider.h"

const float Slider::SLIDER_SCALE = SLIDER_H / 255.0;  // FLoating point must be post-compile computed.

Slider::Slider() {}

bool Slider::begin(Adafruit_ILI9341 *tft, String title, uint16_t x, uint8_t val) {
  _tft = tft;
  _title = title;
  _x = x;
  _value = val;
  _disabled = false;

  blank();
  _tft->setTextColor(SLIDER_GLOW);
  _tft->setCursor(_x - SLIDER_4_W / 2 + 2, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - SLIDER_TITLE_H / 2 - 2);
  _tft->setTextSize(2);
  _tft->println(_title);

  update();

  return 1;
}

/**
 * clear area and draw frame only
 */
void Slider::blank() {
  _tft->fillRoundRect(_x - SLIDER_4_W / 2, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - 2, SLIDER_4_W, SLIDER_H + SLIDER_BTN_H + 4, SLIDER_BTN_H / 3, ILI9341_BLACK);
  if (_disabled) {
    _tft->drawRoundRect(_x - SLIDER_4_W / 2, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - 2, SLIDER_4_W, SLIDER_H + SLIDER_BTN_H + 4, SLIDER_BTN_H / 3, SLIDER_DIM);
  } else {
    _tft->drawRoundRect(_x - SLIDER_4_W / 2, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - 2, SLIDER_4_W, SLIDER_H + SLIDER_BTN_H + 4, SLIDER_BTN_H / 3, SLIDER_LIT);
  }
}

/**
 * draw or update slider
 */
void Slider::update() {

  // blank value area
  _tft->fillRect(_x - SLIDER_4_W / 2, SLIDER_Y + SLIDER_H / 2 + SLIDER_BTN_H / 2 + 2, SLIDER_4_W, SLIDER_VALUE_H, ILI9341_BLACK);

  if (!_disabled) {
    // clear the slider area
    _tft->fillRoundRect(_x - SLIDER_4_W / 2 + 1, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - 1, SLIDER_4_W - 2, SLIDER_H + SLIDER_BTN_H + 2, SLIDER_BTN_H / 3, SLIDER_DIM);

    // draw value
    _tft->setTextColor(ILI9341_DARKGREY);
    _tft->setCursor(_x - SLIDER_4_W / 2 + 2, SLIDER_Y + SLIDER_H / 2 + SLIDER_BTN_H / 2 + 4);
    _tft->setTextSize(2);
    _tft->println(_value);

    uint16_t y = (uint16_t)(SLIDER_Y + SLIDER_H / 2 - (float)(SLIDER_SCALE * _value));
    // draw the slider knob
    _tft->fillRoundRect(_x - SLIDER_4_W / 2 + 2, y - SLIDER_BTN_H / 2 + 1, SLIDER_4_W - 4, SLIDER_BTN_H - 1, SLIDER_BTN_H / 3, SLIDER_GLOW);
  } else {
    _tft->fillRoundRect(_x - SLIDER_4_W / 2 + 1, SLIDER_Y - SLIDER_H / 2 - SLIDER_BTN_H / 2 - 1, SLIDER_4_W - 2, SLIDER_H + SLIDER_BTN_H + 2, SLIDER_BTN_H / 3, SLIDER_DSBL);
  }
}

void Slider::setDisabled(boolean disabled) {
  _disabled = disabled;
  blank();
  update();
}

/**
 * get slider value
 *
 * return uint8 with range 0-255
 */
uint8_t Slider::getVal() {
  return _value;
}

/**
 * set slider value
 *
 * acceptable range 0-255. Out of range will be clamped.
 */
void Slider::setVal(int16_t v) {
  // TODO: Range checking  0-255
  if (v < 0) v = 0;
  if (v > 255) v = 255;
  _value = v;
}

/**
 * set title.  
 * 
 * 1-3 characters only.
 */
void Slider::setTitle(String t) {
  // TODO: length checking  1 or 3 chars only.
  _title = t;
}