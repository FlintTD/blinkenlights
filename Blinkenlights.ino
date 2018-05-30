//TODO: Standardize the number of bytes in one load signal
int ledPin = 13;
long previousMillis = 0;
long interval = 200;
int cpuLoad = 0;
const int MaxBytes = 5;
char srlString[MaxBytes];
int index = 0;
int outdex = 0;
String stringCpuLoad;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  //check to see if it's time to poll the CPU again.
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval)
  {
    //save the last time you blinked the LED.
    previousMillis = currentMillis;
    
    readSerialString();
    writeSerialString();
    blinkLight();
  }
}

void readSerialString()
{
//read the serial port and create a string and an integer out of what you read.
  int buffer;
  if(Serial.available())
  {
    //Serial.print("Reading Serial String: ");     //optional confirmation for debug
    delay(10);
    while(Serial.available() && (index < MaxBytes))
    {
      buffer = Serial.read();
      srlString[index] = buffer;
      index++;
    }
  }
  stringCpuLoad = String(srlString);
  cpuLoad = stringCpuLoad.toInt();
}

void writeSerialString()
{
//try to write the collected information to serial.
  if (index > 0)
  {
    Serial.print(stringCpuLoad);
    outdex = 0;
    index = 0;
  }
}

void blinkLight()
{
//blink the onboard light.
  digitalWrite(ledPin, HIGH);
  delay((int) (cpuLoad / 5));    //replace with actual blinkenlights
  digitalWrite(ledPin, LOW);
}

