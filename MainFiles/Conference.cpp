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
        // default not allowed

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

    public:
        Venue(){}; // not allowed and should not be not used (early implemenatation)
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

class Conference
{
    protected:
        DateTime datetime_;
        Venue venue_;
        std :: vector <Organiser*> organisers_;
        std :: vector <Participant*> participants_;
        std :: vector <Sponsor*> sponsors_;
        double generated_amt_ = 0.0;
        int conference_id_;
        std :: string name_;
        static int init_id;
        static int no_of_conferences;
        static std :: map <std :: string, Conference*> conferenceMap;
        std :: vector <Organiser*> getOrganisers()
        {
            return organisers_;
        }
        void registerOrganiser(Organiser* organiser)
        {
            organisers_.push_back(organiser);
        }
        void registerSponser(Sponsor* sponsor)
        {
            sponsors_.push_back(sponsor);
        }
        

    public:
        static std::pair<Organiser*, Conference*> getOrganiserAndConference(User& user);
        void registerParticipant(Participant* participant)
        {
            participants_.push_back(participant);
        }
        // Constructor
        Conference(std :: string name, DateTime datetime, Venue venue, Organiser* organiser) : name_(name), datetime_(datetime), venue_(venue), generated_amt_(0.0), conference_id_(init_id), organisers_({organiser})
        {
            // Add this Conference instance to the map
            conferenceMap[name_] = this;
            init_id ++;
            no_of_conferences ++;
        }
        ~Conference();     

        int getConferenceID()
        {
            return conference_id_;
        }
        // Method to get Conference instance by name

        static std :: map <std :: string, Conference*> getConferenceMap()
        {
            return conferenceMap;
        }
        static Conference* getConferenceByName(const std :: string& name) 
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
            
            std :: map <std :: string, Conference*> :: iterator it = conferenceMap.begin();
            for (std :: map <std :: string, Conference*> :: iterator end = conferenceMap.end(); it != end; ++ it)
            {
                Conference* conference_ = it -> second;
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
        std :: vector <Sponsor*> getSponsors()
        {
            return sponsors_;
        }

        static void deleteAllConferences()
        {
            
            for (const auto& it : conferenceMap)
            {
                delete it.second;
            }
            conferenceMap.clear();
        }
        
        void organiseConference(Organiser* organiser_);
        void sponsorConference(Sponsor* sponsor_);

};


class User
{
    private:
        std :: string name;
        short int age;
        std :: string regNO;
        std :: string gender;
        std :: string username;
        std :: string password;
        std :: string email;
        static std :: map<std::string, User*> userMap;

    protected:
        bool organiserflag = false;

    public:
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
            userMap[username] = this;
        }

        User(const User& other)
            : name(other.name), age(other.age), regNO(other.regNO), gender(other.gender),
              username(other.username), password(other.password), email(other.email) 
        {
            userMap[username] = this;
        }
        // Default Constructor
        // User() {}; 
        // This implementation must be removed
        // default cons
        ~User(){}
        static User* getUserByUsername(const std::string& username) 
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
        virtual void display() const {//virtual keyword is used so that the method display can be overidden by base classes when necessary
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
                delete it.second;
            }
            userMap.clear();
        }
        // More functions like updateName, updateAge, etc. can be added similarly

};

class Organiser : public virtual User 
{
    private:
        std::string organisationName_;
        std::string organiserTitle_;

    public:
        // Constructor
        // Organiser(){};
        Organiser(const User& user, std::string organisationName_, std::string organiserTitle_) : User(user)
        {
            User :: organiserflag = true;
        };
        // Organiser(std::string name, short int age, std::string regNO, std::string gender,
        //         std::string username, std::string password, std::string email,
        //         std::string orgName, std::string title)
        //         : User(name, age, regNO, gender, username, password, email),
        //         organisationName(orgName), organiserTitle(title) {}

        // Getters and Setters
        void setOrganisationName(std::string orgName) { organisationName_ = orgName; }
        std::string getOrganisationName() const { return organisationName_; }

        void setOrganiserTitle(std::string title) { organiserTitle_ = title; }
        std::string getOrganiserTitle() const { return organiserTitle_; }

        // Display organiser information
        void display() const override
        {
            User :: display(); // Display user information from the base class
            std::cout << "Organisation Name: " << organisationName_ << "\nOrganiser Title: " << organiserTitle_ << std::endl;
        }
        friend void Conference :: organiseConference(Organiser* organiser_);

