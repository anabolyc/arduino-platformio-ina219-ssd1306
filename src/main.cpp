#define SERIAL_SPEED 57600
#define OLED_RESET 4

#include "main.h"
Adafruit_SSD1306* display = new Adafruit_SSD1306(OLED_RESET);

void setup(void)
{
  #if !_NO_SERIAL_
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    delay(1);
  }       
  #endif 

  display_init(display);
}

void loop(void)
{
  Adafruit_INA219* ina219 = new Adafruit_INA219();
  ina_init(ina219);
  ina_data* data = new ina_data();
  get_ina_data(ina219, data);
  delete ina219;

  #if !_NO_SERIAL_
  Serial.print(F("Bus Voltage:   ")); Serial.print(data->busvoltage); Serial.println(F(" V"));
  Serial.print(F("Shunt Voltage: ")); Serial.print(data->shuntvoltage); Serial.println(F(" mV"));
  Serial.print(F("Load Voltage:  ")); Serial.print(data->loadvoltage); Serial.println(F(" V"));
  Serial.print(F("Current:       ")); Serial.print(data->current_mA); Serial.println(F(" mA"));
  Serial.print(F("Power:         ")); Serial.print(data->power_mW); Serial.println(F(" mW"));
  Serial.println("");
  #endif

  display->clearDisplay();

  display->setCursor(0, 0);
  display->print(F("Vb:"));
  display->print(data->busvoltage);
  display->println(F(" V"));

  display->setCursor(0, 10);
  display->print(F("Vs:"));
  display->print(data->shuntvoltage);
  display->println(F("mV"));

  display->setCursor(0, 20);
  display->print(F("Vl:"));
  display->print(data->loadvoltage);
  display->println(F(" V"));

  display->setCursor(64, 0);
  display->print(F("I:"));
  display->print(data->current_mA);
  display->println(F(" mA"));

  display->setCursor(64, 10);
  display->print(F("P:"));
  display->print(data->power_mW);
  display->println(F(" mW"));

  display->display(); 

  delete data;
  delay(50);
}

void ina_init(Adafruit_INA219* self) {
  // Initialize the ina219->
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  self->begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219->setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  self->setCalibration_16V_400mA();
}

void get_ina_data(Adafruit_INA219* self, ina_data* data) {
  data->shuntvoltage = self->getShuntVoltage_mV();
  data->busvoltage = self->getBusVoltage_V();
  data->current_mA = self->getCurrent_mA();
  data->power_mW = self->getPower_mW();
  data->loadvoltage = data->busvoltage + data->shuntvoltage / 1000;
}

void display_init(Adafruit_SSD1306* self) {
  self->begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the buffer.
  //self->clearDisplay();
  //sswordself->display();

  self->setTextSize(1);
  self->setTextColor(WHITE);
}