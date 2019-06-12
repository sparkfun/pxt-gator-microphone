/*
  This is a library written for the ADS1015 ADC->I2C.
  Written by Andy England @ SparkFun Electronics, October 17th, 2017
  The sensor uses I2C to communicate, as well as a single (optional)
  interrupt line that is not currently supported in this driver.
  https://github.com/sparkfun/SparkFun_ADS1015_Arduino_Library
  Do you like this library? Help support SparkFun. Buy a board!
  Development environment specifics:
  Arduino IDE 1.8.1
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "SparkFun_ADS1015_Arduino_Library.h"
#include "mbed.h"
#ifndef __MICROBIT_H_
#define __MICROBIT_H_
#include "MicroBit.h"
#endif

MicroBit *uBit;
//The catch-all default is 32
static const char I2C_BUFFER_LENGTH = 32;

static const char ADS1015_ADDRESS_GND = 0x90; //7-bit unshifted default I2C Address

//Register addresses
static const char ADS1015_DELAY                = (1);

//Pointer Register
static const char ADS1015_POINTER_CONVERT      = (0x00);
static const char ADS1015_POINTER_CONFIG       = (0x01);
static const char ADS1015_POINTER_LOWTHRESH    = (0x02);
static const char ADS1015_POINTER_HITHRESH     = (0x03);

#define ADS1015_CONFIG_OS_NO          (0x8000)
#define ADS1015_CONFIG_OS_SINGLE      (0x8000)
#define ADS1015_CONFIG_OS_READY       (0x0000)
#define ADS1015_CONFIG_OS_NOTREADY    (0x8000)

#define ADS1015_CONFIG_MODE_CONT      (0x0000)
#define ADS1015_CONFIG_MODE_SINGLE    (0x0100)

#define ADS1015_CONFIG_MUX_SINGLE_0     (0x4000)
#define ADS1015_CONFIG_MUX_SINGLE_1     (0x5000)
#define ADS1015_CONFIG_MUX_SINGLE_2     (0x6000)
#define ADS1015_CONFIG_MUX_SINGLE_3     (0x7000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N1   (0x0000)
#define ADS1015_CONFIG_MUX_DIFF_P0_N3   (0x1000)
#define ADS1015_CONFIG_MUX_DIFF_P1_N3   (0x2000)
#define ADS1015_CONFIG_MUX_DIFF_P2_N3   (0x3000)

#define ADS1015_CONFIG_RATE_128HZ     (0x0000)
#define ADS1015_CONFIG_RATE_250HZ     (0x0020)
#define ADS1015_CONFIG_RATE_490HZ     (0x0040)
#define ADS1015_CONFIG_RATE_920HZ     (0x0060)
#define ADS1015_CONFIG_RATE_1600HZ    (0x0080)
#define ADS1015_CONFIG_RATE_2400HZ    (0x00A0)
#define ADS1015_CONFIG_RATE_3300HZ    (0x00C0)

#define ADS1015_CONFIG_PGA_MASK       (0X0E00)
#define ADS1015_CONFIG_PGA_TWOTHIRDS  (0X0000) // +/- 6.144v
#define ADS1015_CONFIG_PGA_1          (0X0200) // +/- 4.096v
#define ADS1015_CONFIG_PGA_2          (0X0400) // +/- 2.048v
#define ADS1015_CONFIG_PGA_4          (0X0600) // +/- 1.024v
#define ADS1015_CONFIG_PGA_8          (0X0800) // +/- 0.512v
#define ADS1015_CONFIG_PGA_16         (0X0A00) // +/- 0.256v

#define ADS1015_CONFIG_CMODE_TRAD    (0x0000)  // Traditional comparator with hysteresis (default)
#define ADS1015_CONFIG_CMODE_WINDOW  (0x0010)  // Window comparator
#define ADS1015_CONFIG_CPOL_ACTVLOW  (0x0000)  // ALERT/RDY pin is low when active (default)
#define ADS1015_CONFIG_CPOL_ACTVHI   (0x0008)  // ALERT/RDY pin is high when active
#define ADS1015_CONFIG_CLAT_NONLAT   (0x0000)  // Non-latching comparator (default)
#define ADS1015_CONFIG_CLAT_LATCH    (0x0004)  // Latching comparator    
#define ADS1015_CONFIG_CQUE_1CONV    (0x0000)  // Assert ALERT/RDY after one conversions
#define ADS1015_CONFIG_CQUE_2CONV    (0x0001)  // Assert ALERT/RDY after two conversions
#define ADS1015_CONFIG_CQUE_4CONV    (0x0002)  // Assert ALERT/RDY after four conversions
#define ADS1015_CONFIG_CQUE_NONE     (0x0003) 
//Sets up the sensor for constant read
//Returns false if sensor does not respond

uint16_t _mode = ADS1015_CONFIG_MODE_CONT;
uint16_t _gain = ADS1015_CONFIG_PGA_2;
uint16_t _sampleRate = ADS1015_CONFIG_RATE_3300HZ;

//Returns true if I2C device ack's
bool ADS1015::isConnected()
{
	return true;
}

//Returns the decimal value of sensor channel single-ended input
uint16_t ADS1015::getSingleEnded(uint8_t channel)
{
	if (channel > 3) {
		return 0;
	}
	
	uint16_t config = ADS1015_CONFIG_OS_SINGLE   |
					  _mode |
					  _sampleRate;
			
	config |= _gain;		  
	
	switch (channel)
    {
    case (0):
        config |= ADS1015_CONFIG_MUX_SINGLE_0;
        break;
    case (1):
        config |= ADS1015_CONFIG_MUX_SINGLE_1;
        break;
    case (2):
        config |= ADS1015_CONFIG_MUX_SINGLE_2;
        break;
    case (3):
        config |= ADS1015_CONFIG_MUX_SINGLE_3;
        break;
    }
	
	writeMicRegister(ADS1015_POINTER_CONFIG, config);
	uBit->sleep(ADS1015_DELAY);
	
    return readMicRegister(ADS1015_POINTER_CONVERT) >> 4;
}

// antiquated function from older library, here for backwards compatibility
uint16_t ADS1015::getAnalogData(uint8_t channel)
{
	return getSingleEnded(channel);
}

//Set the mode. Continuous mode 0 is favored
void ADS1015::setMode(uint16_t mode)
{
  _mode = mode;
}

//getMode will return 0 for continuous and 1 for single shot
uint16_t ADS1015::getMode ()
{
  return _mode;
}

void ADS1015::setGain (uint16_t gain)
{
	_gain = (gain * 2) <<  8;
	updateMultiplierToVolts(); // each new gain setting changes how we convert to volts
}

//Will return a different hex value for each gain
//0x0E00: +/- 0.256V
//0X0000: +/- 6.144V
//0X0200: +/- 4.096V
//0X0400: +/- 2.048V
//0X0600: +/- 1.024V
//0X0800: +/- 0.512V
//0X0A00: +/- 0.256V
uint16_t ADS1015::getGain ()
{
	return _gain;
}

void ADS1015::updateMultiplierToVolts()
{
	switch (_gain)
    {
    case (ADS1015_CONFIG_PGA_TWOTHIRDS):
        _multiplierToVolts = 3.0F;
        break;
    case (ADS1015_CONFIG_PGA_1):
        _multiplierToVolts = 2.0F;
        break;
    case (ADS1015_CONFIG_PGA_2):
        _multiplierToVolts = 1.0F;
        break;
    case (ADS1015_CONFIG_PGA_4):
        _multiplierToVolts = 0.5F;
        break;
    case (ADS1015_CONFIG_PGA_8):
        _multiplierToVolts = 0.25F;
        break;
    case (ADS1015_CONFIG_PGA_16):
        _multiplierToVolts = 0.125F;
        break;		
	default:
		_multiplierToVolts = 1.0F;
    }
}

float ADS1015::getMultiplier()
{
  return _multiplierToVolts;
}

void ADS1015::setSampleRate (uint16_t sampleRate)
{
	_sampleRate = sampleRate;
}

//Will return a different hex value for each sample rate
//0x0000: 128 Hz
//0X0020: 250 Hz
//0X0040: 490 Hz
//0X0060: 920 Hz
//0X0080: 1600 Hz
//0X00A0: 2400 Hz
//0X00C0: 3300 Hz
uint16_t ADS1015::getSampleRate ()
{
	return _sampleRate;
}

//Checks to see if DRDY flag is set in the status register
bool ADS1015::available()
{
  uint16_t value = readMicRegister(ADS1015_POINTER_CONFIG);
  return (value & (1 << 0)); //Bit 0 is DRDY
}

//Reads from a give location
uint16_t ADS1015::readMicRegister(uint8_t location)
{
  uint8_t data[2];
  uBit->i2c.readRegister(ADS1015_ADDRESS_GND, location, data, 2);
  return (data[0] << 8) | data[1];
}

//Write a value to a spot
void ADS1015::writeMicRegister(uint8_t location, uint16_t val)
{
  char data[3];
  data[0] = location;
  data[1] = val >> 8;
  data[2] = val;
  uBit->i2c.write(ADS1015_ADDRESS_GND, data, 3, false);
 }

//Reads a two uint8_t value from a consecutive registers
uint16_t ADS1015::readMicRegister16(uint8_t location)
{
  uint8_t data[2];
  uBit->i2c.readRegister(ADS1015_ADDRESS_GND, location, data, 2);
  return (data[0] << 8) | data[1];
}

/**************************************************************************/
/*!
    @brief  Sets up the comparator to operate in basic mode, causing the
            ALERT/RDY pin to assert (go from high to low) when the ADC
            value exceeds the specified threshold.
            This will also set the ADC in continuous conversion mode.
			
			Note, this function was adapted from the Adafruit Industries
			located here:
			https://github.com/adafruit/Adafruit_ADS1X15
*/
/**************************************************************************/
void ADS1015::setComparatorSingleEnded(uint8_t channel, int16_t threshold)
{
	if (channel > 3) {
		channel = 3;
	}
	
	uint16_t config = 
					ADS1015_CONFIG_MODE_CONT |
					_sampleRate |
					ADS1015_CONFIG_CQUE_1CONV   | 	// Comparator enabled and asserts on 1 match
                    ADS1015_CONFIG_CLAT_LATCH   | 	// Latching mode
                    ADS1015_CONFIG_CPOL_ACTVLOW | 	// Alert/Rdy active low   (default val)
                    ADS1015_CONFIG_CMODE_TRAD; 		// Traditional comparator (default val)
			
	config |= _gain;		  
	
	switch (channel)
    {
    case (0):
        config |= ADS1015_CONFIG_MUX_SINGLE_0;
        break;
    case (1):
        config |= ADS1015_CONFIG_MUX_SINGLE_1;
        break;
    case (2):
        config |= ADS1015_CONFIG_MUX_SINGLE_2;
        break;
    case (3):
        config |= ADS1015_CONFIG_MUX_SINGLE_3;
        break;
    }
	
	// Set the high threshold register
	// Shift 12-bit results left 4 bits for the ADS1015
	writeMicRegister(ADS1015_POINTER_HITHRESH, threshold << 4);

	// Write config register to the ADC
	writeMicRegister(ADS1015_POINTER_CONFIG, config);
}

/**************************************************************************/
/*!
    @brief  In order to clear the comparator, we need to read the
            conversion results.  This function reads the last conversion
            results without changing the config value.
			
			Note, this function was adapted from the Adafruit Industries
			located here:
			https://github.com/adafruit/Adafruit_ADS1X15
*/
/**************************************************************************/
int16_t ADS1015::getLastConversionResults()
{
	// Wait for the conversion to complete
	uBit->sleep(ADS1015_DELAY);

	// Read the conversion results
	uint16_t result = readMicRegister(ADS1015_POINTER_CONVERT) >> 4;

	// Shift 12-bit results right 4 bits for the ADS1015,
	// making sure we keep the sign bit intact
	if (result > 0x07FF)
	{
	  // negative number - extend the sign to 16th bit
	  result |= 0xF000;
	}
	return (int16_t)result;
}