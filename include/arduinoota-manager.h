#ifndef GULINUX_ARDUINOOTA_MANAGER
#define GULINUX_ARDUINOOTA_MANAGER

#include <LittleFS.h>

namespace GuLinux {

class ArduinoOTAManager {
public:
    using CloseFilesystemCB = std::function<void()>;
    using LoggingFunc = std::function<void(const char*)>;
    void setup(const LoggingFunc &logging, const CloseFilesystemCB &closeFS = {});
    void loop();
    static ArduinoOTAManager &Instance;
private:
};
}
#endif
