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

#pragma once

#include "mbed.h"
#include "MicroBit.h"

class ADS1015 {
  public:
    bool isConnected(); //Checks if sensor ack's the I2C request
	
	uint16_t getSingleEnded(uint8_t channel);
	uint16_t getAnalogData(uint8_t channel); // antiquated function; here for backward compatibility
	float getScaledAnalogData(uint8_t channel);
	void calibrate();
	uint16_t getCalibration(uint8_t channel, bool hiLo);
	void setCalibration(uint8_t channel, bool hiLo, uint16_t value);
	void resetCalibration();
	
	float mapf(float val, float in_min, float in_max, float out_min, float out_max);
	
    bool available(); //True if OS bit is set

    void setMode(uint16_t mode); //Set mode of the sensor. Mode 0 is continuous read mode
	uint16_t getMode();
	
	void setGain(uint16_t gain);
	uint16_t getGain();

	void setSampleRate(uint16_t sampleRate);
	uint16_t getSampleRate();
	
	float getMultiplier();

    uint16_t readRegister(uint8_t location); //Basic read of a register
    void writeRegister(uint8_t location, uint16_t val); //Writes to a location
    uint16_t readRegister16(uint8_t location); //Reads a 16bit value
	
	void setComparatorSingleEnded(uint8_t channel, int16_t threshold);
	int16_t getLastConversionResults();

  private:
	
	float _multiplierToVolts = 1.0F; // at a default gain of 2, the multiplier is 1, also updated in setGain()
	void updateMultiplierToVolts();
	
	//Array is structured as calibrationValues[finger][lo/hi]
	uint16_t calibrationValues[2][2] = {{0, 0}, {0, 0}};

    bool _printDebug = false; //Flag to print the serial commands we are sending to the Serial port for debug

    Stream *_debugSerial; //The stream to send debug messages to if enabled
};
