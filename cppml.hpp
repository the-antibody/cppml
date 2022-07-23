#ifndef CPPML_HPP
#define CPPML_HPP

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <map>

// create cppml namespace
namespace cppml 
{
    // create
    class file;
    class exception;
    class object;
}

// exception type enum
enum EXCEPTION_TYPE {
    FILE_NOT_FOUND,
    KEY_NOT_FOUND
};

// public accessible
typedef enum EXCEPTION_TYPE EXCEPTION_TYPE;

// create exception class
class cppml::exception
{
    // private methods
    private:
        /**
         * @brief Converts an exception type enum value to a string
         * 
         * @param type - the type to convert
         */
        std::string to_string(EXCEPTION_TYPE type)
        {
            // the type
            switch (type)
            {
                case FILE_NOT_FOUND:
                    return "FILE_NOT_FOUND_EXCEPTION";
                    break;
                case KEY_NOT_FOUND:
                    return "KEY_NOT_FOUND_EXCEPTION";
                    break;
            }

            // failsafe
            return "NULL";
        }

    // public methods
    public:
        /**
         * @brief Construct a new exception object
         * 
         * @param message 
         * @param type 
         */
        exception(std::string message, EXCEPTION_TYPE type)
        {
            this->message = message;
            this->type = type;
        }

        // the message
        std::string message;

        // the type
        EXCEPTION_TYPE type;

        /**
         * @brief Throw the exception
         */
        void throw_exception()
        {
            std::cout << "Error: " << to_string(this->type) << std::endl << this->message << std::endl;
        }
};

/**
 * @brief Get the name identifier object
 * 
 * @param line 
 * @return std::string 
 */
std::string get_name_identifier(std::string line)
{
    // create cstr
    char *array = new char[line.length() + 1];
                
    // copy to c_str of the line to the array
    std::strcpy(array, line.c_str());

    // create a pointer to the index of the array
    char *index = std::strtok(array, ":");

    // check if null
    while (index != 0)
    {
        return (std::string) index + ": ";

        // go to next index of array (failsafe)
        index = std::strtok(NULL, ":");
                
        break;
    }

    return "NULL";
}

/**
 * @brief Format a list entry
 * 
 * @param entry - the entry to format
 * @return std::string 
 */
std::string format_list_entry(std::string entry)
{
    // create formatted string
    std::string formatted(entry);

    // get line start index
    int index = 0;

    // loop through every character in line
    for (auto i = 0; i < formatted.length(); i++)
    {
        // check if line is "-"
        if (formatted[i] == '-')
        {
            index = i;
            break;
        }
    }

    // remove up to the "-"
    formatted.erase(0, index + 2);

    return formatted;
}

// create object class
class cppml::object
{
    // public methods
    public:
        std::string name;
        std::string file_name;
        std::map<std::string, std::string> strings;
        std::map<std::string, std::pair<int, int>> lists;

        /**
         * @brief Get the name
         * 
         * @return std::string 
         */
        std::string get_name()
        {
            return this->name;
        }

        /**
         * @brief Get the file name
         * 
         * @return std::string 
         */
        std::string get_file_name()
        {
            return this->file_name;
        }

        /**
         * @brief Get a string from an object
         * 
         * @param name - the name to search for
         * @return std::string 
         */
        std::string gets(std::string name)
        {
            // if doesn't exist
            if (this->strings.find(name) == this->strings.end())
            {
                // create exception
                std::string message = "String with the name \"" + name + "\" not found inside of object " + get_name() + ".";
                cppml::exception exception(message, KEY_NOT_FOUND);
                
                // throw exception
                exception.throw_exception();

                exit(0);
            }
            
            return this->strings.at(name);
        }

