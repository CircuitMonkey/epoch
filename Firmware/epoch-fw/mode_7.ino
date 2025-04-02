/**
 * Mode 7 - Tripple Haptic Element Pair
 * 
 * Six Vibrators: (Rumble Size x2 on Channel A, current bonded)
 *       (Left - Right):A,                    Connector A, Channel 1+2 and 3+4
 *       (Left - Right):A, (Foward - Back):B  Connector B, Channel 1-4
 */

// Mode 7. Dual Haptic Element Pair
// Mode 7 functions: 0:Back to Main menu,  1:Sliders, 2:Cycle, 3:Pendulum, 4:Plunge, 5:Draw Out
uint8_t mode_7_function = 0;

Slider m_7_1_slider[4] = {
  Slider("TIP", SLIDER_4_X1, 5, 63),
  Slider("MID", SLIDER_4_X2, 9, 63),
  Slider("ANS", SLIDER_4_X3, 14, 63),
  Slider("END", SLIDER_4_X4, 18, 63)
};
Slider m_7_2_slider[4] = {  // cycle func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
Slider m_7_3_slider[4] = {  // pendulum func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
Slider m_7_4_slider[4] = {  // plunge func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 20, 63),
  Slider("BAK", SLIDER_4_X3, 28, 63),
  Slider("SPD", SLIDER_4_X4, 4, 14)
};
Slider m_7_5_slider[4] = {  // draw func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 20, 63),
  Slider("BAK", SLIDER_4_X3, 28, 63),
  Slider("SPD", SLIDER_4_X4, 4, 14)
};
float mode_7_2_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_7_2_CYC_MAX 10.0f
#define MODE_7_2_CYC_MIN 0.4f

float mode_7_3_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_7_3_CYC_MAX 10.0f
#define MODE_7_3_CYC_MIN 0.4f

uint8_t mode_7_4_cycle = 0;  // in ticks 0 - 64
#define MODE_7_4_CYC_MAX 63
//#define MODE_7_4_CYC_MIN 12

float mode_7_5_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_7_5_CYC_MAX 63
#define MODE_7_5_CYC_MIN 8

// back button is at index 0.
const unsigned char *m_7_0_glyphs_bg[9] = { glyph48m_back, glyph48m_slide_bg, glyph48m_cycle, glyph48m_pendulum, glyph48m_plunge, glyph48m_draw, glyph48m_blank, glyph48m_blank, glyph48m_blank };
const unsigned char *m_7_0_glyphs_fg[9] = { glyph48m_back, glyph48m_slide_fg, glyph48m_cycle, glyph48m_pendulum, glyph48m_plunge, glyph48m_draw, glyph48m_blank, glyph48m_blank, glyph48m_blank };

void mode_7_updateMotors() {
  switch (mode_7_function) {
    // Other cases handled during drag.
    case 1:
      mode_7_1_update_motors();
      break;
    case 2:
      mode_7_2_update_motors();
      break;
    case 3:
      mode_7_3_update_motors();
      break;
    case 4:
      mode_7_4_update_motors();
      break;
    case 5:
      mode_7_5_update_motors();
      break;
  }
  vibes.update();
}

void mode_7_0_start() {
  ui.setStyleDisc("  RUMBLE   ", "M O D E 7", glyph48m_vibe_8, glyph48m_vibe_7, m_7_0_glyphs_bg, m_7_0_glyphs_fg);

  // TODO: Set based on UI pause mode.
  vibes.pause(true);
}

void mode_7_1_start() {
  ui.setStyleSlide4("SLIDERS", glyph48m_slide_bg, glyph48m_slide_fg);

  for (int i = 0; i < 4; i++) {
    m_7_1_slider[i].begin(&tft);
    vibes.set(i, m_7_1_slider[i].getVal());
  }
  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * cycle functions
 */
void mode_7_2_start() {
  ui.setStyleSlide4("CYCLE", glyph48m_cycle, NULL);

  for (int i = 0; i < 4; i++) {
    m_7_2_slider[i].begin(&tft);
    vibes.set(i, m_7_2_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * pendulum functions
 */
void mode_7_3_start() {
  ui.setStyleSlide4("PENDULUM", glyph48m_pendulum, NULL);

  for (int i = 0; i < 4; i++) {
    m_7_3_slider[i].begin(&tft);
    vibes.set(i, m_7_3_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * plunge functions
 */
void mode_7_4_start() {
  ui.setStyleSlide4("PLUNGE", glyph48m_plunge, NULL);

  for (int i = 0; i < 4; i++) {
    m_7_4_slider[i].begin(&tft);
    vibes.set(i, m_7_4_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * draw functions
 */
void mode_7_5_start() {
  ui.setStyleSlide4("DRAW", glyph48m_draw, NULL);

  for (int i = 0; i < 4; i++) {
    m_7_5_slider[i].begin(&tft);
    vibes.set(i, m_7_5_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

void mode_7_loop() {
  if (istouched) {
    if (!wastouched) {  // New touch
      pDragStart.x = p.x;
      pDragStart.y = p.y;
      //Serial.printf("Mode 8 touch: %d\n", ui.getItemPressed(p));
      switch (mode_7_function) {                      // Handle menu
        case 0:                                       // Mode 0 top menu
          mode_7_0_handle_btn(ui.getItemPressed(p));  // will change the mode or function.
          break;
        case 1:  // mode 0 - init handle sliders or back btn
          mode_7_1_handle_touch(ui.getItemPressed(p));
          break;
        case 2:  // mode 0 - init handle sliders or back btn
          mode_7_2_handle_touch(ui.getItemPressed(p));
          break;
        case 3:  // mode 0 - init handle sliders or back btn
          mode_7_3_handle_touch(ui.getItemPressed(p));
          break;
        case 4:  // mode 0 - init handle sliders or back btn
          mode_7_4_handle_touch(ui.getItemPressed(p));
          break;
        case 5:  // mode 0 - init handle sliders or back btn
          mode_7_5_handle_touch(ui.getItemPressed(p));
          break;
      }
      wastouched = istouched;
    } else {  // Dragging or still touching
      switch (mode_7_function) {
        case 1:  // drag slider if selected.
          mode_7_1_handle_slide();
          break;
        case 2:  // drag slider if selected.
          mode_7_2_handle_slide();
          break;
        case 3:  // drag slider if selected.
          mode_7_3_handle_slide();
          break;
        case 4:  // drag slider if selected.
          mode_7_4_handle_slide();
          break;
        case 5:  // drag slider if selected.
          mode_7_5_handle_slide();
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
void mode_7_0_handle_btn(uint8_t btn) {
  Serial.printf("Mode 8 btn pressed: %d\n", btn);
  switch (btn) {
    case 0:  // Back to Mode 0
      guiMode = 0;
      mode_7_function = 0;  // tidy our value.
      mode_0_function = 0;
      mode_0_start();
      break;
    case 1:         // Function 1: Sliders
      guiMode = 7;  // back to mode_7_0
      mode_7_function = 1;
      mode_7_1_start();
      break;
    case 2:         // Function 2: Cycle
      guiMode = 7;  // back to mode_7_0
      mode_7_function = 2;
      mode_7_2_start();
      break;
    case 3:         // Function 3: Pendulum
      guiMode = 7;  // back to mode_7_0
      mode_7_function = 3;
      mode_7_3_start();
      break;
    case 4:         // Function 3: Pendulum
      guiMode = 7;  // back to mode_7_0
      mode_7_function = 4;
      mode_7_4_start();
      break;
    case 5:         // Function 3: Pendulum
      guiMode = 7;  // back to mode_7_0
      mode_7_function = 5;
      mode_7_5_start();
      break;
    default:  // Not a touch. Do nothing.
      break;
  }
}

void mode_7_1_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_7_1_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_7_1_slider[idx].setVal(nv);
      m_7_1_slider[idx].update();
      //vibes.set(idx, m_7_1_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_7_1_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_7_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_7_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_7_1_slider[btn - 1].getVal();
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


void mode_7_2_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_7_2_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_7_2_slider[idx].setVal(nv);
      m_7_2_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_7_2_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_7_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_7_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
        //case 3:  // disabled
        //case 4:  // disabled
        slideDragStart = m_7_2_slider[btn - 1].getVal();
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

void mode_7_3_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_7_3_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_7_3_slider[idx].setVal(nv);
      m_7_3_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_7_3_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_7_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_7_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
        //case 3:  // disabled
        //case 4:  // disabled
        slideDragStart = m_7_3_slider[btn - 1].getVal();
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
void mode_7_4_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_7_4_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_7_4_slider[idx].setVal(nv);
      m_7_4_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_7_4_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_7_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_7_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_7_4_slider[btn - 1].getVal();
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


void mode_7_5_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_7_5_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_7_5_slider[idx].setVal(nv);
      m_7_5_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_7_5_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_7_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_7_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_7_5_slider[btn - 1].getVal();
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

void mode_7_1_update_motors() {
  float mot0 = m_7_1_slider[0].getVal(); // tip
  float mot1 = m_7_1_slider[1].getVal(); // mid
  float mot2 = m_7_1_slider[2].getVal(); // anus
  float mot3 = m_7_1_slider[3].getVal(); // end
 
  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot0);
  vibes.set(3, mot0);
  vibes.set(4, mot1);
  vibes.set(5, mot1);
  vibes.set(6, mot2);
  vibes.set(7, mot3);
  vibes.pack();
}

void mode_7_2_update_motors() {
  // advance tick angle based on speed slider
  // advanceRads = (cycSecsMax - cycSecsMin)/(slMax-1) * ( slVal - 1 ) / 10.0(ticks in a second)
  float adv;
  if (m_7_2_slider[3].getVal() > 0) {
    adv = ((MODE_7_2_CYC_MAX - MODE_7_2_CYC_MIN) / (m_7_2_slider[3].getMax() - 1.0) * (m_7_2_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_7_2_cycle += adv;
  if (mode_7_2_cycle > VIB_PI * 2.0) {
    mode_7_2_cycle = 0.0;
  }
  // calc new motor values
  // vibeVal = (sin(advanceRads) + 1) * vibMax/2
  float wav0 = sin(mode_7_2_cycle);
  float wav1 = sin(mode_7_2_cycle + VIB_PI * 0.25);  //  45deg phase.
  float wav2 = sin(mode_7_2_cycle + VIB_PI * 0.50);  //  90deg phase.
  float wav3 = sin(mode_7_2_cycle + VIB_PI * 0.75);  // 135deg phase.
  float wav4 = sin(mode_7_2_cycle + VIB_PI);         // 180deg phase.
  float wav5 = sin(mode_7_2_cycle + VIB_PI * 1.25);  // 225deg phase.
  float wav6 = sin(mode_7_2_cycle + VIB_PI * 1.50);  // 270deg phase.
  float wav7 = sin(mode_7_2_cycle + VIB_PI * 1.75);  // 315deg phase.
  //Serial.printf( "wav0:%0.3f\n", wav0 );
  // note: wav->mot sequence is 0,2,4,6,7,6,5,3,1
  float mot0 = (wav0 + 1.0f) / 2.0f * m_7_2_slider[0].getVal(); // tip 1
  //float mot1 = (wav0 + 1.0f) / 2.0f * m_7_2_slider[0].getVal(); // tip 1
  float mot2 = (wav1 + 1.0f) / 2.0f * m_7_2_slider[0].getVal(); // tip 2
  //float mot3 = (wav7 + 1.0f) / 2.0f * m_7_2_slider[0].getVal(); // tip 2
  float mot4 = (wav2 + 1.0f) / 2.0f * m_7_2_slider[1].getVal(); // base
  float mot5 = (wav6 + 1.0f) / 2.0f * m_7_2_slider[1].getVal(); // base
  float mot6; // Motor shares two phases. Choose one based on direction.
  if ( mode_7_2_cycle < VIB_PI ) { // Decide which phase.       // mid
    mot6 = (wav3 + 1.0f) / 2.0f * m_7_2_slider[1].getVal();
  } else {
    mot6 = (wav5 + 1.0f) / 2.0f * m_7_2_slider[1].getVal();
  }
  float mot7 = (wav4 + 1.0f) / 2.0f * m_7_2_slider[2].getVal(); // rear
  vibes.set(0, mot0); // wav0
  vibes.set(1, mot0); // wav0
  vibes.set(2, mot2); // wav7
  vibes.set(3, mot2); // wav7
  vibes.set(4, mot4); // wav2
  vibes.set(5, mot5); // wav6
  vibes.set(6, mot6); // wav3,  wav5
  vibes.set(7, mot7); // wav4
  vibes.pack();
}

/**
 * Pendulum
 * Five Phases: Tip Pair (mot:0,1) + (mot:2,3), Base Pair(mot4,5), Motor 6(Mid), Motor 7(rear)
 */
void mode_7_3_update_motors() {  // Pendulum
  // advance tick angle based on speed slider
  // advanceRads = (cycSecsMax - cycSecsMin)/(slMax-1) * ( slVal - 1 ) / 10.0(ticks in a second)
  float adv;
  if (m_7_3_slider[3].getVal() > 0) {
    adv = ((MODE_7_3_CYC_MAX - MODE_7_3_CYC_MIN) / (m_7_3_slider[3].getMax() - 1.0) * (m_7_3_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_7_3_cycle += adv;
  if (mode_7_3_cycle > VIB_PI * 2.0) {
    mode_7_3_cycle = 0.0;
  }

  // calc new motor values
  // vibeVal = (sin(advanceRads) + 1) * vibMax/2
  float wav0 = sin(mode_7_3_cycle);
  //float wav1 = sin(mode_7_3_cycle + VIB_PI * 0.4);
  float wav2 = sin(mode_7_3_cycle + VIB_PI * 0.7);
  float wav3 = sin(mode_7_3_cycle + VIB_PI * 1.1);
  float wav4 = sin(mode_7_3_cycle + VIB_PI * 1.6);
  //Serial.printf( "wav0:%0.3f\n", wav0 );
  // note: wav->mot sequence is 0,1,3,2
  float mot0 = (wav0 + 1.0f) / 2.0f * m_7_3_slider[0].getVal(); // tip 1
  //float mot1 = (wav1 + 1.0f) / 2.0f * m_7_3_slider[0].getVal(); // tip 2
  float mot2 = (wav2 + 1.0f) / 2.0f * m_7_3_slider[1].getVal(); // base
  float mot3 = (wav3 + 1.0f) / 2.0f * m_7_3_slider[1].getVal(); // mid
  float mot4 = (wav4 + 1.0f) / 2.0f * m_7_3_slider[2].getVal(); // rear
  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot0);
  vibes.set(3, mot0);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot3);
  vibes.set(7, mot4);
  vibes.pack();
}

/**
 * Plunge
 * Five Phases: Tip Pair (mot:0,1) + Pair(mot:2,3), Base Pair(mot4,5), Motor 6(Mid), Motor 7(rear)
 */
void mode_7_4_update_motors() {  // Plunge
  uint8_t adv;
  //if (m_7_4_slider[3].getVal() >= 0) {
    adv = m_7_4_slider[3].getVal() + 1; // 1 - 8
  //} 
  mode_7_4_cycle += adv;

  if (mode_7_4_cycle > MODE_7_4_CYC_MAX) {
    mode_7_4_cycle = 0;
  }

  uint16_t phase = mode_7_4_cycle/(MODE_7_4_CYC_MAX/5); // 63/11 == 5-ish phases.
  Serial.printf("Phase: %d\n", phase);

  // Motor zones.  All off.
  uint8_t mot0 = 0;
  uint8_t mot1 = 0;
  uint8_t mot2 = 0;
  uint8_t mot3 = 0;
  uint8_t mot4 = 0;

// Experiment: Apply 50% to previous phase motor (decay).

  switch ( phase ) {
    case 0: // Motor pair 1/2
      mot4 = m_7_4_slider[2].getVal() * 0.5;
      mot0 = m_7_4_slider[0].getVal(); // front motor
      break;
    case 1: // Decay-Ramp up 
      mot0 = m_7_4_slider[0].getVal() * 0.5; // front motor
      mot2 = m_7_4_slider[0].getVal() * 0.5; // front motor
      break;
    case 2: // Motor pair 5/6
      mot2 = m_7_4_slider[1].getVal(); // mid motor
      break;
    case 3: // Motor 7
      mot2 = m_7_4_slider[1].getVal() * 0.5;
      mot3 = m_7_4_slider[2].getVal(); // mid motor
      break;
    case 4: // Motor 8
      mot3 = m_7_4_slider[2].getVal() * 0.5; // mid motor
      mot4 = m_7_4_slider[2].getVal(); // back motor
      break;
    default: // dwell, motors off
      break;
  }

  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot0);
  vibes.set(3, mot0);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot3);
  vibes.set(7, mot4);

  vibes.pack();
}

/**
 * Draw
 * Five Phases: Motor 7(rear), Motor 6(Mid), Base Pair(mot4,5), Tip 2 Pair(mot:2,3), Tip 1 Pair (mot:0,1)
 */
void mode_7_5_update_motors() {  // Draw
  uint8_t adv;
  adv = m_7_5_slider[3].getVal() + 1;
  mode_7_5_cycle += adv;

  if (mode_7_5_cycle > MODE_7_5_CYC_MAX) {
    mode_7_5_cycle = 0;
  }

  uint16_t phase = mode_7_5_cycle/(MODE_7_5_CYC_MAX/5); // 63/11 == 5-ish phases.
  Serial.printf("Phase: %d\n", phase);

  // Motor zones.  All off.
  uint8_t mot0 = 0;
  uint8_t mot1 = 0;
  uint8_t mot2 = 0;
  uint8_t mot3 = 0;
  uint8_t mot4 = 0;

  switch ( phase ) { // Like plunge but CASEs are reversed.
    case 4: // Motor pair 1/2
      mot0 = m_7_5_slider[0].getVal(); // front motor
      break;
    case 3: // Motor pair 3/4
      mot1 = m_7_5_slider[0].getVal() * 0.5; // front motor
      mot2 = m_7_5_slider[1].getVal() * 0.5; // mid motor
      break;
    case 2: // Motor pair 5/6
      mot2 = m_7_5_slider[1].getVal(); // mid motor
      mot3 = m_7_5_slider[2].getVal() * 0.5; // mid motor
      break;
    case 1: // Motor 7
      mot3 = m_7_5_slider[2].getVal(); // mid motor
      mot4 = m_7_5_slider[2].getVal() * 0.5; // back motor
      break;
    case 0: // Motor 8
      mot4 = m_7_5_slider[2].getVal(); // back motor
      mot0 = m_7_5_slider[0].getVal() * 0.5; // front motor
      break;
    default: // dwell, motors off
      break;
  }

  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot0);
  vibes.set(3, mot0);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot3);
  vibes.set(7, mot4);

  vibes.pack();
}