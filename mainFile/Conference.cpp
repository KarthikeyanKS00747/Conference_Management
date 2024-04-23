#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <memory>

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

        std :: string displayTime()
        {
            return "";
            // @2 define this
        }

        static bool checkDateTime(std :: string& date_, std :: string& timeSlot_)
        {
            return true; 
            // @3 define this
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
                    std :: cout << "\nVenue Chosen Successfully.";
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
                std::cerr << "Error: Venue list is full!\n";
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
                std::cout << "- " << placeList_[i] << '\n';
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

    public:
        // void registerParticipant(Conference* conference, Participant* participant)
        // {
        //     conference -> participants_.push_back(participant);
        // }

        // Constructor
        Conference(std :: string name, DateTime datetime, Venue venue, Organiser* organiser) : name_(name), datetime_(datetime), venue_(venue), generated_amt_(0.0), conference_id_(init_id), organisers_({organiser})
        {
            // Add this Conference instance to the map
            conferenceMap[name_] = this;
            init_id ++;

        }
        ~Conference();     

        // Method to get Conference instance by name
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

        static std :: map <std :: string, Conference*> getConferenceMap()
        {
            return conferenceMap;
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
                // if (conference_ -> datetime_ == datetime && conference_ -> venue_ == venue)
                // {
                //     return false;
                // }
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
        std :: bool organizerflag=false;

    public:
        static std :: map<std::string, User*> userMap;
        bool isOrganizer() {
            return organizerflag;
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

class Organiser : public User 
{
    private:
        std::string organisationName;
        std::string organiserTitle;

    public:
        // Constructor
        // Organiser(){};
        Organiser(const User& user) : User(user){};
        // Organiser(std::string name, short int age, std::string regNO, std::string gender,
        //         std::string username, std::string password, std::string email,
        //         std::string orgName, std::string title)
        //         : User(name, age, regNO, gender, username, password, email),
        //         organisationName(orgName), organiserTitle(title) {}

        // Getters and Setters
        void setOrganisationName(std::string orgName) { organisationName = orgName; }
        std::string getOrganisationName() const { return organisationName; }

        void setOrganiserTitle(std::string title) { organiserTitle = title; }
        std::string getOrganiserTitle() const { return organiserTitle; }

        // Display organiser information

        void displayOrganiserInfo() const
        {
            display(); // Display user information from the base class
            std::cout << "Organisation Name: " << organisationName << "\nOrganiser Title: " << organiserTitle << std::endl;
        }
        void organiseConference(Conference *conference){;}
        // @ needs to be defined
        // needs to add the pointer to this instance to the sponsors in Conefrence class
};

class Participant: public User
{
    private:
        std :: vector <Conference*> scheduledConferences_ = {};
        std :: vector <DateTime*> scheduledDateTimes_ = {};
    
        // bool conferenceScheduled;

    public:
        // Constructor
        // copy constructor should be the only way to init
        Participant(const User& user) : User(user){};

        ~Participant()
        {
            for (Conference* conference_ : scheduledConferences_)
            {
                delete conference_;
            }
            for (DateTime* datetime_ : scheduledDateTimes_)
            {
                delete datetime_;
            }
            scheduledConferences_.clear();
            scheduledDateTimes_.clear();
        };

        // friend void registerParticipant(Conference* conference, Participant* participant);
        void scheduleConference(Conference *conference)
        {
            // Check if participant already registered for the conference
            for (Conference* conference_ : scheduledConferences_)
            {
                // should be changed to getID()
                if (conference_ -> getName() == conference -> getName())
                {
                    std :: cout << "\nConference already registered.";
                    return;
                }
            }
            DateTime* newDateTime = new DateTime(conference -> getDateTime());
            scheduledConferences_.push_back(conference);
            scheduledDateTimes_.push_back(newDateTime);
            
            // needs to code for the conference to register a participant

            //registerParticipant(conference, this);
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

class Sponsor : public User {
    private:
        std :: string sponsored_event_;
        double amount_;
    
    public:
        Sponsor(std::string name, short int age, std::string regNO, std::string gender, 
        std::string username, std::string password, std::string email, std :: string event, double amt) 
        : User(name, age, regNO, gender, username, password, email),
        sponsored_event_(event), amount_(amt) {};
        Sponsor(std :: string sponsored_event, User &user) : sponsored_event_(sponsored_event), User(user), amount_(0.0){};

        std :: string getEventName(){return sponsored_event_;}

        void display() const override
        {
            std :: cout << "Sponsor: ";
            User :: display();
            std :: cout << ", Event: " << sponsored_event_ << ", Amount: ₹" << amount_;
        }
        void sponsorConference() 
        {
            double sponsored_amount;
            std :: cout << "\nEnter the amount to sponsor: ";
            std :: cin >> sponsored_amount;
            std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            Conference* conference = Conference :: getConferenceByName(sponsored_event_);
            
            for (Sponsor* sponsor : conference -> getSponsors()) 
            {
                if (sponsor == this) 
                {
                    // Conference already sponsored, update sponsorship amount

                    conference -> updateSponsoredAmount(sponsored_amount, amount_);
                    std::cout << "\nSponsorship amount for the conference updated successfully.";
                    return;
                }
            }
            // Conference not sponsored yet, sponsor it
            conference -> updateSponsoredAmount(sponsored_amount);
            std::cout << "\nConference sponsored successfully.";
        }

        double getSponsoredAmount() const 
        {
            return amount_;
        } 
};
Conference :: ~Conference()
{
    for (Organiser* organiser : organisers_) 
    {
        delete organiser;
    }
    organisers_.clear();

    for (Participant* participant : participants_)
    {
        delete participant;
    }
    participants_.clear();

    for (Sponsor* sponsor : sponsors_) 
    {
        delete sponsor;
    }
    sponsors_.clear();
}   
// @ add more venues since we havent implemented flle handling for now
std :: string Venue :: placeList_[Venue :: MAX_VENUES_];
int Venue :: numVenues_ = 0;
std :: map<std::string, User*> User::userMap;
std :: map <std :: string, Conference*> Conference :: conferenceMap;
int Conference :: init_id = 1000;
int Conference :: no_of_conferences = 0;
