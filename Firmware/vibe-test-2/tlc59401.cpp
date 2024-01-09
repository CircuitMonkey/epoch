/* Motor Vibe library for TLC59401 PWM Chip
 * Copyright (c) 2024, Mark Koch, @maehem on GitHub and Mastodon
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice, development funding notice, and this permission
 * notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "tlc59401.h"
#include "esp32-hal-gpio.h"
#include "esp32-hal.h"

#define SPI_SETTING SPISettings(2000000, MSBFIRST, SPI_MODE0)

bool TLC59401_PWM::begin(SPIClass &wspi) {
  _pspi = &wspi;
  _pspi->begin();
  pinMode(_modePin, OUTPUT);
  mode(HIGH);
  pinMode(_blankPin, OUTPUT);
  blank(HIGH);
  pinMode(_xLatPin, OUTPUT);
  digitalWrite(_xLatPin, LOW);

  // Pre load (GS) GreyScale all on
  if (_pspi) {
    mode(LOW);
    blank(HIGH);
    digitalWrite(_xLatPin, LOW);
    _pspi->beginTransaction(SPI_SETTING);
    for (int i = 0; i < 12; i++) {
      _pspi->transfer16(0xffff);
    }
    digitalWrite(_xLatPin, HIGH);
    digitalWrite(_xLatPin, LOW);
    uint32_t out;
    _pspi->transferBits(1, &out, 1);
    _pspi->endTransaction();

    mode(HIGH);
    blank(LOW);
  } else {
    Serial.println("Vibes: No SPI configured!");
  }

  ledcSetup( GS_TIMER_CHANNEL, GS_FREQ, GS_RES );
  ledcAttachPin( _gsClkPin, GS_TIMER_CHANNEL );
  ledcWrite( GS_TIMER_CHANNEL, GS_DUTY );  // Duty Cycle

  update();

  return true;
}

/**
 * Set the numbered channel to this value. 0-64
 */
void TLC59401_PWM::set(uint8_t channel, uint8_t value) {
  outputs[channel] = value;
}

/**
 * pack 16 8-bit output values into twelve 6-bit values required by chip
 */
void TLC59401_PWM::pack() { // MSB is channel 0 !!!
  packed[11] = outputs[0] & 0x3F;          // pack 11 (5..0) <-- out[0]
  packed[11] |= (outputs[1] & 0x03) << 6;  // pack 11 (7..6) <-- out[1](1..0)
  packed[10] = (outputs[1] & 0x3C) >> 2;   // pack 10 (3..0) <-- out[1](5..2)
  packed[10] |= (outputs[2] & 0x0F) << 4;  // pack 10 (7..4) <-- out[2](3..0)
  packed[9] = (outputs[2] & 0x30) >> 4;   // pack 9 (1..0) <-- out[2](5..4)
  packed[9] |= (outputs[3] & 0x3F) << 2;  // pack 9 (7..2) <-- out[3](5..0)

  packed[8] = outputs[4] & 0x3F;          // pack 8 (5..0) <-- out[4]
  packed[8] |= (outputs[5] & 0x03) << 6;  // pack 8 (7..6) <-- out[5](1..0)
  packed[7] = (outputs[5] & 0x3C) >> 2;   // pack 7 (3..0) <-- out[5](5..2)
  packed[7] |= (outputs[6] & 0x0F) << 4;  // pack 7 (7..4) <-- out[6](3..0)
  packed[6] = (outputs[6] & 0x30) >> 4;   // pack 6 (1..0) <-- out[6](5..4)
  packed[6] |= (outputs[7] & 0x3F) << 2;  // pack 6 (7..2) <-- out[7](5..0)

  packed[5] = outputs[8] & 0x3F;          // pack 5 (5..0) <-- out[8]
  packed[5] |= (outputs[9] & 0x03) << 6;  // pack 5 (7..6) <-- out[9](1..0)
  packed[4] = (outputs[9] & 0x3C) >> 2;   // pack 4 (3..0) <-- out[9](5..2)
  packed[4] |= (outputs[10] & 0x0F) << 4;  // pack 4 (7..4) <-- out[10](3..0)
  packed[3] = (outputs[10] & 0x30) >> 4;   // pack 3 (1..0) <-- out[10](5..4)
  packed[3] |= (outputs[11] & 0x3F) << 2;  // pack 3 (7..2) <-- out[11](5..0)

  packed[2] = outputs[12] & 0x3F;          // pack 2 (5..0) <-- out[12]
  packed[2] |= (outputs[13] & 0x03) << 6;  // pack 2 (7..6) <-- out[13](1..0)
  packed[1] = (outputs[13] & 0x3C) >> 2;   // pack 1 (3..0) <-- out[13](5..2)
  packed[1] |= (outputs[14] & 0x0F) << 4;  // pack 1 (7..4) <-- out[14](3..0)
  packed[0] = (outputs[14] & 0x30) >> 4;   // pack 0 (1..0) <-- out[14](5..4)
  packed[0] |= (outputs[15] & 0x3F) << 2;  // pack 0 (7..2) <-- out[15](5..0)
}

void TLC59401_PWM::update() {

  if (_pspi) {
    pack();  // pack output[] into a 96-bit pack[] buffer.

    mode(HIGH);  // DC mode
    digitalWrite(_xLatPin, LOW);
    blank(HIGH);  // turn off outputs
    ledcWrite( GS_TIMER_CHANNEL, 0 );
    delayMicroseconds(100);

    _pspi->beginTransaction(SPI_SETTING);
    _pspi->transfer(packed, 12); // Packed dot-correction values.
    _pspi->endTransaction();

    // latch it
    digitalWrite(_xLatPin, HIGH);
    digitalWrite(_xLatPin, LOW);

    blank(LOW);  // turn on outputs
    if ( !isPaused() ) {
      ledcWrite( GS_TIMER_CHANNEL, GS_DUTY );
    }
  } else  {
    Serial.println("Vibes: No SPI configured!");
  };  // bail if no SPI is set up.

  //delay(10);
}

void TLC59401_PWM::blank(uint8_t blanked) {
  digitalWrite(_blankPin, blanked);
}

/**
 * set mode
 * 
 * HIGH = DC. Dot Correction vals=0-63
 *  LOW = GS. Grey Scale  NOT USED!
 */
void TLC59401_PWM::mode(uint8_t mode) {
  digitalWrite(_modePin, mode);
}

void TLC59401_PWM::pause( bool p ) {
  _paused = p;
  if ( _paused ) {
    ledcWrite( GS_TIMER_CHANNEL, 0 );
  } else {
    ledcWrite( GS_TIMER_CHANNEL, GS_DUTY );
  }
}

bool TLC59401_PWM::isPaused() {
  return _paused;
}