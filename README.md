<p align="center">
<img width="192px" height="192px" src="https://user-images.githubusercontent.com/71285258/180133684-46db1c15-70c9-4832-ad1b-cd0b29ccc405.png">&nbsp; &nbsp; <img width="450px" height="192px" src="https://user-images.githubusercontent.com/71285258/180306893-b078f92b-af8f-424e-b409-42ad15712163.png">
  
  <h3 align="center">cppml</h3>
  <p align="center">
    C++ Markup Language
    <br>
    <a href="https://github.com/the-antibody/cppml/blob/main/example/main.cpp">Example</a>
    ·
    <a href="https://github.com/the-antibody/cppml/issues/new">Report Issue</a>
    .
    <a href="https://github.com/the-antibody/cppml/issues/new">Request Feature</a>
    <br />
    <img src="https://img.shields.io/github/license/the-antibody/cppml.svg?style=flat-square">
  </p>
</p>

# About
The `.cml` file extension was created by me so that storing data & configuration in my C programs would be much easier. That project, now archived, was called [cml](https://github.com/Yochran/cml), for "C Markup Language". 
<br><br>
As I transition towards C++ for my software engineering, I decided to recode the cml library for C++, now called **cppml**, which is what this project is. Additionally, new features to the library such as lists inside of objects, and writing to the files has been created, as well as vast improvements on the code structure & memory efficiency. On top of that, the `.cml` file extensoin format was completely reworked, now much more clean, straight-forward, easy to understand, and organized.

# Installation
Create a header file in your C project called `cppml.hpp`. Inside of it, copy and paste the contents of [this](https://github.com/the-antibody/cppml/blob/main/cppml.hpp) file. In your C++ project, include it as shown below:
```c
#include "cppml.hpp"
```
**To create a file, use the `.cml` file extension. Follow the format given below.**

# Format
`Variable Name: Variable Value`<br>

### Example
```yml
StringExample: Test
ListExample: [
  - Entry 1
  - Entry 2
  - Entry 3
]
ObjectExample: {
  ObjectString: This is a string from an object
  ObjectList: [
    - list inside of an object
    - lol
  ]
}
```

# Usage
This is how to use CML in your C++ code.

### Getting a file
```cpp
cppml::file file("filename.cml");
file.load();
```

### Getting Strings
```cpp
std::string string = file.gets("StringName");
```

### Setting Strings
```cpp
file.sets("StringName", "New Value");
file.reload();
```

### Getting Lists
```cpp
std::vector<std::string> list = file.getl("ListName");

// print
for (auto index : list)
 std::cout << index << std::endl;
```

### Adding to Lists
```cpp
file.addl("ListName", "Entry");
file.reload();
```

### Removing from Lists
```cpp
file.rml("ListName", "Entry");
file.reload();
```

### Getting Objects
```cpp
cppml::object object = file.geto("ObjectName");

// get string from object
std::string string = object.gets("StringFromObject");

// set string to new value
object.sets("StringFromObject", "New Value");

// get list from an object
std::vector<std::string> list = object.getl("ListFromObject");
```

