#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <memory>
#include <regex>
#include <sstream>
#include <iomanip>
#include <ctime>
class DateTime
{
    private:
        std :: string date_;
        std :: string time_;
        std :: string day_;

        std::string getDay() const 
        {
            const char* date_cstr = date_.c_str();
            // Parse the date
            std :: istringstream ss(date_cstr);
            std :: tm tm = {};
            ss >> std :: get_time(&tm, "%m-%d-%Y");

            // Convert to time_t
            std::time_t time = std::mktime(&tm);

            // Get the day of the week
            char buffer[10];
            std::strftime(buffer, 10, "%A", std::localtime(&time));

            // Convert to string
            return std::string(buffer);
        }

    public:
        // DateTime() : date_("00-00-0000"), time_("00:00:00")
        // {
        //     day_ = getDay();
        // }

        DateTime(const DateTime& other)
        : date_(other.date_), time_(other.time_), day_(other.day_){}
        // Copy constructor for DateTime

        DateTime(std :: string date, std :: string time) : date_(date), time_(time)
        {
            day_ = getDay();
        }

        std :: string displayDate(std :: string format)
        {
            if (format == "HHHH")
            {
                return day_;
            }
            else if (format == "MM-DD-YYYY")
            {
                return (date_.substr(3, 4) + '-' + date_.substr(0, 1) + '-' + date_.substr(6, 9));
            }
            else if (format == "DD-MM-YYYY")
            {
                return (date_.substr(0, 1) + '-' + date_.substr(3, 4) + '-' + date_.substr(6, 9));
            }
            else
            {
                std :: cout << "\nError: Not a valid Date Format\n";
                return "00-00-0000";
            }
        }

        std::string displayTime(const std::string& format = "HH:MM:SS")
        {
            if (format == "HH:MM:SS")
            {
                return time_;
            }
            else if (format == "HH:MM")
            {
                return time_.substr(0, 5);
            }
            else if (format == "HH")
            {
                return time_.substr(0, 2);
            }
            else
            {
                std::cout << "\nError: Not a valid Time Format\n";
                return "00:00:00";
            }
        }

        static bool checkDate(const std::string& date, const std::string& format = "DD-MM-YYYY")
        {
            std::regex pattern;
            if (format == "DD-MM-YYYY")
            {
                pattern = std::regex("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[012])-([12][0-9]{3})$");
            }
            else if (format == "DD-MM")
            {
                pattern = std::regex("^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[012])$");
            }
            else if (format == "DD")
            {
                pattern = std::regex("^(0[1-9]|[12][0-9]|3[01])$");
            }
            else
            {
                std::cout << "\nError: Not a valid Date Format\n";
                return false;
            }
            return std::regex_match(date, pattern);
        }

        static bool checkTime(const std::string& time, const std::string& format = "HH:MM:SS")
        {
            std::regex pattern;
            if (format == "HH:MM:SS")
            {
                pattern = std::regex("^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$");
            }
            else if (format == "HH:MM")
            {
                pattern = std::regex("^([01][0-9]|2[0-3]):[0-5][0-9]$");
            }
            else if (format == "HH")
            {
                pattern = std::regex("^([01][0-9]|2[0-3])$");
            }
            else
            {
                std::cout << "\nError: Not a valid Time Format\n";
                return false;
            }
            return std::regex_match(time, pattern);
        }

        bool operator == (const DateTime& other) const 
        {
            return date_ == other.date_ && time_ == other.time_;
        }

};

class Venue
{
    private:
        std :: string venue_name_;
        static int numVenues_; // Number of venues currently stored
        static const int MAX_VENUES_ = 100; // Maximum number of venues
        static std :: string placeList_[MAX_VENUES_]; // Array to store venue names
        // @7 create venues either here or at the bottom of the code (about 15 atleast)

    public:
        Venue(){};
        Venue(const std :: string& venue_name) 
        {
            for (int i = 0; i < numVenues_; ++ i) 
            {
                if (placeList_[i] == venue_name) 
                {
                    venue_name_ = venue_name;
                }
            }
        }

        ~Venue(){};

