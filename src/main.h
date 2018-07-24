#ifndef _MAIN_H
#define _MAIN_H


#include "Adafruit_SSD1306.h"
#include "Adafruit_INA219.h"

struct ina_data {
    float shuntvoltage;
    float busvoltage;
    float current_mA;
    float loadvoltage;
    float power_mW;
};


void ina_init(Adafruit_INA219* self);
void display_init(Adafruit_SSD1306* self);
void get_ina_data(Adafruit_INA219* self, ina_data* data);

#endif