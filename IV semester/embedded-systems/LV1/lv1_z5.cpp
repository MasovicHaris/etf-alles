#include "mbed.h"

DigitalOut led = LED1;

int main() {
    double t = 0.005;
    double change = 0.9/30;
    double k = 1;
    
    while(1) {
        if(k>1.9||k<1)change = - change;
        led = 0;
        wait(k*t);
        k+=change;
        led=1;
        wait((2-k)*t);
    }
}
