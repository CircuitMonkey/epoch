/*
 * Vibe channels test for Epoch
 */
#include "TLC59401.h"

#define BTN1  2
#define BTN2  3

// Rev. A
#define MODE  33
#define BLANK 14

#define GSCLK  27
#define XLAT   21
#define SCLK   5
#define SIN    18

#define VIBE_MAX 0x0FFF

TLC59401 vibes = TLC59401(MODE, BLANK, GSCLK, XLAT, SCLK, SIN );
int vN = 0;
int v1 = 0;

void setup() {
  Serial.begin(115200);
  delay(600);
  //while (!Serial) {}
  Serial.println("Epoch Vibe Tester...");

  vibes.begin();
  vibes.push();
  vibes.blank(0);
  Serial.println( "Vibes initialized.");
}

void loop() {
  if ( v1%100 == 0 ) Serial.print( ".");
  vibes.set( vN, v1 );
  //vibes.set( 1, potValue1<<2 );
  //vibes.set( 2, potValue2<<2 );
  //vibes.set( 3, potValue3<<2 );
  
  vibes.push();

  v1+=10;
  if ( v1 > VIBE_MAX ) { 
    v1=0;
    vibes.set( vN, v1);
    vN++;
    if ( vN > 3 ) vN = 0;
    Serial.println();
  }

  //delay(10);
}


