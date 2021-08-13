## C++ Hexer - Pretty Print C++ objects or arbitrary ranges of memory to hexadecimal or binary form
## How to use
### Example 1
Let's say we want to print a simple object, and we want to highlight the bytes of the _id_ member (**these two function calls will do the same**):
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};
  };

  TestObject object{};
  std::cout << "\nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex(object, offsetof(TestObject, id),
                             sizeof(std::string));
  // same as above
  std::cout << "\nAddressRange as hex, highlight bytes of TestObject::id member:";
  hexer::print_address_range_as_hex(object, sizeof(TestObject),
                                    offsetof(TestObject, id),
                                    sizeof(std::string), 0);
```
This will print:

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
Let's say we want to print a more complex object, and we want to highlight the bytes of the _id_ member(**these three function calls will do the same**):
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
  // same as above
  std::cout << "\nAddressRange as hex, highlight bytes of "
               "TestObjectComposed::id_outer member:";
  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id_outer),
                                    sizeof(std::string), 0);
  // same as above
  std::cout << "\nAddressRange as hex, highlight bytes of "
               "TestObjectComposed::id_outer member (without last argument "
               "'start_offset'):";
  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id_outer),
                                    sizeof(std::string), 0);
```
This will print:

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
**print_address_range_as_hex** allows us to control the ranges for both the printing and the highlight area.
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
      << "\nprint_address_range_as_hex (printing the 'simple_object' member "
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
This will print:

Here we use print_address_range_as_hex to print the 'simple_object' member and highlighting the bytes of its 'just_an_int3' member):\
00000000&emsp;        0000 0000 0000 0000 **0001 0000** 0000 0000\
00000032&emsp;        52b0 8299 7ffc 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 7717 4b9d 7fd7 0000\
00000064

We can do something similar with **print_object_as_hex** by just passing **composed_object.simple_object** directly:
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
      << "\nprint_object_as_hex (printing the member 'simple_object' "
         "and highlighting the bytes of its 'just_an_int3' member):";
  hexer::print_object_as_hex(
      composed_object.simple_object,  // object we want to print
      offsetof(
          TestObjectComposed,
          simple_object.just_an_int3),  // we will highlight from the start of
                                        // simple_object.just_an_int3 address
      sizeof(composed_object.simple_object
                 .just_an_int3));  // we will stop highlighting at the end of
                                   // simple_object.just_an_int3
```

### Example 4
Same as example 3 using **print_object_as_hex** but with everything printed as bits and in columns of 4:

```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };
  TestObject object{};
  std::cout << "EXAMPLE4: \nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex<hexer::print_as_bits, 4, hexer::print_as_bits>(
      object, offsetof(TestObject, id), sizeof(std::string));
```
This will print:

Object as hex, highlight bytes of TestObject::id member:\
00000000&emsp;        0000000000000000 0000000000000000 0000000000000000 0000000000000000\
00000008&emsp;        0000000000000001 0000000000000000 0111111011111111 0000000000000000\
00000016&emsp;        0000101101000000 1101100100001000 0111111111111101 0000000000000000\
00000024&emsp;        0000000000000111 0000000000000000 0000000000000000 0000000000000000\
00000032&emsp;        0110010101100100 0110000101100110 0110110001110101 0000000001110100\
00000040&emsp;        1100000110001000 0101110000010000 0111111011111111 0000000000000000\
00000048

## API Description
### * print_object_as_hex
Just Pass An Object To Print (optional highlight range)
```c++
template <void PrintFunction(const char) = print_as_hex,
          size_t NewLineAfterNElements = 8,
          void HighlightedPrintFunction(const char) = print_as_hex, class Type>
inline void print_object_as_hex(
    const Type &object, const std::optional<size_t> highlight_offset = {},
    const std::optional<size_t> highlight_size = {})
```
#####**INPUT:** pass an object and/or an optional highlight range [offset from object
address, size of range]\
#####**SIDEEFFECT:** pretty prints the object memory address in hexadecimal, with optional highlighting
#####**TEMPLATE PARAMETERS:**
1. **PrintFunction:** A function that prints a single character. Used to format each character. Hexer has 2 available functions(default =**print_as_hex**):
a. ```c++print_as_hex('\0')``` will print ```00```; ```c++print_as_bits('a')``` will print ```61```\
**inline void print_as_hex(const char character)**
b. ```c++print_as_bits('\0')``` will print ```00000000```; ```c++print_as_bits('a')``` will print ```01100001```\
**template <size_t BitsToPrint = 8>\
inline void print_as_bits(const char character)**
2. **NewLineAfterNElements:** The number of columns our output will have defaults to 8
3. **HighlightedPrintFunction:** Same as **PrintFunction** but for highlighted bytes. This way we can have highlighted bytes in hex or binary, independently from **PrintFunction**.
#####**FUNCTION PARAMETERS:**
1. **object:** The object we want hexer to print.
3. **highlight_offset:** An offset at which hexer will start highlighting bytes.
4. **highlight_size:** A size after which hexer will stop highlighting bytes.
### * print_address_range_as_hex
And Object And Size To Print (optional highlight range, and optional start_offset for the print range)
```c++
template <void PrintFunction(const char) = print_as_hex,
          size_t NewLineAfterNElements = 8,
          void HighlightedPrintFunction(const char) = print_as_hex, class Type>
