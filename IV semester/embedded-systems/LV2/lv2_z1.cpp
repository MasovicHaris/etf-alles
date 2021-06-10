#include "mbed.h"

#define dp23 P0_0

DigitalIn t1 = dp1;
DigitalIn t2 = dp2;
BusOut sevSeg(dp17, dp26, dp27, dp5, dp6, dp28, dp4, dp18);
BusOut digitNo(dp23, dp24, dp25);

unsigned char lookup[10] = { 63, 6, 91, 79, 102, 109, 125, 7, 127, 111 };

void displayNumber(unsigned short int num) {
    // Normalize value
    if(num > 999)
        num = 0;
    
    // 7-seg LED-ovi aktivirani nulama !!!
    
    // cifra jedinica 110
    digitNo = 6;
    sevSeg = ~lookup[num%10];
    num /= 10;
    wait(0.2);
    // cifra desetica 101
    digitNo = 5;
    sevSeg = ~lookup[num%10];
    num /= 10;
    wait(0.2);
    // cifra stotica 011
    digitNo = 3;
    sevSeg = ~lookup[num%10];
    wait(0.2);
}

int main() {
    t1.mode(PullUp);
    t2.mode(PullUp);
    unsigned short int cntr;
    
    while(1) {
        if(t1) {
            cntr++;
            wait(0.03);
            while(t1);
        }else if(t2) {
            cntr--;
            wait(0.03);
            while(t2);
        }
        displayNumber(cntr);
    }
}
