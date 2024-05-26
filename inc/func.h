#ifndef Func_h
#define Func_h

#include <SevenSeg.h>
#include <DS18B20.h>
#include <Sensor.h>

// Numbers of digits on display
#define DIGITS_NUM 3
// Numbers of LEDs
#define LED_NUM 5
// Numbers of sensors
#define SENSORS_NUM 4
// Pinout for dot on display
#define DOT_PIN 5


// Pinout for digits on LED display
extern int digitPins[DIGITS_NUM];
// Pinout for LED
extern int LedPins[LED_NUM];

/**
 * @brief 7-segments display initialization
 * @param display Pointer to SevenSeg object
*/
void display_Init(SevenSeg *display);

/**
 * @brief Find each sesnosr's address
 * @param DQ Pointer to DS18B20 object
 * @param Sens Pointer to Sensor object
 * @param display Pointer to SevenSeg object
 *
*/
void find_sensor(DS18B20 *DQ, Sensor *Sens, SevenSeg *display);

/**
 * @brief Led's initialization
 *
*/
void Led_Init();

/**
 * @brief Turn OFF all Leds
 * 
*/
void Led_OFF();

/**
 * @brief Read temperature from sensor
 * @param DQ Pointer to DS18B20 object
 * @param Sens Pointer to Sensor object
 * @return Return 1 on success, 0 on failure
*/
uint8_t readTemp(DS18B20 *DQ, Sensor *Sens);

/**
 * @brief Print temperature value on display
 * @param sens_num Number of sensor, which temperature was reading
 * @param Sens Pointer to Sensor object
 * @param display Pointer to SevenSeg object
 * 
*/
void print_value(uint8_t sens_num, Sensor *Sens, SevenSeg *display);

/**
 * @brief Print mean temperature value on display
 * @param DQ Pointer to DS18B20 object
 * @param Sens Pointer to Sensor object
 * @param display Pointer to SevenSeg object
 *
*/
void print_mean_value(DS18B20 *DQ, Sensor *Sens, SevenSeg *display);

#endif // Func_h