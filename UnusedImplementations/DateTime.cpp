#include <string>
#include <sstream>
#include <chrono>
#include <format>

class DateTime {
private:
    std::string date_;  // The date in MM-DD-YYYY format
    std::string time_;  // The time in HH:MM:SS format
    std::string day_;   // The day of the week

public:
    
    DateTime();                                         // Default constructor: Initializes date_ and time_ to default values
    DateTime(const DateTime& other);                    // Copy constructor: Initializes a new DateTime object with the same date, time, and day 
                                                        // as another DateTime object
    DateTime(std::string date, std::string time);       // Constructor: Initializes date_ and time_ with the given arguments

    std::string getDay() const;                         // Member function: Returns the day of the week for the date_
    std::string displayDate(std::string format);        // Member function: Returns the date_ in the specified format
    std::string displayTime();                          // Member function: Returns the time_

    static bool checkDateTime(std::string& date_, std::string& timeSlot_);  // Static member function: Checks if the given date and time are valid
    bool operator==(const DateTime& other) const;                           // Operator overload: Compares this DateTime object with 
                                                                            // another based on date_ and time_
};