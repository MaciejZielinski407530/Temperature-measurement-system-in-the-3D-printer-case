#ifndef Sensor_h
#define Sensor_h

// Sensor address length
#define ADDRESS_SIZE 8

///////////////////////////////////////////////////////////
// This class implements address and teperature for sensor
///////////////////////////////////////////////////////////
class Sensor{
  private:
    uint8_t faddress[ADDRESS_SIZE];   // 64-bits address
    float ftemperature;               // Value of temperature
  public:
    //Constructor
    Sensor();
    //Getters and Setters for Sensor class
    void set_temp(float temperature);
    float get_temp() const;
    void set_address(uint8_t address[]);
    const uint8_t* get_address() const;
};

#endif // Sensor_h