        /**
         * @brief Get a list from an object
         * 
         * @param name - the name to search for
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getl(std::string name)
        {
            // if doesn't exist
            if (this->lists.find(name) == this->lists.end())
            {
                // create exception
                std::string message = "List with the name \"" + name + "\" not found inside of object " + get_name() + ".";
                cppml::exception exception(message, KEY_NOT_FOUND);
                
                // throw exception
                exception.throw_exception();

                exit(0);
            }

            // create list variable
            std::vector<std::string> list;

            // open the file
            std::ifstream file(get_file_name());

            // line buffer
            std::string buffer;

            // line's index
            int index = 0;

            // loop through every line
            while (getline(file, buffer))
            {
                // check if line is in the object's list
                if (index > this->lists.at(name).first && index < this->lists.at(name).second)
                    // push
                    list.push_back(format_list_entry(buffer));

                index++;
            }

            // close the file
            file.close();

            return list;
        }

        /**
         * @brief Set a string in an object to a new value
         * 
         * @param name - the string
         * @param value - the value to set to
         */
        void sets(std::string name, std::string value)
        {
            // if doesn't exist
            if (this->strings.find(name) == this->strings.end())
            {
                // create exception
                std::string message = "String with the name \"" + name + "\" not found inside of object " + get_name() + ".";
                cppml::exception exception(message, KEY_NOT_FOUND);
                
                // throw exception
                exception.throw_exception();

                exit(0);
            }

            // create lines list
            std::vector<std::string> _lines;

            // open file for reading
            std::ifstream read(get_file_name());

            // create buffer
            std::string buffer;

            // loop through every line
            while (getline(read, buffer))
            {
                // get identifier
                std::string identifier = get_name_identifier(buffer);

                // get line start index
                int index = 0;

                // loop through every character in line
                for (auto i = 0; i < identifier.length(); i++)
                {
                    // check if line is space
                    if (identifier[i] != ' ')
                    {
                        index = i;
                        break;
                    }
                }

                // erase all spaces
                identifier.erase(0, index);

                // if line is the entered string, push the new value in the list
                if (identifier != name + ": ") _lines.push_back(buffer);
                else 
                {
                    // add the spaces
                    std::string spaces;
                    for (auto i = 0; i < index; i++) spaces.insert(0, " ");

                    // push the final string to the lines
                    _lines.push_back(spaces + identifier + value);
                }
            }

            // close the reader
            read.close();

            // open to write
            std::ofstream write(get_file_name());

            // write to the file
            for (auto _index : _lines)
                write << _index << "\n";
            
            // close the writer
            write.close();

            // re insert
            this->strings.erase(name);
            this->strings.insert({name, value});
        }
};

// create file class
class cppml::file
{
    // private methods
    private:
        /**
         * @brief map of the lines in the file
         */
        std::map<int, std::string> lines;

        /**
         * @brief Get the value of a key from the file
         * 
         * @param name - the name to search
         * @return std::string 
         */
        std::pair<int, std::string> __get(std::string name)
        {
            // create the pair variable
            std::pair<int, std::string> line;

            // get the file
            std::ifstream __file(get_name());

            // create iterator
            std::map<int, std::string>::iterator iterator;

            // loop through every line
            for (auto iterator : this->lines)
            {
                // create cstr
                char *array = new char[iterator.second.length() + 1];
                
                // copy to c_str of the line to the array
                std::strcpy(array, iterator.second.c_str());

                // create a pointer to the index of the array
                char *index = std::strtok(array, ":");

                // check if null
                while (index != 0)
                {
                    // check if matches
                    if (index == name)
                    {
                        // set the line pair to current line
                        line.first = iterator.first;
                        line.second = iterator.second;

                        std::string name_identifier = (std::string) index;

                        // break out of both loops
                        break;
                        break;
                    }

                    // go to next index of array
                    index = std::strtok(NULL, ":");
                }
            }

            // close the file
            __file.close();

            // check if null
            if (line.second.empty())
            {
                // create exception
                std::string message = "Key with the name \"" + name + "\" not found.";
                cppml::exception exception(message, KEY_NOT_FOUND);
                
                // throw exception
                exception.throw_exception();

                exit(0);
            }

            // check if temp string was set (safety)
            return line;
        }
    
    // public methods
    public:
        /**
         * @brief Construct a new file object
         * 
         * @param name - the file name
         */
        file(std::string name)
        {
            // set the name
            set_name(name);
        }

        // name
        std::string name;

        /**
         * @brief Get the file name
         * 
         * @return std::string 
         */
        std::string get_name() 
        {
            return this->name;
        }

