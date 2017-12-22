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

    display.drawRect(0, 0, display.WIDTH - 1, HDR_HEIGHT - 1);
    display.drawRect(0, HDR_HEIGHT, display.WIDTH - 1, display.HEIGHT - 1);
  
    display.drawLine(x, HDR_HEIGHT, display.WIDTH - x, display.HEIGHT);
    display.drawLine(display.WIDTH - x, HDR_HEIGHT, x, display.HEIGHT);

    display.drawCircle(display.WIDTH / 2, (HDR_HEIGHT + display.HEIGHT) / 2, 16);

    display.drawText(x, (HDR_HEIGHT / 2) - (display.FONT_HEIGHT / 2), msg);

    int BITMAP_WIDTH = 35;
    int BITMAP_HEIGHT = 16;
    
    display.drawBitmap(
      4, ((HDR_HEIGHT + display.HEIGHT) / 2) - (BITMAP_HEIGHT / 2), 
      BITMAP_WIDTH, BITMAP_HEIGHT, 
      msft_azure
    );

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