        static void addVenue(const std :: string& venue_name) 
        {
            for (int i = 0; i < numVenues_; ++ i) 
            {
                if (placeList_[i] == venue_name) 
                {
                    std::cout << "Cannot add venue: " << venue_name << " is already in the list.\n";
                    return;
                }
            }
            if (numVenues_ < MAX_VENUES_)
            {
                placeList_[numVenues_ ++] = venue_name; // Add the new venue to the list
            } 
            else 
            {
                std :: cout << "Error: Venue list is full!\n";
            }
        }

        static void deleteVenue(const std :: string& venue_name) 
        {
            int index = -1;
            for (int i = 0; i < numVenues_; ++ i) 
            {
                if (placeList_[i] == venue_name) 
                {
                    index = i;
                    break;
                }
            }
            if (index != -1)
            {
                for (int i = index; i < numVenues_ - 1; ++ i)
                {
                    placeList_[i] = placeList_ [i + 1]; // Shift venues to fill the gap
                }
                numVenues_ --; // Decrease the number of venues
            } 
            else 
            {
                std :: cout << "\nError: Venue not found!\n";
            }
        }

        static void showVenues()
        {
            std :: cout << "Places in the venue list:\n";
            for (int i = 0; i < numVenues_; ++ i) 
            {
                std :: cout << "- " << placeList_[i] << '\n';
            }
        }

        static void editVenue(const std :: string& oldPlace, const std :: string& newPlace) 
        {

            int index = -1;
            for (int i = 0; i < numVenues_; ++ i) 
            {
                if (placeList_[i] == oldPlace) 
                {
                    index = i;
                    break;
                }
            }

            if (index != -1) 
            {
                placeList_[index] = newPlace; // Replace the old venue with the new one
            } 
            else 
            {
                std :: cout  << "\nError: Venue not found!\n";
            }
        }

        static bool checkVenue(const std :: string& venue_name_)
        {
            for (int i = 0; i < numVenues_; ++i)
            {
                if (placeList_[i] == venue_name_)
                {
                    return true; // Venue found
                }
            }
            return false; // Venue not found
        }
        bool operator == (const Venue& other)
        {
            return this -> venue_name_ == other.venue_name_;
        }

};

class User;
class Organiser;
class Participant;    
class Sponsor;


class Conference : std :: enable_shared_from_this<Conference>
{
    protected:
        DateTime datetime_;
        Venue venue_;
        std :: vector <std :: shared_ptr<Organiser>> organisers_;
        std :: vector <std :: shared_ptr<Participant>> participants_;
        std :: vector <std :: shared_ptr<Sponsor>> sponsors_;
        double generated_amt_ = 0.0;
        int conference_id_;
        std :: string name_;
        static int init_id;
        static int no_of_conferences;
        static std :: map <std :: string, std :: shared_ptr<Conference>> conferenceMap;

        std :: vector <std :: shared_ptr<Organiser>> getOrganisers()
        {
            return organisers_;
        }
        void registerOrganiser(std :: shared_ptr<Organiser> organiser)
        {
            organisers_.push_back(organiser);
        }
        void registerSponser(std :: shared_ptr<Sponsor> sponsor)
        {
            sponsors_.push_back(sponsor);
        }
        

    public:
        static std :: pair<std :: shared_ptr<Organiser>, std :: shared_ptr<Conference>> getOrganiserAndConference(std :: shared_ptr<User> user);
        void registerParticipant(std :: shared_ptr<Participant> participant)
        {
            participants_.push_back(participant);
        }
        // Constructor
        Conference(std :: string name, DateTime datetime, Venue venue, std :: shared_ptr<Organiser> organiser) : name_(name), datetime_(datetime), venue_(venue), generated_amt_(0.0), conference_id_(init_id), organisers_({organiser})
        {
            // Add this Conference instance to the map
            conferenceMap[name_] = shared_from_this();
            init_id ++;
            no_of_conferences ++;
        }
        ~Conference();     

        int getConferenceID()
        {
            return conference_id_;
        }
        // Method to get Conference instance by name

        static std :: map <std :: string, std :: shared_ptr<Conference>> getConferenceMap()
        {
            return conferenceMap;
        }

        static std :: shared_ptr<Conference> getConferenceByName(const std :: string& name) 
        {
            if (conferenceMap.find(name) != conferenceMap.end()) 
            {
                return conferenceMap[name];
            } 
            else 
            {
                return nullptr;
            }
        }

        std :: string getName()
        { 
            return name_; 
        }