        /**
         * @brief Set the file name
         * 
         * @param __name - the name to set to
         */
        void set_name(std::string name)
        { 
            // checker
            std::ifstream file(name);

            // check if file exists
            if (file.good())
                this->name = name;
            else
            {
                // create exception
                std::string message = "File with the name \"" + name + "\" not found.";
                cppml::exception exception(message, FILE_NOT_FOUND);

                // throw exception
                exception.throw_exception();
                exit(0);
            }

            // close file
            file.close();
        }

        /**
         * @brief Inserts all lines in the file into the map
         */
        void load()
        {
            // open file for reading
            std::ifstream __file(get_name());

            // create line buffer
            std::string line;
            
            // create line index
            int index = 0;

            // loop through every line
            while (getline(__file, line))
            {
                // insert line into map
                this->lines.insert({index, line});
                index++;
            }

            __file.close();
        }

        void reload()
        {
            // clear data
            this->lines.clear();

            // load data
            load();
        }

        /**
         * @brief Gets a string from the file
         * 
         * @param name - the name to search
         * @return std::string 
         */
        std::string gets(std::string name)
        {
            // get the pair
            std::pair<int, std::string> line = __get(name);

            // get the line
            std::string __line = line.second;

            // get the value of the line
            std::string value = line.second;
            value.erase(0, get_name_identifier(line.second).length());

            if (value != "[]" && value != "{}")
                return value;
            else
            {
                // create exception
                std::string message = "A string with the name \"" + name + "\" was not found.";
                cppml::exception exception(message, KEY_NOT_FOUND);

                // throw exception
                exception.throw_exception();

                // exit
                exit(0);

                return "NULL";
            }
        }

        /**
         * @brief Get a list from the file
         * 
         * @param name - the name to search for
         * @return std::vector<std::string> 
         */
        std::vector<std::string> getl(std::string name)
        {
            // create vector variable
            std::vector<std::string> list;

            // get the line
            std::pair<int, std::string> line = __get(name);

            // get the value of the line
            std::string value = line.second;
            value.erase(0, get_name_identifier(line.second).length());

            // check if a list
            if (value == "[")
            {
                // get index of line
                int index = line.first;

                // create end index;
                int end = 0;

                // loop through every following line in list
                for (auto a = (line.first + 1); a < this->lines.size(); a++)
                {
                    // get current line
                    std::string _line = this->lines.at(a);

                    // if line is end list market, set end index
                    if (_line == "]")
                    {
                        end = a;
                        break;
                    }
                }

                // add lines to list
                for (auto a = (line.first + 1); a < end; a++)
                {
                    // get current line
                    std::string _line = this->lines.at(a);

                    // format entry
                    std::string formatted = format_list_entry(_line);

                    // push
                    list.push_back(formatted);
                }
            } 
            else
            {
                // create exception
                std::string message = "A list with the name \"" + name + "\" was not found.";
                cppml::exception exception(message, KEY_NOT_FOUND);

                // throw exception
                exception.throw_exception();

                // exit
                exit(0);
            }

            return list;
        }

