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
 * Time: 19:28
 *
 * SmoothThermistor (https://github.com/giannivh/SmoothThermistor)
 * A flexible thermistor reading library.
 */

#include "Arduino.h"
#include "SmoothThermistor.h"
#include <math.h>

SmoothThermistor::SmoothThermistor(uint8_t analogPin, uint16_t adcSize, uint32_t nominalResistance, 
                                   uint32_t seriesResistance, uint16_t betaCoefficient, uint8_t nominalTemperature, 
                                   uint8_t samples) {

    _analogPin = analogPin;
    _adcSize = adcSize;
    _nominalResistance = nominalResistance;
    _seriesResistance = seriesResistance;
    _betaCoefficient = betaCoefficient;
    _nominalTemperature = nominalTemperature;
    _samples = samples;
}

void SmoothThermistor::useAREF(bool aref) {

    analogReference(aref? EXTERNAL: DEFAULT);
}

float SmoothThermistor::temperature(void) {

    // take samples
    float average = 0;

    for (uint8_t i = 0; i < _samples; i++) {

        average += analogRead(_analogPin);
        delay(10);
    }

    average /= _samples;

    // convert the value to resistance
    average = _seriesResistance * ((pow(2.0, _adcSize) - 1) / average - 1);

    // Steinhart–Hart equation, based on https://learn.adafruit.com/thermistor/using-a-thermistor
    float steinhart = (log(average / _nominalResistance)) / _betaCoefficient;
    steinhart += 1.0 / (_nominalTemperature + 273.15);
    steinhart = 1.0 / steinhart; // invert
    steinhart -= 273.15; // convert to celsius

    return steinhart;
}