#include "mbed.h"

# define dp23 P0_0 

BusOut display(dp26,dp27,dp5,dp6,dp28,dp4,dp18); // stavila samo 7 ovih
DigitalOut digitMux[]={dp25,dp24,dp23};//od nize ka visoj valjda
int masks[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

void display_number(int value){
    int digit_place=0; //na kojoj cifri broja se nalazim
    do{
        digitMux[0] = 1;
        digitMux[1] = 1;
        digitMux[2] = 1; 
        //if(digit_place) digitMux[digit_place-1]=1;//iskljucujemo staru cifru ako sam na vecim ciframa
        int digit=value%10;
        value/=10;
        digitMux[digit_place]=0; //ukljucujemo odgovarajucu cifru
        display=masks[digit]; 
        digit_place++;
        wait_ms(8);  //ono kratko da se mijenjaju           
    }while(value); //no leading zeroes
}



void display_number_Leading(int value){
    int digit_place=0; //na kojoj cifri broja se nalazim
    for(int i=0;i<3;i++){
        digitMux[0] = 1;
        digitMux[1] = 1;
        digitMux[2] = 1;
       // if(digit_place) digitMux[digit_place-1]=1;//iskljucujemo staru cifru ako sam na vecim ciframa
        int digit=value%10;
        value/=10;
        digitMux[digit_place]=0; //ukljucujemo odgovarajucu cifru
        display=masks[digit]; 
        digit_place++;
        wait_ms(8); 
        }  
}

/****************************/

InterruptIn startStopBtn(dp1);
InterruptIn restartBtn(dp2);

Timer debouncer1;
Timer debouncer2;
Ticker ticker;

int timer = 0;
bool running = false;
const int dbncTimeoutMs = 200;

void tick() {
    if(running) {
        timer = (timer+1)%1000;
    }
    display_number_Leading(timer);
}

void toggleTimer() {
    if(debouncer1.read_ms() > dbncTimeoutMs) {
        running = !running;
        debouncer1.reset();
    }
}

void restartTimer() {
    if(debouncer2.read_ms() > dbncTimeoutMs) {
        running = false;
        timer = 0;
        debouncer2.reset();
    }
}

int main() {
    debouncer1.start();
    debouncer2.start();
    startStopBtn.rise(&toggleTimer);
    restartBtn.rise(&restartTimer);
    ticker.attach(&tick, 0.1);
}
