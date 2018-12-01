#include <noise.h>
#include <TVout.h>



uint16_t x_off = random(0, 1000);
uint16_t y_off = random(0, 1000);
unsigned char x,y;
uint8_t n;

TVout TV;

void setup() {
  TV.begin(NTSC);
}

void loop() {
  //TV.clear_screen();
  // display.fillScreen(0);          // Clear display
  for(x=0;x<TV.hres();x++){
    for(y=0;y<TV.vres();y++){
      n = inoise8(x_off + (x + TV.hres()), y_off + (y * TV.vres()));
      TV.set_pixel(x,y,round(n / 128));
    }
  }
  y_off += 1000;
  //x_off += 100;
  TV.delay(1000);
}
