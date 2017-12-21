/***************************************************

	Creadted By Yang

	Date: 2016.11.23

****************************************************/


#ifndef ROBERT_MAX7130_H
#define ROBERT_MAX7130_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
	Default I2C Address
-----------------------------------------------------------------------*/
#define MAX7130_ADDRESS         0x18 // AD1, AD2, AD3 all GND
/*=========================================================================*/

#define		GND		0
#define		VCC		1
#define		SDA		2
#define		SCL		3

//These are the definitions for the MAX7310 Port Expander
#define     MAX7310_IP		0x00    // byte set to the Input Register
#define     MAX7310_OP		0x01    // byte set to the Output Register
#define     MAX7310_POL		0x02	// byte set to the Polarity Register
#define     MAX7310_Config	0x03    // Byte set for Configuration Register
#define     MAX7310_TO		0x04    // Byte set for Timeout Register

#define		ALL				255

class MAX7130 {
public:
	MAX7130(uint8_t AD1, uint8_t AD2, uint8_t AD3);
	
	void SetAllInput();

	void SetAllOutput();

	void SetTimeout(bool bTO);
	uint8_t GetTimeout();
	
	void SetConfiguration(uint8_t nConfigWord);
	uint8_t GetConfiguration();

	void WritePort(uint8_t nNewData);
	uint8_t ReadPort();

	void i2cwrite(uint8_t x);
	uint8_t i2cread(void);

	void SetPolarity(uint8_t nPol);

	uint8_t ConfigWord;
	uint8_t Polarity;

private:

	uint8_t nI2CAddr; // I2C Slave Address
};


#endif
