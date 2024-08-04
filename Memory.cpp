#include "Memory.h"
#include <EEPROM.h>

Memory::Memory() {
  if (!isInitialized()) {
    initialize();
  }
}

uint8_t Memory::read(int addr) {
  return EEPROM.read(addr);
}

void Memory::update(int addr, uint8_t val) {
  EEPROM.update(addr, val);
}

void Memory::initialize() {
  Serial.println("Intializing EEPROM");
  for (int i = 0; i < EEPROM.length(); i++) {
    update(i, 0);
  }

  update(Memory::INIT_FLAG_ADDR, true);
}

bool Memory::isInitialized() {
  return read(Memory::INIT_FLAG_ADDR) == true;
}