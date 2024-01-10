/*
 * Graphics UI Utils
 *
 */
#include "ui.h"

Ui::Ui() {}

bool Ui::begin(Adafruit_ILI9341 *tft, const unsigned char *backGlyph, const unsigned char *pauseGlyph, const unsigned char *playGlyph) {
  _tft = tft;
  _backGlyph = backGlyph;
  _pauseGlyph = pauseGlyph;
  _playGlyph = playGlyph;
  _backBtn = 0;
  _style = 1;     // style of UI. 1=Disc, 2=sliders-4x, 3=sliders-8x
  _playMode = 0;  // running

  return 1;
}

void Ui::blank() {
  //_tft->fillRect(0, 0, 240, 320, ILI9341_BLACK);
  _tft->fillScreen(ILI9341_BLACK);

  if (_backBtn > 0) {
    switch (_style) {
      case 1:
        _tft->drawBitmap(UI_CX - UI_GL_W / 2, UI_CY - UI_GL_H / 2, _backGlyph, UI_GL_W, UI_GL_H, BTN_LIT);
        break;
      case 2:
      case 3:
        _tft->drawRoundRect(UI_SCR_W - UI_GL_W - 8, 0, UI_GL_W + 8, UI_GL_H + 12, 8, BTN_LIT);
        _tft->drawBitmap(UI_SCR_W - UI_GL_W - 2, 4, _backGlyph, UI_GL_W, UI_GL_H, BTN_LIT);
        break;
    }
  }
}

void Ui::drawDiscBase() {
  uint16_t p45 = (uint16_t)(UI_R * 0.71f);

  _tft->fillCircle(UI_CX, UI_CY, UI_R, 0x30e3);
  _tft->drawLine(UI_CX - p45, UI_CY - p45, UI_CX + p45, UI_CY + p45, ILI9341_BLACK);
  _tft->drawLine(UI_CX + p45, UI_CY - p45, UI_CX - p45, UI_CY + p45, ILI9341_BLACK);
  _tft->drawLine(UI_CX - UI_R, UI_CY, UI_CX + UI_R, UI_CY, ILI9341_BLACK);
  _tft->drawLine(UI_CX, UI_CY - UI_R, UI_CX, UI_CY + UI_R, ILI9341_BLACK);
  _tft->fillCircle(UI_CX, UI_CY, UI_R * 0.40, ILI9341_BLACK);
}

void Ui::drawDiscTouch() {
  _tft->setTextSize(1);
  _tft->setTextColor(ILI9341_RED);
  switch (_backBtn) {
    case 1:
      _tft->drawCircle(UI_CX, UI_CY, UI_B_SZ, ILI9341_RED);
      _tft->setCursor(UI_CX + 4, UI_CY + 4);
      _tft->print("0");
      break;
    case 2:
      _tft->drawCircle(UI_CX - UI_B_SZ, UI_B_SZ, UI_B_SZ, ILI9341_RED);
      _tft->setCursor(UI_CX - UI_B_SZ, UI_B_SZ);
      _tft->print("0");
      break;
  }
  _tft->drawCircle(UI_CX, UI_CY, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_CX + 4, UI_CY + 4);
  _tft->print("0");
  _tft->drawCircle(UI_B1_X, UI_B1_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B1_X + 4, UI_B1_Y + 4);
  _tft->print("1");
  _tft->drawCircle(UI_B2_X, UI_B2_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B2_X + 4, UI_B2_Y + 4);
  _tft->print("2");
  _tft->drawCircle(UI_B3_X, UI_B3_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B3_X + 4, UI_B3_Y + 4);
  _tft->print("3");
  _tft->drawCircle(UI_B4_X, UI_B4_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B4_X + 4, UI_B4_Y + 4);
  _tft->print("4");
  _tft->drawCircle(UI_B5_X, UI_B5_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B5_X + 4, UI_B5_Y + 4);
  _tft->print("5");
  _tft->drawCircle(UI_B6_X, UI_B6_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B6_X + 4, UI_B6_Y + 4);
  _tft->print("6");
  _tft->drawCircle(UI_B7_X, UI_B7_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B7_X + 4, UI_B7_Y + 4);
  _tft->print("7");
  _tft->drawCircle(UI_B8_X, UI_B8_Y, UI_B_SZ, ILI9341_RED);
  _tft->setCursor(UI_B8_X + 4, UI_B8_Y + 4);
  _tft->print("8");
}

uint8_t Ui::getItemPressed(TS_Point p) {
  switch (_style) {
    case UI_STYLE_DISC: return _discItemPressed(p);
    case UI_STYLE_SLIDE_4: return _slide4Pressed(p);
    case UI_STYLE_SLIDE_8: return _slide8Pressed(p);
  }
  return UI_BUTTON_NONE;  // User pressed negative space.
}

