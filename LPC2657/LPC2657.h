/***************************************************

	Creadted By Yang

	Date: 2016.11.23

****************************************************/


#ifndef ROBERT_LPC2657_H
#define ROBERT_LPC2657_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
	Default I2C Address
-----------------------------------------------------------------------*/
#define LPC2657_ADDRESS         0x10 // CA1, CA2, CA3 all GND
/*=========================================================================*/

#ifndef GND
#define		GND		0
#endif

#ifndef VCC
#define		VCC		1
#endif

#define		FLOAT	2

//These are the definitions for the LT2657 8 Channel DAC Device

#define     LTC_Write					0x00      // Configuration byte set to Write to one registor only
#define     LTC_Update					0x10      // Configuration byte set to Update for one registor only
#define     LTC_Write_one_Update_all	0x20      // Write to one and update all
#define     LTC_One						0x30      // Write and update One
#define     LTC_Down_one				0x40      // Power Down One
#define     LTC_Down_all				0x50      // Power Down All
#define     LTC_Internal				0x60      // Select Internal Ref (default)
#define     LTC_External				0x70      // Select External Ref

#define		DAC_A				0x00
#define		DAC_B				0x01
#define		DAC_C				0x02
#define		DAC_D				0x03
#define		DAC_E				0x04
#define		DAC_F				0x05
#define		DAC_G				0x06
#define		DAC_H				0x07
#define		DAC_ALL				0xFF


#define 	OUTPUT_CIRCUIT_GAIN   4    // Circuit Gain = 4

#define		LPC2567_ADDRESS		0x73

#define		RES_12				0
#define		RES_16				1

#define		LSCALE				0
#define		HSCALE				1
#define		OUTPUT_GAIN			4

class LPC2567 {
public:
	LPC2567(uint8_t CA2, uint8_t CA1, uint8_t CA0, uint8_t Res, uint8_t Scale, uint Gain);
	void WriteCommand(uint8_t nCmd, uint16_t nRegVal);

	void WriteToInputReg(uint8_t nChn, uint16_t nRegVal);

	void UpdateReg(uint8_t nChn, uint16_t nRegVal);

	void WriteoneUpdateall(uint8_t nChn, uint16_t nRegVal);

	void WriteoneUpdateone(uint8_t nChn, uint16_t nRegVal);

	void PowerDownone(uint8_t nChn, uint16_t nRegVal);

	void SelectInternalRef();
	void SelectExternalRef();

	void SetChnProg(uint8_t nChn, float fVol);

	void i2cwrite(uint8_t x);
	uint8_t i2cread(void);

private:
	
	uint8_t nI2CAddr; // I2C Slave Address
	
	uint8_t nScale;
	uint8_t nRes;
	uint8_t nGain;

};


#endif
