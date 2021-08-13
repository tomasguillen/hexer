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
00000000&emsp;        0000 0000 0000 0000 0001 0000 0000 0000\
00000016&emsp;        **8d60 3ebd 7fff 0000 0007 0000 0000 0000**    // <- this are the bytes\
00000032&emsp;        **6564 6166 6c75 0074 d740 4bc8 5588 0000**    //    of our "id" string\
00000048

address_range as hex, highlight bytes of TestObject::id member:\
00000000&emsp;        0000 0000 0000 0000 0001 0000 0000 0000\
00000016&emsp;        **8d60 3ebd 7fff 0000 0007 0000 0000 0000**    // same as above\
00000032&emsp;        **6564 6166 6c75 0074 d740 4bc8 5588 0000**    // \
00000048

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

Object as hex, highlight bytes of TestObjectComposed::id_outer member:\
00000000&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032&emsp;        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064&emsp;        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080&emsp;        **756f 6574 6472 6665 7561 746c 5500 0000**\
00000096

AddressRange as hex, highlight bytes of TestObjectComposed::id_outer member:\
00000000&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032&emsp;        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064&emsp;        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080&emsp;        **756f 6574 6472 6665 7561 746c 5500 0000**\
00000096

AddressRange as hex, highlight bytes of TestObjectComposed::id_outer member (without last argument 'start_offset'):\
00000000&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000016&emsp;        0000 0000 0000 0000 0001 0000 7f59 0000\
00000032&emsp;        6f50 9313 7ffd 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 ff90 de2f 7f59 0000\
00000064&emsp;        **6f70 9313 7ffd 0000 000c 0000 0000 0000**\
00000080&emsp;        **756f 6574 6472 6665 7561 746c 5500 0000**
### Example 3
Let's say we want to print a more complex object, and we want to highlight the bytes of the _id_ member:
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};
  };

  struct TestObjectComposed {
    int just_an_int_outer{}, just_an_int_outer2{}, just_an_int_outer3 = 1;
    TestObject simple_object{};
    std::string id_outer{"outerdefault"};
  };
  TestObjectComposed composed_object{};
  std::cout
      << "\nHere we make use of all the features of "
         "print_address_range_as_hex (printing the member 'simple_object' "
         "and highlighting the bytes of its 'just_an_int3' member):";
  hexer::print_address_range_as_hex(
      composed_object,  // object we want to print
      offsetof(TestObjectComposed,
               id_outer),  // we will stop printing
                           // bytes at the start of id_outer address
      offsetof(
          TestObjectComposed,
          simple_object.just_an_int3),  // we will highlight from the start of
                                        // simple_object.just_an_int3 address
      sizeof(composed_object.simple_object
                 .just_an_int3),  // we will stop highlighting at the end of
                                  // simple_object.just_an_int3
      offsetof(TestObjectComposed,
               simple_object));  // we will start printing bytes at the start of
                                 // simple_object address
```
Will Output:\

Here we make use of all the features of print_address_range_as_hex (printing the member 'simple_object' and highlighting the bytes of its 'just_an_int3' member):\
00000000&emsp;        0000 0000 0000 0000 **0001 0000** 0000 0000\
00000032&emsp;        52b0 8299 7ffc 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 7717 4b9d 7fd7 0000\
00000064
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
