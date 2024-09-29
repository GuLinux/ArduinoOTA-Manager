#include "arduinoota-manager.h"
#include <ArduinoOTA.h>
#include <ArduinoLog.h>

GuLinux::ArduinoOTAManager &GuLinux::ArduinoOTAManager::Instance = *new GuLinux::ArduinoOTAManager();

void GuLinux::ArduinoOTAManager::setup(fs::LittleFSFS *littleFS) {
  ArduinoOTA
    .onStart([littleFS]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Log.infoln("Start updating %s", type.c_str());
      if(littleFS) {
        littleFS->end();
      }
    })
    .onEnd([]() {
      Log.infoln("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Log.infoln("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      String errorMessage;
      if (error == OTA_AUTH_ERROR) {
        errorMessage = "Auth Failed";
      } else if (error == OTA_BEGIN_ERROR) {
        errorMessage = "Begin Failed";
      } else if (error == OTA_CONNECT_ERROR) {
        errorMessage = "Connect Failed";
      } else if (error == OTA_RECEIVE_ERROR) {
        errorMessage = "Receive Failed";
      } else if (error == OTA_END_ERROR) {
        errorMessage = "End Failed";
      } else {
        errorMessage = "Unknown error";
      }
      Log.errorln("Error[%u]: %s", error, errorMessage.c_str());
    });

  ArduinoOTA.begin();
}


void GuLinux::ArduinoOTAManager::loop() {
  ArduinoOTA.handle();
}
