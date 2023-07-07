#ifndef LCD1602_HPP
#define LCD1602_HPP

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>

#include "pico.h"
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"

#include "I2CMaster/I2C.hpp"

enum lcd_mode{
    command = 0,
    character
};

class LCD1602_I2C : public I2CMaster{
    protected:
        const static int maxlines = 2;
        const static int maxchars = 16;

        // commands
        static const int LCD_CLEARDISPLAY = 0x01;
        static const int LCD_RETURNHOME = 0x02;
        static const int LCD_ENTRYMODESET = 0x04;
        static const int LCD_DISPLAYCONTROL = 0x08;
        static const int LCD_CURSORSHIFT = 0x10;
        static const int LCD_FUNCTIONSET = 0x20;
        static const int LCD_SETCGRAMADDR = 0x40;
        static const int LCD_SETDDRAMADDR = 0x80;

        // flags for display entry mode
        static const int LCD_ENTRYSHIFTINCREMENT = 0x01;
        static const int LCD_ENTRYLEFT = 0x02;

        // flags for display and cursor control
        static const int LCD_BLINKON = 0x01;
        static const int LCD_CURSORON = 0x02;
        static const int LCD_DISPLAYON = 0x04;

        // flags for display and cursor shift
        static const int LCD_MOVERIGHT = 0x04;
        static const int LCD_DISPLAYMOVE = 0x08;

        // flags for function set
        static const int LCD_5x10DOTS = 0x04;
        static const int LCD_2LINE = 0x08;
        static const int LCD_8BITMODE = 0x10;

        // flag for backlight control
        static const int LCD_BACKLIGHT = 0x08;

        static const int LCD_ENABLE_BIT = 0x04;

        void toggle_enable(uint8_t val, int mode) {
            // Toggle enable pin on LCD display
            // We cannot do this too quickly or things don't work
            assert(mode == 0 || mode == 1);
            const int delay = (mode == character ? 0 : 600); //no delay needed if sending characters? check this later
            sleep_us(delay);
            this->write_byte(val | LCD_ENABLE_BIT);
            sleep_us(delay);
            this->write_byte(val & ~LCD_ENABLE_BIT);
            sleep_us(delay);
        }

        // The display is sent a byte as two separate nibble transfers
        void send_byte(uint8_t val, int mode) {
            uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
            uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

            this->write_byte(high);
            toggle_enable(high, mode);
            this->write_byte(low);
            toggle_enable(low, mode);
        }

        void send_byte_8bit(uint8_t val, lcd_mode mode){

        }

        void clear() {
            send_byte(LCD_CLEARDISPLAY, command);
        }

    public:
        LCD1602_I2C(const int addr, const int sda = PICO_DEFAULT_I2C_SDA_PIN, const int scl = PICO_DEFAULT_I2C_SCL_PIN)
        : I2CMaster(addr, sda, scl){
            send_byte(0x03, command);
            send_byte(0x03, command);
            send_byte(0x03, command);
            send_byte(0x02, command);

            send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, command);
            send_byte(LCD_FUNCTIONSET | LCD_2LINE, command);
            send_byte(LCD_DISPLAYCONTROL | LCD_DISPLAYON, command);
            clear();
        }

        void display_clear(){
            clear();
            set_cursor(0, 0);
        }

        void set_cursor(int& line, int& position) {
            int val = (line == 0) ? 0x80 + position : 0xC0 + position;
            send_byte(val, command);
        }

        void set_cursor(int line, int position) {
            int val = (line == 0) ? 0x80 + position : 0xC0 + position;
            send_byte(val, command);
        }

        void cursor_blink(bool state){//broken
            //send_byte(, command);
        }

        void cursor_toggle(bool state){ //broken
            send_byte((state ? LCD_CURSORON : 0) | LCD_DISPLAYCONTROL, command);
        }

        void cursor_home(){
            send_byte(LCD_RETURNHOME, command);
        }

        void backlight(bool state){ //broken
            write_byte(LCD_DISPLAYCONTROL | LCD_BACKLIGHT);
        }

        void send_char(char val) {
            send_byte(val, character);
        }

        void send_char(char& val){
            send_byte(val, character);
        }

        void send_string(const char *s) {
            while (*s) {
                send_char(*s++);
            }
        }

        void send_string(const std::string s){
            for(auto& c : s){
                send_char(c);
            }
        }

        void display_scroll_messages(std::vector<std::string>& messages, int delay_ms){
            for(int i = 0; i < messages.size(); i += maxlines){
                for(int line = 0; line < maxlines; i++){
                    set_cursor(line, (maxchars/2) - messages[i + line].size()/2);
                    send_string(messages[i + line]);
                }
                sleep_ms(2000);
                clear();
            }
        }

};

#endif