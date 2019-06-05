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
 * Functions to operate the gatorMicrophone sensor
 */
enum audioDataType
{
	gate = 1,
	envelope = 2,
}

//% color=#f44242 icon="\uf185"
namespace gatorMicrophone {
    // Functions for reading Particle from the gatorMicrophone in Particle or straight adv value
	
	//% weight=31 
	//% blockId="gatorMicrophone_begin" 
	//% block="Initialize gator:Microphone"
	//% shim=gatorMicrophone::begin
	export function begin(){
		return
	}
	
	//% weight=30
	//% blockId="gatorMicrophone_readData"
	//% block="Read %audioDataType | value"
	//% shim=gatorMicrophone::readData
	export function readData(type: audioDataType): number{
		return 0
	}
}