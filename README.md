# blinkenlights
Code for an Ardunio blinking light panel and its attendant Python script.


### This repo contains all the code which is required to run your very own Arduino-powered panel of "Das Blinkenlights"!


The intended use for this code is to create a 5" Bay panel which will indicate various computer statuses via blinking LED lights.


## State of the Blinkenlights
Currently, the only thing which this code will do is enable an Arduino Uno to blink its onboard LED in relation to how burdened a host computer's CPU is.  The LED blinks HIGH for an amount of time proportional to 200ms for every 200ms which elapses: 0% usage being not on at all, and 100% being on for the full 200ms.  This creates a flicker effect, similar to a Hard Drive usage LED commonly found on PC cases.

I plan to expand this use case to include arbitrary circuitry (such as electric guages or off-board LEDs) with future updates.  I also plan to expand the amount and kind of data which is sent to the Arduino, to allow for even more plentiful blinkenlights!


## Requirements
+ python3
+ pip
+ virtualenv
+ psutil
+ pyserial

+ Arduino microcontroller
+ Arduino Software IDE


## Principals of Operation 
+ The Arduino is hard-coded to look for new data coming across its serial connection every `interval` milliseconds (this is 200ms by default).
+ Each time it sees data, it reads in a sequence of 5 Characters.  These are 4 numerals and a terminator.
+ After it does this, it sends the exact same message back across the serial connection, and then blinks the lights based on the data it recieved.

+ The Python script scrapes CPU usage data via *psutil* and sends it to the Arduino microcontroller.
+ It does this in a constant loop, which is timed by the Arduino's responses.  The script will wait for `timeout` seconds for 5 Characters to come across the serial connection (this is 0.3sec by default).
+ After it recieves this "handshake" message, it prints it to the terminal and immediately sends the next CPU load percentage back across the serial connection.

+ In this way, the script will wait for the Ardunio to do it's thing before cycling.
+ The 5 Character standard is a safety precaution so that both sides of the serial connection will know where one message starts and another begins.  It also helps with keeping both sides synchronized.


## Startup Procedures
1. Obtain this repository through GitHub
2. Prepare a virtual environment (via virtualenv) to install the Python dependencies within.  I suggest this be done within your copy of the repository.  Dependencies are detailed in a requirements.txt file within this repo for that purpose!
3. Load the **Blinkenlights.ino** file into your Arduino microcontroller via a cable and serial port.  Do not remove this cable.
4. Open up **Blinkenlights.py** (with any text editor you please).
5. Change `COM3` in line `ser = serial.Serial('COM3', 9600, timeout = 0.3)` to be the name of the serial port to which your Arduino is connected.  (I wrote this on a Windows machine, so `COM3` was the serial port my Arduno Uno used.)
6. Ensure the Arduino IDE's Serial Monitor is not active (this blocks Python from accessing the serial port!).
7. Run **Blinkenlights.py** while the virtual environment is active.
8. Enjoy your Blinkenlights!


> Inspired by old mainframe computers and modern servers, and named in reverence of https://en.wikipedia.org/wiki/Blinkenlights
