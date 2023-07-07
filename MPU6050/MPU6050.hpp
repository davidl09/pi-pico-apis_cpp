#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "pico.h"
#include "hardware/i2c.h"

#include "I2CMaster/I2C.hpp"

struct MPU_data{
    int16_t accel[3];
    int16_t gyro[3];
    int16_t temp;
};

class MPU6050{
    private:
        const int addr;
    public:
        MPU6050(const int busaddr = 0x68) : addr(busaddr){
            uint8_t buf[] = {0x6B, 0x80};
            i2c_write_blocking(i2c_default, addr, buf, 2, false);
        }

        MPU_data read_all_raw(){
            uint8_t buffer[6];
            MPU_data retval;
            uint8_t val = 0x3B;
            i2c_write_blocking(i2c_default, addr, &val, 1, true); // true to keep master control of bus
            i2c_read_blocking(i2c_default, addr, buffer, 6, false);
            for (int i = 0; i < 3; i++) {
                retval.accel[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
            }

            // Now gyro data from reg 0x43 for 6 bytes
            // The register is auto incrementing on each read
            val = 0x43;
            i2c_write_blocking(i2c_default, addr, &val, 1, true);
            i2c_read_blocking(i2c_default, addr, buffer, 6, false);  // False - finished with bus

            for (int i = 0; i < 3; i++) {
                retval.gyro[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);;
            }

            // Now temperature from reg 0x41 for 2 bytes
            // The register is auto incrementing on each read
            val = 0x41;
            i2c_write_blocking(i2c_default, addr, &val, 1, true);
            i2c_read_blocking(i2c_default, addr, buffer, 2, false);  // False - finished with bus

            retval.temp = buffer[0] << 8 | buffer[1];
        }
};

#endif