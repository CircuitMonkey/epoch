#include "Adafruit_ILI9341.h"
#include "tlc59401.h"

#define TFT_DC 13
#define TFT_CS 12
#define TFT_MOSI 18
#define TFT_MISO 19
#define TFT_CLK 5
#define TFT_RST A0
#define TFT_LED 15

#define VIB_MODE 33
#define VIB_BLANK 14
#define VIB_GSCLK 27
#define VIB_XLAT 21

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TLC59401_PWM vibes = TLC59401_PWM(VIB_MODE, VIB_BLANK, VIB_GSCLK, VIB_XLAT);

hw_timer_t *Timer0_Cfg = NULL;

void IRAM_ATTR Timer0_ISR() {
  vibes.update();
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(30);
  digitalWrite(TFT_RST, HIGH);

  tft.begin();
  //SPI.begin();  // Use this if no TFT.
  vibes.begin();  // vibes assume SPI was set up by TFT

  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(100, 150, 100, 40, ILI9341_GREEN);
  digitalWrite(TFT_LED, LOW);
  Serial.println("\n\nEpoch Motors Test");

  Timer0_Cfg = timerBegin(0, 80, true);  // channel 7, prescaler 80, tick count up.
  timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR, true);
  timerAlarmWrite(Timer0_Cfg, 17000, true);  // doISR every 17000 ticks =17mS
  timerAlarmEnable(Timer0_Cfg);
}

void loop() {

  // Ramp vibes 1-4  zero to max.
  for (int i = 0; i < 4; i++) {
    Serial.printf("Set vibe: %d\n", i);
    for (int j = 0; j < 64; j++) {
      vibes.set(i, j);
      delay(100);
    }
    vibes.set(i, 0);  // Turn it off.
    //delay(200);
  }

  // Test pause function.  Turn vibe 1 on, pause it then resume.
  vibes.set(1, 63);
  delay(100);
  Serial.print("Pause...");
  vibes.pause(true);
  delay(2000);
  vibes.pause(false);
  delay(100);
  vibes.set(1, 0);
  Serial.println("done.");
}
