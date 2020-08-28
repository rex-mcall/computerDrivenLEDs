### Computer Driven LEDs

---

## This code is designed to allow the computer to talk to an Arduino over a USB COM port.

---

To get this to work properly, you have to change the batch files to work on the correct COM port that your Arduino is connected to. The default for my Arduino/computer setup is COM3, but yours could be different. On Windows it is COM#, but on Linux it will likely be /dev/ttyUSB#.

You also have to make sure you have the Adafruit NEOPIXEL library installed.

---

I setup both Group Policy and Task Scheduler to run the batch scripts. Group Policy activates the lights on sign in and sign out, and Task Scheduler changes the lights when you lock / unlock the account. This is just one possible use for the setup; it is a proof of concept and could be used for any application where the PC needs to drive an Arduino.
