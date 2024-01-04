#include <sys/_stdint.h>
// [glyph16g]  glyph  16x16   greyscale  as nybles
#ifndef Glyphs_h 
#define Glyphs_h

#define G_WH 16

static const unsigned char PROGMEM glyph16m_blank[] = { 
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000 
};
static const unsigned char PROGMEM glyph16m_x[] = { 
  B10000000, B00000001,
  B01000000, B00000010,
  B00100000, B00000100,
  B00010000, B00001000,
  B00001000, B00010000,
  B00000100, B00100000,
  B00000010, B01000000,
  B00000001, B10000000,
  B00000001, B10000000,
  B00000010, B01000000,
  B00000100, B00100000,
  B00001000, B00010000,
  B00010000, B00001000,
  B00100000, B00000100,
  B01000000, B00000010,
  B10000000, B00000001 
};
static const unsigned char PROGMEM glyph48m_blank[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM glyph48m_back[] = { 
  B00000000, B00001000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00011000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00111000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B01111111, B11111111, B11111110, B00000000, B00000000,
  B00000000, B11111111, B11111111, B11111111, B10000000, B00000000,
  B00000000, B01111111, B11111111, B11111111, B11000000, B00000000,
  B00000000, B00111000, B00000000, B00000000, B11000000, B00000000,
  B00000000, B00011000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00001000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B11100000, B00000000,
  B00000000, B11111111, B11111111, B11111111, B11000000, B00000000,
  B00000000, B11111111, B11111111, B11111111, B10000000, B00000000,
  B00000000, B11111111, B11111111, B11111111, B00000000, B00000000
};

static const unsigned char PROGMEM glyph48m_pause[] = { 
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000,
  B00000000, B00000000, B11110000, B00001111, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_play[] = { 
  B00000000, B00000011, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11000000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11110000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11111100, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11000000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11110000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11111100, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11111100, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11110000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B11000000, B00000000, B00000000,
  B00000000, B00000011, B11111111, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11111100, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11110000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B11000000, B00000000, B00000000, B00000000,
  B00000000, B00000011, B00000000, B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM glyph48m_vibe_1[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B01111110, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11111111, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11000011, B00000000, B00000000, B00000000, B00000000, B00000000,
  B11111111, B00000000, B00000000, B00000000, B00000000, B00000000,
  B01111110, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_2[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B01111110, B00011111, B10000000, B00000000, B00000000, B00000000,
  B11111111, B00111111, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11000011, B00110000, B11000000, B00000000, B00000000, B00000000,
  B11111111, B00111111, B11000000, B00000000, B00000000, B00000000,
  B01111110, B00011111, B10000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_3[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000001, B11000000, B00111000, B00000000,
  B00000000, B00000000, B00000001, B10000000, B00011000, B00000000,
  B00000000, B00000000, B00000011, B00000000, B00001100, B00000000,
  B00000000, B00000000, B00000011, B00000000, B00001100, B00000000,
  B00000000, B00000000, B00000011, B00000000, B00001100, B00000000,
  B00000000, B00000000, B00000011, B00000000, B00001100, B00000000,
  B00000000, B00000000, B00000011, B10000000, B00011100, B00000000,
  B00000000, B00000000, B00000001, B10000000, B00011000, B00000000,
  B00000000, B00000000, B00000001, B11000000, B00111000, B00000000,
  B00000000, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_4[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000001, B11000000, B00111000, B00000000,
  B00000000, B00000000, B00000001, B10000000, B00011000, B00000000,
  B00000000, B00000000, B00000011, B00000000, B00001100, B11111110,
  B00000000, B00000000, B00000011, B00000000, B00001101, B11111111,
  B00000000, B00000000, B00000011, B00000000, B00001101, B11111111,
  B00000000, B00000000, B00000011, B00000000, B00001101, B11111111,
  B00000000, B00000000, B00000011, B10000000, B00011100, B11111110,
  B00000000, B00000000, B00000001, B10000000, B00011000, B00000000,
  B00000000, B00000000, B00000001, B11000000, B00111000, B00000000,
  B00000000, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_5[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B01111110, B00000000, B00000000, B11100000, B01110000, B00000000,
  B11111111, B00000000, B00000001, B11000000, B00111000, B00000000,
  B11000011, B00000000, B00000001, B10000000, B00011000, B00000000,
  B11000011, B00000000, B00000011, B00000000, B00001100, B00000000,
  B11000011, B00000000, B00000011, B00000000, B00001100, B00000000,
  B11000011, B00000000, B00000011, B00000000, B00001100, B00000000,
  B11000011, B00000000, B00000011, B00000000, B00001100, B00000000,
  B11000011, B00000000, B00000011, B10000000, B00011100, B00000000,
  B11000011, B00000000, B00000001, B10000000, B00011000, B00000000,
  B11111111, B00000000, B00000001, B11000000, B00111000, B00000000,
  B01111110, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_6[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B01111110, B00011111, B10000000, B11100000, B01110000, B00000000,
  B11111111, B00111111, B11000001, B11000000, B00111000, B00000000,
  B11000011, B00110000, B11000001, B10000000, B00011000, B00000000,
  B11000011, B00110000, B11000011, B00000000, B00001100, B00000000,
  B11000011, B00110000, B11000011, B00000000, B00001100, B00000000,
  B11000011, B00110000, B11000011, B00000000, B00001100, B00000000,
  B11000011, B00110000, B11000011, B00000000, B00001100, B00000000,
  B11000011, B00110000, B11000011, B10000000, B00011100, B00000000,
  B11000011, B00110000, B11000001, B10000000, B00011000, B00000000,
  B11111111, B00111111, B11000001, B11000000, B00111000, B00000000,
  B01111110, B00011111, B10000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_7[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B01111110, B00000000, B00000000, B11100000, B01110000, B00000000,
  B11111111, B00000000, B00000001, B11000000, B00111000, B00000000,
  B11000011, B00000000, B00000001, B10000000, B00011000, B00000000,
  B11000011, B00000000, B00000011, B00000000, B00001100, B11111110,
  B11000011, B00000000, B00000011, B00000000, B00001101, B11111111,
  B11000011, B00000000, B00000011, B00000000, B00001101, B11111111,
  B11000011, B00000000, B00000011, B00000000, B00001101, B11111111,
  B11000011, B00000000, B00000011, B10000000, B00011100, B11111110,
  B11000011, B00000000, B00000001, B10000000, B00011000, B00000000,
  B11111111, B00000000, B00000001, B11000000, B00111000, B00000000,
  B01111110, B00000000, B00000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_vibe_8[] = { 
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B01111110, B00011111, B10000000, B11100000, B01110000, B00000000,
  B11111111, B00111111, B11000001, B11000000, B00111000, B00000000,
  B11000011, B00110000, B11000001, B10000000, B00011000, B00000000,
  B11000011, B00110000, B11000011, B00000000, B00001100, B11111110,
  B11000011, B00110000, B11000011, B00000000, B00001101, B11111111,
  B11000011, B00110000, B11000011, B00000000, B00001101, B11111111,
  B11000011, B00110000, B11000011, B00000000, B00001101, B11111111,
  B11000011, B00110000, B11000011, B10000000, B00011100, B11111110,
  B11000011, B00110000, B11000001, B10000000, B00011000, B00000000,
  B11111111, B00111111, B11000001, B11000000, B00111000, B00000000,
  B01111110, B00011111, B10000000, B11100000, B01110000, B00000000,
  B00000000, B00000000, B00000000, B01111111, B11100000, B00000000,
  B00000000, B00000000, B00000000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};

static const unsigned char PROGMEM glyph48m_slide_bg[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B11000000, B00000001, B10000000, B00000011, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_slide_fg[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00001111, B11111100, B00000000, B00000000, B00000000, B00000000,
  B00001111, B11111100, B00000000, B00000000, B00000000, B00000000,
  B00001111, B11111100, B00000000, B00000000, B00111111, B11110000,
  B00001111, B11111100, B00000000, B00000000, B00111111, B11110000,
  B00000000, B00000000, B00011111, B11111000, B00111111, B11110000,
  B00000000, B00000000, B00011111, B11111000, B00111111, B11110000,
  B00000000, B00000000, B00011111, B11111000, B00000000, B00000000,
  B00000000, B00000000, B00011111, B11111000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000
};
static const unsigned char PROGMEM glyph48m_cycle[] = { 
  B00000000, B00000000, B00000111, B11100001, B10000000, B00000000,
  B00000000, B00000000, B00111111, B11110111, B10000000, B00000000,
  B00000000, B00000000, B00111000, B00011111, B10000000, B00000000,
  B00000000, B00000000, B01100000, B01111111, B10000000, B00000000,
  B00000000, B00000000, B11000000, B00011111, B10000000, B00000000,
  B00000000, B00000001, B10000000, B00000111, B10000000, B00000000,
  B00000000, B00000001, B10000000, B00000001, B10000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000001, B00000000, B00000000, B10000000, B00000000,
  B00000000, B00000001, B11100000, B00000001, B10000000, B00000000,
  B00000000, B00000001, B11111000, B00000011, B00000000, B00000000,
  B00000000, B00000001, B11111110, B00000111, B00000000, B00000000,
  B00000000, B00000001, B10111000, B00011100, B00000000, B00000000,
  B00000000, B00000001, B11110111, B11111100, B00000000, B00000000,
  B00000000, B00000001, B10000111, B11100000, B00000000, B00000000,
};
static const unsigned char PROGMEM glyph48m_wave[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00000000, B00001110, B01110000, B00000000, B00000000,
  B00000000, B00000001, B11001110, B01110000, B00000000, B00000000,
  B00000000, B00000001, B11001110, B01110011, B10000000, B00000000,
  B00000000, B00000001, B11001110, B01110011, B10000000, B00000000,
  B00000000, B00000001, B11001110, B01110011, B10000000, B00000000,
  B00000000, B00111001, B11001110, B01110011, B10011100, B00000000,
  B00000000, B00111001, B11001110, B01110011, B10011100, B00000000,
  B00000000, B00111001, B11001110, B01110011, B10011100, B00000000,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111
};
static const unsigned char PROGMEM glyph48m_pulse[] = { 
  B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B00000000, B00111001, B11000000, B00000011, B10011100, B00000000,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111,
  B11100111, B00111001, B11001110, B01110011, B10011100, B11100111
};


#endif