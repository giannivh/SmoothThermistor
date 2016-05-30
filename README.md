# SmoothThermistor
A flexible thermistor reading library. Calculates the temperature based on the Steinhart–Hart equation, smoothed by taking a number of samples.

# Installation

SmoothThermistor can be found and installed through the Arduino Library Manager.

# Circuit

The easy and most common circuit looks as follows:

```
              Analog pin 0
                    |
5V |-----/\/\/\-----+-----/\/\/\-----| GND

           ^                ^ 
    10K thermistor     10K resistor
```

However, to get more accurate readings, you can use the 3.3V pin on the Arduino, which has less noise. 
Make sure your thermistor is fed using 3.3V, along with the AREF pin.
The circuits looks as follows:

```
      AREF      Analog pin 0
       |              |
3.3V |-+---/\/\/\-----+-----/\/\/\-----| GND

             ^                ^ 
      10K thermistor     10K resistor
```

# Usage

Include the library:
```cpp
#include <SmoothThermistor.h>
```

Create an instance using the most commonly used 10K thermistor:
```cpp
SmoothThermistor smoothThermistor(A0);
```

If you have a thermistor with different values, you can override the default values. Create an instance as follows:
```cpp
SmoothThermistor smoothThermistor(A0,              // the analog pin to read from
                                  ADC_SIZE_10_BIT, // the ADC size
                                  10000,           // the nominal resistance
                                  10000,           // the series resistance
                                  3950,            // the beta coefficient of the thermistor
                                  25,              // the temperature for nominal resistance
                                  10);             // the number of samples to take for each measurement
```

When using the more advanced circuit, don't forget to use AREF:
```cpp
smoothThermistor.useAREF(true);
```

Get the smoothed temperature:
```cpp
smoothThermistor.temperature();
```

See the example inside the repository. 

## ADC size

The [ADC size](https://en.wikipedia.org/wiki/Analog-to-digital_converter) can be one of the following values:
```cpp
ADC_SIZE_8_BIT 
ADC_SIZE_10_BIT
ADC_SIZE_12_BIT
ADC_SIZE_16_BIT
```

Default size is 10 BIT.
