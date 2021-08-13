## C++ Hexer - Pretty Print C++ objects or arbitrary ranges of memory to hexadecimal or binary form
## How to use
### Example 1
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
  std::cout << "\nAddressRange as hex, highlight bytes of TestObject::id member:";

  hexer::print_address_range_as_hex(object, sizeof(TestObject),
                                    offsetof(TestObject, id),
                                    sizeof(std::string), 0);
```
Will Output:\
\
Object as hex, highlight bytes of TestObject::id member:\
00000000        0000 0000 0000 0000 0001 0000 0000 0000\
00000016        **8d60 3ebd 7fff 0000 0007 0000 0000 0000** // <- this are the bytes\
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000** //    of our "id" string\
00000048\

address_range as hex, highlight bytes of TestObject::id member:\
00000000        0000 0000 0000 0000 0001 0000 0000 0000\
00000016        **8d60 3ebd 7fff 0000 0007 0000 0000 0000** // same as above\
00000032        **6564 6166 6c75 0074 d740 4bc8 5588 0000** // \
00000048\

### Example 2
Let's say we want to print a more complex object, and we want to highlight the bytes of the _id_ member:
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};
  };

  struct TestObjectComposed {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    TestObject simple_object{};
    std::string id_outer{"outerdefault"};
  };

  TestObjectComposed composed_object{};
  std::cout << "\nObject as hex, highlight bytes of "
               "TestObjectComposed::id_outer member:";
  hexer::print_object_as_hex(composed_object,
                             offsetof(TestObjectComposed, id_outer),
                             sizeof(std::string));
  std::cout << "\nAddressRange as hex, highlight bytes of "
               "TestObjectComposed::id_outer member:";
  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id_outer),
                                    sizeof(std::string), 0);
  std::cout << "\nAddressRange as hex, highlight bytes of "
               "TestObjectComposed::id_outer member (without last argument "
               "'start_offset'):";
  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id_outer),
                                    sizeof(std::string), 0);
```
Will Output:\
\
Object as hex, highlight bytes of TestObjectComposed::id_outer member:\
00000000        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080        **756f 6574 6472 6665 7561 746c 5500 0000**\
00000096\
\
AddressRange as hex, highlight bytes of TestObjectComposed::id_outer member:\
00000000        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080        **756f 6574 6472 6665 7561 746c 5500 0000**\
00000096\
\
AddressRange as hex, highlight bytes of TestObjectComposed::id_outer member (without last argument 'start_offset'):\
00000000        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080        **756f 6574 6472 6665 7561 746c 5500 0000**\
## API Description
### Just Pass An Object To Print (optional highlight range)
```c++
template <class Type>
void print_object_as_hex(
    const Type &object, const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {})
```
INPUT: pass an object and/or an optional highlight range [offset from object
address, size of range] SIDEEFFECT: pretty prints the object memory address
in hexadecimal

### A Pointer And Size To Print (optional highlight range, and optional start offset for the range)
```c++
template <class Type>
void print_address_range_as_hex(
    const Type &object, size_t size,
    std::optional<size_t> highlight_offset = {},
    std::optional<size_t> highlight_size = {},
    std::optional<size_t> start_offset = {})
```
INPUT: pass an object pointer and a size [offset from object address] and/or an
optional highlight range [offset from object address, size of range]
SIDEEFFECT: pretty prints the address range up to the address of
object+size in hexadecimal
