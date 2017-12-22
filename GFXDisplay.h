// Licensed under the MIT license. 

#ifndef __GFX_DISPLAY_H__
#define __GFX_DISPLAY_H__

#include <Arduino.h>
#include <OledDisplay.h>

class GFXDisplay : public OLEDDisplay
{
  protected:
    // Off-screen buffer, each consecutive byte is an 8-pixel *column*
    // proceeding from the LHS
    byte _buffer[1024];

  public:
    // Display size constants
    static const int WIDTH = 128;
    static const int HEIGHT = 64;

    // Font size constants
    static const int FONT_WIDTH; 
    static const int FONT_HEIGHT;

    /**
     * @brief Clear the off-screen buffer. Will not clear the display until 
     * flush() is called.
     */
    void clear();

    /**
     * @brief Copy the contents of the off-screen buffer to the display
     */
    void flush();

    /**
     * @brief Set the pixel at x,y. Origin (0,0) is top left corner
     */
    void setPixel(int x, int y);

    /**
     * @brief Write text at position x,y. font.h provides the font definition
     */
    void drawText(int x, int y, const char *s);

    /**
     * @brief Draw line from x0,y0 to x1,y1
     */
    void drawLine(int x0, int y0, int x1, int y1);

    /**
     * @brief Draw rect with defined by top-left x0,y0 to bottom-right x1,y1
     */
    void drawRect(int x0, int y0, int x1, int y1);

    /**
     * @brief Draw circle of radius r centred on xm,ym
     */
    void drawCircle (int xm, int ym, int r);

    /**
     * Draw bitmap of dimensions w*h at position x,y
     * bmp is an array of 1's or 0's
     */
    void drawBitmap(int x, int y, int w, int h, const byte *bmp);
};

#endif