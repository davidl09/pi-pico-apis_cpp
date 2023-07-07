#include "lcd1602.hpp"

#include <string>

inline void timer_screen(LCD1602_I2C* screen, time_t time){
    screen->set_cursor(0, 4);
    screen->send_string(std::to_string((time/1000000)/60) + ":" + std::to_string((time/1000000)%60) + ":" + std::to_string((time/1000)%1000) + "     ");
    
}


int main(void){
    LCD1602_I2C screen(0x27, 4, 5);
    screen.set_cursor(0, 0);
    gpio_init(14);
    gpio_set_input_enabled(14, true);
    gpio_init(15);
    gpio_set_input_enabled(15, true);
    gpio_init(16);
    gpio_set_input_enabled(16, true);
    
    int clicks = 0;
    time_t start = time_us_64();
    time_t counting = 0;
    screen.set_cursor(1, 6);
    screen.send_string(">|#");
    timer_screen(&screen, 0);
    
    while (true){
        while (gpio_get(14)){
            timer_screen(&screen, 0);
            
            while(gpio_get(14)){
                start = time_us_64();
                break;
            }
            break;
        }
        while(gpio_get(15)){
            counting = time_us_64();
            while(gpio_get(15));
            start += counting - time_us_64();
        }
        while (gpio_get(16)){
            timer_screen(&screen, (time_us_64() - start));
            while(gpio_get(16));
            while(!(gpio_get(16))); //wait until second press to reset
            start = time_us_64();
            screen.display_clear();
            screen.set_cursor(1, 6);
            screen.send_string(">|#");
            timer_screen(&screen, 0);
            while(!gpio_get(14));
            break;
        }
        timer_screen(&screen, time_us_64() - start);

        
    }
}