        bool operator == (Organiser* other)
        {
            return User :: operator == (*static_cast<User*>(other));
        }
};

std::pair<Organiser*, Conference*> Conference :: getOrganiserAndConference(User& user) 
{
    for (auto& pair : Conference::getConferenceMap()) {
        Conference* conference = pair.second;
        for (Organiser* organiser : conference -> getOrganisers()) 
        {
            if (*static_cast<User*>(organiser) == user) {
                return {organiser, conference};
            }
        }
    }
    return {nullptr, nullptr};
}
void Conference :: organiseConference(Organiser* organiser_)
{
    for (Organiser* organiser : getOrganisers())
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
        std :: vector <Conference*> scheduledConferences_ = {};
        std :: vector <DateTime*> scheduledDateTimes_ = {};
        
        // bool conferenceScheduled;

    public:
        // Constructor
        // copy constructor should be the only way to init
        Participant(const User& user) : User(user){}

        ~Participant()
        {
            for (Conference* conference_ : scheduledConferences_)
            {
                if (conference_ != nullptr)
                {
                    delete conference_;
                    conference_ = nullptr;
                }
            }
            scheduledConferences_.clear();
            for (DateTime* datetime_ : scheduledDateTimes_)
            {
                delete datetime_;
                datetime_ = nullptr;
            }
            scheduledDateTimes_.clear();
        };
        // friend void registerParticipant(Conference* conference, Participant* participant);
        void scheduleConference(Conference *conference)
        {
            // Check if participant already registered for the conference
            for (Conference* conference_ : scheduledConferences_)
            {
                if (conference_ -> getConferenceID() == conference -> getConferenceID())
                {
                    std :: cout << "\nConference already registered.";
                    return;
                }
            }
            DateTime* newDateTime = new DateTime(conference -> getDateTime());
            scheduledConferences_.push_back(conference);
            scheduledDateTimes_.push_back(newDateTime);
            conference -> registerParticipant(this);
        
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
            for (Conference *conference_ : scheduledConferences_)
            {
                std :: cout << "\nConference Name: " << conference_ -> getName();
                DateTime datetime_ = conference_ -> getDateTime();
                std :: cout << "\nDay: " << datetime_.displayDate("HHHH") << ", Time: " << datetime_.displayTime(/*some time format*/);
            }
        }

        void showTimes(/*std :: string format*/)
        {
            for (DateTime* datetime_ : scheduledDateTimes_)
            {
                std :: cout << "\n" << datetime_ -> displayDate("DD-MM-YYYY"/*format1*/) << datetime_ -> displayTime(/*format2*/);
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
        Sponsor(std :: string sponsored_event, User &user) : sponsored_event_(sponsored_event), User(user), amount_(0.0){};

        std :: string getEventName(){return sponsored_event_;}

        void display() const override
        {
            std :: cout << "Sponsor: ";
            User :: display();
            std :: cout << ", Event: " << sponsored_event_ << ", Amount: ₹" << amount_;
        }
        bool operator == (Sponsor* other)
        {
            return User :: operator == (*static_cast<User*>(other));
        }
        friend void Conference :: sponsorConference(Sponsor* sponsor);

        double getSponsoredAmount() const 
        {
            return amount_;
        } 
};

void Conference :: sponsorConference(Sponsor* sponsor)
{
    double sponsored_amount;
    std :: cout << "\nEnter the amount to sponsor: ";
    std :: cin >> sponsored_amount;
    std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
    
    for (Sponsor* sponsor_ : this -> getSponsors()) 
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
    for (Organiser* organiser : organisers_) 
    {
        delete organiser;
        organiser = nullptr;
    }
    organisers_.clear();

    for (Participant* participant : participants_)
    {
        delete participant;
        participant = nullptr;
    }
    participants_.clear();

    for (Sponsor* sponsor : sponsors_) 
    {
        delete sponsor;
        sponsor = nullptr;
    }
    sponsors_.clear();
    no_of_conferences --;
    init_id --;
}   

// @ add more venues since we havent implemented flle handling for now
std :: string Venue :: placeList_[Venue :: MAX_VENUES_];
int Venue :: numVenues_ = 0;
std :: map <std :: string, User*> User :: userMap;
std :: map <std :: string, Conference*> Conference :: conferenceMap;
int Conference :: init_id = 1000;
int Conference :: no_of_conferences = 0;
