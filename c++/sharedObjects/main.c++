#include <iostream>
#include <vector>

class Ram
{
  public:
    std::vector<uint16_t> ram;

    Ram(size_t size) {ram.resize(size);}
};

class Component
{
  private:
    Ram& mem;

  public:
    Component(Ram& mem) : mem(mem){}
    void set(uint16_t a) {mem.ram[0] = a;}
    uint16_t get() {return mem.ram[0];}
};

int main (int argc, char *argv[]) {
  Ram ram(0xFF);
  Component x(ram);
  x.set(8);
  std::cout << x.get() << std::endl;
  std::cout << ram.ram[0] << std::endl;
  return 0;
}
