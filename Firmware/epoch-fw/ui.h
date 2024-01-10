#ifndef Ui_h
#define Ui_h
#include "XPT2046_Touchscreen.h"
#include <sys/_types.h>
#include <sys/_stdint.h>
#include "Adafruit_ILI9341.h"
#define BTN_GREY 0x1202
#define BTN_LIT ILI9341_GREEN
#define UI_PLAY_GREEN 0x02E0
#define UI_PAUSE_RED 0x5800

#define UI_SCR_W 240
#define UI_SCR_H 320
#define UI_CX UI_SCR_W/2
#define UI_CY UI_SCR_H/2
#define UI_R 116

#define UI_B1_X 88
#define UI_B1_Y 80
#define UI_B2_X 152
#define UI_B2_Y 80
#define UI_B3_X 200
#define UI_B3_Y 128
#define UI_B4_X 200
#define UI_B4_Y 192
#define UI_B5_X 152
#define UI_B5_Y 240
#define UI_B6_X 88
#define UI_B6_Y 240
#define UI_B7_X 40
#define UI_B7_Y 192
#define UI_B8_X 40
#define UI_B8_Y 128

#define UI_S4_W UI_SCR_W/6
#define UI_S4_H UI_SCR_H/2
#define UI_S4_Y UI_SCR_H/2
#define UI_S4_X1 UI_S4_W*0.75
#define UI_S4_X2 UI_S4_X1+UI_S4_W*1.5
#define UI_S4_X3 UI_S4_X2+UI_S4_W*1.5
#define UI_S4_X4 UI_S4_X3+UI_S4_W*1.5

#define UI_B_SZ 26
#define UI_GL_W 48
#define UI_GL_H 16

#define UI_BAK_NONE 0
#define UI_BAK_CENTER 1
#define UI_BAK_TR 2

#define UI_PAUSE_H 48

#define UI_BTN_EXIT 0
#define UI_BTN_PAUSE 20
#define UI_BUTTON_NONE 99

#define UI_STYLE_DISC 1
#define UI_STYLE_SLIDE_4 2
#define UI_STYLE_SLIDE_8 3
#define UI_STYLE_CUSTOM 4

#define UI_MODE_PLAY 0
#define UI_MODE_PAUSE 1

class Ui {
public:
  Ui();
  bool begin(Adafruit_ILI9341 *tft, const unsigned char *backGlyph, const unsigned char *pauseGlyph, const unsigned char *playGlyph);
  void blank();
  void drawDiscBase();
  void drawDiscTouch();
  void drawDiscGlyph(uint16_t n, const unsigned char *g1, const unsigned char *g2);
  void drawTopGlyph(const unsigned char *g1, const unsigned char *g2);
  void drawSlider( uint16_t x, uint16_t y, uint16_t w, uint16_t h);
  void drawPausePlay();
  void setBackBtn(uint8_t loc); // 0=none, 1=center, 2=top-right
  void setStyle(uint8_t style); // UI_STYLE_*
  void setStyleSlide4(String title, const unsigned char *bg, const unsigned char *fg);
  void setPlayMode( uint8_t mode ); // UI_MODE_*
  uint8_t getPlayMode(); // returns UI_MODE_*
  void drawTopTxt(uint8_t indent);
  void drawBotTxt();
  void setTopText( String t );
  void setBotText( String t );
  uint8_t getItemPressed(TS_Point p );
private:
  Adafruit_ILI9341* _tft;
  String _topTxt;
  String _botTxt;
  uint8_t _backBtn; // UI_BAK_*
  const unsigned char *_backGlyph;
  const unsigned char *_pauseGlyph;
  const unsigned char *_playGlyph;
  uint8_t _style; // UI_STYLE_*   disc, slider-x4, slider-x8, custom
  uint8_t _playMode;
  uint8_t _discItemPressed(TS_Point p);
  uint8_t _slide4Pressed(TS_Point p);
  uint8_t _slide8Pressed(TS_Point p);
  boolean _exitPressed(TS_Point p);
  boolean _pausePressed(TS_Point p);

};
#endif
