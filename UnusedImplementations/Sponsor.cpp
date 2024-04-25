#include <iostream>
#include <string>
#include "User.hpp"


class Sponsor : public User {
    private:
        std :: string sponsoredEvent;
        double amount;
    
    public:
        Sponsor(){};
        Sponsor(std::string name, short int age, std::string regNO, std::string gender, 
        std::string username, std::string password, std::string email, std :: string event, double amt) 
        : User(name, age, regNO, gender, username, password, email),
        sponsoredEvent(event), amount(amt) {}

        void display()
        {
            std :: cout << "Sponsor: ";
            User :: display();
            std :: cout << ", Event: " << sponsoredEvent << ", Amount: ₹" << amount;
        }
    
};

// int main() {
//     std :: string name, email, event;
//     double amount;
    
//     std :: cout << "Enter sponsor's name: ";
//     getline(std :: cin, name);
    
//     cout << "Enter sponsor's email: ";
//     getline(cin, email);
    
//     cout << "Enter sponsored event: ";
//     getline(cin, event);
    
//     cout << "Enter sponsorship amount: ";
//     cin >> amount;

//     Sponsor sponsor1(name, email, event, amount);
//     sponsor1.display();
    
//     cout << endl;

//     return 0;
    
// }