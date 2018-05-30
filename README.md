# blinkenlights
Code for an Ardunio blinking light panel and its attendant Python script.

### This repo contains all the code which is required to run your very own Arduino-powered panel of "Das Blinkenlights"!

## Requirements
+python3
+pip
+virtualenv
+psutil
+pyserial

+Arduino microcontroller
+Arduino Software IDE

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
