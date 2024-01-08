#ifndef tlc5940_h
#define tlc5940_h

// 16-ch x 12-bit Greyscale values as six 32-bit values
static const uint32_t PROGMEM gs_vals[] = { 
  B11111111111111111111111111111111,
  B11111111111111111111111111111111,
  B11111111111111111111111111111111,
  B11111111111111111111111111111111,
  B11111111111111111111111111111111,
  B11111111111111111111111111111111
};

class TLC59401 {
  public:
    TLC59401(int mode, int blank, int gsClk, int xLat, int sClk, int sIn );
    void begin();
    void set( int channel, int amount);
    void blank( int blanked );
    void push();
  private:
    int _modePin;
    int _blankPin;
    int _gsClkPin;
    int _xLatPin;
    int _sClkPin;
    int _sInPin;

    int outputs[16] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };
    
};

#endif // tlc5940_h