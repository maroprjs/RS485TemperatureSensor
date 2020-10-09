/**
 *  @file		RS485TemSensorSample.ino
 *
 *  @author		maro
 *  @date		mm/dd/yyyy
 *  @version	x.y
 *
 *  @brief 		Main
 *
 *  @section DESCRIPTION
 *
 *  This example shows how to use the RS485TemperatureSensor library
 *
 *  used libraries and references:
 *  	-Modbus https://github.com/maroprjs/modbus 

 *
 */



/////////// INcludes /////////////////
#include "TypeDefs.h"
#include <stdio.h>
#include "Modbus.h"
#include "RS485TemperatureSensor.h"

/////////defines //////////////////////
#define MODBUS_SPEED (9600)
#define PUBLISH_INTERVAL   (1500)

////////// Object Instantiation //////////////////

/******************************************
 * Modbus for Temperature-/Humidity- Sensor
 */
Modbus modbus(0,3,0);//master adrress, serial id, tx pin(not used, this parameter is overwritten in library)


/******************************************
 * RS485 Temperature- and Humidity- Sensor
 */
temperature_t temp = 0;
char str_temp[6];
humidity_t humi = 0;
char str_humi[6];
RS485TemperatureSensor humiditySensor(&modbus, &temp, &humi);

//////// Global primitive variables /////////////////
interval_t publish_interval = PUBLISH_INTERVAL;
elapsedMillis_t currentMillis = 0;
elapsedMillis_t previousMillis = 0;
char measData[512] ;



void setup()
{
	Serial.begin( 9600 );
	modbus.begin(MODBUS_SPEED);
	humiditySensor.setup();
}


void loop()
{

	//////////////////// Let it roll  ////////////////////////////////
	humiditySensor.loop();
	currentMillis = millis();
	if (currentMillis - previousMillis >= publish_interval) {

		/////////////////////   Measurement Reports /////////////////////////
       /****
        *   %.2f not working here due performance...
        *  3 is mininum width, 1 is precision; float value is copied onto str_temp
        */
       dtostrf(temp, 3, 1, str_temp);
       dtostrf(humi, 3, 1, str_humi);
	   sprintf(measData,"{\"topic\":\"meas\",\"temp\":%s,\"humi\":%s}", str_temp, str_humi);
	   //sprintf(measData,"{\"topic\":\"meas\",\"temp\":%.2f,\"humi\":%.2f}", temp, humi, wind);
	   Serial.println(measData);
	   memset(measData, 0, 512);

	   previousMillis = millis();
    }

}
