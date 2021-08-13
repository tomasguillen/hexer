#include "../hexer.hpp"

auto main() -> int {
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
  /*
  struct TestObjectComposed {
    int just_an_int{}, just_an_int2{}, just_an_int3 = 1;
    TestObject simple_object{};
    std::string id{"default"};
  };

  TestObjectComposed composed_object{};
  hexer::print_object_as_hex(composed_object, offsetof(TestObjectComposed, id),
                             sizeof(std::string));

  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id),
                                    sizeof(std::string));

  hexer::print_address_range_as_hex(composed_object, sizeof(TestObjectComposed),
                                    offsetof(TestObjectComposed, id),
                                    sizeof(std::string));

  hexer::print_address_range_as_hex(
      composed_object, sizeof(TestObjectComposed),
      offsetof(TestObjectComposed, simple_object.just_an_int3),
      sizeof(composed_object.simple_object.just_an_int3),
      offsetof(TestObjectComposed, simple_object.id));
  */
}
