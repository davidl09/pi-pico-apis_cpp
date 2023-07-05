#include "lcd1602.hpp"

#include <vector>
#include <string>


int main(void){
    LCD1602_I2C screen(0x27, 4, 5);
    screen.set_cursor(1, 8);
    //screen.cursor_toggle(true);
    //screen.cursor_blink(true);
    while(1){
        screen.send_string("Test 1\n");
        break;
    }
}

