#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
  std::vector<uint32_t> v;
  v.resize(0xFFFF);
  size_t s;
  s = v.size();
  s = s - 0x66;
  std::cout << std::hex << s << std::endl;
  return 0;
}
