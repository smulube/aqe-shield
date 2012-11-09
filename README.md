# Air Quality Egg Shield to Cosm - v0.0.1

This project contains a basic sketch for uploading data from an Air Quality Egg
Shield mounted on a Nanode to Cosm.

I've only tested this sketch on a Nanode, but it should work with any device
that uses the ENC28J60 Ethernet controller. This means it *will not* work with a
standard Arduino Ethernet board. The EggBus sensor reading stuff would be fine,
but all the networky stuff would be completely different.

This sketch basically combines one of the EggBus examples with the Pachube
example in the EtherCard library, so everything that's right in this code is
copied from there, any mistakes are from my merging of the two.

## Requirements

To compile and upload the following sketch to your device, you'll need to have
the following libraries available in your Arduino libraries folder.

Download them and unpack the zips into your libraries folder (or you can clone
the git repos there), then restart the IDE, and everything *should* work.

 * EtherCard library: https://github.com/jcw/ethercard
 * DHT Sensor library: https://github.com/adafruit/DHT-sensor-library
 * EggBus library: http://aqe.wickeddevice.com/wp-content/uploads/2012/10/EggBus.zip

----

copyright (c) 2012 sam mulube

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
