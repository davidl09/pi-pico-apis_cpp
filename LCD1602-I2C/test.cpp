#include "lcd1602.hpp"

#include <vector>
#include <string>


int main(void){
    LCD1602_I2C screen(0x27, 4, 5);

    screen.set_cursor(0, 0);
    while(1){
        for(int i = 0; i < 128; i++){
            if(i % 16 == 0) screen.set_cursor(i % 32 == 0 ? 0 : 1, 0);
            screen.send_char(i);
            sleep_ms(250);
        }
    }
}

