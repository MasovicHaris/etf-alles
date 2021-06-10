#include "mbed.h"

#define dp23 P0_0

// dark -> 29 kohm
// light -> 0.34 kohm

BusOut leds(dp23, dp24, dp25, dp26, dp27, dp5, dp6, dp28);
AnalogIn photo(dp9);
DigitalOut enable(dp14);

int period_ms = 5;
float t = 0;

int main() {
    enable = 0; // ?
    
    while(1) {
        t = 2.30696 * photo.read() - 1.28567;
        
        leds = 255;
        wait_ms(t * period_ms);
        leds = 0;
        wait_ms((1-t)*period_ms);
    }
}
