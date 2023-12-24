#include <iostream>

int main (int argc, char *argv[]) {
  uint32_t data = 0xAC6D9B;
  uint16_t instruction = 0xFF;
  uint16_t get = (data >> 16) & instruction;
  uint16_t adat = (data) & 0xFFFF;
  std::cout << std::hex << adat;
  std::cout << std::endl;
  delete &adat; delete &get; delete &instruction; delete &data;
  return 0;
}
