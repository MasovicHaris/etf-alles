#include "mbed.h"
#define dp23 P0_0

Serial pc(USBTX , USBRX);
// prerasporediti pinove!!!
BusOut leds(dp28,dp6,dp5,dp27,dp26,dp25,dp24,dp23);

DigitalOut enable(dp14);

int main() {
    leds = 0;
    enable = 0;
    while(1) {
        char znak = pc.getc();
        int broj = znak - '0';
        if (broj >=0 && broj <= 7)
            leds = 1 << broj;
        wait(0.01);
    }
}