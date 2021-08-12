#ifndef HEXER_H // This is the include guard macro
#define HEXER_H 1
#include <iomanip>
#include <iostream>
#include <optional>

/*

  Copyright 2021 Pedro Tomas Guillen

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

*/

inline void print_as_hex(char character) {
  std::cout << std::setw(2) << std::setfill('0') << std::hex
            << static_cast<int>(static_cast<unsigned char>(character));
}
inline void print_as_hex_highlighted(
    char character, size_t pos, std::optional<size_t> highlight_offset = {},
    std::optional<size_t> highlight_size = {}) {
  if (highlight_offset && highlight_size && pos >= highlight_offset.value() &&
      highlight_offset.value() + highlight_size.value() > pos) {
    std::cout << "\033[1;31m";
    print_as_hex(character);
    std::cout << "\033[0m";
  } else {
    print_as_hex(character);
  }
}

inline void print_as_hex(auto &object, size_t size,
                         std::optional<size_t> highlight_offset = {},
                         std::optional<size_t> highlight_size = {}) {
  auto &&char_pointer = reinterpret_cast<char *>(&object);
  std::cout << "\n";
  if (size % 2 != 0) --size;
  std::cout << std::setw(8) << std::setfill('0') << std::dec << int(0) << "\t";
  for (size_t group = 1, i = 0; i < size; i += 2, ++group) {
    print_as_hex_highlighted(char_pointer[i + 1], i + 1, highlight_offset,
                             highlight_size);
    print_as_hex_highlighted(char_pointer[i], i, highlight_offset,
                             highlight_size);

    std::cout << " ";
    if (group == 8) {
      group = 0;
      std::cout << "\n";
      std::cout << std::setw(8) << std::setfill('0') << std::dec << int(i + 2)
                << "\t";
    }
  }
  std::cout << std::dec << '\n';
}

template <class Type>
inline void print_as_hex(Type &object,
                         std::optional<size_t> highlight_offset = {},
                         std::optional<size_t> highlight_size = {}) {
  print_as_hex(object, sizeof(Type), highlight_offset, highlight_size);
}

void print_vec(auto &vector_data) {
  std::cout << "Reading contents of vector: \n";
  for (auto &val : vector_data) {
    std::cout << val << ", ";
  }
  std::cout << "\nEND\n";
}
#endif
