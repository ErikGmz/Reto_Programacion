#pragma once
#include "exception"
#include <string>

using namespace std;

//Custom exceptions class to print error messages.
class number_parsing_exception: public std::exception {
    private:
        string error_message;
    public:
        number_parsing_exception(const char *error_message): exception() {
            this->error_message = error_message;
        }

        string get_error_message();
};

string number_parsing_exception::get_error_message() {
    return this->error_message;
}