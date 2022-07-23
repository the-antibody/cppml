#include <iostream>
#include <vector>

#include "cppml.hpp"

int main()
{
    // create the file
    cppml::file file("file.cml");
    file.load();

    // get a string
    std::string string = file.gets("StringExample");

    // print string
    std::cout << string << std::endl;
  
    // get a list
    std::vector<std::string> list = file.getl("ListExample");
  
    // print every entry in the list
    for (auto entry : list)
      std::cout << entry << std::endl;
  
    // set the string "StringExample"'s value to "new value"
    file.sets("StringExample", "new value");
    file.reload();

    // add the entry "new entry" to the list "ListExample"
    file.addl("ListExample", "new entry");
    file.reload();
  
    // get an object
    cppml::object object = file.geto("ObjectExample");
  
    // get a string from the object
    std::string object_string = object.gets("ObjectString");
  
    // print object string
    std::cout << object_string << std::endl;

    // set the string "ObjectString"'s value to "new value"
    object.sets("ObjectString", "new value");
  
    // get a list from the object
    std::vector<std::string> object_list = object.getl("ObjectList");
  
    // print every entry in the list
    for (auto entry : object_list)
      std::cout << entry << std::endl;

    return 0;
}
