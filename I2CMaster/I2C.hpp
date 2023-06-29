#ifndef _I2C_HPP
#define _I2C_HPP

#include <cstdio>

#include "pico.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

class I2CMaster{
    private:
        i2c_inst_t* i2c;
        const int bus_addr;
        static int num_busy_i2c;

    public:
        I2CMaster(int addr, int sda = PICO_DEFAULT_I2C_SDA_PIN, int scl = PICO_DEFAULT_I2C_SCL_PIN) : bus_addr(addr){
            assert(num_busy_i2c < 2 && num_busy_i2c >= 0);
            i2c = (num_busy_i2c == 0 ? i2c0 : i2c1);
            i2c_init(i2c, 100 * 1000);
            gpio_set_function(sda, GPIO_FUNC_I2C);
            gpio_set_function(scl, GPIO_FUNC_I2C);
            gpio_pull_up(sda);
            gpio_pull_up(scl);

            // Make the I2C pins available to picotool
            bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
        }

        ~I2CMaster(){
            i2c_deinit(this->i2c);
        }

        void write_byte(uint8_t value){
            i2c_write_blocking(i2c, bus_addr, &value, 1, false);
        }

        void write_byte(uint8_t *value){
            i2c_write_blocking(i2c, bus_addr, value, 1, false);
        }

        void write_bytes(uint8_t value, int len){
            i2c_write_blocking(i2c, bus_addr, &value, len, false);
        }

        void write_bytes(uint8_t *value, int len){
            i2c_write_blocking(i2c, bus_addr, value, len, false);
        }
};

#endif