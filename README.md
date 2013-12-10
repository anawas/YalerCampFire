YALERCAMPFIRE for Arduino 
  -------------------------
This sketch for Arduino boards mimics a camp fire made
of two LEDs connected to pin 3 and 6, respectively.
The LEDs flicker randomly giving the impression of a
fire burning. The brightness of the LEDs is controlled 
via the yaler service.
 
It uses the yaler API provided by yaler.org.
The API blocks the sketch while updating the yaler status.
Thus, the LEDs would not flicker until the API returns. The
solution to this was to use the built-in timer interrupt. 
(see sketch interrupt).
The function connected to the interrupt gets called every
0.6 ms. A random counter in the range of 30 to 50 is decreased 
 at each call. If it's == 0, then the state of one of the LED is
changed. This gives a reasonable flickering.
The code comes in 5 files:
YalerCampFire.ino: the main code with setup() and loop()
interrupts.ino: sketch which implements the flickering with a timer interrupt
webdefs.h: declarartions of variables and constants for the yaler API
yalerapi.ino: the code provided by yaler.org to access the yaler service
yalerscript.h: the html/js script that gets uploaded to the yaler server.
 
Enjoy!
7.2.13 / Andreas Wassmer
 
