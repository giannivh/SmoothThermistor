/*
 * This file is part of SmoothThermistor.
 *
 * Copyright (c) 2016 Gianni Van Hoecke <gianni.vh@gmail.com>
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * User: Gianni Van Hoecke <gianni.vh@gmail.com>
 * Date: 23/05/16
 * Time: 20:19
 *
 * SmoothThermistor (https://github.com/giannivh/SmoothThermistor)
 * A flexible thermistor reading library.
 *
 * The components:
 * - Thermistor (here a 10K thermistor is used)
 * - Resistor (here a 10K resistor is used)
 * - Some wires
 *
 * The easy circuit:
 *
 *                  Analog pin 0
 *                        |
 *    5V |-----/\/\/\-----+-----/\/\/\-----| GND
 *
 *               ^                ^ 
 *        10K thermistor     10K resistor
 *
 * The advanced circuit:
 *
 *          AREF      Analog pin 0
 *           |              |
 *    3.3V |-+---/\/\/\-----+-----/\/\/\-----| GND
 *
 *                 ^                ^ 
 *          10K thermistor     10K resistor
 */
 
// include the SmoothThermistor library
#include <SmoothThermistor.h>

// create a SmoothThermistor instance, reading from analog pin 0
// using a common 10K thermistor.
SmoothThermistor smoothThermistor(A0);

// if you have a different type of thermistor, you can override the default values
// example:
// SmoothThermistor smoothThermistor(A0,              // the analog pin to read from
//                                   ADC_SIZE_10_BIT, // the ADC size
//                                   10000,           // the nominal resistance
//                                   10000,           // the series resistance
//                                   3950,            // the beta coefficient of the thermistor
//                                   25,              // the temperature for nominal resistance
//                                   10);             // the number of samples to take for each measurement

void setup() {

  // set up UART
  Serial.begin(9600);

  // use the AREF pin, so we can measure on 3.3v, which has less noise on an Arduino
  // make sure your thermistor is fed using 3.3v, along with the AREF pin
  // so the 3.3v output pin goes to the AREF pin and the thermistor
  // see "the advanced circuit" on top of this sketch
  smoothThermistor.useAREF(true);
}

void loop() {

  // print the temperature
  Serial.print("Temperature = ");
  Serial.println(smoothThermistor.temperature());

  // pause for a second
  delay(1000);
}
