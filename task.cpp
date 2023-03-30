#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <unordered_map>


std::vector<std::string> number_to_parts(std::string phone_number) {
    std::vector<std::string> phone_parts;
    
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
        return phone_parts;
    }

    std::string part;

    pos = 0;
    s_counter = 0;
    int s_pos = 0;
    
    while (s_counter < 2) {
        s_pos = phone_number.find(' ', pos);

        for (int i = pos; i < s_pos; i ++) {
            part.push_back(phone_number[i]);
        }

        pos = ++s_pos;
        phone_parts.push_back(part);

        part.clear();
        s_counter ++;
    }

    for (int i = pos; i < number_size; i ++) {
        part.push_back(phone_number[i]);
    }

    phone_parts.push_back(part);
    part.clear();

    return phone_parts;
};



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
            phone_parts = number_to_parts(phone_number);

            if (phone_parts.size() == 0)
                return;

            if (is_valid()) {
                class User new_user;
                std::string user_num = phone_parts[2];
                user_base[user_num] = new_user;

                std::cout << "new user added\n";
            }
            else {
                std::cout << "the phone you entered is invalid for this operator\n";
            }
        };


        bool is_valid () {
            if (country_code.compare(phone_parts[0]) || operator_code.compare(phone_parts[1]))
                return false;

            else
                return true;
        }

        bool find_user(std::string user_code) {
            if (user_base.find(user_code) != user_base.end()) {
                user_to_find = user_base[user_code];

                std::cout << "user was found\n";
                return true;
            }
            else 
                return false;
        }

        std::string country_code; // i can store hash instead of strings
        std::string operator_code;
        std::vector<std::string> phone_parts;

        class User user_to_find;
        std::unordered_map<std::string, class User> user_base;
};


class Country {
    public:


        class Operator create_new_operator(std::string op_code){
        if (find_operator(op_code)){
            std::cout << "country is already exists\n";

            return operator_base[op_code];
        }
        else {
            class Operator new_operator;
            operator_base[op_code] = new_operator;

            new_operator.country_code  = country_code;
            new_operator.operator_code = op_code;

            return new_operator;
        }
    };

    bool find_operator(std::string operator_code) {
        if (operator_base.find(operator_code) != operator_base.end()) {
            operator_to_find = operator_base[operator_code];
            return true;
        }
        else 
            return false;
    };

    std::string country_code;

    class Operator operator_to_find;
    std::unordered_map<std::string, class Operator> operator_base;
};


class Switch {
public:


    void send(std::string phone_number, std::string message) {
        phone_parts = number_to_parts(phone_number);

        if (phone_parts.size() == 0)
            return;

        for (int i = 0; i < 3; i ++) {
            std::cout << phone_parts[i] << "\n";
        }

        if (find_country(phone_parts[0])) {
            if (country_to_find.find_operator(phone_parts[1])) {
                if (country_to_find.operator_to_find.find_user(phone_parts[2])) {
                    
                    country_to_find.operator_to_find.user_to_find.add_new_message(message);
                    return;
                }
                else {
                    std::cout << "number is incorrect\n";
                    return;
                }
            }
            else {
                std::cout << "number or operator code is incorrect\n";
                return;
            }
        }
        else {
            std::cout << "no clients in this country\n";
            return;
        }
    };


    void read(std::string phone_number) {
        phone_parts = number_to_parts(phone_number);

        if (phone_parts.size() == 0)
            return;

        if (find_country(phone_parts[0])) {
            if (country_to_find.find_operator(phone_parts[1])) {
                if (country_to_find.operator_to_find.find_user(phone_parts[2])) {
                    
                    country_to_find.operator_to_find.user_to_find.print_last_message();
                    return;
                }
                else {
                    std::cout << "number is incorrect\n";
                    return;
                }
            }
            else {
                std::cout << "number or operator code is incorrect\n";
                return;
            }
        }
        else {
            std::cout << "no clients in this country\n";
            return;
        }
    };


    class Country create_new_country(std::string country_code) {
        if (find_country(country_code)){
            std::cout << "country is already exists\n";

            return country_base[country_code];
        }
        else {
            class Country new_country;
            country_base[country_code] = new_country;
            new_country.country_code   = country_code;

            return new_country;
        }
    };


    bool find_country(std::string country_code) {
        if (country_base.find(country_code) != country_base.end()) {
            country_to_find = country_base[country_code];

            return true;
        }
        else 
            return false;
    };


    class Country country_to_find;
    std::vector<std::string> phone_parts;

    std::unordered_map<std::string, class Country> country_base;

};

//kontrolnaya
//code is growing, i am copying and pasting --- it sucks !!!


int main () {

    class Switch new_switch;

    class Country Russia;
    Russia = new_switch.create_new_country("+7");

    class Operator Beeline;
    Beeline = Russia.create_new_operator("905");

    Beeline.create_new_user ("+7 905 7664566");
    Beeline.create_new_user ("+7 905 1234578");

    new_switch.send("+7 905 1234578", "hello");
    
    new_switch.read("+7 905 1234578");
    new_switch.read("+7 905 7664566");


    return 0;
}