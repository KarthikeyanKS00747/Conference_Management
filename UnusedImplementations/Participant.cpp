#include <iostream>
#include <string>
#include "User.hpp"
#include <limits>

class Participant: public User
{
    private:
        std :: string conferenceName;
        std :: string scheduledDay;
        std :: string scheduledTime;
        bool conferenceScheduled;

    public:
        // Constructor
        Participant(const User& user) : User(user)
        {
            
        }
        Participant() : conferenceName(""), scheduledDay(""), scheduledTime(""), conferenceScheduled(false)
        {
            std :: cout << "" << std :: endl;
        }
        // Destructor
        ~Participant()
        {
            std :: cout << "" << std :: endl;
        }
        void scheduleConference(std :: string name, std :: string day, std :: string time);
        void showConference();
        void showTime();
};
void Participant :: scheduleConference(std :: string name, std :: string day, std :: string time)
{
    // Check if the conference is already scheduled
    if (conferenceScheduled && scheduledDay == day && scheduledTime == time)
    {
        std :: cout << "There is already a conference scheduled on " << day << " at " << time << ". Please choose another time." << std :: endl;
        return;
    }

    // Schedule the conference
    conferenceName = name;
    scheduledDay = day;
    scheduledTime = time;
    conferenceScheduled = true;
    std :: cout << "Conference '" << conferenceName << "' scheduled successfully on " << day << " at " << time << std :: endl;
    showConference();
}
void Participant::showConference()
{
    if (!conferenceScheduled)
    {
        std :: cout << "No conference scheduled." << std :: endl;
        return;
    }
    std :: cout << "Scheduled Conference:" << std :: endl;
    std :: cout << "Conference Name: " << conferenceName << std :: endl;
    std :: cout << "Day: " << scheduledDay << ", Time: " << scheduledTime << std :: endl;
}
void Participant::showTime()
{
    std :: cout << "Available Time Slots:" << std :: endl;
    std :: cout << "8:00 AM - 10:00 AM" << std :: endl;
    std :: cout << "10:00 AM - 12:00 PM" << std :: endl;
    std :: cout << "2:00 PM - 5:00 PM" << std :: endl;
    std :: cout << "5:00 PM - 7:00 PM" << std :: endl;
}
// int main()
// {
//     Participant p;
//     p.showTime();
//     char choice;
//     do
//     {
//         std :: string name, day, time;

//         std :: cout << "\nEnter the name of the conference: ";
//         getline(std :: cin, name);

//         std :: cout << "Enter the date for scheduling the conference (e.g., 2024-03-21): ";
//         getline(std :: cin, day);

//         std :: cout << "Enter the time for scheduling the conference (e.g., 10:00 AM): ";
//         getline(std :: cin, time);

//         p.scheduleConference(name, day, time);

//         std :: cout << "\nDo you want to schedule another conference? (y/n): ";
//         std :: cin >> choice;
//         std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n'); // Clear input buffer
//     }
//     while (choice == 'y' || choice == 'Y');
//     return 0;
// }
