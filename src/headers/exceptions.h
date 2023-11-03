#pragma once
#include "exception"
#include <string>

using namespace std;

//Custom exceptions class to print error messages.
class number_parsing_exception: public std::exception {
    private:
        //Attribute.
        string *error_message;
    public:
        //Inheritance constructor extension.
        number_parsing_exception(const char *error_message);

        //Method.
        string get_error_message();

        //Inheritance destructor extension.
        ~number_parsing_exception();
};

//Inheritance constructor extension.
number_parsing_exception::number_parsing_exception(const char *error_message): exception() {
    this->error_message = new string(error_message);
}

//Method.
string number_parsing_exception::get_error_message() {
    return *this->error_message;
}

//Inheritance destructor extension.
number_parsing_exception::~number_parsing_exception() {
    delete this->error_message;
}