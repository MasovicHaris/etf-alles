#include "mbed.h"
#define dp23 P0_0

BusOut prikaz1(dp26,dp25,dp24,dp23);
BusOut prikaz2(dp28,dp6,dp5,dp27);

DigitalOut enable(dp14);
InterruptIn taster(dp1);
// DigitalIn taster(dp1);
Timer deb;

const float T(2);
int brojac1(0);
int brojac2(0);

Ticker ticker;

void tick2() {
    if(deb.read_ms() > 100) {
        brojac2=(brojac2+1)%16; 
        prikaz2=brojac2;
        deb.reset();
    }
}

void tick1() {
    brojac1=(brojac1+1)%16;
    prikaz1=brojac1;
    // if(taster) tick2();
}

int main() {
    enable=0;    
    prikaz1=brojac1;
    prikaz2=brojac2;
    deb.start();
    ticker.attach(&tick1, T);
    taster.rise(&tick2);
}