        DateTime getDateTime()
        {
            return datetime_;
        }

        static void showAvailableTimeSlots(Venue& venue) // @ Change this so that it accesses the slot from conference and shows the rest only 
        {
            std :: cout << "\nAvailable Time Slots:" << std :: endl;
            std :: cout << "1. 8:00 AM - 10:00 AM" << std :: endl;
            std :: cout << "2. 10:00 AM - 12:00 PM" << std :: endl;
            std :: cout << "3. 2:00 PM - 5:00 PM" << std :: endl;
            std :: cout << "4. 5:00 PM - 7:00 PM" << std :: endl;
        }

        static bool isTimeSlotAvailable(DateTime datetime, Venue venue) 
        {
            
            std :: map <std :: string, std :: shared_ptr<Conference>> :: iterator it = conferenceMap.begin();
            for (std :: map <std :: string, std :: shared_ptr<Conference>> :: iterator end = conferenceMap.end(); it != end; ++ it)
            {
                std :: shared_ptr<Conference> conference_ = it -> second;
                if (conference_ -> datetime_ == datetime && conference_ -> venue_ == venue)
                {
                    return false;
                }
            }
            return true;

        }
        void updateSponsoredAmount(double new_sponsored_amount, double old_sponsored_amount = 0)
        {
            generated_amt_ += new_sponsored_amount - old_sponsored_amount;
            return;
        }
        std :: vector <std :: shared_ptr<Sponsor>> getSponsors()
        {
            return sponsors_;
        }

        static void deleteAllConferences()
        {
            conferenceMap.clear();
            // no requirement for deleteing the pointer separately
        }
        
        void organiseConference(std :: shared_ptr<Organiser> organiser_);
        void sponsorConference(std :: shared_ptr<Sponsor> sponsor_);

};


class User : public std :: enable_shared_from_this<User>
{
    private:
        std :: string name;
        short int age;
        std :: string regNO;
        std :: string gender;
        std :: string username;
        std :: string password;
        std :: string email;

    protected:
        bool organiserflag = false;
        std :: shared_ptr<User> getUserPtr() 
        {
            return shared_from_this();
        }
        void copyUserDetails()
        {
            std::shared_ptr<User> userPtr = getUserPtr();
            if (userPtr) 
            {
                this -> name = userPtr -> name;
                this -> age = userPtr -> age;
                this -> regNO = userPtr -> regNO;
                this -> gender = userPtr -> gender;
                this -> username = userPtr -> username;
                this -> password = userPtr -> password;
                this -> email = userPtr -> email;
                this -> organiserflag = userPtr -> organiserflag;
            }
        }

    public:
        static std :: map<std::string, std :: shared_ptr<User>> userMap;


        bool operator == (const User& other) const
        {
            return this -> regNO == other.regNO;
        }
        bool isOrganizer() 
        {
            return organiserflag;
        }
        // Constructor
        User
        (std :: string name, short int age, std :: string regNO, std :: string gender, 
        std :: string username, std :: string password, std :: string email)
        : name(name), age(age), regNO(regNO), gender(gender), 
        username(username), password(password), email(email) 
        {
            userMap[username] = shared_from_this();

        }

        User(std::shared_ptr<User> other)
            : name(other -> name), age(other -> age), regNO(other -> regNO), gender(other -> gender),
              username(other -> username), password(other -> password), email(other -> email) 
        {
            userMap[username] = shared_from_this();

        }
        // Default Constructor
        // User() {}; 
        // This implementation must be removed
        // default cons
        ~User(){}
        static std :: shared_ptr<User> getUserByUsername(const std::string& username) 
        {
            if (userMap.find(username) != userMap.end()) 
            {
                std :: cout << "\nUser Found\n";
                return userMap[username];
            }
            else 
            {
                std :: cout << "\nUser Not Found\n";
                return nullptr;
            }
        }

        // Getters and Setters
        void setName(std :: string n) { name = n; }
        std :: string getName() const { return name; }

        void setAge(short int a) { age = a; }
        short int getAge() const { return age; }

        void setRegNO(std :: string r) { regNO = r; }
        std :: string getRegNO() const { return regNO; }

        void setGender(std :: string g) { gender = g; }
        std :: string getGender() const { return gender; }

        void setUsername(std :: string u) { username = u; }
        std :: string getUsername() const { return username; }

