/*
 * RS485TemperatureSensor.h
 *
 *  Created on: 17 Feb 2020
 *      Author: maro
 */

#ifndef RS485TEMPERATURESENSOR_H_
#define RS485TEMPERATURESENSOR_H_

#include "TypeDefs.h"
#include "Modbus.h"

#define DEFAULT_MEASUREMENT_INTERVAL 500

//#define version1

//#ifdef version1
//   #define  HUM_SENSOR_ADDRESS 2 // slave address
//   #define  HUM_FUNCTION_CODE 4 // function code
//   #define  HUM_START_ADDRESS 1 // start address
//   #define  HUM_NUM_OF_REQUESTED_REGISTERS 2 //number of elements (coils or registers) to read -temp & humi
//#else
   #define  HUM_SENSOR_ADDRESS 2 // slave address
   #define  HUM_FUNCTION_CODE 3 // function code
   #define  HUM_START_ADDRESS 0 // start address
   #define  HUM_NUM_OF_REQUESTED_REGISTERS 2 //number of elements (coils or registers) to read -temp & humi

//#endif

class RS485TemperatureSensor {
public:
	RS485TemperatureSensor(Modbus* modbus, temperature_t* temp, humidity_t* humi, interval_t interval = DEFAULT_MEASUREMENT_INTERVAL);
	void setup();
	void loop();
	virtual ~RS485TemperatureSensor();

private:
	temperature_t* _temp;
	humidity_t* _humi;
	Modbus* _modbus;
	uint8_t _u8state;
	modbus_t _request;
	uint16_t _response[HUM_NUM_OF_REQUESTED_REGISTERS]; //query response on modbus
	elapsedMillis_t _elapsedTime;
	interval_t _measurementInterval;
	temperature_t _temp10;
	humidity_t _humi10;
};

#endif /* RS485TEMPERATURESENSOR_H_ */

