
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "Robert_LPC2657.h"

LPC2567::LPC2567(uint8_t CA2 = GND, uint8_t CA1 = GND, uint8_t CA0 = GND, uint8_t Res = RES_16, uint8_t Scale = LSCALE, uint Gain = OUTPUT_GAIN)
{
	// default value
	nI2CAddr = LPC2567_ADDRESS;
	nScale = Scale;
	nRes = Res;
	
	//
	nGain = Gain;

	// Address Mapping
	if ((CA2 == GND && CA1 == GND) && CA0 == GND)
		nI2CAddr = 0x10;
	else if ((CA2 == GND && CA1 == GND) && CA0 == FLOAT)
		nI2CAddr = 0x11;
	else if ((CA2 == GND && CA1 == GND) && CA0 == VCC)
		nI2CAddr = 0x12;
	else if ((CA2 == GND && CA1 == FLOAT) && CA0 == GND)
		nI2CAddr = 0x13;
	else if ((CA2 == GND && CA1 == FLOAT) && CA0 == FLOAT)
		nI2CAddr = 0x20;
	else if ((CA2 == GND && CA1 == FLOAT) && CA0 == VCC)
		nI2CAddr = 0x21;
	else if ((CA2 == GND && CA1 == VCC) && CA0 == GND)
		nI2CAddr = 0x22;
	else if ((CA2 == GND && CA1 == VCC) && CA0 == FLOAT)
		nI2CAddr = 0x23;
	else if ((CA2 == GND && CA1 == VCC) && CA0 == VCC)
		nI2CAddr = 0x30;
	else if ((CA2 == FLOAT && CA1 == GND) && CA0 == GND)
		nI2CAddr = 0x31;
	else if ((CA2 == FLOAT && CA1 == GND) && CA0 == FLOAT)
		nI2CAddr = 0x32;
	else if ((CA2 == FLOAT && CA1 == GND) && CA0 == VCC)
		nI2CAddr = 0x33;
	else if ((CA2 == FLOAT && CA1 == FLOAT) && CA0 == GND)
		nI2CAddr = 0x40;
	else if ((CA2 == FLOAT && CA1 == FLOAT) && CA0 == FLOAT)
		nI2CAddr = 0x41;
	else if ((CA2 == FLOAT && CA1 == FLOAT) && CA0 == VCC)
		nI2CAddr = 0x42;
	else if ((CA2 == FLOAT && CA1 == VCC) && CA0 == GND)
		nI2CAddr = 0x43;
	else if ((CA2 == FLOAT && CA1 == VCC) && CA0 == FLOAT)
		nI2CAddr = 0x50;
	else if ((CA2 == FLOAT && CA1 == VCC) && CA0 == VCC)
		nI2CAddr = 0x51;
	else if ((CA2 == VCC && CA1 == GND) && CA0 == GND)
		nI2CAddr = 0x52;
	else if ((CA2 == VCC && CA1 == GND) && CA0 == FLOAT)
		nI2CAddr = 0x53;
	else if ((CA2 == VCC && CA1 == GND) && CA0 == VCC)
		nI2CAddr = 0x60;
	else if ((CA2 == VCC && CA1 == FLOAT) && CA0 == GND)
		nI2CAddr = 0x61;
	else if ((CA2 == VCC && CA1 == FLOAT) && CA0 == FLOAT)
		nI2CAddr = 0x62;
	else if ((CA2 == VCC && CA1 == FLOAT) && CA0 == VCC)
		nI2CAddr = 0x63;
	else if ((CA2 == VCC && CA1 == VCC) && CA0 == GND)
		nI2CAddr = 0x70;
	else if ((CA2 == VCC && CA1 == VCC) && CA0 == FLOAT)
		nI2CAddr = 0x71;
	else if ((CA2 == VCC && CA1 == VCC) && CA0 == VCC)
		nI2CAddr = 0x72;
}

void LPC2657::SetChnProg(uint8_t nChn, float fVol)
{
	uint16_t nIval;
	fVol /= nGain;
	fVol *= 65535.0f;
	if (nScale == LSCALE)
		fVol /= 2.5f;
	else
		fVol /= 4.096f;
	nIval = (uint16_t)fVol;
	if (nRes == RES_12)
		nIval >>= 4;
	WriteoneUpdateone(nChn, nIval);
}

/*
*/
void LPC2567::WriteCommand(uint8_t nCmd, uint16_t nRegVal)
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return;
	}
	uint8_t highbyte, lowbyte;
	highByte = highByte(nRegVal);
	lowbyte = lowByte(nRegVal);

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(nCmd);
	i2cwrite(highByte);
	i2cwrite(lowbyte);
	Wire.endTransmission();
}

/*
*/
void LPC2567::WriteToInputReg(uint8_t nChn, uint16_t nRegVal)
{
	WriteCommand(LTC_Write | nChn, nRegVal);
}

/*
*/
void LPC2567::UpdateReg(uint8_t nChn, uint16_t nRegVal)
{
	WriteCommand(LTC_Update | nChn, nRegVal);
}

/**/
void LPC2567::WriteoneUpdateall(uint8_t nChn, uint16_t nRegVal)
{
	WriteCommand(LTC_Write_one_Update_all | nChn, nRegVal);
}

/**/
void LPC2567::WriteoneUpdateone(uint8_t nChn, uint16_t nRegVal)
{
	WriteCommand(LTC_One | nChn, nRegVal);
}

/*
*/
void LPC2567::PowerDownone(uint8_t nChn, uint16_t nRegVal)
{
	WriteCommand(LTC_Down_one | nChn, nRegVal);
}

/**/
void LPC2657::SelectInternalRef()
{
	WriteCommand(LTC_Internal | 0x0F, 0);
}

/**/
void LPC2657::SelectExternalRef()
{
	WriteCommand(LTC_External | 0x0F, 0);
}


/**************************************************************************/
/*!
@brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void LPC2567::i2cwrite(uint8_t x)
{
#if ARDUINO >= 100
	Wire.write((uint8_t)x);
#else
	Wire.send(x);
#endif
}

/**************************************************************************/
/*!
@brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
uint8_t LPC2567::i2cread(void)
{
#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}