        void setPassword(std :: string p) { password = p; }
        std :: string getPassword() const { return password; }

        void setEmail(std :: string e) { email = e; }
        std :: string getEmail() const { return email; }

        // Display user information
        virtual void display()
        {
            //virtual keyword is used so that the method display can be overidden by base classes when necessary
            std :: cout << "Name: " << name << "\nAge: " << age 
                << "\nRegistration Number: " << regNO 
                << "\nGender: " << gender << "\nUsername: " 
                << username << "\nEmail: " << email << std :: endl;
        }

        // Login verification
        bool verifyLogin(std :: string uname, std :: string pword) {
            return uname == username && pword == password;
        }

        // Update Information
        void updateEmail(std :: string newEmail)
        {
            email = newEmail;
        }

        void updatePassword(std :: string newPassword)
        {
            password = newPassword;
        }
        static void deleteAllUsers()
        {
            for (auto& it : userMap)
            {
                it.second.reset();
            }
            userMap.clear();
        }
        // More functions like updateName, updateAge, etc. can be added similarly

};

class Organiser : public virtual User 
{
    private:
        std :: string organisationName_;
        std :: string organiserTitle_;

    public:

        Organiser(std :: shared_ptr<User> user, std::string organisationName, std::string organiserTitle) 
            : User(*user), organisationName_(organisationName), organiserTitle_(organiserTitle)
        {
            this -> organiserflag = true;
        };
        // Organiser(std::string name, short int age, std::string regNO, std::string gender,
        //         std::string username, std::string password, std::string email,
        //         std::string orgName, std::string title)
        //         : User(name, age, regNO, gender, username, password, email),
        //         organisationName(orgName), organiserTitle(title) {}

        // Getters and Setters
        // void setOrganisationName(std::string orgName) { organisationName_ = orgName; }
        // std::string getOrganisationName() const { return organisationName_; }

        // void setOrganiserTitle(std::string title) { organiserTitle_ = title; }
        // std::string getOrganiserTitle() const { return organiserTitle_; }

        // Display organiser information
        void display()
        {
            copyUserDetails();
            User :: display(); // Display user information from the base class
            std::cout << "Organisation Name: " << organisationName_ << "\nOrganiser Title: " << organiserTitle_ << std::endl;
        }
        //@ whats the point here
        bool operator == (Organiser& other)
        {
            copyUserDetails();
            return User :: operator == (other);
            // previous declaration where changing into static cast of User cant work
            // through the use of shared pointer
        }
        bool operator == (User& other)
        {
            copyUserDetails();
            return User :: operator == (other);
            // previous declaration where changing into static cast of User cant work
            // through the use of shared pointer
        }

        friend void Conference :: organiseConference(std :: shared_ptr<Organiser> organiser_);

};
// @ needs to change conference to shared pointer implementation
std :: pair <std :: shared_ptr<Organiser>, std :: shared_ptr<Conference>> Conference :: getOrganiserAndConference(std :: shared_ptr<User> user) 
{
    for (auto& pair : Conference :: getConferenceMap()) 
    {
        std :: shared_ptr<Conference> conference = pair.second;
        for (std :: shared_ptr<Organiser> organiser : conference -> getOrganisers()) 
        {
            if (*organiser == *user) 
            {
                return {organiser, conference};
            }
        }
    }
    return {nullptr, nullptr};
}
void Conference :: organiseConference(std :: shared_ptr<Organiser> organiser_)
{
    for (std :: shared_ptr<Organiser> organiser : getOrganisers())
    {
        if (organiser_ == organiser) 
        {
            std :: cout << "\nThe conference " << this -> getName() << " is already organised by " << organiser_ -> getName() << ".\n";
            return;
        }
    }
    this -> registerOrganiser(organiser_);
    std :: cout << "\nChanges have been made successfully.\n";
}
class Participant: public virtual User
{
    private:
        std :: vector <std :: shared_ptr<Conference>> scheduledConferences_ = {};
        std :: vector <std :: shared_ptr<DateTime>> scheduledDateTimes_ = {};

    public:
        Participant(std :: shared_ptr<User> user) : User(*user){}
        Participant(Participant* p) : User(*p){}

