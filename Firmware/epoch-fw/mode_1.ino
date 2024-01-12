/**
 * Mode 1 - Single Haptic Element Pair
 * 
 * Two Vibrators (Left - Right) Connector A, Channel 1-2
 */

// Mode 1. Single Haptic Element Pair
// Mode 1 functions: 0:Main menu,  1:Sliders, 2:Cycle, 3:Wave, 4:Pulse
uint8_t mode_1_function = 0;

Slider m_1_1_slider[4] = {  // slider func
  Slider(" 1", SLIDER_4_X1, 5, 63),
  Slider(" 2", SLIDER_4_X2, 9, 63),
  Slider(" 3", SLIDER_4_X3, 0, 63),
  Slider(" 4", SLIDER_4_X4, 0, 63)
};
Slider m_1_2_slider[4] = {  // cycle func
  Slider("INT", SLIDER_4_X1, 12, 63),
  Slider("SPD", SLIDER_4_X2, 25, 63),
  Slider("   ", SLIDER_4_X3, 0, 63),
  Slider("   ", SLIDER_4_X4, 0, 63)
};

float mode_1_2_cycle = 0.0; // in Radians 0 - 6.283
#define MODE_1_2_CYC_MAX 10.0f
#define MODE_1_2_CYC_MIN 0.4f

// back button is at index 0.
const unsigned char *m_1_0_glyphs_bg[9] = { glyph48m_back, glyph48m_slide_bg, glyph48m_cycle, glyph48m_wave, glyph48m_pulse, glyph48m_blank, glyph48m_blank, glyph48m_blank, glyph48m_blank };
const unsigned char *m_1_0_glyphs_fg[9] = { glyph48m_back, glyph48m_slide_fg, glyph48m_cycle, glyph48m_wave, glyph48m_pulse, glyph48m_blank, glyph48m_blank, glyph48m_blank, glyph48m_blank };

/**
 * Update Motors - Called every tick (100mS)
 */
void mode_1_updateMotors() {
  switch( mode_1_function ) {
    // Other cases handled during drag.
    case 2:

      // advance tick angle based on speed slider
      // advanceRads = (cycSecsMax - cycSecsMin)/(slMax-1) * ( slVal - 1 ) / 10.0(ticks in a second)
      float adv;
      if ( m_1_2_slider[1].getVal() > 0 ) {
        adv = ((MODE_1_2_CYC_MAX-MODE_1_2_CYC_MIN)/(m_1_2_slider[1].getMax()-1.0) * (m_1_2_slider[1].getVal() -1.0));
        adv /= 10.0;
      } else {
        adv = 0.0;
      }

      mode_1_2_cycle += adv;
      if ( mode_1_2_cycle > VIB_PI*2.0 ) {
        mode_1_2_cycle = 0.0;
      }
      // calc new motor values
      // vibeVal = (sin(advanceRads) + 1) * vibMax/2
      float wav0 = sin(mode_1_2_cycle);
      float wav1 = sin(mode_1_2_cycle + VIB_PI); // 180deg phase.
      float mot0 = (wav0 + 1.0f) / 2.0f * m_1_2_slider[0].getVal();
      float mot1 = (wav1 + 1.0f) / 2.0f * m_1_2_slider[0].getVal();
      //Serial.printf("int:%d,spd:%d,cyc:%0.3f,adv:%0.3f,mot0:%0.3f,mot1:%0.3f\n", m_1_2_slider[0].getVal(), m_1_2_slider[1].getVal(), mode_1_2_cycle, adv, mot0, mot1);
      vibes.set(0, mot0);
      vibes.set(1, mot1);
      vibes.pack();
      break;
  }
  vibes.update();
}
void mode_1_0_start() {
  ui.setStyleDisc("O N E   R I N G", "M O D E 1", glyph48m_vibe_8, glyph48m_vibe_1, m_1_0_glyphs_bg, m_1_0_glyphs_fg);

  // TODO: Set based on UI pause mode.
  vibes.pause(true);
}

void mode_1_1_start() {
  ui.setStyleSlide4("SLIDERS", glyph48m_slide_bg, glyph48m_slide_fg);

  for (int i = 0; i < 4; i++) {
    m_1_1_slider[i].begin(&tft);
    vibes.set(i, m_1_1_slider[i].getVal());
  }
  m_1_1_slider[2].setDisabled(true);
  m_1_1_slider[3].setDisabled(true);

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * cycle functions
 */
void mode_1_2_start() {
  ui.setStyleSlide4("CYCLE", glyph48m_cycle, NULL);

  for (int i = 0; i < 4; i++) {
    m_1_2_slider[i].begin(&tft);
    vibes.set(i, m_1_2_slider[i].getVal());
  }
  m_1_2_slider[2].setDisabled(true);
  m_1_2_slider[3].setDisabled(true);

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * UI Loop - Called as fast as needed.
 */
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
        case 2:  // mode 0 - init handle sliders or back btn
          mode_1_2_handle_touch(ui.getItemPressed(p));
          break;
      }
      wastouched = istouched;
    } else {  // Dragging or still touching
      switch (mode_1_function) {
        case 1:  // sliders. drag slider if selected.
          mode_1_1_handle_slide();
          break;
        case 2:  // cycle. drag slider if selected.
          mode_1_2_handle_slide();
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
      guiMode = 0; // mode_0.ino
      mode_1_function = 0;  // tidy our value.
      mode_0_function = 0;
      mode_0_start();
      break;
    case 1:  // Function 1: Sliders
      guiMode = 1;  // mode_1.ino
      mode_1_function = 1; // mode_1_1 : sliders
      mode_1_1_start();
      break;
    case 2:  // Function 2: Cycle
      guiMode = 1;  // mode_1.ino
      mode_1_function = 2; // mode_1_2 : cycle
      mode_1_2_start();
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
      uint8_t idx = btn - 1;
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
      case 2:
      //case 3:  // disabled
      //case 4:  // disabled
        slideDragStart = m_1_1_slider[btn-1].getVal();
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

void mode_1_2_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_1_2_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_1_2_slider[idx].setVal(nv);
      m_1_2_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}
void mode_1_2_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_1_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_1_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      //case 3:  // disabled
      //case 4:  // disabled
        slideDragStart = m_1_2_slider[btn-1].getVal();
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

