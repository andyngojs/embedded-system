/*
DHT Library 0x03

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  - DHT-11 Library, by Charalampos Andrianakis on 18/12/11
*/


#ifndef DHT_H_
#define DHT_H_

#include <stdio.h>
#include <io.h>

//setup port
#define DHT_DDR			DDRA
#define DHT_PORT		PORTA
#define DHT_PIN			PINA
#define DHT_INPUTPIN	PORTA.0

//sensor type
#define DHT_DHT11		1
#define DHT_DHT22		2
#define DHT_TYPE		DHT_DHT22

//enable decimal precision (float)
#if DHT_TYPE == DHT_DHT11
#define DHT_FLOAT 0
#elif DHT_TYPE == DHT_DHT22
#define DHT_FLOAT 1
#endif

//timeout retries
#define DHT_TIMEOUT 200

//functions
#if DHT_FLOAT == 1
extern int dht_gettemperature(float *temperature);
extern int dht_gethumidity(float *humidity);
extern int dht_gettemperaturehumidity(float *temperature, float *humidity);
#elif DHT_FLOAT == 0
extern int dht_gettemperature(int8_t *temperature);
extern int dht_gethumidity(int8_t *humidity);
extern int dht_gettemperaturehumidity(int8_t *temperature, int8_t *humidity);
#endif

#endif