        ~Participant()
        {
            scheduledConferences_.clear();
            scheduledDateTimes_.clear();
            // why does this implementation work?
            // because if all shared pointers point to not the object
            // then the object is deleted and also delete cannot be used
            // since we are not dealing with raw pointers
        };

        void scheduleConference(std :: shared_ptr<Conference> conference)
        {
            // Check if participant already registered for the conference
            for (std :: shared_ptr<Conference> conference_ : scheduledConferences_)
            {
                if (conference_ -> getConferenceID() == conference -> getConferenceID())
                {
                    std :: cout << "\nConference already registered.";
                    return;
                }
            }
            std :: shared_ptr<DateTime> newDateTime = std :: make_shared<DateTime>(conference -> getDateTime());
            // @ have to change Conference class implementation
            scheduledConferences_.push_back(conference);
            scheduledDateTimes_.push_back(newDateTime);
            conference -> registerParticipant(std :: make_shared<Participant>(this));
        
            std :: cout << "\nConference registered successfully.";
        }

        void showConferences()
        {
            if (scheduledConferences_.empty())
            {
                std :: cout << "\nNo conferences scheduled.";
                return;
            }

            std :: cout << "\nScheduled Conferences : ";
            for (std :: shared_ptr<Conference> conference_ : scheduledConferences_)
            {
                std :: cout << "\nConference Name: " << conference_ -> getName();
                DateTime datetime_ = conference_ -> getDateTime();
                std :: cout << "\nDay: " << datetime_.displayDate("HHHH") << ", Time: " << datetime_.displayTime(/*some time format*/);
            }
        }

        void showTimes(/*std :: string format*/)
        {
            for (std :: shared_ptr<DateTime> datetime_ : scheduledDateTimes_)
            {
                std :: cout << "\n" << datetime_ -> displayDate("DD-MM-YYYY") << datetime_ -> displayTime();
            }
        }

};

class Sponsor : public virtual User {
    private:
        std :: string sponsored_event_;
        double amount_;
    
    public:
        // Sponsor(std::string name, short int age, std::string regNO, std::string gender, 
        // std::string username, std::string password, std::string email, std :: string event, double amt) 
        // : User(name, age, regNO, gender, username, password, email),
        // sponsored_event_(event), amount_(amt) {};
        Sponsor(std :: string sponsored_event, std :: shared_ptr<User> user) : sponsored_event_(sponsored_event), User(*user), amount_(0.0){};

        std :: string getEventName(){return sponsored_event_;}

        void display() override
        {
            copyUserDetails();
            std :: cout << "Sponsor Details: ";
            User :: display();
            std :: cout << ", Event: " << sponsored_event_ << ", Amount: ₹" << amount_;
        }
        bool operator == (Sponsor& other)
        {
            copyUserDetails();
            return User :: operator == (other);
        }
        friend void Conference :: sponsorConference(std :: shared_ptr<Sponsor> sponsor);

        double getSponsoredAmount() const 
        {
            return amount_;
        } 
};

void Conference :: sponsorConference(std :: shared_ptr<Sponsor> sponsor)
{
    double sponsored_amount;
    std :: cout << "\nEnter the amount to sponsor: ";
    std :: cin >> sponsored_amount;
    std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
    
    for (std :: shared_ptr<Sponsor> sponsor_ : this -> getSponsors()) 
    {
        if (sponsor_ == sponsor) 
        {
            // Conference already sponsored, update sponsorship amount
            this -> updateSponsoredAmount(sponsor_ -> amount_, sponsored_amount);
            std::cout << "\nSponsorship amount for the conference updated successfully.";
            return;
        }
    }
    // Conference not sponsored yet, sponsor it
    this -> updateSponsoredAmount(sponsored_amount);
    this -> registerSponser(sponsor);
    std::cout << "\nConference sponsored successfully.";
}

Conference :: ~Conference()
{
    organisers_.clear();
    participants_.clear();
    sponsors_.clear();
    no_of_conferences --;
    init_id --;
}   

// @ add more venues since we havent implemented flle handling for now
std :: string Venue :: placeList_[Venue :: MAX_VENUES_];
int Venue :: numVenues_ = 0;
std :: map <std :: string, std :: shared_ptr<User>> User :: userMap;
std :: map <std :: string, std :: shared_ptr<Conference>> Conference :: conferenceMap;
int Conference :: init_id = 1000;
int Conference :: no_of_conferences = 0;
