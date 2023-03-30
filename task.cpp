#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <unordered_map>




class User {
    public:
        void add_new_message(std::string message) {
            message_buffer.push_back(message);
            std::cout << "ok\n";
        };

        void print_last_message() {
            if (message_buffer.size() == 0){
                std::cout << "no new messages\n";
                return;
            }
            else {
                std::string message = message_buffer.back();
                std::cout << message << "\n";

                message_buffer.pop_back();
            }
            return;
        };

        std::vector<std::string> message_buffer;
};


class Operator {
    public:
        void create_new_user(std::string phone_number) {
            class User new_user;
            user_base[phone_number] = new_user;

            std::cout << "new user added\n";
        };

        std::unordered_map<std::string, class User> user_base;
};


class Country {
    public:
        class Operator create_new_operator(std::string op_code){
        if (operator_base.find(op_code) != operator_base.end()){
            std::cout << "country is already exists\n";

            return operator_base[op_code];
        }
        else {
            class Operator new_operator;
            operator_base[op_code] = new_operator;

            return new_operator;
        }
    };

        std::unordered_map<std::string, class Operator> operator_base;
};

class Switch {
public:
    void send(std::string phone_number) {
    };
    void read(std::string phone_number) {

    };

    // return class for switch build facility
    //same thing above

    class Country create_new_country(std::string country_code) {
        if (country_base.find(country_code) != country_base.end()){
            std::cout << "country is already exists\n";

            return country_base[country_code];
        }
        else {
            class Country new_country;
            country_base[country_code] = new_country;

            return new_country;
        }
    };

    void number_to_parts(std::string phone_number) {
        int number_size = phone_number.length();
        int s_counter = 0;
        int pos = 0;

        while (pos < number_size) {
            pos = phone_number.find(' ', pos);

            if (pos < 0)
                break;

            else {
                pos++;
                s_counter ++;
            }
        }

        if (s_counter != 2) {
            std::cout << "operation wasn't completed, pls, check your phone format\n";
            return;
        }

        // needs to be wraped in one while loop
        int s_pos = phone_number.find(' ');
        pos = 0;

        
        for (int i = pos; i < s_pos; i ++) {
            country_code_on_switch.push_back(phone_number[i]);
        }

        pos = ++s_pos;
        s_pos = phone_number.find(' ', s_pos);

        for (int i = pos; i < s_pos; i ++) {
            operator_code_on_switch.push_back(phone_number[i]);
        }

        pos = ++s_pos;

        for (int i = pos; i < number_size; i ++) {
            number_on_switch.push_back(phone_number[i]);
        }

        std::cout << country_code_on_switch  << "\n";
        std::cout << operator_code_on_switch << "\n";
        std::cout << number_on_switch        << "\n";
        
    };

    bool is_exist        () {

    };

    bool look_up_country () {

    };

    bool look_up_operator() {

    };

    bool look_up_number  () {

    };


    std::map<std::string, class Country> country_base;

    private:
        std::string country_code_on_switch;
        std::string operator_code_on_switch;
        std::string number_on_switch;
};


//kontrolnaya


int main () {

    class Switch new_switch;

    new_switch.number_to_parts("+7 9878 4753574");


    return 0;
}