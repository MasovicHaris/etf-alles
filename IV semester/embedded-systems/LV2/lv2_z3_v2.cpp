#include "mbed.h"

#define dp23 P0_0

BusOut rows(dp16, dp15, dp17, dp18);
BusIn cols(dp9, dp10, dp11, dp13);
BusOut sevSeg(dp17, dp26, dp27, dp5, dp6, dp28, dp4, dp18);
BusOut digitNo(dp23, dp24, dp25);

unsigned char lookup[11] = { 63, 6, 91, 79, 102, 109, 125, 7, 127, 111, 0};
unsigned char keyboard[16] = {'1', '2', '3', 'A',
                              '4', '5', '6', 'B',
                              '7', '8', '9', 'C',
                              '*', '0', '#', 'D'};

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

char getKeyboardInput() {
    for(char i = 0; i < 4; i++) {
        rows = 1 << i;
        char c = cols;
        char pos = i * 4;
        if(c == 1) {
            return keyboard[pos + 0];
        }else if(c == 2) {
            return keyboard[pos + 1];
        }else if(c == 4) {
            return keyboard[pos + 2];
        }else if(c == 8) {
            return keyboard[pos + 3];
        }
    }
    
    return 0;
}


int main() {
    int number = 0;
    while(1) {
        char key = getKeyboardInput();
        // ako je cifra, upisi je u number, ako se moze pisati dalje
        if(key >= '0' && key <= '9' && number < 999)
            number = number*10 + key - '0';
        else if(key == 'C')
            number = 0;
        displayNumber(number);
    }
}
