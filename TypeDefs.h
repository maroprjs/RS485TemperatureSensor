/*
 * TypeDefs.h
 *
 *  Created on: 17 Feb 2020
 *      Author: maro
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <inttypes.h>
#include <Arduino.h>

//typedef unsigned long uint32_t;
//typedef unsigned int uint16_t;

enum ON_OFF_STATE
{
    OFF                   = false,
    ON	                  = true

};

typedef enum ON_OFF_STATE on_off_state_t;

//typedef unsigned char analogDriverPin_t;
typedef uint8_t driverPin_t;
typedef uint8_t sensingPin_t;

typedef int pinSample_t;
typedef uint32_t total_t;
typedef int simpleCount_t;
typedef uint32_t interval_t;
typedef uint32_t elapsedMillis_t;

typedef double humidity_t;
typedef double temperature_t;
typedef double windspeed_t;
//typedef double voltage_t;
//typedef double current_t;
typedef int voltage_t;
typedef int current_t;


#endif /* TYPEDEFS_H_ */
