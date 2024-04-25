#ifndef VENUE_HPP
#define VENUE_HPP

#include <string>

class Venue
{
private:
    static const int MAX_VENUES = 100;
    static std :: string placeList[MAX_VENUES];
    static int numVenues;
    std :: string venue_name;

public:
    Venue();
    Venue(const std :: string& p); // Constructor
    ~Venue(); // Destructor

    void addVenue(const std :: string& newPlace); // Method to add a new venue
    void deleteVenue(const std :: string& place); // Method to remove a venue
    void editVenue(const std :: string& oldPlace, const std :: string& newPlace); // Method to update a venue
};

#endif // VENUE_H