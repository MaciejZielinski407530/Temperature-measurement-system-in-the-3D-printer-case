
#include "Arduino.h"
#include <func.h>

// Pinout for digits on LED display
int digitPins[DIGITS_NUM]={12,9,6};
// Pinout for LED
int LedPins[LED_NUM] = {18,17,16,15,19};

void display_Init(SevenSeg *display){
  display->setCommonAnode();                    // Set display with common anode
  display->setDigitPins(DIGITS_NUM,digitPins);  // Set digits pins
  display->setDPPin(DOT_PIN);                   // Set dot pin
  display->setTimer(2);                         // Set Timera 2
  display->startTimer();                        // Start Timer 2
}

void find_sensor(DS18B20 *DQ, Sensor *Sens, SevenSeg *display){ 
  uint8_t addr_temp[ADDRESS_SIZE];
  for (int i = 0; i < SENSORS_NUM; i++){
    if(DQ->selectNext()!=0){            // If find next sensor, save address to the appropriate Sesnsor.faddress
      DQ->getAddress(addr_temp);
      (Sens+i)->set_address(addr_temp);
    }
    else{
      display->write("ER1");            // If find less address than number of sensor, print error code on display
      break;
    }
  }
}

void Led_Init(){
  for (uint8_t i=0; i < LED_NUM; i++){
    pinMode(LedPins[i], OUTPUT);      // Set Led pins as output
  } 
}

void Led_OFF(){
  for (uint8_t i=0; i < LED_NUM; i++){
    digitalWrite(LedPins[i], LOW);    // Set Led output to LOW state
  } 
}

uint8_t readTemp(DS18B20 *DQ, Sensor *Sens){
  if(DQ->select(Sens->get_address())!=0){ 
    Sens->set_temp(DQ->getTempC());         // Reat temperature if sensor is available
    return 1;
  }
  return 0;
}

void print_value(uint8_t sens_num, Sensor *Sens, SevenSeg *display){
  Led_OFF();
  digitalWrite(LedPins[sens_num], HIGH);    // Turn ON the appropriate LED
  display->write(Sens->get_temp());         // Print temmperature value on display
}

void print_mean_value(DS18B20 *DQ, Sensor *Sens, SevenSeg *display){
  uint8_t num_available_sesnor = 0;         // Number of available sensors
  Led_OFF();                                // Turn OFF all Leds
  digitalWrite(LedPins[LED_NUM-1], HIGH);   // Turn ON the appropriate LED
  float mean = 0.0;
  for (int i = 0; i < SENSORS_NUM; i++){
    if(readTemp(DQ, Sens+i) == 1){          // Read temperature from all available sensors
      mean+= (Sens+i)->get_temp();
      num_available_sesnor++;
    }   
  }
  mean = mean/num_available_sesnor;         // Count mean value:  MEAN = SUM_TEMP_FROM_ALL_AVAILABLE_SENSORS / NUMBER_OF_AVAILABLE_SENSORS
  display->write(mean);                     // Print result on display
}