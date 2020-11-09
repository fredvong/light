#include <EEPROM.h>

const byte MAJOR_VERSION = 0;
const byte MINOR_VERSION = 1;
const byte REVISION = 0;

const byte WIFI_RUNNING_AP = 0;
const byte WIFI_RUNNING_CLIENT = 1;

const int GLOBAL_CONFIG_EPROM_OFFSET = 0;

const int DEFAULT_LED_OUTPUT_PIN = 14;
const int DEFAULT_LED_OUTPUT = 10;

const int DEFAULT_FAN_OUTPUT_PIN = 12;
const int DEFAULT_FAN_OUTPUT = 10;

const int DEFAULT_FAN_SPEED_PIN = 39;

struct GlobalConfig {
  // global configuration
  byte majorVersion;
  byte minorVersion; 
  byte revision;
  
  // wifi info
  byte wifiMode;
  byte wifiLocalIp[4];
  byte wifeGatewayIp[4];
  byte wifiSubnetMask[4];
  char wifiUsername[16];
  char wifiPassword[16];

  // LED
  byte ledPinNumber;
  byte ledOutputSetting;

  // Fan controller
  byte fanOutputPin;
  byte fanOutputSetting;

  // Fan speed readback
  byte FanSpeedPin;
  
};

GlobalConfig globalConfig;

void getGlobalConfig() {
  EEPROM.get(GLOBAL_CONFIG_EPROM_OFFSET, globalConfig);
}

void putGlobalConfig() {
  EEPROM.put(GLOBAL_CONFIG_EPROM_OFFSET, globalConfig);
}

bool isGlobalConfigValid() {
  return globalConfig.majorVersion == MAJOR_VERSION && globalConfig.minorVersion == MINOR_VERSION && globalConfig.revision == REVISION;
}

void setWIFILocalIp(byte d0, byte d1, byte d2, byte d3) {
  globalConfig.wifiLocalIp[0] = d0;
  globalConfig.wifiLocalIp[1] = d1;
  globalConfig.wifiLocalIp[2] = d2;
  globalConfig.wifiLocalIp[3] = d3;
}

bool initDefaultGlobalConfig() {
    globalConfig.majorVersion = MAJOR_VERSION;
    globalConfig.minorVersion = MINOR_VERSION;
    globalConfig.revision = REVISION;

    globalConfig.wifiMode = WIFI_RUNNING_AP;

    // LED
    globalConfig.ledPinNumber = DEFAULT_LED_OUTPUT_PIN;
    globalConfig.ledOutputSetting = DEFAULT_LED_OUTPUT;  

    // Fan control
    globalConfig.fanOutputPin = DEFAULT_FAN_OUTPUT_PIN;
    globalConfig.fanOutputSetting = DEFAULT_FAN_OUTPUT;

    // Fan speed readback
    globalConfig.FanSpeedPin = DEFAULT_FAN_SPEED_PIN;
}
