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
 * Time: 19:27
 *
 * SmoothThermistor (https://github.com/giannivh/SmoothThermistor)
 * A flexible thermistor reading library.
 */

#ifndef SmoothThermistor_h
#define SmoothThermistor_h

#include "Arduino.h"

#define DEFAULT_NOMINAL_RESISTANCE  10000
#define DEFAULT_SERIES_RESISTANCE   10000
#define DEFAULT_BETA_COEFFICIENT    3950
#define DEFAULT_NOMINAL_TEMPERATURE 25
#define DEFAULT_SAMPLES             10
#define ADC_SIZE_8_BIT              8
#define ADC_SIZE_10_BIT             10
#define ADC_SIZE_12_BIT             12
#define ADC_SIZE_16_BIT             16

class SmoothThermistor {
  public:

    /**
     * @param analogPin          The analog pin where the thermistor is connected to.
     * @param adcSize            The ADC size. This is usually ADC_SIZE_10_BIT.
     * @param nominalResistance  The nominal resistance at 25 degrees celsius.
     * @param seriesResistance   The value of the series resistor.
     * @param betaCoefficient    The beta coefficient of the thermistor.
     * @param nominalTemperature The temperature for nominal resistance. This is usually 25.
     * @param samples            The number of samples to take for temperature smoothing.
     */
    SmoothThermistor(uint8_t analogPin,
                     uint16_t adcSize = ADC_SIZE_10_BIT,
                     uint32_t nominalResistance = DEFAULT_NOMINAL_RESISTANCE,
                     uint32_t seriesResistance = DEFAULT_SERIES_RESISTANCE,
                     uint16_t betaCoefficient = DEFAULT_BETA_COEFFICIENT,
                     uint8_t nominalTemperature = DEFAULT_NOMINAL_TEMPERATURE,
                     uint8_t samples = DEFAULT_SAMPLES);

    void useAREF(bool aref);
    float temperature(void);

  private:

    uint8_t  _analogPin;
    uint16_t _adcSize;
    uint32_t _nominalResistance;
    uint32_t _seriesResistance;
    uint16_t _betaCoefficient;
    uint8_t  _nominalTemperature;
    uint8_t  _samples;
};

#endif
