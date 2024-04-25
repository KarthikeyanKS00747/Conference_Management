#ifndef SPONSOR_HPP
#define SPONSOR_HPP

#include <string>
#include "User.hpp"

class Sponsor : public User 
{
private:
    std::string sponsoredEvent;
    double amount;

public:
    // Constructor
    Sponsor();
    Sponsor(std::string name, short int age, std::string regNO, std::string gender, 
            std::string username, std::string password, std::string email, 
            std::string event, double amt);

    // Display method
    void display();
};

#endif // SPONSOR_H