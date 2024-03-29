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

gatorMicrophone.setGain(GainOptions.Two_Thirds)
basic.forever(function () {
    serial.writeLine("" + gatorMicrophone.getSoundIntensity())
    serial.writeLine("" + gatorMicrophone.readGateData())
})