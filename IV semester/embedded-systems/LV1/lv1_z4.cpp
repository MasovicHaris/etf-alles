#include "mbed.h"

#define dp23 P0_0 

DigitalOut pin14 = dp14;
BusOut diode(dp23, dp24, dp25, dp26, dp27, dp5, dp6, dp28);

int main() {
    pin14 = 0;
    unsigned short cnt = 1;
    while(1) {
        diode = cnt;
        //cnt = cnt << 1;
        wait(1);
        cnt *= 2;
        if(cnt > 256)
            cnt = 1;
    }
}