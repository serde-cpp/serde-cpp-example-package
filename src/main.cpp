#include <cassert>
#include <iostream>
#include <string>

#include <serde_yaml/serde_yaml.h>
#include "main_serde.h"  // the generated file with serialization code

struct [[serde]] Point {
  int x;
  int y;
};

int main() {
  Point point{ 10, 20 };

  // automatic serialization
  std::string serialized = serde_yaml::to_string(point).value();
  std::cout << serialized << std::endl;

  // automatic deserialization
  Point deserialized = serde_yaml::from_str<Point>("x: 10\ny: 20\n\n").value();
  assert(point.x == deserialized.x && point.y == deserialized.y);
}
