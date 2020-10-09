/*
 * RS485TemperatureSensor.cpp
 *
 *  Created on: 17 Feb 2020
 *      Author: maro
 */

#include "RS485TemperatureSensor.h"
//#include "Debug.h"

RS485TemperatureSensor::RS485TemperatureSensor(Modbus* modbus, temperature_t* temp, humidity_t* humi, interval_t interval) {
	_temp = temp;
	_humi = humi;
	_temp10 = 0;
	_humi10 = 0;
	_modbus = modbus;
	_u8state = 0;
	_measurementInterval = interval;
	_elapsedTime = 0;


}

void RS485TemperatureSensor::setup(){
	//_modbus->begin(MODBUS_SPEED);
	//_modbus->setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over <- default is 1000

	_elapsedTime = millis();


}


void RS485TemperatureSensor::loop() {
	//_elapsedTime = millis();

   switch( _u8state ) {
	  case 0:
	    if (millis() >= (_elapsedTime + _measurementInterval)) _u8state++; // wait state
	    break;
	  case 1:
	    _request.u8id = HUM_SENSOR_ADDRESS; // slave address
	    _request.u8fct = HUM_FUNCTION_CODE; // function code (this one is registers read)
	    _request.u16RegAdd = HUM_START_ADDRESS; // start address in slave
	    _request.u16CoilsNo = HUM_NUM_OF_REQUESTED_REGISTERS; // number of elements (coils or registers) to read
	    _request.au16reg = _response; // pointer to a memory array in the Arduino
	    _modbus->query( _request );
	    _u8state++;
	    break;
	  case 2:
		 _modbus->poll();
		 if (_modbus->getState() == COM_IDLE) {
   	           for (int i = 0; i < HUM_NUM_OF_REQUESTED_REGISTERS; i++){
   	              //DPRINTLN(_response[i]);
   	              _temp10 = _response[0];
   	              _humi10 = _response[1];
   	  	         *_temp = _temp10 / 10;
   	   	         *_humi = _humi10 / 10;

   	           };
		 };
		 _u8state = 0;
		 _elapsedTime = millis() + (rand() % 50 + 50); //random betwen 50 and 100
         break;
   }
}

RS485TemperatureSensor::~RS485TemperatureSensor() {
	// TODO Auto-generated destructor stub
}

