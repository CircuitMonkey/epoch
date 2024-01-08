#include <sys/_stdint.h>
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

#ifndef _TLC59401_Pwm_h_
#define _TLC59401_Pwm_h_

#include "Arduino.h"
#include <SPI.h>

#if ARDUINO < 10600
#error "Arduino 1.6.0 or later (SPI library) is required"
#endif

#define GS_TIMER_CHANNEL 8
#define GS_RES 4
#define GS_FREQ 250000
#define GS_DUTY 8

class TLC59401_PWM {
public:
  constexpr TLC59401_PWM(int mode, int blank, int gsClk, int xLat)
    : _modePin(mode), _blankPin(blank), _gsClkPin(gsClk), _xLatPin(xLat) {}
  bool begin(SPIClass &wspi = SPI);
  void set(uint8_t channel, uint8_t value);
  void update();
  void pause( bool p);
  bool isPaused();

private:
  uint8_t _modePin, _blankPin, _gsClkPin, _xLatPin;
  bool _paused = false;
  void pack();
  void mode(uint8_t mode);
  void blank(uint8_t blanked);

  uint16_t outputs[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  uint8_t packed[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

  SPIClass *_pspi = nullptr;
};

#endif