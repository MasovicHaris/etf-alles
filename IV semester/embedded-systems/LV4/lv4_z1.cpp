#include "mbed.h"

PwmOut led(dp18);
DigitalOut enable(dp14);
AnalogIn pmetar(dp9);

int main() {
    enable = 0;
    int t_ms = 500;
    
    led.period(.5);
    
    while(1) {
        led.write(pmetar.read());
    }
}
