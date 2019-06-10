# gator:microphone sound Sensor

[![Community Discord](https://img.shields.io/discord/448979533891371018.svg)](https://aka.ms/makecodecommunity)

The gator:microphone, which includes a microphone along with an analog-to-I2C converter can be purchased [here.](https://www.sparkfun.com/products/15289)
The gator:microphone can be used to look at the envelope, or volume of sound, along with a simple gate value, which will tell whether a sound is detected above a certain threshold.

![SparkFun gator:microphone](https://raw.githubusercontent.com/sparkfun/pxt-gator-microphone/master/icon.png)  

## ~ hint

To use this package, go to https://makecode.microbit.org, click ``Add package`` and search for **gator-microphone**. The package is located [here](https://makecode.microbit.org/pkg/sparkfun/pxt-gator-microphone)

## ~

## Basic usage

```blocks
//Reads the volume of sound
gatorMicrophone.readEnvelopeData()
```

Use ``||Get sound intensity||`` to get the value from the envelope channel. 

```blocks
//Reads whether or not sound is above a certain level
gatorMicrophone.readGateData()
```

Use ``||Check for sound||`` to return a boolean for whether or not the sound is above a certain level

## Example: Red Detector

```blocks
//Read volume value and write it to the micro:bit screen as a bar graph.
basic.forever(function () {
    led.plotBarGraph(
    gatorMicrophone.readEnvelopeData(),
    2047
    )
})
```

## Supported targets

* for PXT/microbit

## License

MIT

```package
gatorMicrophone=github:sparkfun/pxt-gator-microphone
```