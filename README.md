# TM1640LEDDisplay
show numbers with esp32 on  led array using tm1640 and tm1640B

Both TM1640 and 1460B worked with same code!
 
 ### here is a schematic:
![This is an image](https://github.com/amin-amani/TM1640LEDDisplay/blob/main/doc/schematic.PNG)


```
void loop()
{
  module.setupDisplay(true, 1);
  delay(4); // wait
}
```

 ### here is a signal image for set contrast command:
![This is an image](https://github.com/amin-amani/TM1640LEDDisplay/blob/main/doc/setup%20display.PNG)



```
void loop()
{
  module.setSegments(0x1f,2);
  delay(4); // wait

}
```
 ### here is a signal image for set segment with addres 2 and data=0x1f  command:
![This is an image](https://github.com/amin-amani/TM1640LEDDisplay/blob/main/doc/set%20seg.PNG)


### usefull links:

https://wiki.keyestudio.com/KS0357A_Keyestudio_8x16_LED_Matrix_Panel

https://whadda.com/product/i%C2%B2c-8x16-blue-led-matrix-panel-wpi451/
