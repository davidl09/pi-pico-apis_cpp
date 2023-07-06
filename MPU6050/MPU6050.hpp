#include "pico.h"
#include "hardware/i2c.h"

class MPU6050{
    private:
        const int addr;
    public:
        MPU6050(const int busaddr) : addr(busaddr){

        }
};