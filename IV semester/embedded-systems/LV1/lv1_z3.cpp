#include "mbed.h"

#define dp23 P0_0 

DigitalOut pin14 = dp14;
BusOut diode(dp23, dp24, dp25, dp26, dp27, dp5, dp6, dp28);
DigitalIn taster1 = dp1;

int main() {
    pin14 = 0;
    unsigned char cnt = 0;
    while(1) {
        diode = cnt;
        if(taster1) {
            cnt--;
        }else {
            cnt++;
        }
        wait(1);
        
    }
}