inline void print_address_range_as_hex(
    const Type &object, size_t size,
    std::optional<size_t> highlight_offset = {},
    std::optional<size_t> highlight_size = {},
    std::optional<size_t> start_offset = {})
```
#####**INPUT:** pass an object pointer and a size [offset from object address], and/or an
optional highlight range [offset from object address, size of range], and or an 
optional start_offset
#####**SIDEEFFECT:**
pretty prints the address range up to the address of object+size in hexadecimal with optional highlighting and start_offset
#####**TEMPLATE PARAMETERS:**
1. **PrintFunction:** A function that prints a single character. Used to format each character. Hexer has 2 available functions(default =**print_as_hex**):
a. ```c++print_as_hex('\0')``` will print ```00```; ```c++print_as_bits('a')``` will print ```61```\
**inline void print_as_hex(const char character)**
b. ```c++print_as_bits('\0')``` will print ```00000000```; ```c++print_as_bits('a')``` will print ```01100001```\
**template <size_t BitsToPrint = 8>\
inline void print_as_bits(const char character)**
2. **NewLineAfterNElements:** The number of columns our output will have defaults to 8
3. **HighlightedPrintFunction:** Same as **PrintFunction** but for highlighted bytes. This way we can have highlighted bytes in hex or binary, independently from **PrintFunction**.
#####**FUNCTION PARAMETERS:**
1. **object:** The object we want hexer to print.
2. **size:** An offset at which hexer will stop printing bytes.
3. **highlight_offset:** An offset at which hexer will start highlighting bytes.
4. **highlight_size:** A size after which hexer will stop highlighting bytes.
5. **start_offset:** An offset from the start of the object at which hexer will start printing the bytes

### Advanced Examples:
Let's say we want to inspect the bits of **composed_object.simple_object.just_an_int3**, suppose we want to start printing bytes as hexadecimal but have the highlighted bytes in binary format:
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };
  TestObject object{};
  std::cout << "\nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex<hexer::print_as_bits, 4>(
      object, offsetof(TestObject, id), sizeof(std::string));
}
void example5() {
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };
  struct TestObjectComposed {
    int just_an_int_outer{}, just_an_int_outer2{}, just_an_int_outer3 = 1;
    TestObject simple_object{};
    std::string id_outer{"outerdefault"};
  };
  TestObjectComposed composed_object{};

  std::cout << "\nAddress of composed_object.simple_object as hexadecimal with composed_object.simple_object.just_an_int3 highlighted and in binary format";
  hexer::print_address_range_as_hex<hexer::print_as_hex, 8,
                                    hexer::print_as_bits>(
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
This will print:

Address of composed_object.simple_object as hexadecimal with composed_object.simple_object.just_an_int3 highlighted and in binary format\
00000000&emsp;        0000 0000 0000 0000 **0000000000000001 0000000000000000** 7f8f 0000\
00000032&emsp;        abd0 43b2 7fff 0000 0007 0000 0000 0000\
00000048&emsp;        6564 6166 6c75 0074 0000 0000 0000 0000\
00000064

We can achieve the same with **print_object_as_hex**:
```c++
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };
  struct TestObjectComposed {
    int just_an_int_outer{}, just_an_int_outer2{}, just_an_int_outer3 = 1;
    TestObject simple_object{};
    std::string id_outer{"outerdefault"};
  };
  TestObjectComposed composed_object{};

  std::cout << "\nAddress of composed_object.simple_object as hexadecimal with "
               "composed_object.simple_object.just_an_int3 highlighted and in "
               "binary format";
  hexer::print_object_as_hex<hexer::print_as_hex, 8,
                                    hexer::print_as_bits>(
      composed_object.simple_object,  // object we want to print
      offsetof(
          TestObjectComposed,
          simple_object.just_an_int3),  // we will highlight from the start of
                                        // simple_object.just_an_int3 address
      sizeof(composed_object.simple_object
	     .just_an_int3));  // we will stop highlighting at the end of
                                  // simple_object.just_an_int3
```
