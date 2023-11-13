/**
* Andy England @ SparkFun Electronics
* September 6, 2018

* Development environment specifics:
* Written in Microsoft Makecode
* Tested with a SparkFun gatorMicrophone sensor and micro:bit
*
* This code is released under the [MIT License](http://opensource.org/licenses/MIT).
* Please review the LICENSE.md file included with this example. If you have any questions
* or concerns with licensing, please contact techsupport@sparkfun.com.
* Distributed as-is; no warranty is given.
*/


/**
 * Functions to operate the gator:microphone sensor
 */
//% color=#f44242 icon="\uf130"
namespace gatorMicrophone {
    // Functions for reading envelope and gate data
	
	/**
	* Reads the intensity of sound from the microphone as a value between 0 and 2047, sensitivity is determined by the switch on the gator:microphone
	*/
	//% weight=25
	//% blockId="gatorMicrophone_getSoundIntensity"
	//% block="sound intensity"
	//% shim=gatorMicrophone::getSoundIntensity
	export function getSoundIntensity(): number{
		return 0
	}
	
	/**
	* Returns true if the sound is above a certain level, sensitivity is determined by the switch on the gator:microphone
	*/
	//% weight=24
	//% blockId="gatorMicrophone_readGateData"
	//% block="check for sound"
	//% shim=gatorMicrophone::readGateData
	export function readGateData(): boolean{
		return true
	}
	
	/**
	* Sets the gain, or volume of the microphone. Lower gain means more sensitivity to smaller changes in volume.
	*/
	//% weight=23
	//% blockId="gatorMicrophone_setGain"
	//% block="change gain to %GainOptions"
	//% shim=gatorMicrophone::setGain
	//% advanced=true
	export function setGain(gainOption: GainOptions){
		return
	}
}