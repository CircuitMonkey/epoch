#ifndef Slider_h
#define Slider_h
#include <sys/_stdint.h>
#include <sys/_types.h>
#include "XPT2046_Touchscreen.h"
#include "Adafruit_ILI9341.h"

#define SLIDER_DSBL 0x1042
#define SLIDER_DIM 0x1202
#define SLIDER_GLOW 0x85F0
#define SLIDER_LIT ILI9341_GREEN

#define SLIDER_TITLE_H  32
#define SLIDER_VALUE_H  16
#define SLIDER_VAL_MAX 255

#define SLIDER_SCR_W 240
#define SLIDER_SCR_H 320

#define SLIDER_BTN_H 32

#define SLIDER_H SLIDER_SCR_H*0.40
#define SLIDER_Y SLIDER_SCR_H/2

#define SLIDER_4_W SLIDER_SCR_W/6
#define SLIDER_4_X1 SLIDER_4_W*0.75
#define SLIDER_4_X2 SLIDER_4_X1+SLIDER_4_W*1.5
#define SLIDER_4_X3 SLIDER_4_X2+SLIDER_4_W*1.5
#define SLIDER_4_X4 SLIDER_4_X3+SLIDER_4_W*1.5

class Slider {
public:
  Slider( String title, uint16_t x, uint8_t val, uint8_t max ) : _title(title), _x(x), _value(val), _vmax(max) {};
  //static const float SLIDER_SCALE;
  bool begin(Adafruit_ILI9341 *tft);
  //bool begin(Adafruit_ILI9341 *tft, uint16_t x, uint8_t val);
  //bool begin(Adafruit_ILI9341 *tft, uint16_t x, uint8_t val, uint8_t max);
  void blank(); // clear area and draw frame only
  void update(); // draw or update slider
  uint8_t getVal(); // 0-255
  float getScale();
  void setVal(int16_t v); // 0-255
  void setTitle(String t); // 1-3 characters only
  void setDisabled(boolean disabled);
private:
  Adafruit_ILI9341* _tft;
  uint8_t _value;
  uint8_t _vmax;
  uint16_t _x;
  boolean _disabled;
  String _title;
};

#endif