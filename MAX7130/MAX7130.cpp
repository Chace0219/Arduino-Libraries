
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "Robert_MAX7130.h"

/*
AD2 AD1 AD0 A6 A5 A4 A3 A2 A1 A0
GND SCL GND 0 0 0 1 0 0 0
GND SCL V+ 0 0 0 1 0 0 1
GND SDA GND 0 0 0 1 0 1 0
GND SDA V+ 0 0 0 1 0 1 1
V+ SCL GND 0 0 0 1 1 0 0
V+ SCL V+ 0 0 0 1 1 0 1
V+ SDA GND 0 0 0 1 1 1 0
V+ SDA V+ 0 0 0 1 1 1 1
GND GND SCL 0 0 1 0 0 0 0
GND GND SDA 0 0 1 0 0 0 1
GND V+ SCL 0 0 1 0 0 1 0
GND V+ SDA 0 0 1 0 0 1 1
V+ GND SCL 0 0 1 0 1 0 0
V+ GND SDA 0 0 1 0 1 0 1
V+ V+ SCL 0 0 1 0 1 1 0
V+ V+ SDA 0 0 1 0 1 1 1
GND GND GND 0 0 1 1 0 0 0
GND GND V+ 0 0 1 1 0 0 1
GND V+ GND 0 0 1 1 0 1 0
GND V+ V+ 0 0 1 1 0 1 1
V+ GND GND 0 0 1 1 1 0 0
V+ GND V+ 0 0 1 1 1 0 1
V+ V+ GND 0 0 1 1 1 1 0
V+ V+ V+ 0 0 1 1 1 1 1
SCL SCL SCL 0 1 0 0 0 0 0
SCL SCL SDA 0 1 0 0 0 0 1
SCL SDA SCL 0 1 0 0 0 1 0
SCL SDA SDA 0 1 0 0 0 1 1
SDA SCL SCL 0 1 0 0 1 0 0
SDA SCL SDA 0 1 0 0 1 0 1
SDA SDA SCL 0 1 0 0 1 1 0
SDA SDA SDA 0 1 0 0 1 1 1
SCL SCL GND 0 1 0 1 0 0 0
SCL SCL V+ 0 1 0 1 0 0 1
SCL SDA GND 0 1 0 1 0 1 0
SCL SDA V+ 0 1 0 1 0 1 1
SDA SCL GND 0 1 0 1 1 0 0
SDA SCL V+ 0 1 0 1 1 0 1
SDA SDA GND 0 1 0 1 1 1 0
SDA SDA V+ 0 1 0 1 1 1 1
*/

