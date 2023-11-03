#include "headers/number_parser.h"
#include <iostream>

using namespace std;

/*
*   The program receives three arguments.
*   1.- Input number string.
*   2.- Digits height printing.
*   3.- Digits width printing.
*/
int main(int const argc, char* argv[]) {
    try {
        string *number_string = new string("0123456789"),
        *digits_height = new string("1"), *digits_width = new string("1");

        //Check digits width validity.
        if(argc < 4) {
            cout << "Digits width not provided. Using default value (1)." << endl;
        }
        else {
            digits_width = new string(argv[3]);
        }

        //Check digits height validity.
        if(argc < 3) {
            cout << "Digits height not provided. Using default value (1)." << endl;
        }
        else {
            digits_height = new string(argv[2]);
        }
        
        //Check source number string.
        if(argc < 2) {
            cout << "Input number not provided. Using default value (0123456789)." << endl;
        }
        else {
            number_string = new string(argv[1]);
        }

        cout << "Input string: " << *number_string << "." << endl;
        cout << "Digits height printing: " << *digits_height << "." << endl;
        cout << "Digits width printing: " << *digits_width << "." << endl;
        number_to_lcd_parser *number_parser = new number_to_lcd_parser(*number_string, *digits_height, *digits_width);

        cout << "Generated LCD number:" << endl;
        number_parser->print_lcd_number();

        delete number_string, digits_height, digits_width, number_parser;
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