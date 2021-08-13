#include "../hexer.hpp"

void example1() {
  struct TestObject {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    std::string id{"default"};  // <-- We want to highlight id member
  };

  TestObject object{};
  std::cout << "\nObject as hex, highlight bytes of TestObject::id member:";
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
}
void example3() {
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
}

auto main() -> int {
  // example1();
  // example2();
  example3();
}
