# mxchip_iotdevkit_gfx
Enable simple graphics on the MXCHIP IoT DevKit OLED display

## Intro

The [MXCHIP IoT DevKit](http://mxchip.com/az3166) is pretty cool but out of the box its [display capabilities](https://microsoft.github.io/azure-iot-developer-kit/docs/apis/display/) are pretty basic. It does have bitmap capabilities though so it seemed to me we should be able to use that get us a pixel-addressable display. Long story short, it took a bit of figuring out but here that is...

## Demo

<a href="http://www.youtube.com/watch?feature=player_embedded&v=fnjp_DWiCbQ
" target="_blank"><img src="http://img.youtube.com/vi/fnjp_DWiCbQ/0.jpg" 
alt="MXCHIP IoT DevKit Graphics Demo" width="240" height="180" border="10" /></a>

## Basic usage

```cpp
#include "GFXDisplay.h"

GFXDisplay display; // Don't call this Screen, you'll get link confusion

void setup() {
    display.init();
    display.setPixel(0, 0);
    display.flush(); // <- Nothing on screen until this
}

void loop() {
    // etc
}
```

## API

```cpp
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
```

## Acknowledgements

Full credit to [https://gist.github.com/bert] for the Bresenham drawing implementation. Thanks!!
