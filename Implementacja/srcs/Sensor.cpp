
#include "Arduino.h"
#include "Sensor.h"

Sensor::Sensor(){    
    uint8_t address[ADDRESS_SIZE] = {1,1,1,1,1,1,1,1};
    memcpy(faddress, address, ADDRESS_SIZE);
    ftemperature = 0.0;
}

void Sensor::set_temp(float temperature){
    ftemperature = temperature;
}

float Sensor::get_temp() const{
    return ftemperature;
}

void Sensor::set_address(uint8_t address[]){
  memcpy(faddress, address, ADDRESS_SIZE);
}

const uint8_t* Sensor::get_address() const {
  return faddress;
}