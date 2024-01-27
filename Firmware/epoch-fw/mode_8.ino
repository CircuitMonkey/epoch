/**
 * Mode 8 - Quad Haptic Element Pair
 * 
 * Eight Vibrators:
 *       (Left - Right):A, (Left - Right):B  Connector A, Channel 1-4
 *       (Left - Right):A, (Foward - Back):B Connector B, Channel 1-4
 */

// Mode 8. Dual Haptic Element Pair
// Mode 8 functions: 0:Back to Main menu,  1:Sliders, 2:Cycle, 3:Pendulum, 4:Plunge, 5:Draw Out
uint8_t mode_8_function = 0;

Slider m_8_1_slider[4] = {
  Slider(" 1", SLIDER_4_X1, 5, 63),
  Slider(" 2", SLIDER_4_X2, 9, 63),
  Slider(" 3", SLIDER_4_X3, 14, 63),
  Slider(" 4", SLIDER_4_X4, 18, 63)
};
Slider m_8_2_slider[4] = {  // cycle func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
Slider m_8_3_slider[4] = {  // pendulum func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
Slider m_8_4_slider[4] = {  // plunge func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
Slider m_8_5_slider[4] = {  // draw func
  Slider("FRT", SLIDER_4_X1, 12, 63),
  Slider("MID", SLIDER_4_X2, 25, 63),
  Slider("BAK", SLIDER_4_X3, 12, 63),
  Slider("SPD", SLIDER_4_X4, 28, 63)
};
float mode_8_2_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_8_2_CYC_MAX 10.0f
#define MODE_8_2_CYC_MIN 0.4f

float mode_8_3_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_8_3_CYC_MAX 10.0f
#define MODE_8_3_CYC_MIN 0.4f

float mode_8_4_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_8_4_CYC_MAX 10.0f
#define MODE_8_4_CYC_MIN 0.4f

float mode_8_5_cycle = 0.0;  // in Radians 0 - 6.283
#define MODE_8_5_CYC_MAX 10.0f
#define MODE_8_5_CYC_MIN 0.4f

// back button is at index 0.
const unsigned char *m_8_0_glyphs_bg[9] = { glyph48m_back, glyph48m_slide_bg, glyph48m_cycle, glyph48m_pendulum, glyph48m_plunge, glyph48m_draw, glyph48m_blank, glyph48m_blank, glyph48m_blank };
const unsigned char *m_8_0_glyphs_fg[9] = { glyph48m_back, glyph48m_slide_fg, glyph48m_cycle, glyph48m_pendulum, glyph48m_plunge, glyph48m_draw, glyph48m_blank, glyph48m_blank, glyph48m_blank };

void mode_8_updateMotors() {
  switch (mode_8_function) {
    // Other cases handled during drag.
    case 2:
      mode_8_2_update_motors();
      break;
    case 3:
      mode_8_3_update_motors();
      break;
    case 4:
      mode_8_4_update_motors();
      break;
    case 5:
      mode_8_5_update_motors();
      break;
  }
  vibes.update();
}

void mode_8_0_start() {
  ui.setStyleDisc(" FULL RIDE ", "M O D E 8", glyph48m_vibe_8, glyph48m_vibe_8, m_8_0_glyphs_bg, m_8_0_glyphs_fg);

  // TODO: Set based on UI pause mode.
  vibes.pause(true);
}

void mode_8_1_start() {
  ui.setStyleSlide4("SLIDERS", glyph48m_slide_bg, glyph48m_slide_fg);

  for (int i = 0; i < 4; i++) {
    m_8_1_slider[i].begin(&tft);
    vibes.set(i, m_8_1_slider[i].getVal());
  }
  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * cycle functions
 */
void mode_8_2_start() {
  ui.setStyleSlide4("CYCLE", glyph48m_cycle, NULL);

  for (int i = 0; i < 4; i++) {
    m_8_2_slider[i].begin(&tft);
    vibes.set(i, m_8_2_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * pendulum functions
 */
void mode_8_3_start() {
  ui.setStyleSlide4("PENDULUM", glyph48m_pendulum, NULL);

  for (int i = 0; i < 4; i++) {
    m_8_3_slider[i].begin(&tft);
    vibes.set(i, m_8_3_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * plunge functions
 */
void mode_8_4_start() {
  ui.setStyleSlide4("PLUNGE", glyph48m_plunge, NULL);

  for (int i = 0; i < 4; i++) {
    m_8_4_slider[i].begin(&tft);
    vibes.set(i, m_8_4_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

/**
 * draw functions
 */
void mode_8_5_start() {
  ui.setStyleSlide4("DRAW", glyph48m_draw, NULL);

  for (int i = 0; i < 4; i++) {
    m_8_5_slider[i].begin(&tft);
    vibes.set(i, m_8_5_slider[i].getVal());
  }

  vibes.pack();  // do whenever you call one or more vibes.set()

  // TODO: ask UI for play mode and set appropriately.
  vibes.pause(true);
}

void mode_8_loop() {
  if (istouched) {
    if (!wastouched) {  // New touch
      pDragStart.x = p.x;
      pDragStart.y = p.y;
      //Serial.printf("Mode 8 touch: %d\n", ui.getItemPressed(p));
      switch (mode_8_function) {                      // Handle menu
        case 0:                                       // Mode 0 top menu
          mode_8_0_handle_btn(ui.getItemPressed(p));  // will change the mode or function.
          break;
        case 1:  // mode 0 - init handle sliders or back btn
          mode_8_1_handle_touch(ui.getItemPressed(p));
          break;
        case 2:  // mode 0 - init handle sliders or back btn
          mode_8_2_handle_touch(ui.getItemPressed(p));
          break;
        case 3:  // mode 0 - init handle sliders or back btn
          mode_8_3_handle_touch(ui.getItemPressed(p));
          break;
        case 4:  // mode 0 - init handle sliders or back btn
          mode_8_4_handle_touch(ui.getItemPressed(p));
          break;
        case 5:  // mode 0 - init handle sliders or back btn
          mode_8_5_handle_touch(ui.getItemPressed(p));
          break;
      }
      wastouched = istouched;
    } else {  // Dragging or still touching
      switch (mode_8_function) {
        case 1:  // drag slider if selected.
          mode_8_1_handle_slide();
          break;
        case 2:  // drag slider if selected.
          mode_8_2_handle_slide();
          break;
        case 3:  // drag slider if selected.
          mode_8_3_handle_slide();
          break;
        case 4:  // drag slider if selected.
          mode_8_4_handle_slide();
          break;
        case 5:  // drag slider if selected.
          mode_8_5_handle_slide();
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
void mode_8_0_handle_btn(uint8_t btn) {
  Serial.printf("Mode 8 btn pressed: %d\n", btn);
  switch (btn) {
    case 0:  // Back to Mode 0
      guiMode = 0;
      mode_8_function = 0;  // tidy our value.
      mode_0_function = 0;
      mode_0_start();
      break;
    case 1:         // Function 1: Sliders
      guiMode = 8;  // back to mode_8_0
      mode_8_function = 1;
      mode_8_1_start();
      break;
    case 2:         // Function 2: Cycle
      guiMode = 8;  // back to mode_8_0
      mode_8_function = 2;
      mode_8_2_start();
      break;
    case 3:         // Function 3: Pendulum
      guiMode = 8;  // back to mode_8_0
      mode_8_function = 3;
      mode_8_3_start();
      break;
    case 4:         // Function 3: Pendulum
      guiMode = 8;  // back to mode_8_0
      mode_8_function = 4;
      mode_8_4_start();
      break;
    case 5:         // Function 3: Pendulum
      guiMode = 8;  // back to mode_8_0
      mode_8_function = 5;
      mode_8_5_start();
      break;
    default:  // Not a touch. Do nothing.
      break;
  }
}

void mode_8_1_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_8_1_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_8_1_slider[idx].setVal(nv);
      m_8_1_slider[idx].update();
      vibes.set(idx, m_8_1_slider[idx].getVal());
      vibes.pack();
    }
  }
}

void mode_8_1_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_8_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_8_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_8_1_slider[btn - 1].getVal();
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


void mode_8_2_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_8_2_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_8_2_slider[idx].setVal(nv);
      m_8_2_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_8_2_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_8_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_8_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
        //case 3:  // disabled
        //case 4:  // disabled
        slideDragStart = m_8_2_slider[btn - 1].getVal();
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

void mode_8_3_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_8_3_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_8_3_slider[idx].setVal(nv);
      m_8_3_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_8_3_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_8_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_8_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
        //case 3:  // disabled
        //case 4:  // disabled
        slideDragStart = m_8_3_slider[btn - 1].getVal();
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
void mode_8_4_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_8_4_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_8_4_slider[idx].setVal(nv);
      m_8_4_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_8_4_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_8_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_8_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_8_4_slider[btn - 1].getVal();
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


void mode_8_5_handle_slide() {
  // If point is on a slider, move it.
  uint8_t btn = ui.getItemPressed(p);
  if (btn != UI_BUTTON_NONE && btn == lastBtn) {  // still dragging the same thing.
    if (btn >= 1 && btn <= 4) {                   // yes, it's a slider
      uint8_t idx = btn - 1;
      float vDrag = (float)(pDragStart.y - p.y) / m_8_5_slider[idx].getScale();
      uint16_t nv = slideDragStart + vDrag;
      m_8_5_slider[idx].setVal(nv);
      m_8_5_slider[idx].update();
      //vibes.set(idx, m_1_2_slider[idx].getVal());
      //vibes.pack();
    }
  }
}

void mode_8_5_handle_touch(uint8_t btn) {
  // Start of slide or touch of button
  if (btn == UI_BTN_EXIT) {  // exit button
    mode_8_function = 0;
    lastBtn = UI_BUTTON_NONE;
    mode_8_0_start();
  } else {
    lastBtn = btn;  // might be start of slide.
    switch (btn) {
      case 1:
      case 2:
      case 3:
      case 4:
        slideDragStart = m_8_5_slider[btn - 1].getVal();
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


void mode_8_2_update_motors() {
  // advance tick angle based on speed slider
  // advanceRads = (cycSecsMax - cycSecsMin)/(slMax-1) * ( slVal - 1 ) / 10.0(ticks in a second)
  float adv;
  if (m_8_2_slider[3].getVal() > 0) {
    adv = ((MODE_8_2_CYC_MAX - MODE_8_2_CYC_MIN) / (m_8_2_slider[3].getMax() - 1.0) * (m_8_2_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_8_2_cycle += adv;
  if (mode_8_2_cycle > VIB_PI * 2.0) {
    mode_8_2_cycle = 0.0;
  }
  // calc new motor values
  // vibeVal = (sin(advanceRads) + 1) * vibMax/2
  float wav0 = sin(mode_8_2_cycle);
  float wav1 = sin(mode_8_2_cycle + VIB_PI * 0.25);  // 45deg phase.
  float wav2 = sin(mode_8_2_cycle + VIB_PI / 2.0);   // 90deg phase.
  float wav3 = sin(mode_8_2_cycle + VIB_PI * 0.75);  // 135deg phase.
  float wav4 = sin(mode_8_2_cycle + VIB_PI);         // 180deg phase.
  float wav5 = sin(mode_8_2_cycle + VIB_PI * 1.25);  // 225deg phase.
  float wav6 = sin(mode_8_2_cycle + VIB_PI * 1.50);  // 270deg phase.
  float wav7 = sin(mode_8_2_cycle + VIB_PI * 1.75);  // 315deg phase.
  //Serial.printf( "wav0:%0.3f\n", wav0 );
  // note: wav->mot sequence is 0,2,4,6,7,6,5,3,1
  float mot0 = (wav0 + 1.0f) / 2.0f * m_8_2_slider[0].getVal(); // tip 1
  float mot1 = (wav0 + 1.0f) / 2.0f * m_8_2_slider[0].getVal(); // tip 1
  float mot2 = (wav1 + 1.0f) / 2.0f * m_8_2_slider[0].getVal(); // tip 2
  float mot3 = (wav7 + 1.0f) / 2.0f * m_8_2_slider[0].getVal(); // tip 2
  float mot4 = (wav2 + 1.0f) / 2.0f * m_8_2_slider[1].getVal(); // base
  float mot5 = (wav6 + 1.0f) / 2.0f * m_8_2_slider[1].getVal(); // base
  float mot6; // Motor shares two phases. Choose one based on direction.
  if ( mode_8_2_cycle < VIB_PI ) { // Decide which phase.       // mid
    mot6 = (wav3 + 1.0f) / 2.0f * m_8_2_slider[1].getVal();
  } else {
    mot6 = (wav5 + 1.0f) / 2.0f * m_8_2_slider[1].getVal();
  }
  float mot7 = (wav4 + 1.0f) / 2.0f * m_8_2_slider[2].getVal(); // rear
  vibes.set(0, mot0);
  vibes.set(1, mot1);
  vibes.set(2, mot2);
  vibes.set(3, mot3);
  vibes.set(4, mot4);
  vibes.set(5, mot5);
  vibes.set(6, mot6);
  vibes.set(7, mot7);
  vibes.pack();
}

/**
 * Pendulum
 * Five Phases: Tip 1 Pair (mot:0,1), Tip 2 Pair(mot:2,3), Base Pair(mot4,5), Motor 6(Mid), Motor 7(rear)
 */
void mode_8_3_update_motors() {  // Pendulum
  // advance tick angle based on speed slider
  // advanceRads = (cycSecsMax - cycSecsMin)/(slMax-1) * ( slVal - 1 ) / 10.0(ticks in a second)
  float adv;
  if (m_8_3_slider[3].getVal() > 0) {
    adv = ((MODE_8_3_CYC_MAX - MODE_8_3_CYC_MIN) / (m_8_3_slider[3].getMax() - 1.0) * (m_8_3_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_8_3_cycle += adv;
  if (mode_8_3_cycle > VIB_PI * 2.0) {
    mode_8_3_cycle = 0.0;
  }

  // calc new motor values
  // vibeVal = (sin(advanceRads) + 1) * vibMax/2
  float wav0 = sin(mode_8_3_cycle);
  float wav1 = sin(mode_8_3_cycle + VIB_PI * 0.4);
  float wav2 = sin(mode_8_3_cycle + VIB_PI * 0.8);
  float wav3 = sin(mode_8_3_cycle + VIB_PI * 1.2);
  float wav4 = sin(mode_8_3_cycle + VIB_PI * 1.6);
  Serial.printf( "wav0:%0.3f\n", wav0 );
  // note: wav->mot sequence is 0,1,3,2
  float mot0 = (wav0 + 1.0f) / 2.0f * m_8_3_slider[0].getVal(); // tip 1
  float mot1 = (wav1 + 1.0f) / 2.0f * m_8_3_slider[0].getVal(); // tip 2
  float mot2 = (wav2 + 1.0f) / 2.0f * m_8_3_slider[1].getVal(); // base
  float mot3 = (wav3 + 1.0f) / 2.0f * m_8_3_slider[1].getVal(); // mid
  float mot4 = (wav4 + 1.0f) / 2.0f * m_8_3_slider[2].getVal(); // rear
  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot1);
  vibes.set(3, mot1);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot3);
  vibes.set(7, mot4);
  vibes.pack();
}

/**
 * Plunge
 * Five Phases: Tip 1 Pair (mot:0,1), Tip 2 Pair(mot:2,3), Base Pair(mot4,5), Motor 6(Mid), Motor 7(rear)
 */
void mode_8_4_update_motors() {  // Plunge
  float adv;
  if (m_8_4_slider[3].getVal() > 0) {
    adv = ((MODE_8_4_CYC_MAX - MODE_8_4_CYC_MIN) / (m_8_4_slider[3].getMax() - 1.0) * (m_8_4_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_8_4_cycle += adv;

  if (mode_8_4_cycle > VIB_PI*2.0) {
    mode_8_4_cycle = 0.0;
  }
  //Serial.printf( "cyc:%0.3f\n", mode_8_4_cycle );

  // calc new motor values
  // vibeVal = (sin(advanceRads) + 1) * vibMax/2
  // float wav0 = cos(mode_8_4_cycle);
  // float wav1 = cos(mode_8_4_cycle + VIB_PI * 0.25);
  // float wav2 = cos(mode_8_4_cycle + VIB_PI * 0.5);
  // float wav3 = cos(mode_8_4_cycle + VIB_PI * 0.75);
  // float wav4 = cos(mode_8_4_cycle + VIB_PI);
    
    float wavA = cos(mode_8_4_cycle);
    float wavB = sin(mode_8_4_cycle);
    float wav0 = wavA;
    float wav1 = wavB;
    float wav2 = 0.0;
    float wav3 = 0.0;
    float wav4 = 0.0;
    if ( wav0 < 0.0 ) {
      wav2 = -wav0;
      wav0 = 0.0;
    } else {
      wav2 = 0.0;
      if ( mode_8_4_cycle > VIB_PI*1.5 ) {
        wav4 = wav0;
        wav0 = 0.0;
      }
    }
    if ( wav1 < 0 ) {
      wav3 = -wav1;
      wav1 = 0.0;
    } else {
      wav3 = 0.0;
    }

  // Serial.printf( "A:%0.3f\n", abs(wavA) );
  // Serial.printf( "B:%0.3f\n", abs(wavB) );
  // Serial.printf( "wav0:%0.3f\n", wav0 );
  // Serial.printf( "wav1:%0.3f\n", wav1 );
  // Serial.printf( "wav2:%0.3f\n", wav2 );
  // Serial.printf( "wav3:%0.3f\n", wav3 );
  // Serial.printf( "wav4:%0.3f\n", wav4 );

  // note: wav->mot sequence is 0,1,3,2
  float mot0 = (wav0 + 1.0f) / 2.0f * m_8_4_slider[0].getVal(); // tip 1
  float mot1 = (wav1 + 1.0f) / 2.0f * m_8_4_slider[0].getVal(); // tip 2
  float mot2 = (wav2 + 1.0f) / 2.0f * m_8_4_slider[1].getVal(); // base
  float mot3 = (wav3 + 1.0f) / 2.0f * m_8_4_slider[1].getVal(); // mid
  float mot4 = (wav4 + 1.0f) / 2.0f * m_8_4_slider[2].getVal(); // rear
  // vibes.set(0, mot0);
  // vibes.set(1, mot0);
  // vibes.set(2, mot1);
  // vibes.set(3, mot1);
  // vibes.set(4, mot2);
  // vibes.set(5, mot2);
  // vibes.set(6, mot3);
  // vibes.set(7, mot4);

  vibes.set(0, mot4);
  vibes.set(1, mot4);
  vibes.set(2, mot3);
  vibes.set(3, mot3);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot1);
  vibes.set(7, mot0);

  vibes.pack();
}

/**
 * Draw
 * Five Phases: Motor 7(rear), Motor 6(Mid), Base Pair(mot4,5), Tip 2 Pair(mot:2,3), Tip 1 Pair (mot:0,1)
 */
void mode_8_5_update_motors() {  // Draw
  float adv;
  if (m_8_5_slider[1].getVal() > 0) {
    adv = ((MODE_8_4_CYC_MAX - MODE_8_4_CYC_MIN) / (m_8_5_slider[3].getMax() - 1.0) * (m_8_5_slider[3].getVal() - 1.0));
    adv /= 10.0;
  } else {
    adv = 0.0;
  }

  mode_8_5_cycle += adv;
  if (mode_8_5_cycle > VIB_PI*2.0) { // Arc over just a bit.
    mode_8_5_cycle = 0.0;
  }
  // calc new motor values
  // float wav0 = cos(mode_8_5_cycle);
  // float wav1 = cos(mode_8_5_cycle + VIB_PI * 0.25);
  // float wav2 = cos(mode_8_5_cycle + VIB_PI * 0.5);
  // float wav3 = cos(mode_8_5_cycle + VIB_PI * 0.75);
  // float wav4 = cos(mode_8_5_cycle + VIB_PI);

    float wavA = cos(mode_8_5_cycle);
    float wavB = sin(mode_8_5_cycle);
    float wav0 = wavA;
    float wav1 = wavB;
    float wav2 = 0.0;
    float wav3 = 0.0;
    float wav4 = 0.0;
    if ( wav0 < 0.0 ) {
      wav2 = -wav0;
      wav0 = 0.0;
    } else {
      wav2 = 0.0;
      if ( mode_8_4_cycle > VIB_PI*1.5 ) {
        wav4 = wav0;
        wav0 = 0.0;
      }
    }
    if ( wav1 < 0 ) {
      wav3 = -wav1;
      wav1 = 0.0;
    } else {
      wav3 = 0.0;
    }
  // Serial.printf( "wav0:%0.3f\n", wav0 );
  // Serial.printf( "wav1:%0.3f\n", wav1 );
  // Serial.printf( "wav2:%0.3f\n", wav2 );
  // Serial.printf( "wav3:%0.3f\n", wav3 );
  // Serial.printf( "wav4:%0.3f\n", wav4 );

  float mot0 = (wav0 + 1.0f) / 2.0f * m_8_5_slider[0].getVal(); // rear
  float mot1 = (wav1 + 1.0f) / 2.0f * m_8_5_slider[0].getVal(); // mid
  float mot2 = (wav2 + 1.0f) / 2.0f * m_8_5_slider[1].getVal(); // base
  float mot3 = (wav3 + 1.0f) / 2.0f * m_8_5_slider[1].getVal(); // tip 2
  float mot4 = (wav4 + 1.0f) / 2.0f * m_8_5_slider[2].getVal(); // tip 1

  // vibes.set(0, mot4);
  // vibes.set(1, mot4);
  // vibes.set(2, mot3);
  // vibes.set(3, mot3);
  // vibes.set(4, mot2);
  // vibes.set(5, mot2);
  // vibes.set(6, mot1);
  // vibes.set(7, mot0);

  vibes.set(0, mot0);
  vibes.set(1, mot0);
  vibes.set(2, mot1);
  vibes.set(3, mot1);
  vibes.set(4, mot2);
  vibes.set(5, mot2);
  vibes.set(6, mot3);
  vibes.set(7, mot4);

  vibes.pack();
}