#include "arduinoota-manager.h"
#include <ArduinoOTA.h>

GuLinux::ArduinoOTAManager &GuLinux::ArduinoOTAManager::Instance = *new GuLinux::ArduinoOTAManager();

void GuLinux::ArduinoOTAManager::setup(const LoggingFunc &logging, const CloseFilesystemCB &closeFS) {
  ArduinoOTA
    .onStart([logging, closeFS]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH) {
        type = "sketch";
      } else {  // U_SPIFFS
        type = "filesystem";
      }

      if(logging) { logging("[OTA] Start updating "); logging(type.c_str()); logging("\n"); }
      if(closeFS) {
        closeFS();
      }
    })
    .onEnd([logging]() {
      if(logging) logging("\n[OTA] End\n");
    })
    .onProgress([logging](unsigned int progress, unsigned int total) {
      if(logging) {
        static char str[30];
        sprintf(str, "[OTA] Progress: %d%%\r", (progress / (total / 100)));
        logging(str);
      }
    })
    .onError([logging](ota_error_t error) {
      if(!logging) return;
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
      char str[40];
      sprintf(str, "[OTA] Error [%d]: %s\n", error, errorMessage.c_str());
      logging(str);
    });

  ArduinoOTA.begin();
}


void GuLinux::ArduinoOTAManager::loop() {
  ArduinoOTA.handle();
}
