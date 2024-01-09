/**
 * Mode 1 - Single Haptic Element Pair
 * 
 * Two Vibrators (Left - Right) Connector A, Channel 1-2
 */

// Mode 1. Single Haptic Element Pair
// Mode 1 functions: 0:Main menu,  1:Sliders, 2:Cycle, 3:Wave, 4:Pulse
uint8_t mode_1_function = 0;

Slider slider1 = Slider();
Slider slider2 = Slider();
Slider slider3 = Slider();
Slider slider4 = Slider();
uint8_t mode_1_1_vibeVals[4] = { 5, 9, 14, 18 };

void mode_1_0_start() {

  // TODO: Glyph
  vibes.pause(true);
  ui.setStyle(UI_STYLE_DISC);
  ui.blank();

  ui.setTopText("  O N E   R I N G");  // 17 chars
  ui.drawTopTxt(0);

  ui.setBotText("M O D E 1");  // 9 chars
  ui.drawBotTxt();

  ui.drawDiscBase();

  ui.drawDiscGlyph(1, glyph48m_slide_bg, glyph48m_slide_fg);
  ui.drawDiscGlyph(2, glyph48m_cycle, glyph48m_cycle);
  ui.drawDiscGlyph(3, glyph48m_wave, glyph48m_wave);
  ui.drawDiscGlyph(4, glyph48m_pulse, glyph48m_pulse);
  ui.drawDiscGlyph(5, glyph48m_blank, glyph48m_blank);
  ui.drawDiscGlyph(6, glyph48m_blank, glyph48m_blank);
  ui.drawDiscGlyph(7, glyph48m_blank, glyph48m_blank);
  ui.drawDiscGlyph(8, glyph48m_blank, glyph48m_blank);

  ui.setBackBtn(UI_BAK_CENTER);
}

void mode_1_1_start() {
  ui.setStyle(UI_STYLE_SLIDE_4);
  ui.blank();
  ui.drawTopGlyph(glyph48m_slide_bg, glyph48m_slide_fg);

  ui.setTopText("SLIDERS");  // 17 chars
  ui.drawTopTxt(UI_GL_W + 12);

  slider1.begin(&tft, " 1", SLIDER_4_X1, mode_1_1_vibeVals[0], 63);
  slider2.begin(&tft, " 2", SLIDER_4_X2, mode_1_1_vibeVals[1], 63);
  slider3.begin(&tft, " 3", SLIDER_4_X3, mode_1_1_vibeVals[2], 63);
  slider4.begin(&tft, " 4", SLIDER_4_X4, mode_1_1_vibeVals[3], 63);
  vibes.set(0, mode_1_1_vibeVals[0]);
  vibes.set(1, mode_1_1_vibeVals[1]);
  vibes.set(2, mode_1_1_vibeVals[2]);
  vibes.set(3, mode_1_1_vibeVals[3]);
  vibes.pack();
  vibes.pause(true);

  //slider3.setDisabled(true);
  //slider4.setDisabled(true);

  ui.setBackBtn(UI_BAK_TR);
  ui.setPlayMode(UI_MODE_PAUSE);  // test pause/play glyph
  ui.drawPausePlay();            // Pause button
}

void mode_1_loop() {
  if (istouched) {
    if (!wastouched) {  // New touch
      pDragStart.x = p.x;
      pDragStart.y = p.y;
      switch (mode_1_function) {                      // Handle menu
        case 0:                                       // Mode 0 top menu
          mode_1_0_handle_btn(ui.getItemPressed(p));  // will change the mode or function.
          break;
        case 1:  // mode 0 - init handle sliders or back btn
          mode_1_1_handle_touch(ui.getItemPressed(p));
          break;
      }
      wastouched = istouched;
    } else {  // Dragging or still touching
      switch (mode_1_function) {
        case 1:  // drag slider if selected.
          mode_1_1_handle_slide();
          break;
          // default: // do nothing.
      }
    }
  } else {  // end of istouched
    wastouched = 0;
    lastBtn = 99;
  }
}

/**
 * change to the selected function or mode.
 */
void mode_1_0_handle_btn(uint8_t btn) {
  switch (btn) {
    case 0:  // Back to Mode 0
      guiMode = 0;
      mode_1_function = 0;  // tidy our value.
      mode_0_function = 0;
      mode_0_start();
      break;
    case 1:  // Function 1: Sliders
      guiMode = 1;
      mode_1_function = 1;
      mode_1_1_start();
      break;
    case 2:  // Function 2: Cycle
      break;
    default:  // Not a touch. Do nothing.
      break;
  }
}

void mode_1_1_handle_slide() {
  //TS_Point pL = p2lcd
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.

    switch (btn) {
      case 1:
        {
          float vD = (float)(pDragStart.y - p.y) / slider1.getScale();
          uint16_t nv = slideDragStart + vD;
          slider1.setVal(nv);
          slider1.update();
          mode_1_1_vibeVals[0] = slider1.getVal();
          vibes.set(0, mode_1_1_vibeVals[0]);
          vibes.pack();
        }
        break;
      case 2:
        {
          float vD = (float)(pDragStart.y - p.y) / slider2.getScale();
          uint16_t nv = slideDragStart + vD;
          slider2.setVal(nv);
          slider2.update();
          mode_1_1_vibeVals[1] = slider2.getVal();
          vibes.set(1, mode_1_1_vibeVals[1]);
          vibes.pack();
        }
        break;
      case 3:
        {
          float vD = (float)(pDragStart.y - p.y) / slider3.getScale();
          uint16_t nv = slideDragStart + vD;
          slider3.setVal(nv);
          slider3.update();
          mode_1_1_vibeVals[2] = slider3.getVal();
          vibes.set(2, mode_1_1_vibeVals[2]);
          vibes.pack();
        }
        break;
      case 4:
        {
          float vD = (float)(pDragStart.y - p.y) / slider4.getScale();
          uint16_t nv = slideDragStart + vD;
          slider4.setVal(nv);
          slider4.update();
          mode_1_1_vibeVals[3] = slider4.getVal();
          vibes.set(3, mode_1_1_vibeVals[3]);
          vibes.pack();
        }
        break;
    }
  }
}

void mode_1_1_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_1_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_1_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
        slideDragStart = slider1.getVal();
        break;
      case 2:
        slideDragStart = slider2.getVal();
        break;
      case 3:
        slideDragStart = slider3.getVal();
        break;
      case 4:
        slideDragStart = slider4.getVal();
        break;
      case UI_BTN_PAUSE:
        switch (ui.getPlayMode()) {
          case UI_MODE_PLAY:
            ui.setPlayMode(UI_MODE_PAUSE);
            vibes.pause(true);
            break;
          case UI_MODE_PAUSE:
            ui.setPlayMode(UI_MODE_PLAY);
            vibes.pause(false);
            break;
        }
        ui.drawPausePlay();
        delay(14);
        break;
    }
  }
}