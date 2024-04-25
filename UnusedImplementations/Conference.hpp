#ifndef CONFERENCE_HPP
#define CONFERENCE_HPP

#include <string>
#include "DateTime.hpp"
#include "Venue.hpp"
#include "Sponsor.hpp"
#include "Participant.hpp"
#include "Organiser.hpp"
#include <map>

class Conference
{
private:
    DateTime datetime;
    Venue venue;
    Organiser organisers[30];
    Participant participants[500];
    Sponsor sponsors[20];
    double generated_amt;
    std::string conference_id;
    std::string name;

public:
    static std::map<std::string, Conference*> conferenceMap;
    static int no_of_conferences;

    // Constructor
    Conference();

    // Method to get Conference instance by name
    static Conference* getConferenceByName(const std::string& name);
    std :: string getName();
};

#endif // CONFERENCE_H