/**
 * Mode 1 - Single Haptic Element Pair
 * 
 * Two Vibrators (Left - Right) Connector A, Channel 1-2
 */

// Mode 1. Single Haptic Element Pair
// Mode 1 functions: 0:Main menu,  1:Sliders, 2:Cycle, 3:Wave, 4:Pulse
uint8_t mode_1_function = 0;

Slider m_1_1_slider[4] = {
  Slider(" 1", SLIDER_4_X1, 5, 63),
  Slider(" 2", SLIDER_4_X2, 9, 63),
  Slider(" 3", SLIDER_4_X3, 14, 63),
  Slider(" 4", SLIDER_4_X4, 18, 63)
};

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
  ui.setStyleSlide4("SLIDERS", glyph48m_slide_bg, glyph48m_slide_fg);

  for (int i = 0; i < 4; i++) {
    m_1_1_slider[i].begin(&tft);
    vibes.set(i, m_1_1_slider[i].getVal());
  }
  //m_1_1_slider[2].setDisabled(true);
  //m_1_1_slider[3].setDisabled(true);

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
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
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn-1;
      float vDrag = (float)(pDragStart.y - p.y) / m_1_1_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_1_1_slider[idx].setVal(nv);
      m_1_1_slider[idx].update();
      vibes.set(idx, m_1_1_slider[idx].getVal());
      vibes.pack();
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
        slideDragStart = m_1_1_slider[0].getVal();
        break;
      case 2:
        slideDragStart = m_1_1_slider[1].getVal();
        break;
      case 3:
        slideDragStart = m_1_1_slider[2].getVal();
        break;
      case 4:
        slideDragStart = m_1_1_slider[3].getVal();
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