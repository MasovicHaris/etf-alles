#include "mbed.h"
#include "stdio.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28"
#include "font_big.h"

#define dp23 P0_0

// mosi, miso, sclk, cs, reset, dc
SPI_TFT_ILI9341 TFT(dp2, dp1, dp6, dp24, dp23, dp25, "TFT");

int main() {
    int i = 0;
    
    // init
    TFT.claim(stdout);
    TFT.set_orientation(1);
    TFT.background(Blue);
    TFT.foreground(White);
    TFT.cls();
    
    while(1) {
        TFT.set_font((unsigned char*) Arial28x28);
        TFT.locate(10, 10);
        printf("Mi volimo US!");
        wait(2);
        
        TFT.line(0, 0, 100, 0, Green);
        TFT.line(0, 0, 0, 200, Green);
        TFT.line(0, 0, 100, 200, Green);
        
        double s;
        for(i = 0; i < 320; i++) {
            s = 20 * sin((long double) i / 10);
            TFT.pixel(i, 100 + (int)s, Red);
        }
        
        wait(2);
        TFT.cls();
    }
}
