#include <Arduino.h>
#include <TM1640.h>

#if !defined(LED_BUILTIN)
#define LED_BUILTIN 4
#endif

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
  module.setSegments(SEG_NUMS[num % 10] | ((ring > 2) << 7), 5);
  num /= 10;
  module.setSegments((num > 0) ? (SEG_NUMS[num % 10] | ((ring > 1) << 7)) : ((ring > 1) << 7), 2);
  module.setSegments((num > 0) ? (SEG_NUMS[num % 10] | ((ring > 1) << 7)) : ((ring > 1) << 7), 3);
  num /= 10;
  module.setSegments((num > 0) ? (SEG_NUMS[num % 10] | ((ring > 0) << 7)) : ((ring > 0) << 7), 0);
  module.setSegments((num > 0) ? (SEG_NUMS[num % 10] | ((ring > 0) << 7)) : ((ring > 0) << 7), 1);

  module.setSegments((SEG_NUMS[numL % 10] | ((ring > 4) << 7)), 8);
  module.setSegments((SEG_NUMS[numL % 10] | ((ring > 4) << 7)), 9);
  numL /= 10;
  module.setSegments((numL > 0) ? (SEG_NUMS[numL % 10] | ((ring > 3) << 7)) : ((ring > 3) << 7), 6);
  module.setSegments((numL > 0) ? (SEG_NUMS[numL % 10] | ((ring > 3) << 7)) : ((ring > 3) << 7), 7);

  module.setSegments((SEG_NUMS[numR % 10] | ((leftLed) << 7)), 14);
  module.setSegments((SEG_NUMS[numR % 10] | ((leftLed) << 7)), 15);
  numR /= 10;
  module.setSegments((numR > 0) ? (SEG_NUMS[numR % 10] | ((rightLed) << 7)) : ((rightLed) << 7), 12);
  module.setSegments((numR > 0) ? (SEG_NUMS[numR % 10] | ((rightLed) << 7)) : ((rightLed) << 7), 13);
  numR /= 10;
  module.setSegments((numR > 0) ? (SEG_NUMS[numR % 10] | ((ring > 5) << 7)) : ((ring > 5) << 7), 10);
  module.setSegments((numR > 0) ? (SEG_NUMS[numR % 10] | ((ring > 5) << 7)) : ((ring > 5) << 7), 11);
}
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);

  module.setupDisplay(true, 1);
  delay(500);
  module.clearDisplay();
}

int i = 0;
void loop()
{
  module.setupDisplay(true, 1);

  delay(1000);

  DisplayNumber(i % 100, i % 1000, i % 1000, i % 7, i % 2 ? 0 : 1, i % 2 ? 1 : 0);
  i++;
}