
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "Robert_LPC2657.h"

ADS1112::ADS1112(uint8_t A0 = GND, uint8_t A1 = GND)
{
	nI2CAddr = ADS1112_ADDRESS;
	if (A0 == GND && A1 == GND)
		nI2CAddr = 0x48;
	else if (A0 == GND && A1 == FLOAT)
		nI2CAddr = 0x49;
	else if (A0 == GND && A1 == VCC)
		nI2CAddr = 0x4A;
	else if (A0 == VCC && A1 == GND)
		nI2CAddr = 0x4C;
	else if (A0 == VCC && A1 == FLOAT)
		nI2CAddr = 0x4D;
	else if (A0 == VCC && A1 == VCC)
		nI2CAddr = 0x4E;
	else if (A0 == FLOAT && A1 == GND)
		nI2CAddr = 0x4B;
	else if (A0 == FLOAT && A1 == VCC)
		nI2CAddr = 0x4F;
	nPGA = 1;
	nDataRate = SPS15;
	nMode = CONTICONV;
	nChn = 0;

	nOutputCode = 0;
}

void ADS1112::WriteConfig()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return;
	}

	uint8_t nConfig = 0;
	
	// ADC Start
	bitSet(nConfig, 7);

	// 
	switch (nChn)
	{
		case AIN0_AIN1:
		{
			bitClear(nConfig, 5);
			bitClear(nConfig, 6);
		}
		break;

		case AIN2_AIN3:
		{
			bitClear(nConfig, 5);
			bitSet(nConfig, 6);
		}
		break;

		case AIN0_AIN3:
		{
			bitSet(nConfig, 5);
			bitClear(nConfig, 6);
		}
		break;

		case AIN1_AIN3:
		{
			bitSet(nConfig, 5);
			bitSet(nConfig, 6);
		}
		break;
	}
	bitSet(nConfig, 7);

	if (nMode == SINGLECONV)
		bitSet(nConfig, 4);
	else
		bitClear(nConfig, 4);

	switch (nDataRate)
	{
		case SPS240:
		{
			bitClear(nConfig, 3);
			bitClear(nConfig, 2);

		}
		break;

		case SPS60:
		{
			bitClear(nConfig, 3);
			bitSet(nConfig, 2);
		}
		break;

		case SPS30:
		{
			bitSet(nConfig, 3);
			bitClear(nConfig, 2);
		}
		break;

		case SPS15:
		{
			bitSet(nConfig, 3);
			bitSet(nConfig, 2);
		}
		break;
	}

	switch (nPGA)
	{
		case GAIN1:
		{
			bitClear(nConfig, 1);
			bitClear(nConfig, 0);
		}
		break;

		case GAIN2:
		{
			bitClear(nConfig, 1);
			bitSet(nConfig, 0);
		}
		break;

		case GAIN4:
		{
			bitSet(nConfig, 1);
			bitClear(nConfig, 0);
		}
		break;

		case GAIN8:
		{
			bitSet(nConfig, 1);
			bitSet(nConfig, 0);
		}
		break;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(nConfig);
	Wire.endTransmission();
}


void ADS1112::SetPGA(uint8_t Gain)
{
	nPGA = Gain;
}

void ADS1112::Setup(uint8_t Chn, uint8_t dataRate = SPS15, uint8_t Mode = CONTICONV, uint8_t Gain = GAIN1)
{
	SetChannel(Chn);
	SetDataRate(dataRate);
	SetMode(Mode);
	SetPGA(Gain);
	//WriteConfig();
}

float ADS1112::GetVoltage()
{
	float fVoltage = 0.0F;
	float fFullScale = 32768F;
	// 
	WriteConfig();
	switch (nDataRate)
	{
	case SPS240:
		delay(10);
		fFullScale = 2048F;
		break;

	case SPS60:
		delay(20);
		fFullScale = 8192F;
		break;

	case SPS30:
		delay(40);
		fFullScale = 16384F;
		break;

	case SPS15:
		delay(80);
		fFullScale = 32768F;
		break;
	}
	if (ReadDeviceInfo())
	{
		fVoltage = (float)nOutputCode;
		fVoltage *= ADS1112_REF;
		fVoltage /= fFullScale;
		fVoltage /= nPGA;
	}
	else
	{
		// Error
	}
}

bool ADS1112::ReadDeviceInfo()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return false;
	}

	uint8_t nBuff[3];
	Wire.requestFrom(nI2CAddr, 3);
	for (uint8_t idx = 0; idx < 3; idx++)
	{
		if(Wire.available())
			nBuff[idx] = i2cread();
	}
	Wire.endTransmission();
	
	uint16_t nRes = nBuff[0] << 8 + nBuff[1];
	uint8_t nConfig = nBuff[2];

	if (bitRead(nConfig, 7) == 0)
	{
		nOutputCode = nRes;
		return true;
	}
	return false;
}

void ADS1112::SetMode(uint8_t Mode)
{
	nMode = Mode;
}

void ADS1112::SetChannel(uint8_t Chn)
{
	nChn = Chn;
}

void ADS1112::SetDataRate(uint8_t DataRate)
{
	nDataRate = DataRate;
}

/**************************************************************************/
/*!
@brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void ADS1112::i2cwrite(uint8_t x)
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
uint8_t ADS1112::i2cread(void)
{
#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}