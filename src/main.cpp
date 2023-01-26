#include <Arduino.h>
/*
  Basic library example for TM1640. Kept small to fit in the limited space of an ATtiny44.
  Library based on TM1638 library by Ricardo Batista, adapted by Maxint-RD MMOLE 2018.
  Confirmed to work in the following environments:
      ATtiny44A using Arduino IDE 1.8.2 and ATTinyCore (8MHz, LTO enabled), 3232 bytes flash, 103 bytes RAM
      ATtiny44A using Arduino IDE 1.8.2 and ATtiny Microcontrolers (8MHz), 3212 bytes flash, 103 bytes RAM ==> 2892/95 ==> 2878/95
  Only compiled: not tested yet:
      Arduino Nano using Arduino IDE 1.8.2, Nano (Old Bootloader)), 3176 bytes flash, 95 bytes RAM
  For more information see  https://github.com/maxint-rd/TM16xx
*/
#include <TM1640.h>

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 4
#endif
// const byte SEG_NUMS[] = {
//     0b00111111,  // (48)   0
//     0b00000110,  // (49)   1
//     0b101011011, // (50)   2
//     0b101001111, // (51)   3
//     0b101100110, // (52)   4
//     0b101101101, // (53)   5
//     0b101111101, // (54)   6
//     0b00100111,  // (55)   7
//     0b101111111, // (56)   8
//     0b101101111, // (57)   9
// };

const byte SEG_NUMS[] = {
    0x3f,       // (48)   0
    0x06,       // (49)   1
    0b01011011, // (50)   2
    0b01001111, // (51)   3
    0b01100110, // (52)   4
    0b01101101, // (53)   5
    0b01111101, // (54)   6
    0b00100111, // (55)   7
    0b01111111, // (56)   8
    0b01101111, // (57)   9
};
// Define a 4-digit display module. Pin suggestions:
// ESP8266 (Wemos D1): data pin 5 (D1), clock pin 4 (D2)
// ATtiny44A: data pin 9, clock pin 10 (LED_BUILTIN: 8 on ATTinyCore)
TM1640 module(22, 23, 16); // data, clock, 4 digits
void DisplayNumber(uint8_t numL, uint16_t num, uint16_t numR, uint8_t ring, bool rightLed, bool leftLed)
{

  if (num > 999 || num < 0)
    num = 0;
  if (numR > 999 || numR < 0)
    numR = 0;
  if (numL > 99 || numL < 0)
    numL = 0;

  module.setSegments(SEG_NUMS[num % 10] | ((ring > 2) << 7), 4);
  num /= 10;
  module.setSegments(SEG_NUMS[num % 10] | ((ring > 1) << 7), 2);
  num /= 10;
  module.setSegments(SEG_NUMS[num % 10] | ((ring > 0) << 7), 0);

  module.setSegments(SEG_NUMS[numL % 10] | ((ring > 4) << 7), 8);
  numL /= 10;
  module.setSegments(SEG_NUMS[numL % 10] | ((ring > 3) << 7), 6);

  module.setSegments(SEG_NUMS[numR % 10] | ((leftLed) << 7), 14);
  numR /= 10;
  module.setSegments(SEG_NUMS[numR % 10] | ((rightLed) << 7), 12);
  numR /= 10;
  module.setSegments(SEG_NUMS[numR % 10] | ((ring > 5) << 7), 10);
}
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Initialize the LED_BUILTIN pin as an output
                                // module.setDisplayToString("8888888888888887");
  module.setupDisplay(true, 1);
  delay(500); // wait
  DisplayNumber(123, 123, 123, 123, 0, 0);
  // module.clearDisplay();
}

int i = 0;
void loop()
{
  module.setupDisplay(true, 1);
  delay(500); // wait
  DisplayNumber(123, 456, 127, 123, 0, 0);

}