uint8_t Ui::_discItemPressed(TS_Point p) {
  uint16_t bSz = UI_B_SZ;
  if (_exitPressed(p)) { return UI_BTN_EXIT; }
  // if (_backBtn == UI_BAK_CENTER && p.x > UI_CX - bSz && p.x < UI_SCR_W && p.y > 0 && p.y < 2 * bSz  // center of screen
  // ) { return 0; }
  // if (_backBtn == UI_BAK_TR && p.x > UI_SCR_W - 2 * bSz && p.x < UI_CX + bSz && p.y > UI_CY - bSz && p.y < UI_CY + bSz  // top right
  // ) { return 0; }
  if (p.x > UI_B1_X - bSz && p.x < UI_B1_X + bSz && p.y > UI_B1_Y - bSz && p.y < UI_B1_Y + bSz) { return 1; }
  if (p.x > UI_B2_X - bSz && p.x < UI_B2_X + bSz && p.y > UI_B2_Y - bSz && p.y < UI_B2_Y + bSz) { return 2; }
  if (p.x > UI_B3_X - bSz && p.x < UI_B3_X + bSz && p.y > UI_B3_Y - bSz && p.y < UI_B3_Y + bSz) { return 3; }
  if (p.x > UI_B4_X - bSz && p.x < UI_B4_X + bSz && p.y > UI_B4_Y - bSz && p.y < UI_B4_Y + bSz) { return 4; }
  if (p.x > UI_B5_X - bSz && p.x < UI_B5_X + bSz && p.y > UI_B5_Y - bSz && p.y < UI_B5_Y + bSz) { return 5; }
  if (p.x > UI_B6_X - bSz && p.x < UI_B6_X + bSz && p.y > UI_B6_Y - bSz && p.y < UI_B6_Y + bSz) { return 6; }
  if (p.x > UI_B7_X - bSz && p.x < UI_B7_X + bSz && p.y > UI_B7_Y - bSz && p.y < UI_B7_Y + bSz) { return 7; }
  if (p.x > UI_B8_X - bSz && p.x < UI_B8_X + bSz && p.y > UI_B8_Y - bSz && p.y < UI_B8_Y + bSz) { return 8; }
  return UI_BUTTON_NONE;
}

uint8_t Ui::_slide4Pressed(TS_Point p) {
  // Check for exit
  if (_exitPressed(p)) { return UI_BTN_EXIT; }
  if (_pausePressed(p)) { return UI_BTN_PAUSE; }

  // or report if button pressed.
  if (p.x > UI_S4_X1 - UI_S4_W / 2 && p.x < UI_S4_X1 + UI_S4_W / 2 && p.y > UI_S4_Y - UI_S4_H / 2 && p.y < UI_S4_Y + UI_S4_H / 2) { return 1; }
  if (p.x > UI_S4_X2 - UI_S4_W / 2 && p.x < UI_S4_X2 + UI_S4_W / 2 && p.y > UI_S4_Y - UI_S4_H / 2 && p.y < UI_S4_Y + UI_S4_H / 2) { return 2; }
  if (p.x > UI_S4_X3 - UI_S4_W / 2 && p.x < UI_S4_X3 + UI_S4_W / 2 && p.y > UI_S4_Y - UI_S4_H / 2 && p.y < UI_S4_Y + UI_S4_H / 2) { return 3; }
  if (p.x > UI_S4_X4 - UI_S4_W / 2 && p.x < UI_S4_X4 + UI_S4_W / 2 && p.y > UI_S4_Y - UI_S4_H / 2 && p.y < UI_S4_Y + UI_S4_H / 2) { return 4; }

  return UI_BUTTON_NONE;
}

uint8_t Ui::_slide8Pressed(TS_Point p) {
  // Check for exit
  if (_exitPressed(p)) { return UI_BTN_EXIT; }
  // or report if button pressed.
  return UI_BUTTON_NONE;
}

boolean Ui::_exitPressed(TS_Point p) {
  uint16_t bSz = UI_B_SZ;
  if (_backBtn == UI_BAK_CENTER && p.x > UI_CX - bSz && p.x < UI_CX + bSz && p.y > UI_CY - bSz && p.y < UI_CY + bSz  // center of screen
  ) { return true; }
  if (_backBtn == UI_BAK_TR && p.x > UI_SCR_W - 2 - bSz && p.x < UI_SCR_W && p.y > 0 && p.y < bSz  // top right
  ) { return true; }
  return false;
}

boolean Ui::_pausePressed(TS_Point p) {
  if (p.x > 0 && p.x < UI_SCR_W && p.y > (UI_SCR_H - UI_PAUSE_H - 4) && p.y < UI_SCR_H  // bottom of screen
  ) { return true; }
  return false;
}

