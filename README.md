# C++ Hexer - Pretty Print C++ objects or arbitrary ranges of memory to hexadecimal or binary form
## How to use:

INPUT: pass an object and/or an optional highlight range [offset from object
address, size of range] SIDEEFFECT: pretty prints the object memory address
in hexadecimal
```c++
print_as_hex(Type &object,
                         std::optional<size_t> highlight_offset = {},
                         std::optional<size_t> highlight_size = {})
```
INPUT: pass an object and a size [offset from object address] and/or an
optional highlight range [offset from object address, size of range]
SIDEEFFECT: pretty prints the object memory address up to the address of
object+size in hexadecimal

```c++

print_as_hex(auto &object, size_t size,
                         std::optional<size_t> highlight_offset = {},
                         std::optional<size_t> highlight_size = {})
```
