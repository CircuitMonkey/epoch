int16_t tsMinX = 360;
int16_t tsMaxX = 3880;
int16_t tsMinY = 219;
int16_t tsMaxY = 3880;
int16_t tsXrat = (tsMaxX-tsMinX)/tft.width();
int16_t tsYrat = (tsMaxY-tsMinY)/tft.height();

TS_Point p2lcd( TS_Point p ) {
  // Axis are flipped in Portriat screen mode

  // Can't be negative, bad things happen.
  int16_t tX = (p.x-tsMinX)/tsXrat;
  if ( tX < 0 ) {
    tX = 0;
  }

  int16_t tY = (p.y-tsMinY)/tsYrat;
  if ( tY < 0 ) {
    tY = 0;
  }

  return TS_Point( tX, tY, 0);
}

void printTftSettings() {
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);  // Default 0xCA
  Serial.print("Display Power Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);  // Default 0x24
  Serial.print("MADCTL Mode: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x");  // Default 0x2;
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);  // Default 0xC0
  Serial.print("Image Format: 0x");
  Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);  // Default 0xE0
  Serial.print("Self Diagnostic: 0x");
  Serial.println(x, HEX);
}
