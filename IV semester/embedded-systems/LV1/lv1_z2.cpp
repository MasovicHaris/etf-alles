#include "mbed.h"

DigitalOut myled1 = LED1;
DigitalOut myled2 = LED2;
DigitalOut myled3 = LED3;

int main() {
    int timer = 1000;
    while(1) {
        myled3 = 1;
        myled1 = 0;
        wait_ms(timer);
        myled1=1;
        myled2=0;
        wait_ms(timer);
        myled2=1;
        myled3=0;
        wait_ms(timer);
        if(timer>100)timer-=100;
    }
}
