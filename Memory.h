#ifndef Memory_h
#define Memory_h

#include <Arduino.h>

class Memory {
  public:
    static const uint8_t INIT_FLAG_ADDR = 0;

    Memory();

    uint8_t read(int addr);
    void update(int addr, uint8_t val);
  private:
    void initialize();
    bool isInitialized();
};

#endif