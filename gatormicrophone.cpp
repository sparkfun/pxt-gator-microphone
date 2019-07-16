/**
* Andy England @ SparkFun Electronics
* September 6, 2018
* https://github.com/sparkfun/pxt-light-bit
*
* Development environment specifics:
* Written in Microsoft PXT
* Tested with a SparkFun temt6000 sensor and micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


#include "pxt.h"
#include <cstdint>
#include <math.h>
#include "SparkFun_ADS1015_Arduino_Library.h"

enum GainOptions
{
	//% block="Two Thirds" enumval=0
	Two_Thirds = 0,
	//% block="One" enumval=1
	One = 1,
	//% block="Two" enumval=2
	Two = 2,
	//% block="Four" enumval=3
	Four = 3,
	//% block="Eight" enumval=4
	Eight = 4,
	//% block="Sixteen" enumval=5
	Sixteen = 5,
};

using namespace pxt;

namespace gatorMicrophone {
	ADS1015 *mic; //Create an ADS1015 sensor	

	//%
	uint16_t getSoundIntensity()
	{
		uint16_t envelopeData = mic->getSingleEnded(2);
		//release_fiber();
		return envelopeData;
	}
	
	//%
	bool readGateData()
	{
		uint16_t gateData = mic->getSingleEnded(3);
		if (gateData > 1000)
		{
			//release_fiber();
			return true;
		}
		return false;
	}
	
	//%
	void setGain(uint16_t gainOption)
	{
		mic->setGain(gainOption);
	}
}