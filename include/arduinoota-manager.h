#ifndef GULINUX_ARDUINOOTA_MANAGER
#define GULINUX_ARDUINOOTA_MANAGER

#include <LittleFS.h>

namespace GuLinux {

class ArduinoOTAManager {
public:
    void setup(fs::LittleFSFS *littleFS = nullptr);
    void loop();
    static ArduinoOTAManager &Instance;
};
}
#endif
