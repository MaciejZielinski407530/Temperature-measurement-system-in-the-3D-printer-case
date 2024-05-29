#include <SevenSeg.h>
#include <DS18B20.h>
#include <Sensor.h>
#include <func.h>

// Resolution for DS18B20 sensor [bits]
#define DS18B20_RESOLUTION 12
// Pinout DQ for DS18B20 sensors
#define SENSOR_PIN 14
// Pinout for Switch_1
#define S1_PIN 2
// Pinout for Switch_2
#define S2_PIN 3

SevenSeg Display(11,1,4,7,8,10,0);
DS18B20 DQ (SENSOR_PIN);
Sensor Sensor_list[SENSORS_NUM];

volatile bool switch_1_Flag = false;        // Press Switch 1 flag
volatile bool switch_2_Flag = false;        // Press Switch 2 flag
volatile uint8_t press_num = SENSORS_NUM;

void setup(){
  // Set Switch_1 and Switch_2 as INPUT with pullup resistor
  pinMode(S1_PIN, INPUT_PULLUP);
  pinMode(S2_PIN, INPUT_PULLUP);
  
  // LEDs Initialization
  Led_Init();
  // Display Initialization
  display_Init(&Display);

  // Set DS18B20 resolution 
  DQ.setResolution(DS18B20_RESOLUTION);

  // Find each sensors address 
  find_sensor(&DQ, &Sensor_list[0], &Display);

  // Turn ON interrupts for Switch 1 and Switch 2. Trigger: Falling edge
  attachInterrupt(digitalPinToInterrupt(S1_PIN), switch_1_Handler, FALLING);
  attachInterrupt(digitalPinToInterrupt(S2_PIN), switch_2_Handler, FALLING);
  
}

void loop(){
  
 if (switch_1_Flag) {          // If press switch 1, print value of temperature from single sensor
   switch_1_Flag = false;      // Clear Switch 1 flag
    if (press_num >= 0 && press_num <= SENSORS_NUM-1){
      if (readTemp(&DQ, &Sensor_list[press_num]) != 0){             // Print value of temperature, if read was success
        print_value(press_num, &Sensor_list[press_num], &Display);
      }
      else{                                         // If read was failure, print error code on display
        Led_OFF();                                    // Turn OFF all Leds
        digitalWrite(LedPins[press_num], HIGH);       // Turn ON Led which appropriate Sesnsor with problem
        Display.write("ER2");
      }      
    }
 }
 
if (switch_2_Flag) {            // If press switch 2, print mean value of temperature from each sensors
    switch_2_Flag = false;      // Clear Switch 2 flag
    print_mean_value(&DQ, &Sensor_list[0],&Display);
  }

}

void switch_1_Handler(){
  delay(10);                        // Eliminate debouncing
  if(digitalRead(S1_PIN) == LOW){   // Eliminate debouncing cdn.
    switch_1_Flag = true;           // Set Switch 1 flag
    press_num++;
    if(press_num >= SENSORS_NUM){
      press_num = 0;
    }
  } 
}
void switch_2_Handler(){
  delay(10);                        // Eliminate debouncing
  if(digitalRead(S2_PIN) == LOW){   // Eliminate debouncing cdn.
    switch_2_Flag = true;           // Set Switch 2 flag
  }   
}

ISR(TIMER2_COMPA_vect){
  Display.interruptAction();
}