MAX7130::MAX7130(uint8_t AD1 = GND, uint8_t AD2 = GND, uint8_t AD3 = GND)
{
	if ((AD1 == GND && AD1 == SCL) && AD2 == GND)
		nI2CAddr = 0x08;
	else if((AD1 == GND && AD1 == SCL) && AD2 == VCC)
		nI2CAddr = 0x09;
	else if ((AD1 == GND && AD1 == SDA) && AD2 == GND)
		nI2CAddr = 0x0A;
	else if ((AD1 == GND && AD1 == SDA) && AD2 == VCC)
		nI2CAddr = 0x0B;
	else if ((AD1 == VCC && AD1 == SCL) && AD2 == GND)
		nI2CAddr = 0x0C;
	else if ((AD1 == VCC && AD1 == SCL) && AD2 == VCC)
		nI2CAddr = 0x0D;
	else if ((AD1 == VCC && AD1 == SDA) && AD2 == GND)
		nI2CAddr = 0x0E;
	else if ((AD1 == VCC && AD1 == SDA) && AD2 == VCC)
		nI2CAddr = 0x0F;
	else if ((AD1 == GND && AD1 == GND) && AD2 == SCL)
		nI2CAddr = 0x10;
	else if ((AD1 == GND && AD1 == GND) && AD2 == SDA)
		nI2CAddr = 0x11;
	else if ((AD1 == GND && AD1 == VCC) && AD2 == SCL)
		nI2CAddr = 0x12;
	else if ((AD1 == GND && AD1 == VCC) && AD2 == SDA)
		nI2CAddr = 0x13;
	else if ((AD1 == VCC && AD1 == GND) && AD2 == SCL)
		nI2CAddr = 0x14;
	else if ((AD1 == VCC && AD1 == GND) && AD2 == SDA)
		nI2CAddr = 0x15;
	else if ((AD1 == VCC && AD1 == VCC) && AD2 == SCL)
		nI2CAddr = 0x16;
	else if ((AD1 == VCC && AD1 == VCC) && AD2 == SDA)
		nI2CAddr = 0x17;
	else if ((AD1 == GND && AD1 == GND) && AD2 == GND)
		nI2CAddr = 0x18;
	else if ((AD1 == GND && AD1 == GND) && AD2 == VCC)
		nI2CAddr = 0x19;
	else if ((AD1 == GND && AD1 == VCC) && AD2 == GND)
		nI2CAddr = 0x1A;
	else if ((AD1 == GND && AD1 == VCC) && AD2 == VCC)
		nI2CAddr = 0x1B;
	else if ((AD1 == VCC && AD1 == GND) && AD2 == GND)
		nI2CAddr = 0x1C;
	else if ((AD1 == VCC && AD1 == GND) && AD2 == VCC)
		nI2CAddr = 0x1D;
	else if ((AD1 == VCC && AD1 == VCC) && AD2 == GND)
		nI2CAddr = 0x1E;
	else if ((AD1 == VCC && AD1 == VCC) && AD2 == VCC)
		nI2CAddr = 0x1F;
	else if ((AD1 == SCL && AD1 == SCL) && AD2 == SCL)
		nI2CAddr = 0x20;
	else if ((AD1 == SCL && AD1 == SCL) && AD2 == SDA)
		nI2CAddr = 0x21;
	else if ((AD1 == SCL && AD1 == SDA) && AD2 == SCL)
		nI2CAddr = 0x22;
	else if ((AD1 == SCL && AD1 == SDA) && AD2 == SDA)
		nI2CAddr = 0x23;
	else if ((AD1 == SDA && AD1 == SCL) && AD2 == SCL)
		nI2CAddr = 0x24;
	else if ((AD1 == SDA && AD1 == SCL) && AD2 == SDA)
		nI2CAddr = 0x25;
	else if ((AD1 == SDA && AD1 == SDA) && AD2 == SCL)
		nI2CAddr = 0x26;
	else if ((AD1 == SDA && AD1 == SDA) && AD2 == SDA)
		nI2CAddr = 0x27;
	else if ((AD1 == SCL && AD1 == SCL) && AD2 == GND)
		nI2CAddr = 0x28;
	else if ((AD1 == SCL && AD1 == SCL) && AD2 == VCC)
		nI2CAddr = 0x29;
	else if ((AD1 == SCL && AD1 == SDA) && AD2 == GND)
		nI2CAddr = 0x2A;
	else if ((AD1 == SCL && AD1 == SDA) && AD2 == VCC)
		nI2CAddr = 0x2B;
	else if ((AD1 == SDA && AD1 == SCL) && AD2 == GND)
		nI2CAddr = 0x2C;
	else if ((AD1 == SDA && AD1 == SCL) && AD2 == VCC)
		nI2CAddr = 0x2D;
	else if ((AD1 == SDA && AD1 == SDA) && AD2 == GND)
		nI2CAddr = 0x2E;
	else if ((AD1 == SDA && AD1 == SDA) && AD2 == VCC)
		nI2CAddr = 0x2F;
	else if ((AD1 == SCL && AD1 == GND) && AD2 == SCL)
		nI2CAddr = 0x30;
	else if ((AD1 == SCL && AD1 == GND) && AD2 == SDA)
		nI2CAddr = 0x31;
	else if ((AD1 == SCL && AD1 == VCC) && AD2 == SCL)
		nI2CAddr = 0x32;
	else if ((AD1 == SCL && AD1 == VCC) && AD2 == SDA)
		nI2CAddr = 0x33;
	else if ((AD1 == SDA && AD1 == GND) && AD2 == SCL)
		nI2CAddr = 0x34;
	else if ((AD1 == SDA && AD1 == GND) && AD2 == SDA)
		nI2CAddr = 0x35;
	else if ((AD1 == SDA && AD1 == VCC) && AD2 == SCL)
		nI2CAddr = 0x36;
	else if ((AD1 == SDA && AD1 == VCC) && AD2 == SDA)
		nI2CAddr = 0x37;
	else if ((AD1 == SCL && AD1 == GND) && AD2 == GND)
		nI2CAddr = 0x38;
	else if ((AD1 == SCL && AD1 == GND) && AD2 == VCC)
		nI2CAddr = 0x39;
	else if ((AD1 == SCL && AD1 == VCC) && AD2 == GND)
		nI2CAddr = 0x3A;
	else if ((AD1 == SCL && AD1 == VCC) && AD2 == VCC)
		nI2CAddr = 0x3B;
	else if ((AD1 == SDA && AD1 == GND) && AD2 == GND)
		nI2CAddr = 0x3C;
	else if ((AD1 == SDA && AD1 == GND) && AD2 == VCC)
		nI2CAddr = 0x3D;
	else if ((AD1 == SDA && AD1 == VCC) && AD2 == GND)
		nI2CAddr = 0x3E;
	else if ((AD1 == SDA && AD1 == VCC) && AD2 == VCC)
		nI2CAddr = 0x3F;
}

