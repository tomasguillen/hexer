#ifndef HEXER_H  // This is the include guard macro
#define HEXER_H 1
#include <cassert>
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

#ifndef NDEBUG
#define HEXER_ASSERT(condition, message)                                 \
  do {                                                                   \
    if (!(condition)) {                                                  \
      std::cerr << "Assertion `" #condition "` failed in " << __FILE__   \
                << " line " << __LINE__ << ": " << message << std::endl; \
      std::terminate();                                                  \
    }                                                                    \
  } while (false)
#else
#define HEXER_ASSERT(condition, message) \
  do {                                   \
  } while (false)
#endif

namespace hexer {
// prints passed character
inline void print_as_hex(const char character) {
  std::cout << std::setw(2) << std::setfill('0') << std::hex
            << static_cast<int>(static_cast<unsigned char>(character));
}
// when called with just character and pos it just prints that character if
// called with highlight_offset and highlight_size it checks if pos is inside
// that range and then prints the character red
inline void print_as_hex_highlighted(
    const char character, const size_t pos,
    const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {}) {
  if (highlight_offset && highlight_size && pos >= highlight_offset.value() &&
      highlight_offset.value() + highlight_size.value() > pos) {
    std::cout << "\033[1;31m";
    print_as_hex(character);
    std::cout << "\033[0m";
  } else {
    print_as_hex(character);
  }
}
// INPUT: pass an object and a size [offset from object address] and/or an
// optional highlight range [offset from object address, size of range]
// SIDEEFFECT: pretty prints the object memory address up to the address of
// object+size in hexadecimal
template <class Type>
inline void print_address_range_as_hex(
    const Type &object, size_t size,
    std::optional<size_t> highlight_offset = {},
    std::optional<size_t> highlight_size = {},
    std::optional<size_t> start_offset = {}) {
  HEXER_ASSERT(size <= sizeof(Type),
               "HEXER_HELP: size="
                   << size
                   << " Parameter CANNOT Be Larger Than sizeof(Object Type)="
                   << sizeof(Type)
                   << ". Check that you are passing the right size to hexer");
  // NOLINTNEXTLINE
  auto &&char_pointer = reinterpret_cast<const char *>(&object);
  auto start_byte = 0;
  if (start_offset) {
    HEXER_ASSERT(start_offset < size,
                 "HEXER_HELP: start_offset="
                     << start_offset.value()
                     << "Parameter CANNOT Be Larger Than size=" << size
                     << " Parameter "
                        "OF OBJECT TO PRINT");
    start_byte = start_offset.value();
  }
  std::cout << "\n";
  if (size % 2 != 0) --size;
  std::cout << std::setw(8) << std::setfill('0') << std::dec << int(0) << "\t";
  for (size_t group = 1, i = start_byte; i < size; i += 2, ++group) {
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
// INPUT: pass an object and/or an optional highlight range [offset from object
// address, size of range] SIDEEFFECT: pretty prints the object memory address
// in hexadecimal
template <class Type>
inline void print_object_as_hex(
    const Type &object, const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {}) {
  print_address_range_as_hex(object, sizeof(Type), highlight_offset,
                             highlight_size);
}

void print_vec(auto &vector_data) {
  std::cout << "Reading contents of vector: \n";
  for (auto &val : vector_data) {
    std::cout << val << ", ";
  }
  std::cout << "\nEND\n";
}
}  // namespace hexer
#endif
