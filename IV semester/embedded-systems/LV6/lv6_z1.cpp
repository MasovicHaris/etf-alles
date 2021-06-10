#include "mbed.h"

Serial pc(USBTX, USBRX);
AnalogIn VRx ( dp11 );
AnalogIn VRy ( dp10 );
DigitalIn SW ( dp9 );
 
float lijevo = 1./6; 
float desno = 5./6;
float gore = 5./6;
float dole = 1./6;

int main() {
    
    SW.mode(PullUp);
    
    while(1) {
        if (VRx < lijevo) { 
            pc.printf("Lijevo");
            lijevo = 2./6;
            while(VRx < lijevo);
            
        } 
        else if (VRx > desno) {
            pc.printf("Desno");
            desno = 4./6;
            while(VRx > desno);
        }
        else if (VRy > gore) {
            pc.printf("Dolje");
            gore = 4./6;
            while(VRy > gore);   
        }
        else if (VRy < dole) { 
            pc.printf("Gore");
            dole = 2./6;
            while(VRy < dole);
        }
        else if ((VRx >= lijevo && VRx <= desno) && (VRy >= dole && VRy <= gore)) {
            pc.printf("Centar");
            lijevo = 1./6; 
            desno = 5./6;
            gore = 5./6;
            dole = 1./6;
            while ((VRx >= lijevo && VRx <= desno) && (VRy >= dole && VRy <= gore));
        }
        printf("\n"); //?
        wait(0.01);
    }
}