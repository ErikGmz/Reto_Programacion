#pragma once
#include "exceptions.h"
#include <vector>
#include <string>
#include <regex>
#include <iostream>

using namespace std;

//Class declarations.
class number_to_lcd_parser {
    private:
        //Attributes.
        int lcd_height = 3;
        string *source_number;
        vector<vector<char>*> *lcd_numbers_matrix;

        //Internal methods.
        bool source_number_string_is_valid(string source_number_string);
        void clear_lcd_matrix();
        void append_lcd_digit(char digit);
        void generate_lcd_number();

    public:
        //Class constructor.
        number_to_lcd_parser(string source_number);

        //Methods.
        void set_source_number(string source_number);
        void print_lcd_number();

        //Class destructor.
        ~number_to_lcd_parser();
};


//Class methods definitions.
//Constructor.
number_to_lcd_parser::number_to_lcd_parser(string source_number) {
    //Initialize class attributes.
    this->lcd_numbers_matrix = new vector<vector<char>*>();
    for(int i = 1; i <= this->lcd_height; i++) {
        this->lcd_numbers_matrix->push_back(new vector<char>());
    }

    this->set_source_number(source_number);
}

//Internal methods.
bool number_to_lcd_parser::source_number_string_is_valid(string source_number_string) {
    //Check if string is a number with at least 1 digit.
    return regex_match(source_number_string, regex("[0-9]+"));
}

void number_to_lcd_parser::clear_lcd_matrix() {
    for(vector<char>* lcd_matrix_row: *(this->lcd_numbers_matrix)) {
        lcd_matrix_row->clear();
    }
}

void number_to_lcd_parser::append_lcd_digit(char digit) {
    //Format LCD digit from char.
    switch(digit) {
        case '0':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', ' ', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {'|', '_', '|'});
        break;

        case '1':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {'|'});
        break;

        case '2':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {' ', '_', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {'|', '_', ' '});
        break;

        case '3':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {' ', '_', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {' ', '_', '|'});
        break;

        case '4':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', ' ', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', '_', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {' ', ' ', '|'});
        break;

        case '5':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', '_', ' '});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {' ', '_', '|'});
        break;

        case '6':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', '_', ' '});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {'|', '_', '|'});
        break;

        case '7':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {' ', ' ', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {' ', ' ', '|'});
        break;

        case '8':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', '_', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {'|', '_', '|'});
        break;
        
        case '9':
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', '_', ' '});
            lcd_numbers_matrix->at(1)->insert(lcd_numbers_matrix->at(1)->end(), {'|', '_', '|'});
            lcd_numbers_matrix->at(2)->insert(lcd_numbers_matrix->at(2)->end(), {' ', '_', '|'});
        break;
    }
}

void number_to_lcd_parser::generate_lcd_number() {
    this->clear_lcd_matrix();
    for(char &digit: *(this->source_number)) {
        this->append_lcd_digit(digit);
    }
}

//Methods.
void number_to_lcd_parser::set_source_number(string source_number) {
    if(!this->source_number_string_is_valid(source_number)) {
        throw number_parsing_exception("Invalid source string (it should be a number with at least 1 digit)");
    }

    this->source_number = new string();
    *this->source_number = source_number;
    this->generate_lcd_number();
}

void number_to_lcd_parser::print_lcd_number() {
    for(vector<char>* lcd_matrix_row: *(this->lcd_numbers_matrix)) {
        for(char lcd_matrix_char: *(lcd_matrix_row)) {
            cout << lcd_matrix_char;
        }
        cout << endl;
    }
}

//Destructor.
number_to_lcd_parser::~number_to_lcd_parser() {
    //Free variables memory space.
    delete this->source_number;
    for(vector<char>* lcd_matrix_row: *(this->lcd_numbers_matrix)) {
        delete lcd_matrix_row;
    }
    delete this->lcd_numbers_matrix;
}