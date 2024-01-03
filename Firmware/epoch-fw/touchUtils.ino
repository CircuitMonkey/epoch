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

