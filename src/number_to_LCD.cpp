#include "headers/number_parser.h"
#include <iostream>

using namespace std;

/*
*   The program receives one argument.
*   1.- Input number string.
*/
int main(int const argc, char* argv[]) {
    try {
        string *number_string;
        if(argc < 2) {
            cout << "Input number not supplied. Using default value (0123456789)." << endl;
            number_string = new string("0123456789");
        }
        else {
            number_string = new string(argv[1]);
        }

        cout << "Input string: " << *number_string << "." << endl;
        number_to_lcd_parser *number_parser = new number_to_lcd_parser(*number_string);

        cout << "Generated LCD number:" << endl;
        number_parser->print_lcd_number();

        delete number_string, number_parser;
        return 0;
    }
    catch(number_parsing_exception &error) {
        cerr << error.get_error_message() << ".";
    }
    catch(exception &error) {
        cerr << error.what() << ".";
    }
    catch(...) {
        cerr << "An error has ocurred while trying to generate the LCD number.";
    }
    return 1;
}