
#include "Conference.cpp"


void page_1();
void page_2(User& user);
void exploreConferences(User& user);
void createConferences(User& user);

void deleteAllExit()
{
    Conference :: deleteAllConferences();
    User :: deleteAllUsers();
    exit(0);
}
void createConferences(User& user)
{
    std :: string name;
    std :: string date, timeSlot;
    std :: string venue_name;
    int choice;

    std :: cout << "\nEnter the name of the conference: ";
    getline(std :: cin, name);
    std :: cout << "\n\n\n";


    while (true)
    {
        Venue :: showVenues();
        std :: cout << "\n\n";
        std :: cout << "\nEnter the name of the venue: ";
        getline(std :: cin, venue_name);
        Venue venue(venue_name);
        
        if (Venue :: checkVenue(venue_name))
        {
            std :: cout << "\nVenue exists.\n";
            Conference :: showAvailableTimeSlots(venue);
            std :: cout << "\nEnter date in DD-MM-YYYY format.\n";
            // @ checkDate() here in a while loop
            getline(std :: cin, date);

            std :: cout << "\nChoose the time slot by number (1-4): ";
            std :: cin >> choice;
            std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n'); // Clear the input buffer after reading

            switch (choice) 
            {
                case 1: timeSlot = "8:00 AM"; break;
                case 2: timeSlot = "10:00 AM"; break;
                case 3: timeSlot = "2:00 PM"; break;
                case 4: timeSlot = "5:00 PM"; break;
                default:
                    std :: cout << "Invalid choice. Defaulting to the first time slot." << std :: endl;
                    timeSlot = "8:00 AM";
            }

            DateTime datetime(date, timeSlot);
            if (Conference :: isTimeSlotAvailable(datetime, venue))
            {
                std :: cout << "\nSlot Available.\nSlot booked successfully.\n";
                Organiser* organiser = new Organiser(user);

                std :: string conference_name;
                new Conference(name, datetime, venue, organiser);
                break;
            }
            else 
            {
                std :: cout << "\nSlot already booked.\nTry Again.\n";
            }
        }
        else
        {
            std :: cout << "\nVenue doesn't exist.\nAdd to Venues?[y / any key]";
            std :: string resp;
            std :: cin >> resp;
            std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            std :: cout << "Enter the name of the new venue to be added: ";
            std :: cin >> resp;
            std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            Venue :: addVenue(resp);
            std :: cout << "Venue added to list.\n\n";
        }  
    }
    page_2(user);
}

bool isDigits(const std :: string &str) 
{
    for (char c : str) 
    {
        if (!std :: isdigit(static_cast <unsigned char> (c))) 
        {
            return false;
        }
    }
    return true;
}

std :: map <std :: string, Conference*> :: iterator getConference(int n = 10)
{
    std :: map <std :: string, Conference*> conferenceMap = Conference :: getConferenceMap();
    auto it = conferenceMap.begin();
    size_t size = conferenceMap.size();
    // if (size == 0)
    // {
    //     std :: cout << "\nNo conferences created.\n";
    //     return;
    // } @ decide on this and fix
    size_t i = 0;
    while (true)
    {
        std :: cout << "\n";
        
        while (i < n - 1 && i < size)
        {
            std :: cout << i + 1 << "." << it -> first << "\n";
            ++ i;
            ++ it;
        }

        std :: cout << "Enter your choice [n / next / prev]: ";
        std :: string resp;
        std :: cin >> resp;
        std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
        std :: cout << "\n";


        if (isDigits(resp))
        {
            int num = std :: stoi(resp);
            // @ create code to check for things like if resp was less than 1 or more than 10
            if (num < 1 || num > 10)
            {
                std :: cout << "\nInvalid Input.\nTry Again.\n";
                continue;
            }
            num --;
            std :: advance(it, num - i);
            return it;
        }
        else if (resp == "next")
        {
            if ((size - 10) < i) 
            {
                i = 0;
                n = 10;
            }
            else 
            {
                i += 10;
                n += 10;
            }
        }
        else if (resp == "prev")
        {
            if (i != 0)
            {
                i -= 10;
                n -= 10;
            }
        }
        else
        {
            std :: cout << "error : 1";
        }
    }
}

void page_2(User &user)
{
    while (true)
    {
        std :: cout << "\n\t\tMAIN MENU";
        std :: cout << "\n1. Explore Conferences"; 
        std :: cout << "\n2. Create Conference";
        std :: cout << "\n3. Organiser Portal";
        std :: cout << "\n4. Exit";
        int resp;
        std :: cout << "\n: ";
        std :: cin >> resp;
        std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
        switch(resp)
        {
            case 1:
                exploreConferences(user);
                break;
            case 2:
                createConferences(user);
                break;
            case 3:
                deleteAllExit();
            default:
                std :: cout << "\nInvalid response\n";

        }
    }
}

