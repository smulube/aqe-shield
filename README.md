# Air Quality Egg Shield to Cosm - v0.0.1

This project contains a basic sketch for uploading data from an Air Quality Egg
Shield mounted on a Nanode to Cosm.

I've only tested this sketch on a Nanode, but it should work with any device
that uses the ENC28J60 Ethernet controller. This means it *will not* work with a
standard Arduino Ethernet board. The EggBus sensor reading stuff would be fine,
but all the networky stuff would be completely different.

## Requirements

To compile and upload the following sketch to your device, you'll need to have
the following libraries available in your Arduino libraries folder.

Download them and unpack the zips into your libraries folder (or you can clone
the git repos there), then restart the IDE, and everything *should* work.

 * EtherCard library: https://github.com/jcw/ethercard
 * DHT Sensor library: https://github.com/adafruit/DHT-sensor-library
 * EggBus library: http://aqe.wickeddevice.com/wp-content/uploads/2012/10/EggBus.zip


copyright (c) 2012 sam mulube
