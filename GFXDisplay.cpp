#include "GFXDisplay.h"

#include "font.h"
#include <Arduino.h>

const int GFXDisplay::FONT_WIDTH = ::FONT_WIDTH;
const int GFXDisplay::FONT_HEIGHT = ::FONT_HEIGHT;

void GFXDisplay::clear()
{
  memset(_buffer, 0, sizeof(_buffer));
}

void GFXDisplay::flush()
{
  // Copy the back buffer to screen
  draw(0, 0, 128, 8, _buffer);
}

void GFXDisplay::setPixel(int x, int y)
{
  // Simple clipping
  if (x < 0 || x >= WIDTH || y < 0 || y > HEIGHT)
    return;

  // Calc the byte idx we're going to update
  int _byte = x + ((y >> 3) * WIDTH);

  // Appears to be either a driver or firmware bug whereby byte 127 is written to column
  // 0 on the display and everything else is shifted up one (so byte 0 is col 1 etc)
  // Fix that here.. 
  if (_byte % 128 == 0) {
    _byte += 127;
  }
  else {
    _byte -= 1;
  }

  // Set the corresponding bit
  _buffer[_byte] |= 0x01 << (y % 8);
}

void GFXDisplay::drawText(int x, int y, const char *s)
{
  // Font definition from front.h. Just replace to use a different font
  while (*s != 0) {
    char *c = font[(*s) - 0x20];
    for (int _y = 0; _y < FONT_HEIGHT; _y++) {
      for (int _x = 0; _x < FONT_WIDTH; _x++) {
        if (c[_y] & (0x01 << _x)) {
          setPixel(x + _x, y + _y);
        }
      }
    }
    x += FONT_WIDTH;
    s++;
  }
}

void GFXDisplay::drawLine(int x0, int y0, int x1, int y1)
{
  // With credit to https://gist.github.com/bert/1085538

  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */

  for (;;){  /* loop */
    setPixel(x0, y0);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void GFXDisplay::drawRect(int x0, int y0, int x1, int y1)
{
  drawLine(x0, y0, x0, y1);
  drawLine(x0, y1, x1, y1);
  drawLine(x1, y1, x1, y0);
  drawLine(x1, y0, x0, y0);
}

void GFXDisplay::drawCircle(int xm, int ym, int r)
{
  // With credit to https://gist.github.com/bert/1085538

  int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
  do {
    setPixel(xm-x, ym+y); /*   I. Quadrant */
    setPixel(xm-y, ym-x); /*  II. Quadrant */
    setPixel(xm+x, ym-y); /* III. Quadrant */
    setPixel(xm+y, ym+x); /*  IV. Quadrant */
    r = err;
    if (r >  x) err += ++x*2+1; /* e_xy+e_x > 0 */
    if (r <= y) err += ++y*2+1; /* e_xy+e_y < 0 */
  } while (x < 0);
}

void GFXDisplay::drawBitmap(int x, int y, int w, int h, const byte *bmp)
{
  // bmp is an array of 0's and 1's *not* RGB values
  // We definitely could be more efficient here

  for (int i = 0; i < w * h; i++) {
    if (bmp[i]) {
      setPixel(x + (i % w), y + (i / w));
    }
  }
}
