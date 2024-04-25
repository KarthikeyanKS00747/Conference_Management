#include <iostream>
#include <string>
#include "User.hpp"
#include "Conference.hpp"
#include <limits>

//#include "DateTime.hpp"
//#include "Venue.h"
//#include "Sponsor.h"
#include "Participant.hpp"
// #include "Organiser.h"
#include <map>


std::map<std::string, Conference*> Conference::conferenceMap;
int Conference::no_of_conferences = 0;
std :: map<std::string, User*> userMap;
static int numVenues = 0;
void page_1();
void exploreConferences(User &user)
{
    int i = 1;
    for (const auto& pair : Conference :: conferenceMap)
    {
        std::cout << i << ". " << pair.first << "\n";
        i++;
    }

    std::cout << "Enter the number of the conference you want to explore: ";
    int choice;
    std::cin >> choice;

    // Get the selected conference
    auto it = Conference :: conferenceMap.begin();
    std::advance(it, choice - 1);
    Conference* selectedConference = it -> second;

    std::cout << "You selected: " << selectedConference->getName() << "\n";
    std::cout << "1. Join\n";
    std::cout << "2. Organise\n";
    std::cout << "3. Sponsor\n";
    std::cout << "4. Back to main menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch(choice) {
        case 1:
        {
            Participant p(user);
            p.showTime();
            char choice;
            do
            {
                std :: string name, day, time;

                std :: cout << "\nEnter the name of the conference: ";
                getline(std :: cin, name);

                std :: cout << "Enter the date for scheduling the conference (e.g., 2024-03-21): ";
                getline(std :: cin, day);

                std :: cout << "Enter the time for scheduling the conference (e.g., 10:00 AM): ";
                getline(std :: cin, time);

                p.scheduleConference(name, day, time);

                std :: cout << "\nDo you want to schedule another conference? (y/n): ";
                std :: cin >> choice;
                std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n'); // Clear input buffer
            }
            while (choice == 'y' || choice == 'Y');
            break;
        }
        case 2:
            // Code to organise the conference
            break;
        case 3:
            // Code to sponsor the conference
            break;
        case 4:
            // Code to go back to the main menu
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
    }
}
void createConferences(){};

void page_2(User &user)
{
    std :: cout << "\t\tMAIN MENU";
    std :: cout << "1. Explore Conferences\n"; 
    std :: cout << "2. Create Conference\n";
    std :: cout << "3. Exit\n";
    int resp;
    std :: cin >> resp;
    do
    {
        switch(resp)
        {
            case 1:
                exploreConferences(user);
                break;
            case 2:
                createConferences();
                break;
            case 3:
                exit(0);
            default:
                std :: cout << "Invalid response\n";

        }
    }
    while (true);
}

void sign_up()
{
    std::string name;
    short int age;
    std::string regNO;
    std::string gender;
    std::string username;
    std::string password;
    std::string email;

    std::cout << "Enter your details:\n";
    std::cout << "Name: ";
    std::cin >> name;
    std::cout << "Age: ";
    std::cin >> age;
    std::cout << "Registration Number: ";
    std::cin >> regNO;
    std::cout << "Gender: ";
    std::cin >> gender;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Email: ";
    std::cin >> email;

    // Create a new User and add it to the userMap
    new User(name, age, regNO, gender, username, password, email);

    std::cout << "Signed up successfully.\n";
    page_1();
}

void sign_in()
{
    std :: string username;
    std :: string password;
    std :: cout << "Username : ";
    std :: cin >> username;
    std :: cin >> password;
    User *user = User :: getUserByUsername(username);
    if (user != nullptr && user -> getPassword() == password)
    {
        std :: cout << "Password is correct.\n";
        std :: cout << "Signed in successfully.";
    }
    else
    {
        std::cout << "Invalid username or password.\n";
    }
    page_2(*user);
}
void page_1()
{
    std :: cout << "\t\tMAIN MENU";
    std :: cout << "1. Sign-In\n";
    std :: cout << "2. Sign-Up\n";
    std :: cout << "3. Exit\n";
    int resp;
    std :: cin >> resp;
    do
        switch(resp)
        {
            case 1:
                sign_in();
                break;
            case 2:
                sign_up();
                break;
            case 3:
                exit(0);
            default:
                std :: cout << "Invalid response\n";

        }
    while (true);
}

int main(void)
{
    page_1();

    return 0;
}