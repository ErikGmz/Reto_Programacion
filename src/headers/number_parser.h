#pragma once
#include "number_formatting_config.h"
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
        int digits_height;
        int digits_width; 
        string *source_number;
        vector<vector<char>*> *lcd_numbers_matrix;

        //Internal methods.
        bool digits_parameter_is_valid(string digits_parameter);
        bool source_number_string_is_valid(string source_number_string);
        void clear_lcd_matrix();
        vector<char> generate_width_line(char character_filling);
        void load_number_into_matrix(number_formatting_config *formatting);
        void control_number_loading(number_formatting_config *formatting);
        void append_lcd_digit(char digit);
        void generate_lcd_number();

    public:
        //Class constructor.
        number_to_lcd_parser(string source_number, string digits_height, string digits_width);

        //Methods.
        void set_digits_height(string digits_height);
        void set_digits_width(string digits_width);
        void set_source_number(string source_number);
        void print_lcd_number();

        //Class destructor.
        ~number_to_lcd_parser();
};


//Class methods definitions.
//Constructor.
number_to_lcd_parser::number_to_lcd_parser(string source_number, string digits_height, string digits_width) {
    this->set_digits_height(digits_height);
    this->set_digits_width(digits_width);

    //Initialize class attributes.
    this->lcd_numbers_matrix = new vector<vector<char>*>();
    for(int i = 1; i <= 1 + this->digits_height * 2; i++) {
        this->lcd_numbers_matrix->push_back(new vector<char>());
    }

    this->set_source_number(source_number);
}

//Internal methods.
bool number_to_lcd_parser::digits_parameter_is_valid(string digits_parameter) {
    //Check if string is a number with a one digit between 1 and 10.
    return regex_match(digits_parameter, regex("[1-9]|10"));
}

bool number_to_lcd_parser::source_number_string_is_valid(string source_number_string) {
    //Check if string is a number with a digit count between 1 and 25.
    return regex_match(source_number_string, regex("[0-9]{1,25}"));
}

void number_to_lcd_parser::clear_lcd_matrix() {
    for(vector<char>* lcd_matrix_row: *(this->lcd_numbers_matrix)) {
        lcd_matrix_row->clear();
    }
}

vector<char> number_to_lcd_parser::generate_width_line(char character_filling) {
    return vector<char>(this->digits_width, character_filling);
}

void number_to_lcd_parser::load_number_into_matrix(number_formatting_config *formatting) {
    vector<char> *helper_row = formatting->get_helper_row();
    vector<char> *filling_line = formatting->get_filling_line();

    //Construct each line output.
    helper_row->push_back(formatting->get_start_char());
    helper_row->insert(helper_row->end(), filling_line->begin(), filling_line->end());
    helper_row->push_back(formatting->get_end_char());
    lcd_numbers_matrix->at(formatting->get_loop_index_beggining())->insert(lcd_numbers_matrix->at(formatting->get_loop_index_beggining())->end(), helper_row->begin(), helper_row->end());
    helper_row->clear();
}

void number_to_lcd_parser::control_number_loading(number_formatting_config *formatting) {
    if(!formatting->is_using_for_loop()) {
        //For horizontal lines printing.
        load_number_into_matrix(formatting);
    }
    else {
        //For vertical lines printing.
        for(int i = 0; i < formatting->get_loop_limit(); i++) {
            load_number_into_matrix(formatting);
            formatting->set_loop_index_beggining(formatting->get_loop_index_beggining() + 1);
        }
    }
    delete formatting;
}

void number_to_lcd_parser::append_lcd_digit(char digit) {
    vector<char>* helper_row = new vector<char>(), *width_line = new vector<char>(this->generate_width_line('_')),
    *width_spaces = new vector<char>(this->generate_width_line(' '));

    //Format LCD digit from char.
    switch(digit) {
        case '0':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, 1, lcd_numbers_matrix->size() - 2));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '1':
            //Generate number vertical line.
            lcd_numbers_matrix->at(0)->insert(lcd_numbers_matrix->at(0)->end(), {' ', ' ', ' '});

            for(int i = 0; i < lcd_numbers_matrix->size() - 1; i++) {
                lcd_numbers_matrix->at(1 + i)->insert(lcd_numbers_matrix->at(1 + i)->end(), {' ', '|', ' '});
            }
        break;

        case '2':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', '|', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', ' ', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', ' ', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '3':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', '|', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '4':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        
        case '5':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', ' ', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', ' ', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '6':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', ' ', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', ' ', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '7':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, 1, lcd_numbers_matrix->size() - 2));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;

        case '8':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;
        
        case '9':
            //Generate first number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', ' ', false, 0, 0));

            //Generate number first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, '|', '|', true, 1, this->digits_height - 1));

            //Generate intermediate number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, '|', '|', false, this->digits_height, 0));

            //Generate second first vertical lines.
            control_number_loading(new number_formatting_config(*helper_row, *width_spaces, ' ', '|', true, this->digits_height + 1, this->digits_height - 1));

            //Generate last number line.
            control_number_loading(new number_formatting_config(*helper_row, *width_line, ' ', '|', false, lcd_numbers_matrix->size() - 1, 0));
        break;
    }
    delete helper_row, width_line, width_spaces;
}

void number_to_lcd_parser::generate_lcd_number() {
    this->clear_lcd_matrix();
    for(char &digit: *(this->source_number)) {
        this->append_lcd_digit(digit);
    }
}

//Methods.
void number_to_lcd_parser::set_digits_height(string digits_height) {
    if(!this->digits_parameter_is_valid(digits_height)) {
        throw number_parsing_exception("Invalid digits height (it should be a number between 1 and 10)");
    }

    this->digits_height = stoi(digits_height);
}

void number_to_lcd_parser::set_digits_width(string digits_width) {
    if(!this->digits_parameter_is_valid(digits_width)) {
        throw number_parsing_exception("Invalid digits width (it should be a number between 1 and 10)");
    }

    this->digits_width = stoi(digits_width);
}

void number_to_lcd_parser::set_source_number(string source_number) {
    if(!this->source_number_string_is_valid(source_number)) {
        throw number_parsing_exception("Invalid source string (it should be a number with a digit count between 1 and 25)");
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