// setting PWM properties
const int fanFreq = 1000;
const int fanChannel = 2; // using timer 1
const int fanResolution = 8;

const int ledFreq = 2000;
const int ledChannel = 3; // using timer 1
const int ledResolution = 8;

String ledSliderValue = "0";
String fanSliderValue = "0";

const int FanOutput = 12;
const int LEDOutput = 14;

void configLED() {
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, ledFreq, ledResolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LEDOutput, ledChannel);
  
  ledcWrite(ledChannel, ledSliderValue.toInt()); 
}

void configFan() {
  // configure Fan PWM functionalitites
  ledcSetup(fanChannel, fanFreq, fanResolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(FanOutput, fanChannel);
  
  ledcWrite(fanChannel, fanSliderValue.toInt()); 
}

void configHardware() {
  configLED();
  configFan();
}

void setLED(String value) {
  ledSliderValue = value;
  ledcWrite(ledChannel, ledSliderValue.toInt()); 
}

void setFan(String value) {
  fanSliderValue = value;
  ledcWrite(fanChannel, ledSliderValue.toInt()); 
}