void exploreConferences(User &user)
{
    std :: cout << "\n\t\tExplore Conferences\n";
    std :: cout << "\n1. Join";
    std :: cout << "\n2. Organise";
    std :: cout << "\n3. Sponsor";
    std :: cout << "\n4. Back to main menu";
    std :: cout << "\nEnter your choice: ";
    int choice;
    char resp = 'y';
    std :: cin >> choice;

    switch(choice)
    {
        case 1:
        {
            Participant* participant = new Participant(user);
            do
            {
                std :: map <std :: string, Conference*> :: iterator it = getConference();
                std :: cout << "\nYou selected: " << it -> first;
                participant -> scheduleConference(it -> second);
                std :: cout << "\nSchedule More? [y / any key]: ";
                std :: cin >> resp;
                std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            }
            while (resp == 'y');
            break;
        }
        case 2:
        {
            // Code to organise the conference
            Organiser* organiser = new Organiser(user);
            do
            {
                std :: map <std :: string, Conference*> :: iterator it = getConference();
                std :: cout << "\nYou selected: " << it -> first;
                it -> second -> organiseConference(organiser);
                std :: cout << "\nOrganise More? [y / any key]: ";
                std :: cin >> resp;
                std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            }
            while (resp == 'y');
            break;
        }
        case 3:
        {
            // Code to sponsor the conference
            do
            {
                std :: map <std :: string, Conference*> :: iterator it = getConference();
                Sponsor* sponsor = new Sponsor(it -> first, user);
                std :: cout << "\nYou selected: " << it -> first;
                sponsor -> sponsorConference();
                std :: cout << "\nSponsor More? [y / any key]: ";
                std :: cin >> resp;
                std :: cin.ignore(std :: numeric_limits<std :: streamsize> :: max(), '\n');
            }
            while (resp == 'y');
            break;
        }
        case 4:
        {
            page_2(user);
            break;
        }
        default:
        {
            std :: cout << "\nInvalid choice. Please try again.\n";
        }
    }
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

    // @ <lengthy medium task> the getters defined in the user class must be overloaded 
    // with static functions having the similar signature
    // to check whether the followign attributes are correct or just name it somn
    // like std :: string get<Attribute>Input() and make it use cin within the function
    // like input in python. please make this static so everyother class can do this.
    // the whole point of this is to check for abnormalities. use regex for email, name, username, reg no
    // and finally use it here in place of the cin statements
    std::cout << "\nEnter your details:\n";
    std::cout << "\nName: ";
    std::cin >> name;
    std::cout << "\nAge: ";
    std::cin >> age;
    std::cout << "\nRegistration Number: ";
    std::cin >> regNO;
    std::cout << "\nGender: ";
    std::cin >> gender;
    std::cout << "\nUsername: ";
    std::cin >> username;
    std::cout << "\nPassword: ";
    // have to create a function for setting good password
    std::cin >> password;
    std::cout << "\nEmail: ";
    std::cin >> email;

    // Create a new User and add it to the userMap
    User(name, age, regNO, gender, username, password, email); 
    std :: cout << "\nSigned up successfully.\n\n";
    page_1();
}

void sign_in()
{
    // Implementation can be changed for security reasons
    while (true)
    {
        std :: string username;
        std :: string password;
        std :: cout << "\nUsername : ";
        std :: cin >> username;
        std :: cout << "\nPassword : ";
        std :: cin >> password;
        User *user = User :: getUserByUsername(username);
        if (user != nullptr && user -> getPassword() == password)
        {
            std :: cout << "\nPassword is correct.";
            std :: cout << "\nSigned in successfully.\n";
            page_2(*user);
        }
        else
        {
            std::cout << "\nInvalid username or password.";
        }
        
    }
}



void page_1()
{
    while (true)
    {
        std :: cout << "\n\n\t\tMAIN MENU\n";
        std :: cout << "\n1. Sign-In\n";
        std :: cout << "\n2. Sign-Up\n";
        std :: cout << "\n3. Exit\n";
        int resp;
        std :: cout << "\n: ";
        std :: cin >> resp;
        std :: cin.ignore(std  :: numeric_limits<std :: streamsize> :: max(), '\n');
        switch(resp)
        {
            case 1:
                sign_in();
                break;
            case 2:
                sign_up();
                break;
            case 3:
                deleteAllExit();
            default:
                std :: cout << "Invalid response\n";
        }
    }
}
// @ <lengthy moderately tough task> implementation of the "<-" to go back to everything
// in the ui each time to use it. for example if you go from page 1 to page 2, typing "<-"
// should make the control flow go back to page 1, since we wont be using goto or async
// the function should figure out where to go back to (probably by the use of parameters)
// 
int main(void)
{
    Venue :: addVenue("Anna Auditorium");
    Venue :: addVenue("1");
    page_1();
    deleteAllExit();

    return 0;
}