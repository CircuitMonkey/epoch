/**
 * Mode 2 - Dual Haptic Element Pair
 * 
 * Four Vibrators (Left - Right):A, (Left - Right):B  Connector A, Channel 1-4
 */

// Mode 2. Dual Haptic Element Pair
// Mode 2 functions: 0:Back to Main menu,  1:Sliders, 2:Cycle, 3:Wave, 4:Pulse
uint8_t mode_2_function = 0;

Slider m_2_1_slider[4] = {
  Slider(" 1", SLIDER_4_X1, 5, 63),
  Slider(" 2", SLIDER_4_X2, 9, 63),
  Slider(" 3", SLIDER_4_X3, 14, 63),
  Slider(" 4", SLIDER_4_X4, 18, 63)
};

// back button is at index 0.
const unsigned char *m_2_0_glyphs_bg[9] = { glyph48m_back, glyph48m_slide_bg, glyph48m_cycle, glyph48m_wave, glyph48m_pulse, glyph48m_blank, glyph48m_blank, glyph48m_blank, glyph48m_blank };
const unsigned char *m_2_0_glyphs_fg[9] = { glyph48m_back, glyph48m_slide_fg, glyph48m_cycle, glyph48m_wave, glyph48m_pulse, glyph48m_blank, glyph48m_blank, glyph48m_blank, glyph48m_blank };

void mode_2_0_start() {
  ui.setStyleDisc(" DUAL RING ", "M O D E 2", glyph48m_vibe_8, glyph48m_vibe_2, m_2_0_glyphs_bg, m_2_0_glyphs_fg);

  // TODO: Set based on UI pause mode.
  vibes.pause(true);
}

void mode_2_1_start() {
  ui.setStyleSlide4("SLIDERS", glyph48m_slide_bg, glyph48m_slide_fg);

  for (int i = 0; i < 4; i++) {
    m_2_1_slider[i].begin(&tft);
    vibes.set(i, m_2_1_slider[i].getVal());
  }
  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

void mode_2_loop() {
  if (istouched) {
    if (!wastouched) {  // New touch
      pDragStart.x = p.x;
      pDragStart.y = p.y;
      switch (mode_2_function) {                      // Handle menu
        case 0:                                       // Mode 0 top menu
          mode_2_0_handle_btn(ui.getItemPressed(p));  // will change the mode or function.
          break;
        case 1:  // mode 0 - init handle sliders or back btn
          mode_2_1_handle_touch(ui.getItemPressed(p));
          break;
      }
      wastouched = istouched;
    } else {  // Dragging or still touching
      switch (mode_2_function) {
        case 1:  // drag slider if selected.
          mode_2_1_handle_slide();
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
void mode_2_0_handle_btn(uint8_t btn) {
  switch (btn) {
    case 0:  // Back to Mode 0
      guiMode = 0;
      mode_2_function = 0;  // tidy our value.
      mode_0_function = 0;
      mode_0_start();
      break;
    case 1:  // Function 1: Sliders
      guiMode = 2; // back to mode_2_0
      mode_2_function = 1;
      mode_2_1_start();
      break;
    case 2:  // Function 2: Cycle
      break;
    default:  // Not a touch. Do nothing.
      break;
  }
}

void mode_2_1_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_2_1_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_2_1_slider[idx].setVal(nv);
      m_2_1_slider[idx].update();
      vibes.set(idx, m_2_1_slider[idx].getVal());
      vibes.pack();
    }
  }
}

void mode_2_1_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_2_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_2_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_2_1_slider[btn-1].getVal();
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