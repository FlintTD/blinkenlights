#TODO: Standardize the number of bytes in one load signal
import serial
import psutil
import time

#open the serial port COM3 as "ser" at 9600 baud.
ser = serial.Serial('COM3', 9600, timeout = 0.3)
#dummy cpu load value for first iteration.
cpuLoad = '0000'

while (0 < 1):
	#write cpu load value to serial as "%%%.% * 10"-valued integer.
	ser.write(str(cpuLoad).encode())
	#polling CPU usage data for 0.1 seconds.
	cpuLoadRaw = psutil.cpu_percent(interval=0.1)
	cpuLoad = str(round(cpuLoadRaw*10)).zfill(4)
	#wait for return value handshake.
	time.sleep(0.05)
	ret = ser.read(5)
	print(ret)