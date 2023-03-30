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

        int is_fake;        //shows wheather  its mask number or real
        User* transferring; // if its a mask, it has pointer inside to the real user.

        std::vector<std::string> message_buffer;
};


class Operator {
    public:
        ~Operator() {
            std::unordered_map<std::string, User*>::iterator it = user_base.begin();
            while (it != user_base.end()) {
                delete it->second;

                user_base.erase(it);
                it++;
            }
        };

        void create_new_user(std::string phone_number) {
            phone_parts = number_to_parts(phone_number);

            if (phone_parts.size() < 3) // country code // operator code //  number //
                return;                 //    +7        //      905      // 1234578 //

            if (is_valid()) {
                std::string user_num = phone_parts[2];

                if (find_user(user_num)) {
                    std::cout << "user with this phone number already exists\n";
                    return;
                }
                else {
                    User* new_user = new User;

                    new_user->is_fake = 0;          //creating real user
                    user_base[user_num] = new_user;
                    std::cout << "new user added\n";
                }
            }
            else
                std::cout << "the phone you entered is invalid for this operator\n";
        };


        void create_new_hidden_user(std::string mask_number, std::string phone_number) {
            User* new_fake_user = nullptr;

            if (validation(mask_number)){
                std::string mask = phone_parts[2];

                if (find_user(mask)) {
                    std::cout << "this number in use, think about different mask\n";
                }
                else {
                    new_fake_user = new User;
                    new_fake_user->is_fake = 1;

                    user_base[mask] = new_fake_user;
                }

            }
            else
                std::cout << "The mask you entered is invalid for this operator\n";


            if (validation(phone_number)){
                std::string number = phone_parts[2];

                if (find_user(number)) {
                    std::cout << "the number u chose is in use\n";
                }
                else {
                    if (new_fake_user != nullptr) {
                        User* new_user = new User;    
                        new_user->is_fake = 0;
                        new_fake_user->transferring = new_user;

                        user_base[number] = new_user;
                    }
                    else 
                        std::cout << "the mask is invalid. TRUE user wasn't not created";
                }
            }
            else
                std::cout << "the phone you entered is invalid for this operator\n";
        };


        bool validation(std::string number){
            phone_parts = number_to_parts(number);

            if (phone_parts.size() < 3)
                return false; 

            else if (!is_valid())
                return false;
            
            else 
                return true;
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

                return true;
            }
            else 
                return false;
        }

        std::string country_code; // i can store hash instead of strings
        std::string operator_code;
        std::vector<std::string> phone_parts;

        User* user_to_find;
        std::unordered_map<std::string, User*> user_base;
};


class Country {
    public:
        ~Country() {
            std::unordered_map<std::string, Operator*>::iterator it = operator_base.begin();
            while (it != operator_base.end()) {
                delete it->second;

                operator_base.erase(it);
                it++;
            }
        };


        Operator* create_new_operator(std::string op_code){

            if (find_operator(op_code)){
                std::cout << "country is already exists\n";

                return operator_base[op_code];
            }
            else {
                Operator* new_operator = new Operator;

                operator_base[op_code] = new_operator;

                new_operator->country_code  = country_code;
                new_operator->operator_code = op_code;

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

    Operator* operator_to_find;
    std::unordered_map<std::string, Operator*> operator_base;
};


class Switch {
public:
    //deleting all allocated memory bloks
    ~Switch() {
        std::unordered_map<std::string, Country*>::iterator it = country_base.begin();
        while (it != country_base.end()) {
            delete it->second;

            country_base.erase(it);
            it++;
        }
    };


    void send(std::string phone_number, std::string message) {
        phone_parts = number_to_parts(phone_number);

        if (phone_parts.size() == 0)
            return;

        if (find_country(phone_parts[0])) {
            if (country_to_find->find_operator(phone_parts[1])) {
                if (country_to_find->operator_to_find->find_user(phone_parts[2])) {

                    User* user = country_to_find->operator_to_find->user_to_find;

                    if (!user->is_fake)
                        user->add_new_message(message);
                    else 
                        user->transferring->add_new_message(message);

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
            if (country_to_find->find_operator(phone_parts[1])) {
                if (country_to_find->operator_to_find->find_user(phone_parts[2])) {
                    
                    country_to_find->operator_to_find->user_to_find->print_last_message();
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


    Country* create_new_country(std::string country_code) {

        if (find_country(country_code)){
            std::cout << "country is already exists\n";

            return country_base[country_code];
        }
        else {
            Country* new_country = new Country;
            country_base[country_code] = new_country;
            new_country->country_code   = country_code;

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


    Country* country_to_find;
    std::vector<std::string> phone_parts;

    std::unordered_map<std::string, Country*> country_base;

};


int main () {

    class Switch new_switch;

    Country*  Russia = new_switch.create_new_country("+7");

    Operator* Beeline = Russia->create_new_operator("905");

    std::cout << "\n\n-------------------------------------------------\n\n";

    Beeline->create_new_user("+7 905 7664566"); //print successfully added user
    Beeline->create_new_user("+7 905 7664566"); //print two same numbers are impossible
    Beeline->create_new_user("+8 906 7738766"); //print invalide country code, operator code

    Beeline->create_new_hidden_user("+7 905 0000000", "+7 905 1234578"); //print successfully added user

    new_switch.send("+7 905 12898"  , "hello");      //print that number is incorrect

    new_switch.send("+7 905 0000000", "how are u");  //print ok, sent message to +7 905 1234578
    new_switch.send("+7 905 7664566", "feels good"); //print ok

    new_switch.read("+7 905 1234578"); //print messages
    new_switch.read("+7 905 7664566"); //print messages

    std::cout << "\n-------------------------------------------------\n\n";

    return 0;
}