#ifndef LCD1602_HPP
#define LCD1602_HPP

#include <cstdio>
#include <cstdlib>

#include "pico.h"
#include "lcd1602.hpp"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

enum lcd_mode{
    command = 0,
    byte
};

class LCD1602_I2C{
    private:
        const int bus_addr;
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

        i2c_inst_t i2c;

    public:
        LCD1602_I2C() : bus_addr(0x27){
            
        }

        LCD1602_I2C(const int address) : bus_addr(address){

        }
};

#endif