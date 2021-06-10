#include "mbed.h"
#include "N5110.h"
#include "stdio.h"

#define dp23 P0_0

// N5110 lcd ( VCC , SCE , RST , DC , MOSI , SCLK , LED ));
N5110 lcd(dp4, dp24, dp23, dp25, dp2, dp6, dp18);
DigitalOut enable(dp14);

AnalogIn potenciometar(dp9);

int main() {
    // deaktivacija LEDa
    enable = 1;
    
    // inicijalizacija displeja
    lcd.init();
    
    while(1) {
        // prikaz vrijednosti
        /*char output[25];
        sprintf(output, "%fV", potenciometar.read());
        wait(0.02);*/
        // lcd.clear(); // treba vjerovatno clear uraditi prije pisanja!!!
        lcd.printString("aaa", 8, 8);
        // lcd.refresh(); // treba li refresh raditi nakon pisanja???
        wait(0.02);
    }
}


/*
# include " mbed . h "
# include " N5110 . h "
# define dp23 P0_0
// N5110 lcd ( VCC , SCE , RST , DC , MOSI , SCLK , LED ));
N5110 lcd ( dp4 , dp24 , dp23 , dp25 , dp2 , dp6 , dp18 );
DigitalOut enable ( dp14 );
*/