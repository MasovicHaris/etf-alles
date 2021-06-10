#include "mbed.h"

Serial pc(USBTX, USBRX); // tx, rx
Serial wifi(PTE0,PTE1);

char pc_char, wifi_char;

int main() {
    pc.baud(115200);
    wifi.baud(115200);
    while(1) {
        
        if(pc.readable()) {
            pc_char=pc.getc();
            wifi.putc(pc_char);
        }
        if (wifi.readable()) {
            wifi_char=wifi.getc();
            pc.putc(wifi_char);
        }
    }
}