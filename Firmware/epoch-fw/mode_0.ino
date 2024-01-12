#include "glyphs.h"

uint8_t mode_0_function = 0;

void mode_0_start() {
  ui.setStyle(UI_STYLE_DISC);
  ui.blank();
  ui.drawDiscBase();

  ui.drawDiscGlyph(1, glyph48m_vibe_8, glyph48m_vibe_1);
  ui.drawDiscGlyph(2, glyph48m_vibe_8, glyph48m_vibe_2);
  ui.drawDiscGlyph(3, glyph48m_vibe_8, glyph48m_vibe_3);
  ui.drawDiscGlyph(4, glyph48m_vibe_8, glyph48m_vibe_4);
  ui.drawDiscGlyph(5, glyph48m_vibe_8, glyph48m_vibe_5);
  ui.drawDiscGlyph(6, glyph48m_vibe_8, glyph48m_vibe_6);
  ui.drawDiscGlyph(7, glyph48m_vibe_8, glyph48m_vibe_7);
  ui.drawDiscGlyph(8, glyph48m_vibe_8, glyph48m_vibe_8);

  ui.setTopText("  C O N F I G U R E");  // 17 chars
  ui.drawTopTxt(0);
  ui.setBotText("E P O C H");  // 9 chars
  ui.drawBotTxt();
}

void mode_0_loop() {
  if (istouched) {
    if (!wastouched) {  // New touch
      uint8_t btn = ui.getItemPressed(p);
      //Serial.print("Button Pressed: ");
      //Serial.println(btn);
      guiMode = btn;

      // TODO: Switch statement
      switch( guiMode ) {
        //  case 0: // nothing this is mode 0
        case 1:
          mode_1_0_start();
          break;
        case 2:
          mode_2_0_start();
          break;
      }
      wastouched = istouched;
    
    } else {  // Dragging or still touching
    }
  } else {  // end of istouched
    wastouched = 0;
  }
  delay(70);
}

void mode_0_updateMotors() {
  vibes.update();
}
