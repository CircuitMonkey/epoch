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

void mode_1_0_start() {

  // TODO: Glyph

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
  ui.drawTopTxt(UI_GL_W+12);

  slider1.begin(&tft, " 1", SLIDER_4_X1, 40);
  slider2.begin(&tft, " 2", SLIDER_4_X2, 80);
  slider3.begin(&tft, "  ", SLIDER_4_X3, 0);
  slider4.begin(&tft, "  ", SLIDER_4_X4, 0);

  slider3.setDisabled(true);
  slider4.setDisabled(true);

  ui.setBackBtn(UI_BAK_TR);
  ui.setPlayMode(UI_MODE_PLAY);  // test pause/play glyph
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
      //TS_Point pTft = p2lcd(p);
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
  delay(100);
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
    // Serial.print("M1.1 Drag: btn=");
    // Serial.print(btn);
    // Serial.print("  ");
    // Serial.print(pDragStart.x - p.x);
    // Serial.print(",");
    // Serial.print(pDragStart.y - p.y);
    // Serial.print(" valDiff:");
    double vD = (double)(pDragStart.y - p.y) / slider1.SLIDER_SCALE;
    //Serial.println(vD);
    //uint8_t v = slider1.getVal();
    //Serial.print( "  oldVal: ");
    //Serial.print( v );
    uint16_t nv = slideDragStart + vD;
    // Serial.print( "  newVal: ");
    // Serial.println( nv );

    switch (btn) {
      case 1:
        slider1.setVal(nv);
        slider1.update();
        break;
      case 2:
        slider2.setVal(nv);
        slider2.update();
        break;
      case 3:
        slider3.setVal(nv);
        slider3.update();
        break;
      case 4:
        slider4.setVal(nv);
        slider4.update();
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
            break;
          case UI_MODE_PAUSE:
            ui.setPlayMode(UI_MODE_PLAY);
            break;
        }
        ui.drawPausePlay();
        break;
    }
  }
}