        /**
         * @brief Get an object from the file
         * 
         * @param name - the name to search for
         * @return cppml::object 
         */
        cppml::object geto(std::string name)
        {
            // create object variable
            cppml::object object;

            // get the line
            std::pair<int, std::string> line = __get(name);

            // get the value of the line
            std::string value = line.second;
            value.erase(0, get_name_identifier(line.second).length());

            // check if an object
            if (value == "{")
            {
                // get index of line
                int index = line.first;

                // create end index;
                int end = 0;

                // loop through every following line in object
                for (auto i = (line.first + 1); i < this->lines.size(); i++)
                {
                    // get current line
                    std::string _line(this->lines.at(i));

                    // if line is end object market, set end index
                    if (_line == "}")
                    {
                        end = i;
                        break;
                    }
                }

                // add everything to the object
                for (auto a = (line.first + 1); a < end; a++)
                {
                    // get current line
                    std::string _line(this->lines.at(a));

                    // get line start index
                    int _index = 0;

                    // loop through every character in line
                    for (auto b = 0; b < _line.length(); b++)
                    {
                        // check if line is space
                        if (_line[b] != ' ')
                        {
                            _index = b;
                            break;
                        }
                    }

                    // erase all spaces
                    _line.erase(0, _index);

                    // create name and value strings
                    std::string name, _value;

                    // create cstr
                    char *array = new char[_line.length() + 1];
                
                    // copy to c_str of the line to the array
                    std::strcpy(array, _line.c_str());

                    // create a pointer to the index of the array
                    char *__index = std::strtok(array, ": ");

                    // check if null
                    while (__index != 0)
                    {
                        name = __index;
                        break;
                    }

                    // format the value
                    _value = _line.erase(0, get_name_identifier(_line).length());

                    // if string, insert to strings
                    if (name != "-" && name != "]" && _value != "[") 
                        object.strings.insert({name, _value});
                    // if list, insert to lists
                    else if (_value == "[")
                    {
                        // create start end pair
                        std::pair<int, int> start_end;

                        // create end index;
                        int _end = 0;

                        // loop through every following line in list
                        for (auto b = a; b < this->lines.size(); b++)
                        {
                            // get current line
                            std::string __line(this->lines.at(b));

                            // get line start index
                            int __index_ = 0;

                            // loop through every character in line
                            for (auto b = 0; b < __line.length(); b++)
                            {
                                // check if line is space
                                if (__line[b] != ' ')
                                {
                                    __index_ = b;
                                    break;
                                }
                            }

                            // erase all spaces
                            __line.erase(0, __index_); 

                            // if line is end list market, set end index
                            if (__line == "]")
                            {
                                _end = b;
                                break;
                            }
                        }

                        // set the start line
                        start_end.first = a;

                        // set the end line
                        start_end.second = _end;

                        object.lists.insert({name, start_end});
                    }
                }
            } 
            else
            {
                // create exception
                std::string message = "An object with the name \"" + name + "\" was not found.";
                cppml::exception exception(message, KEY_NOT_FOUND);

                // throw exception
                exception.throw_exception();

                // exit
                exit(0);
            }

            // set the name
            object.name = name;

            // set the file name
            object.file_name = get_name();

            return object;
        };

        /**
         * @brief Set a string to a value in the file
         * 
         * @param string - the string
         * @param value - the value to set to
         */
        void sets(std::string string, std::string value)
        {
            // create lines list
            std::vector<std::string> _lines;

            // loop through every line
            for (auto index : this->lines)
            {
                // get identifier
                std::string identifier = get_name_identifier(index.second);

                // if line is the entered string, push the new value in the list
                if (identifier != string + ": ") _lines.push_back(index.second);
                else _lines.push_back(identifier + value);
            }

            // open to write
            std::ofstream write(get_name());

            // write to the file
            for (auto _index : _lines)
                write << _index << "\n";
            
            // close the writer
            write.close();
        }

        /**
         * @brief Add a value to the list
         * 
         * @param string - the list
         * @param value - the new list to set to
         */
        void addl(std::string name, std::string value)
        {
            // get the current list
            std::vector<std::string> _list = this->getl(name);

            // create lines list
            std::vector<std::string> _lines;

            // loop through every line
            for (auto index : this->lines)
            {
                // create line variable
                std::string line(index.second);

                // get identifier
                std::string identifier = get_name_identifier(line);

                // push the line
                _lines.push_back(line);

                // check if line is declaration of list, if is, add to list
                if (identifier == name + ": ") _lines.push_back("  - " + value);
            }

            // open to write
            std::ofstream write(get_name());

            // write to the file
            for (auto _index : _lines)
                write << _index << "\n";
            
            // close the writer
            write.close();
        }

        /**
         * @brief Remove an entry from a list
         * 
         * @param name - the list
         * @param entry - the entry to remove
         */
        void rml(std::string name, std::string entry)
        {
            // get the current list
            std::vector<std::string> list = this->getl(name);

            // create lines list
            std::vector<std::string> _lines;

            // loop through every line
            for (auto index : this->lines)
            {
                // create line variable
                std::string line(index.second);

                // get identifier
                std::string identifier = get_name_identifier(line);

                // format the entry
                std::string _line = format_list_entry(line);

                // check if line is declaration of list, if is, remove from list
                if (entry != _line)
                    _lines.push_back(line);
            }

            // open to write
            std::ofstream write(get_name());

            // write to the file
            for (auto _index : _lines)
                write << _index << "\n";
            
            // close the writer
            write.close();
        }
};

#endif