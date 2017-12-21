/***************************************************

	Creadted By Yang

	Date: 2016.11.23

****************************************************/


#ifndef ROBERT_ADS1112_H
#define ROBERT_ADS1112_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
	Default I2C Address
-----------------------------------------------------------------------*/
#define ADS1112_ADDRESS         0x48 // A0, A1 all GND
/*=========================================================================*/

#ifndef GND
#define		GND		0
#endif

#ifndef VCC
#define		VCC		1
#endif

#ifndef FLOAT
#define		FLOAT	2
#endif

#define 	ADS1112_REF   2.048F    // ADS1112 reference = 2.048V

#define 	INPUT_CIRCUIT_GAIN   5.22    // Circuit divide = 0.19156 Therefore to compinsate Gain = 5.22

#define		SPS240	0
#define		SPS60	1
#define		SPS30	2
#define		SPS15	3

#define		SINGLECONV		1
#define		CONTICONV		0

// Channel definitions
#define		AIN0_AIN1		0
#define		AIN2_AIN3		1
#define		AIN0_AIN3		2
#define		AIN1_AIN3		3

#define		GAIN1			1
#define		GAIN2			2
#define		GAIN4			4
#define		GAIN8			8

class ADS1112 {
public:
	ADS1112(uint8_t A0, uint8_t A1);

	void GerneralReset();
	bool ReadDeviceInfo();

	void Setup(uint8_t Chn, uint8_t dataRate, uint8_t Mode, uint8_t Gain);

	void SetDataRate(uint8_t DataRate);
	void SetChannel(uint8_t Chn);
	void SetMode(uint8_t Mode);
	void SetPGA(uint8_t Gain);

	void WriteConfig();

	void i2cwrite(uint8_t x);
	uint8_t i2cread(void);

	float GetVoltage();

private:
	
	uint8_t nI2CAddr; // I2C Slave Address
	
	// Config data
	uint8_t nPGA;
	uint8_t nDataRate;
	uint8_t nMode;
	uint8_t nChn;
	int16_t nOutputCode;
};


#endif
