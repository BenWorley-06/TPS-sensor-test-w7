#include "ICM_20948.h" // Click here to get the library: http://librarymanager/All#SparkFun_ICM_20948_IMU
#include "HX711.h"

#define USE_SPI       // Uncomment this to use SPI

#define SPI_PORT SPI // Your desired SPI port.       Used only when "USE_SPI" is defined
#define CS_PIN 2     // Which pin you connect CS to. Used only when "USE_SPI" is defined

#define WIRE_PORT 18 // Your desired Wire port.      Used when "USE_SPI" is not defined
// The value of the last bit of the I2C address.
// On the SparkFun 9DoF IMU breakout the default is 1, and when the ADR jumper is closed the value becomes 0
#define AD0_VAL 1

#ifdef USE_SPI
ICM_20948_SPI myICM; // If using SPI create an ICM_20948_SPI object
#else
ICM_20948_I2C myICM; // Otherwise create an ICM_20948_I2C object
#endif

const uint8_t  DATA_PIN = 2;
const uint8_t CLOCK_PIN = 3;

const int t_delay = 250;

HX711 pressure_sensor; // Sensor Object

void setup()
{
  
  Serial.begin(115200);
  // Pressure Sensor Setup
  pressure_sensor.begin(DATA_PIN,CLOCK_PIN);
  pressure_sensor.set_offset(4019569);
  pressure_sensor.set_scale(-35463.812500);
  pressure_sensor.tare();
  // IMU Setup
  #ifdef USE_SPI
    SPI_PORT.begin();
  #else
    WIRE_PORT.begin();
    WIRE_PORT.setClock(400000);
  #endif

  //myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;
  while (!initialized)
  {

  #ifdef USE_SPI
      myICM.begin(CS_PIN, SPI_PORT);
  #else
      myICM.begin(WIRE_PORT, AD0_VAL);
  #endif

    Serial.print(F("Initialization of the sensor returned: "));
    Serial.println(myICM.statusString());
    if (myICM.status != ICM_20948_Stat_Ok)
    {
      Serial.println("Trying again...");
      delay(500);
    }
    else
    {
      initialized = true;
    }
  }
}

void loop()
{

  if (myICM.dataReady())
  {
    // IMU
    myICM.getAGMT();         // The values are only updated when you call 'getAGMT'
                             //    printRawAGMT( myICM.agmt );     // Uncomment this to see the raw values, taken directly from the agmt structure
    printScaledAGMT(&myICM); // This function takes into account the scale settings from when the measurement was made to calculate the values with units
    // Pressure
    Serial.print(", Pressure: ");
    Serial.println(pressure_sensor.get_units(5));
    delay(t_delay);
  }
  else
  {
    Serial.println("Waiting for IMU data");
    delay(500);
  }
}
