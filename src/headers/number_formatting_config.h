#pragma once
#include <vector>
#include <iostream>

using namespace std;

class number_formatting_config {
    private:
        //Attributes.
        vector<char> *helper_row;
        vector<char> *filling_line; 
        char start_char;
        char end_char;
        bool using_for_loop;
        int loop_index_beggining;
        int loop_limit;

    public:
        //Constructor.
        number_formatting_config(vector<char> helper_row, vector<char> filling_line, char start_char, char end_char, bool using_for_loop, int loop_index_beggining, int loop_limit);
        
        //Getters.
        vector<char> *get_helper_row();
        vector<char> *get_filling_line();
        char get_start_char();
        char get_end_char();
        bool is_using_for_loop();
        int get_loop_index_beggining();
        int get_loop_limit();

        //Setter.
        void set_loop_index_beggining(int index_beggining);

        //Destructor.
        ~number_formatting_config();
};

//Constructor
number_formatting_config::number_formatting_config(vector<char> helper_row, vector<char> filling_line, char start_char, char end_char, bool using_for_loop, int loop_index_beggining, int loop_limit) {
    this->helper_row = new vector<char>(helper_row);
    this->filling_line = new vector<char>(filling_line);
    this->start_char = start_char;
    this->end_char = end_char;
    this->using_for_loop = using_for_loop;
    this->loop_index_beggining = loop_index_beggining;
    this->loop_limit = loop_limit;
}

//Getters.
vector<char> *number_formatting_config::get_helper_row() {
    return this->helper_row;
}

vector<char> *number_formatting_config::get_filling_line() {
    return this->filling_line;
}

char number_formatting_config::get_start_char() {
    return this->start_char;
}

char number_formatting_config::get_end_char() {
    return this->end_char;
}

bool number_formatting_config::is_using_for_loop() {
    return this->using_for_loop;
}

int number_formatting_config::get_loop_index_beggining() {
    return this->loop_index_beggining;
}

int number_formatting_config::get_loop_limit() {
    return this->loop_limit;
}

//Setter.
void number_formatting_config::set_loop_index_beggining(int index_beggining) {
    this->loop_index_beggining = index_beggining;
}

//Destructor.
number_formatting_config::~number_formatting_config() {
    delete helper_row, filling_line;
}