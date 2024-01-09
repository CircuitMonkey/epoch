/**
 Epoch Project - A 16-channel vibrator controller
 with touch screen.
        https://www.patreon.com/maehem

 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 Uses code from AdaFruit and Paul Stoffregen
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 *********************************************************************/

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "XPT2046_Touchscreen.h"
#include "tlc59401.h"
#include "glyphs.h"
#include "ui.h"
#include "slider.h"

// ILI9341 TFT Display
#define TFT_DC 13
#define TFT_CS 12
#define TFT_MOSI 18
#define TFT_MISO 19
#define TFT_CLK 5
#define TFT_RST A0
#define TFT_LED 15

// Touch
#define TCH_CS A1
#define TCH_IRQ A4

// Motor Chip
#define VIB_MODE 33
#define VIB_BLANK 14
#define VIB_GSCLK 27
#define VIB_XLAT 21

//#define SPI_DEFAULT_FREQ 2000000
//#define SPI_SETTING     SPISettings(2000000, MSBFIRST, SPI_MODE0)

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
XPT2046_Touchscreen ts(TCH_CS);
//XPT2046_Touchscreen ts(TCH_CS,TCH_IRQ);
TLC59401_PWM vibes = TLC59401_PWM(VIB_MODE, VIB_BLANK, VIB_GSCLK, VIB_XLAT);

Ui ui = Ui();

boolean wastouched = false;
boolean istouched = false;
TS_Point p;
TS_Point pLast;
TS_Point pDragStart;
uint8_t slideDragStart;
uint8_t lastBtn = 99;
uint8_t guiMode = 0;
bool updateSemaphore = false;

hw_timer_t *Timer0_Cfg = NULL;
portMUX_TYPE timerMux0 = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR Timer0_ISR() {
  // Set semaphore.
  updateSemaphore = true;

  //vibes.update();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("\n\nEpoch Haptic Generator");
  Serial.flush();

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(30);
  digitalWrite(TFT_RST, HIGH);

  tft.begin();
  ts.begin();
  ts.setRotation(2);  // X/Y==0 top-left.
  vibes.begin();  // vibes assume SPI was set up by TFT


  Timer0_Cfg = timerBegin(1, 80, true);  // channel 7, prescaler 80, tick count up.
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 17000, true);  // doISR every 17000 ticks =17mS
  timerAlarmEnable(Timer0_Cfg);

  vibes.pause(true);

  digitalWrite(TFT_LED, LOW);
  // TODO:  PWM LED brightness

  // read diagnostics (optional but can help debug problems)
  // uint8_t x = tft.readcommand8(ILI9341_RDMODE);  // Default 0xCA
  // Serial.print("Display Power Mode: 0x");
  // Serial.println(x, HEX);
  // x = tft.readcommand8(ILI9341_RDMADCTL);  // Default 0x24
  // Serial.print("MADCTL Mode: 0x");
  // Serial.println(x, HEX);
  // x = tft.readcommand8(ILI9341_RDPIXFMT);
  // Serial.print("Pixel Format: 0x");  // Default 0x2;
  // Serial.println(x, HEX);
  // x = tft.readcommand8(ILI9341_RDIMGFMT);  // Default 0xC0
  // Serial.print("Image Format: 0x");
  // Serial.println(x, HEX);
  // x = tft.readcommand8(ILI9341_RDSELFDIAG);  // Default 0xE0
  // Serial.print("Self Diagnostic: 0x");
  // Serial.println(x, HEX);

  // Serial.println(F("Done!"));

  ui.begin(&tft, glyph48m_back, glyph48m_pause, glyph48m_play );
  mode_0_start();
}


void loop() {
  istouched = ts.touched();
  p = p2lcd(ts.getPoint());
  switch (guiMode) {
    case 0:
      mode_0_loop();
      break;
    case 1:  // Single ring.
      mode_1_loop();
      break;
    case 2:
      if (istouched) {
        if (!wastouched) {
          tft.fillScreen(ILI9341_BLACK);
          //tft.setTextColor(ILI9341_YELLOW);
          //tft.setFont(Arial_60);
          tft.setTextColor(ILI9341_GREEN);
          tft.setTextSize(1);
          tft.setCursor(60, 80);
          tft.print("Touch");
          Serial.print("New Touch...");
        }
        tft.fillRect(100, 150, 100, 40, ILI9341_BLACK);
        tft.setTextSize(1);
        tft.setTextColor(ILI9341_GREEN);
        //tft.setFont(Arial_24);
        tft.setCursor(100, 150);
        tft.print("X = ");
        tft.print(p.x);
        tft.setCursor(100, 180);
        tft.print("Y = ");
        tft.print(p.y);
        Serial.print(" x = ");
        Serial.print(p.x);
        Serial.print(", y = ");
        Serial.println(p.y);
      } else {
        if (wastouched) {
          tft.fillScreen(ILI9341_BLACK);
          tft.setTextColor(ILI9341_RED);
          //tft.setFont(Arial_48);
          tft.setCursor(120, 50);
          tft.print("No...");
          tft.setCursor(80, 120);
          tft.print("Touch");
          Serial.println("No Touch");
        }
        //Serial.println("no touch");
      }
      wastouched = istouched;

      delay(70);
      // Touch test
  }
  pLast.x = p.x;
  pLast.y = p.y;
  if ( updateSemaphore ) {
    vibes.update();
    updateSemaphore = false;
  }
}
