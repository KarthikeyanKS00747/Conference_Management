#include <iostream>
#include <string>

class Venue
{
    private:
        static const int MAX_VENUES = 100; // Maximum number of venues
        static std :: string placeList[MAX_VENUES]; // Array to store venue names
        static int numVenues; // Number of venues currently stored
        std :: string venue_name;

    public:
        Venue(){};
        Venue(const std :: string& p) 
        {
            for (int i = 0; i < numVenues; ++i) 
            {
                if (placeList[i] == p) 
                {
                    venue_name = p;
                    std :: cout << "Venue Found\n";
                    std :: cout << "Venue Chosen Successfully.\n";
                }
            }
        }
        ~Venue(){};

        static void addVenue(const std :: string& p) 
        {
            for (int i = 0; i < numVenues; ++i) 
            {
                if (placeList[i] == p) 
                {
                    std::cout << "Cannot add venue: " << p << " is already in the list.\n";
                    return;
                }
            }
            if (numVenues < MAX_VENUES)
            {
                placeList[numVenues++] = p; // Add the new venue to the list
            } 
            else 
            {
                std::cerr << "Error: Venue list is full!\n";
            }
        }

        static void deleteVenue(const std :: string& p) 
        {
            int index = -1;
            for (int i = 0; i < numVenues; ++i) 
            {
                if (placeList[i] == p) 
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                for (int i = index; i < numVenues - 1; ++ i)
                {
                    placeList[i] = placeList[i + 1]; // Shift venues to fill the gap
                }
                numVenues--; // Decrease the number of venues
            } 
            else 
            {
                std :: cerr << "Error: Venue not found!\n";
            }
        }

        static void showVenues()
        {
            std::cout << "Places in the venue list:\n";
            for (int i = 0; i < numVenues; ++i) 
            {
                std::cout << "- " << placeList[i] << '\n';
            }
        }

        static void editVenue(const std :: string& oldPlace, const std :: string& newPlace) 
        {

            int index = -1;
            for (int i = 0; i < numVenues; ++ i) 
            {
                if (placeList[i] == oldPlace) 
                {
                    index = i;
                    break;
                }
            }

            if (index != -1) 
            {
                placeList[index] = newPlace; // Replace the old venue with the new one
            } 
            else 
            {
                std::cerr << "Error: Venue not found!\n";
            }
        }
};

std :: string Venue :: placeList[MAX_VENUES];
int Venue :: numVenues = 0;