# C++ Hexer - Pretty Print C++ objects or arbitrary ranges of memory to hexadecimal or binary form
## How to use
Let's say we want to print a simple object, and we want to highlight the bytes of the _id_ member:
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};
  };

  TestObject object{};
  std::cout << "\nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex(object, offsetof(TestObject, id),
                             sizeof(std::string));
  std::cout << "\naddress_range as hex, highlight bytes of TestObject::id member:";

  hexer::print_address_range_as_hex(object, sizeof(TestObject),
                                    offsetof(TestObject, id),
                                    sizeof(std::string), 0);
```
Will Output:
```
Object as hex, highlight bytes of TestObject::id member:
00000000        0000 0000 0000 0000 0001 0000 0000 0000
00000016        **8d60 3ebd 7fff 0000 0007 0000 0000 0000**
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000**
00000048

address_range as hex, highlight bytes of TestObject::id member:
00000000        0000 0000 0000 0000 0001 0000 0000 0000
00000016        **8d60 3ebd 7fff 0000 0007 0000 0000 0000**
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000**
00000048
```

Object as hex, highlight bytes of TestObject::id member:
00000000        0000 0000 0000 0000 0001 0000 0000 0000
00000016        *8d60 3ebd 7fff 0000 0007 0000 0000 0000*
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000**
00000048

address_range as hex, highlight bytes of TestObject::id member:
00000000        0000 0000 0000 0000 0001 0000 0000 0000
00000016        **8d60 3ebd 7fff 0000 0007 0000 0000 0000**
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000**
00000048


## API Description
### Just Pass An Object To Print (optional highlight range)
INPUT: pass an object and/or an optional highlight range [offset from object
address, size of range] SIDEEFFECT: pretty prints the object memory address
in hexadecimal
```c++
template <class Type>
void print_object_as_hex(
    const Type &object, const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {})
```

### A Pointer And Size To Print (optional highlight range)
INPUT: pass an object pointer and a size [offset from object address] and/or an
optional highlight range [offset from object address, size of range]
SIDEEFFECT: pretty prints the address range up to the address of
object+size in hexadecimal
```c++
void print_address_range_as_hex(
    const auto *object_ptr, size_t size,
    const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {})
```
