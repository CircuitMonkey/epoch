#include "esp32-hal.h"


#include "Arduino.h"
#include "TLC59401.h"
//#define NOP __asm__ __volatile__ ("nop\n\t")
//#define NOP delayMicroseconds(5)

TLC59401::TLC59401(int mode, int blank, int gsClk, int xLat, int sClk, int sIn ) {
    _modePin = mode;
    _blankPin = blank;
    _gsClkPin = gsClk;
    _xLatPin = xLat;
    _sClkPin = sClk;
    _sInPin = sIn;

    //outputs[] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

}

void TLC59401::begin() {
    // Set BLANK initially high (outputs off)
    pinMode( _blankPin, OUTPUT );
    digitalWrite( _blankPin, HIGH );

    // No support for GS mode yet. So set MODE high.
    pinMode( _modePin, OUTPUT );
    digitalWrite( _modePin, HIGH );

    // 
    pinMode( _gsClkPin, OUTPUT );
    digitalWrite( _gsClkPin, LOW );
    
    // 
    pinMode( _xLatPin, OUTPUT );
    digitalWrite( _xLatPin, LOW );
    
    // 
    pinMode( _sClkPin, OUTPUT );
    digitalWrite( _sClkPin, LOW );
    
    // 
    pinMode( _sInPin, OUTPUT );
    digitalWrite( _sInPin, LOW );

    // 16-ch x 12-bits
    // LATCH = Low
    // MODE = low
    // SIN = high
    // For each 192 CLK, toggle LATCH high
    // TO DO Pre fill the GS register!

    // Arduino SPI commands
    // void beginTransaction(SPISettings settings);
    // void endTransaction(void);
    // void transfer(void * data, uint32_t size);

  //use it as you would the regular arduino SPI API
  // spi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  // digitalWrite(spi->pinSS(), LOW); //pull SS slow to prep other end for transfer
  // spi->transfer(data);
  // digitalWrite(spi->pinSS(), HIGH); //pull ss high to signify end of data transfer
  // spi->endTransaction();

    // for ( int ck=0; ck<4096; ck++ ) {
    //   digitalWrite(_gsClkPin, HIGH);
    //   //NOP;
    //   digitalWrite(_gsClkPin, LOW );
    // }
    // // One additional sclock pulse is needed after 192 clocks.
    //   digitalWrite(_gsClkPin, HIGH);
    //   digitalWrite(_gsClkPin, LOW );
    // MODE = high
    
    
}

/**
 * Set the numbered channel to this PWM value.
 */
void TLC59401::set( int channel, int value ) {
  outputs[channel] = value;
}

/** 
 *  Push the buffer into the chip.
 */
void TLC59401::push() {
    digitalWrite( _xLatPin, LOW );
    blank(HIGH);

    // TODO: Pack the short (6bit) data into one buffer.

    // Clock out each bit in the buffers (at 12-bits MSB to LSB)
    // Also MS Byte is first too.
    for ( int i=15; i>=0; i-- ) {
      int v = (outputs[i]>>6) & 0x3f; // truncate to 6 bits
      for( int j=5; j>=0; j-- ) {
        //SPI.transfer(v);

        digitalWrite(_sInPin, (v&(1<<j))>>j);
        digitalWrite(_sClkPin, HIGH);
        //NOP;
        digitalWrite(_sClkPin, LOW);
        
      }
    }
    digitalWrite(_sInPin, LOW);

    // latch it
    digitalWrite( _xLatPin, HIGH );
    //NOP;
    digitalWrite( _xLatPin, LOW );

    blank(LOW);
    for ( int ck=0; ck<4096; ck++ ) {
      digitalWrite(_gsClkPin, HIGH);
      //NOP;
      digitalWrite(_gsClkPin, LOW );
    }
//    blank(HIGH);
}

void TLC59401::blank( int blanked) {
  digitalWrite( _blankPin, blanked );  
}
