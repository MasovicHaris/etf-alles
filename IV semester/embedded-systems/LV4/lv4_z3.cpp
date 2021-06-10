#include "mbed.h"

AnalogOut sig(PTE30);
const double pi = 3.14159265359;

int main() {
    double val;
    while(1) {
        for(int i = 0; i < 50; i++) {
            val = sin(i/50.0 * 2 * pi);
            sig = (val/3.3 + 1)/2;
            //wait_us(50);
        }
    }
}
