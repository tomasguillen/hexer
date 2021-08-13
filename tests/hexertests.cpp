#include "../hexer.hpp"

void example1() {
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };

  TestObject object{};
  std::cout << "EXAMPLE1: \nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex(object, offsetof(TestObject, id),
                             sizeof(std::string));

  std::cout
      << "\nAddressRange as hex, highlight bytes of TestObject::id member:";
  hexer::print_address_range_as_hex(object, sizeof(TestObject),
                                    offsetof(TestObject, id),
                                    sizeof(std::string), 0);
}

void example2() {
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
  std::cout << "EXAMPLE2: \nObject as hex, highlight bytes of "
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
}
void example3a() {
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
      << "EXAMPLE3: \nprint_address_range_as_hex (printing the member 'simple_object' "
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
}

void example3b() {
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
  std::cout << "EXAMPLE3b: \nprint_object_as_hex (printing the member 'simple_object' "
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
}

void example4() {
  hexer::print_as_hex('a');
  std::cout << '\n';
  hexer::print_as_hex('\0');
  std::cout << '\n';

  hexer::print_as_bits('a');
  std::cout << '\n';
  hexer::print_as_bits<16>('\0');
  std::cout << '\n';

  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };
  TestObject object{};
  std::cout << "EXAMPLE4: \nObject as hex, highlight bytes of TestObject::id member:";
  hexer::print_object_as_hex<hexer::print_as_bits, 4, hexer::print_as_bits>(
      object, offsetof(TestObject, id), sizeof(std::string));
}
void example5a() {
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

  std::cout << "EXAMPLE5a: \nAddress of composed_object.simple_object as hexadecimal with "
               "composed_object.simple_object.just_an_int3 highlighted and in "
               "binary format";
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
}
void example5b() {
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

  std::cout << "EXAMPLE5b: \nAddress of composed_object.simple_object as hexadecimal with "
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
}
auto main() -> int {
  example1();
  example2();
  example3a();
  example3b();
  example4();
  example5a();
  example5b();
}
