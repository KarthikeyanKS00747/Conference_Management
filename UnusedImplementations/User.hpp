#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>

class User
{
private:
    std::string name;
    short int age;
    std::string regNO;
    std::string gender;
    std::string username;
    std::string password;
    std::string email;
    static std :: map<std::string, User*> userMap;

public:
    // Constructor
    User(std::string name, short int age, std::string regNO, std::string gender, 
         std::string username, std::string password, std::string email);

    // Default Constructor
    User();


    static User* getUserByUsername(const std::string& username);
    // Getters and Setters
    void setName(std::string n);
    std::string getName() const;

    void setAge(short int a);
    short int getAge() const;

    void setRegNO(std::string r);
    std::string getRegNO() const;

    void setGender(std::string g);
    std::string getGender() const;

    void setUsername(std::string u);
    std::string getUsername() const;

    void setPassword(std::string p);
    std::string getPassword() const;

    void setEmail(std::string e);
    std::string getEmail() const;

    // Display user information
    void display() const;

    // Login verification
    bool verifyLogin(std::string uname, std::string pword);

    // Update Information
    void updateEmail(std::string newEmail);
    void updatePassword(std::string newPassword);
};

#endif // USER_H