void Ui::drawTopGlyph(const unsigned char *g1, const unsigned char *g2) {
  if (g1 != NULL) {
    _tft->drawBitmap(4, 8, g1, UI_GL_W, UI_GL_H, BTN_GREY);
  }
  if (g2 != NULL) {
    _tft->drawBitmap(4, 8, g2, UI_GL_W, UI_GL_H, BTN_LIT);
  }
}

void Ui::drawDiscGlyph(uint16_t n, const unsigned char *g1, const unsigned char *g2) {
  uint16_t x = 0;
  uint16_t y = 0;
  switch (n) {
    case 1:
      x = UI_B1_X;
      y = UI_B1_Y;
      break;
    case 2:
      x = UI_B2_X;
      y = UI_B2_Y;
      break;
    case 3:
      x = UI_B3_X;
      y = UI_B3_Y;
      break;
    case 4:
      x = UI_B4_X;
      y = UI_B4_Y;
      break;
    case 5:
      x = UI_B5_X;
      y = UI_B5_Y;
      break;
    case 6:
      x = UI_B6_X;
      y = UI_B6_Y;
      break;
    case 7:
      x = UI_B7_X;
      y = UI_B7_Y;
      break;
    case 8:
      x = UI_B8_X;
      y = UI_B8_Y;
      break;
  }
  _tft->drawBitmap(x - UI_B_SZ, y - UI_GL_H / 2, g1, UI_GL_W, UI_GL_H, BTN_GREY);
  _tft->drawBitmap(x - UI_B_SZ, y - UI_GL_H / 2, g2, UI_GL_W, UI_GL_H, BTN_LIT);
}

void Ui::drawTopTxt(uint8_t indent) {
  _tft->setTextColor(ILI9341_DARKGREY);
  _tft->setCursor(indent, 8);
  _tft->setTextSize(2);
  _tft->println(_topTxt);
}

void Ui::drawBotTxt() {
  _tft->setTextColor(ILI9341_DARKGREY);
  _tft->setCursor(14, 290);
  _tft->setTextSize(4);
  _tft->println(_botTxt);
}

void Ui::drawSlider(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
  _tft->drawRect(x - w / 2, y - h / 2, w, h, BTN_LIT);
}

void Ui::drawPausePlay() {
  _tft->fillRoundRect(2, UI_SCR_H - UI_PAUSE_H - 2, UI_SCR_W - 4, UI_PAUSE_H, UI_PAUSE_H / 4, ILI9341_BLACK);
  switch (_playMode) {
    case UI_MODE_PLAY:  // running, show pause glyph
      _tft->fillRoundRect(2, UI_SCR_H - UI_PAUSE_H - 2, UI_SCR_W - 4, UI_PAUSE_H, UI_PAUSE_H / 4, UI_PAUSE_RED);
      _tft->drawBitmap(UI_SCR_W / 2 - UI_GL_W / 2, UI_SCR_H - UI_PAUSE_H / 2 - UI_GL_H / 2 - 2, _pauseGlyph, UI_GL_W, UI_GL_H, ILI9341_DARKGREY);
      break;
    case UI_MODE_PAUSE:  // paused, show play gylph
      _tft->fillRoundRect(2, UI_SCR_H - UI_PAUSE_H - 2, UI_SCR_W - 4, UI_PAUSE_H, UI_PAUSE_H / 4, UI_PLAY_GREEN);
      _tft->drawBitmap(UI_SCR_W / 2 - UI_GL_W / 2, UI_SCR_H - UI_PAUSE_H / 2 - UI_GL_H / 2 - 2, _playGlyph, UI_GL_W, UI_GL_H, ILI9341_DARKGREY);
      break;
  }
  _tft->drawRoundRect(2, UI_SCR_H - UI_PAUSE_H - 2, UI_SCR_W - 4, UI_PAUSE_H, UI_PAUSE_H / 4, BTN_LIT);
}

void Ui::setTopText(String t) {
  _topTxt = t;
}
void Ui::setBotText(String t) {
  _botTxt = t;
}

void Ui::setBackBtn(uint8_t loc) {
  _backBtn = loc;
}
void Ui::setStyle(uint8_t style) {
  _style = style;
}

void Ui::setStyleSlide4(String title, const unsigned char *bg, const unsigned char *fg) {
  setStyle(UI_STYLE_SLIDE_4);
  blank();
  drawTopGlyph(bg, fg);

  setTopText(title);     // 17 chars
  drawTopTxt(UI_GL_W + 12);  // offset text to right of glyph.

  setBackBtn(UI_BAK_TR);

  // always start paused.
  setPlayMode(UI_MODE_PAUSE);  // test pause/play glyph
  drawPausePlay();             // Pause button
}


void Ui::setPlayMode(uint8_t mode) {
  _playMode = mode;
}

uint8_t Ui::getPlayMode() {
  return _playMode;
}