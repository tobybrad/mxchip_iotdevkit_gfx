#include <Arduino.h>
#include "GFXDisplay.h"

#include "azure_logo.h"
#include "msft_azure.h"

GFXDisplay display;

void setup() {
  display.init();
}

void loop() {

  int dir = 1;
  const char *msg = "@tobecodex";
  int textLen = strlen(msg) * display.FONT_WIDTH, margin = 2, x = margin;

  while (1) {

    display.clear();

    int HDR_HEIGHT = 16;

    // Border round header (yellow) area
    display.drawRect(0, 0, display.WIDTH - 1, HDR_HEIGHT - 1);

    // Border round main (blue) area
    display.drawRect(0, HDR_HEIGHT, display.WIDTH - 1, display.HEIGHT - 1);

    // Draw a big 'X' across main area 
    display.drawLine(x, HDR_HEIGHT, display.WIDTH - x, display.HEIGHT);
    display.drawLine(display.WIDTH - x, HDR_HEIGHT, x, display.HEIGHT);

    // Circle centred in the main area
    display.drawCircle(display.WIDTH / 2, (HDR_HEIGHT + display.HEIGHT) / 2, 16);

    // Show a message in the header area
    display.drawText(x, (HDR_HEIGHT / 2) - (display.FONT_HEIGHT / 2), msg);

    // Bitmap on lhs    
    int BITMAP_WIDTH = 35;
    int BITMAP_HEIGHT = 16;
    
    display.drawBitmap(
      4, ((HDR_HEIGHT + display.HEIGHT) / 2) - (BITMAP_HEIGHT / 2), 
      BITMAP_WIDTH, BITMAP_HEIGHT, 
      msft_azure
    );

    // Bitmap on rhs
    BITMAP_WIDTH = 19;
    BITMAP_HEIGHT = 20;

    display.drawBitmap(
      100, ((HDR_HEIGHT + display.HEIGHT) / 2) - (BITMAP_HEIGHT / 2), 
      BITMAP_WIDTH, BITMAP_HEIGHT, 
      azure_logo
    );

    display.flush();
    
    x += dir;
    if (x <= margin || x >= display.WIDTH - margin - textLen)
      dir *= -1;
  }
}