/*
*/
void MAX7130::SetTimeout(bool bTO = true)
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_TO); // Timeout Register 
	i2cwrite(bTO); // Enable/Disable Timeout 
	Wire.endTransmission();
}

/*
*/
uint8_t MAX7130::GetTimeout()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return 0;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_TO); // Timeout Register 
	Wire.endTransmission(false);

	uint8_t nResult = false;
	Wire.requestFrom(nI2CAddr, 1);
	if(Wire.available())
		nResult = i2cread();
	Wire.endTransmission();
	return nResult;
}

/*
*/
uint8_t MAX7130::ReadPort()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return 0;
	}
	
	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_IP);
	Wire.endTransmission(false);
	
	uint8_t nResult = false;
	Wire.requestFrom(nI2CAddr, 1);
	if (Wire.available())
		nResult = i2cread();
	Wire.endTransmission();
	return nResult;
}

/*
*/
void MAX7130::WritePort(uint8_t nNewData)
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return 0;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_OP); // Timeout Register 
	i2cwrite(nNewData); // Timeout Register 
	Wire.endTransmission();
}

/*
*/
uint8_t MAX7130::GetConfiguration()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return 0;
	}
	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_Config);
	Wire.endTransmission(false);
	
	uint8_t nResult = false;
	Wire.requestFrom(nI2CAddr, 1);
	if (Wire.available())
		nResult = i2cread();
	Wire.endTransmission();

	return nResult;
}

/**/
void MAX7130::SetAllInput()
{
	SetConfiguration(0xFF);
	delay(1);
	
	// None Invert
	SetPolarity(0x00);
	delay(1);

	// Disable Timeout
	SetTimeout(false);
	delay(1);
}

/*
*/
void MAX7130::SetAllOutput()
{
	SetConfiguration(0x00);
	delay(1);

	// None Invert
	SetPolarity(0x00);
	delay(1);

	// Disable Timeout
	SetTimeout(false);
	delay(1);
}

/*
*/
uint8_t MAX7130::GetPolarity()
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return 0;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_POL);
	Wire.endTransmission(false);

	uint8_t nResult = false;
	Wire.requestFrom(nI2CAddr, 1);
	if (Wire.available())
		nResult = i2cread();
	Wire.endTransmission();

}

/*
*/
void MAX7130::SetPolarity(uint8_t nPol)
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_POL);
	i2cwrite(nPol);
	Wire.endTransmission();
}

/*
*/
void MAX7130::SetConfiguration(uint8_t nConfigWord)
{
	byte error;
	Wire.beginTransmission(nI2CAddr);
	error = Wire.endTransmission();
	if (error)
	{ // No Slave device or Commnication Error
		return;
	}

	Wire.beginTransmission(nI2CAddr);
	i2cwrite(MAX7310_Config);
	i2cwrite(nConfigWord);
	Wire.endTransmission();
}

/**/
void MAX7130::SetAllInput()
{

}

/**************************************************************************/
/*!
@brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
void MAX7130::i2cwrite(uint8_t x) 
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
uint8_t MAX7130::i2cread(void) 
{
#if ARDUINO >= 100
	return Wire.read();
#else
	return Wire.receive();
#endif
}