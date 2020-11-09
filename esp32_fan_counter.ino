// Report time is in second(s)
const int reportTime = 2;

const int pulse_per_count = 2;

// 60 because rpm is measured in minutes
const int factor = 60/reportTime/pulse_per_count;

const int sampleError = 60 / pulse_per_count;

const int oneAnalogThreshold = 1000;

// input pin
const int inputPin = 39;

// interval is in microseconds
const int interval = 100;

// reset pulse count after readCount >= resetCount
const int resetCount = reportTime * 1000000 / interval;

// number of read since Last reset
int readCount = 0;

// number of transitions from 0 to 1 since last reset 
int pulseCount = 0;

int lastInput = 0;

String fanSpeed = "0";

int rawFanSpeed = -1;

// set whether it is analog or digital read
bool IsAnalogRead = true;

void initFanPin() {
  pinMode(inputPin, INPUT);
}


void countPulse() {
  int currentInput;
  if (IsAnalogRead) {
    currentInput = analogRead(inputPin) > oneAnalogThreshold;
  } else {
    currentInput = digitalRead(inputPin);
  }
  if (currentInput == 1 && lastInput == 0) {
    pulseCount++;
  }
  lastInput = currentInput;
  
  if (readCount >= resetCount) {
    int newFanSpeed = pulseCount * factor;
    if (rawFanSpeed < 0) {
      rawFanSpeed = newFanSpeed;
    } else {
      int delta = newFanSpeed - rawFanSpeed;
      if (delta > sampleError || delta < -sampleError) {
        // Beyond the sample error, take the new value
        rawFanSpeed = newFanSpeed;
      } else {
        // Just Average the result
        rawFanSpeed = (rawFanSpeed + newFanSpeed) / 2;
      }
    }
    fanSpeed = String(rawFanSpeed);
//    Serial.println("rpm: " + fanSpeed);
    readCount = 0;
    pulseCount = 0;
  }
  readCount++;
  delayMicroseconds(interval);   
}
