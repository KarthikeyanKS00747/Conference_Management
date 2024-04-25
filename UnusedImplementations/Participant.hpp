#ifndef PARTICIPANT_HPP
#define PARTICIPANT_HPP

#include <string>
#include "User.hpp"

class Participant : public User 
{
private:
    std::string conferenceName;
    std::string scheduledDay;
    std::string scheduledTime;
    bool conferenceScheduled;

public:
    // Constructor
    Participant();
    Participant(const User& user);

    // Destructor
    ~Participant();

    // Methods
    void scheduleConference(std::string name, std::string day, std::string time);
    void showConference();
    void showTime();
};

#endif // PARTICIPANT_H