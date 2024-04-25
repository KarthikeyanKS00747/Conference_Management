
#include "Conference.cpp"


void page_1();
void page_2(User& user);
void exploreConferences(User& user);
void createConferences(User& user);

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

int getIntegerInput()
{
    while(1)
    {
        std::string temp;
        getline(std::cin,temp);
        if(isDigits(temp))
        {
             return(std::stoi(temp));
        }
        std::cout<<"\nInvalid Input\nEnter an Integer.\n";
    }
}
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
            std :: cout << "\nVenue Chosen Successfully.\n";
            Conference :: showAvailableTimeSlots(venue);
            while (true)
            {
                std :: cout << "\nEnter date in DD-MM-YYYY format.\n";
                getline(std :: cin, date);
                if (DateTime :: checkDate(date))
                {
                    break;
                }
                else
                {
                    std :: cout << "\nInvalid date format. Please enter date in DD-MM-YYYY format.\n";
                }
            }

            std :: cout << "\nChoose the time slot by number (1-4): ";
            choice = getIntegerInput();
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
                std::string organisationName;
                do {
                    std::cout << "Enter your organisation name: ";
                    std::getline(std::cin, organisationName);
                } while (organisationName.empty());
                std::string organiserTitle;
                do {
                    std::cout << "Enter your organisation title: ";
                    std::getline(std::cin, organiserTitle);
                } while (organiserTitle.empty());
                std :: cout << "\nDetails have been successfully saved.\n";
                Organiser* organiser = new Organiser(user, organisationName, organiserTitle);

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
            std :: cout << "\nVenue doesn't exist.\nAdd to Venues? [y / any key]: ";
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
void orgPortal(User &user)
{
    while (true)
    {
        std::cout << "\n";
        std::cout << "\n1. Venue manipulation";
        std::cout << "\n2. Show Conference";
        std::cout << "\n3. Back to main menu";
        std::cout << "\nEnter your choice (1-3): ";
        int choice;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            // Edit Conference
            int editChoice;
            std::cout << "1. Add Venue\n";
            std::cout << "2. Delete Venue\n";
            std::cout << "3. Show Venues\n";
            std::cout << "4. Edit Venue\n";
            std::cout << "Enter your choice (1-4): ";
            std::cin >> editChoice;

            switch (editChoice)
            {
            case 1:
            {
                std::string newVenue;
                std::cout << "Enter the name of the venue to add: ";
                std::cin >> newVenue;
                Venue::addVenue(newVenue);
                std::cout << "The venue has been successfully added\n";
                break;
            }
            case 2:
            {
                std::string venueToDelete;
                std::cout << "Enter the name of the venue to delete: ";
                std::cin >> venueToDelete;
                Venue::deleteVenue(venueToDelete);
                std::cout << "The venue has been successfully deleted\n";
                break;
            }
            case 3:
            {
                std::cout << "The venue available for a conference booking are:\n";
                Venue::showVenues();
                break;
            }
            case 4:
            {
                std::string oldVenue, newVenueName;
                std::cout << "Enter the name of the venue to edit: ";
                std::cin >> oldVenue;
                std::cout << "Enter the new name of the venue: ";
                std::cin >> newVenueName;
                Venue::editVenue(oldVenue, newVenueName);
                std::cout << "The venue has been successfully updated\n";
                break;
            }
            default:
                std::cout << "Invalid choice\n";
                break;
            }
            break;
        }
        case 2:
        {
            std::pair<Organiser*, Conference*> organiserAndConference = Conference::getOrganiserAndConference(user);
            Organiser* organiser = organiserAndConference.first;
            Conference* conference = organiserAndConference.second;
        
            if (organiser && conference) {
                std::cout << "Organiser: " << organiser->getName() << " is organising Conference: " << conference->getName() << "\n";
            } else {
                std::cout << "No conference found for the organiser.\n";
            }
            break;
        }
        case 3:
            page_2(user);
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
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
        std :: cout << "\n4. Back to Start Menu";
        std :: cout << "\n5. Exit";
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
                if (user.isOrganizer()) orgPortal(user);
                else 
                {
                    std::cout<<"You are not registered as an organiser.\n";
                    break;
                }
            case 4:
                page_1();
                break;
            case 5:
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
    std :: cout << "\n5. Exit";

    std :: cout << "\nEnter your choice: ";
    int choice = getIntegerInput();
    char resp = 'y';

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
            std::string organisationName;
            do 
            {
                std::cout << "Enter your organisation name: ";
                std::getline(std::cin, organisationName);
            } while (organisationName.empty());
            std::string organiserTitle;
            do {
                std::cout << "Enter your organisation title: ";
                std::getline(std::cin, organiserTitle);
            } while (organiserTitle.empty());

            Organiser* organiser = new Organiser(user, organisationName, organiserTitle);

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
                it -> second -> sponsorConference(sponsor);
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
        case 5:
            deleteAllExit();
        default:
        {
            std :: cout << "\nInvalid choice. Please try again.\n";
        }
    }
}

void sign_up() {
    std::string name;
    std::string ageStr;
    std::string regNO;
    std::string gender;
    std::string username;
    std::string password;
    std::string email;

    auto isValidName = [](const std::string& name) {
        return std::regex_match(name, std::regex("^[a-zA-Z ]+$"));
    };

    auto isValidAge = [](const std::string& age) {
        return std::regex_match(age, std::regex("^[1-9][0-9]*$"));
    };

    auto isValidRegNo = [](const std::string& regNo) {
        return std::regex_match(regNo, std::regex("^[a-zA-Z0-9]+$"));
    };

    auto isValidGender = [](const std::string& gender) {
        return (gender == "male" || gender == "female");
    };

    auto isValidUsername = [](const std::string& username) {
        return std::regex_match(username, std::regex("^[a-zA-Z0-9]+$"));
    };

    auto isValidPassword = [](const std::string& password) {
        return (password.length() >= 6);
    };

    auto isValidEmail = [](const std::string& email) {
        return std::regex_match(email, std::regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$"));
    };

    std::cout << "\nEnter your details:\n\n";

    do {
        std::cout << "Name: ";
        std::getline(std::cin, name);
        if (!isValidName(name)) {
            std::cout << "Please enter a valid name.\n\n";
        }
    } while (!isValidName(name));

    do {
        std::cout << "\nAge: ";
        std::getline(std::cin, ageStr);
        if (!isValidAge(ageStr)) {
            std::cout << "Please enter a valid age.\n\n";
        }
    } while (!isValidAge(ageStr));
    int age = std::stoi(ageStr);

    do {
        std::cout << "\nRegistration Number: ";
        std::getline(std::cin, regNO);
        if (!isValidRegNo(regNO)) {
            std::cout << "Please enter a valid registration number.\n\n";
        }
    } while (!isValidRegNo(regNO));

    do {
        std::cout << "\nGender(male/female): ";
        std::getline(std::cin, gender);
        if (!isValidGender(gender)) {
            std::cout << "Please enter a valid gender.\n\n";
        }
    } while (!isValidGender(gender));

    do {
        std::cout << "\nUsername: ";
        std::getline(std::cin, username);
        if (!isValidUsername(username)) {
            std::cout << "Please enter a valid username.\n\n";
        }
    } while (!isValidUsername(username));

    do {
        std::cout << "\nPassword: ";
        std::getline(std::cin, password);
        if (!isValidPassword(password)) {
            std::cout << "Please enter a valid password (at least 6 characters).\n\n";
        }
    } while (!isValidPassword(password));

    do {
        std::cout << "\nEmail: ";
        std::getline(std::cin, email);
        if (!isValidEmail(email)) {
            std::cout << "Please enter a valid email address.\n\n";
        }
    } while (!isValidEmail(email));

    new User(name, age, regNO, gender, username, password, email); 
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
            std::cout << "\nInvalid username or password.\n";
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
        std :: cout << "\n: ";
        int resp = getIntegerInput();
        // std :: cin.ignore(std  :: numeric_limits<std :: streamsize> :: max(), '\n');
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

void initialiseData()
{
    // to be changed to support file handling
    Venue :: addVenue("Anna Auditorium");
    Venue :: addVenue("Ambedkar Auditorium");
    Venue :: addVenue("SMV Front");
    User* user = new User("User Name", 21, "Reg123", "Male", "username", "password", "user@email.com");
    Organiser* organiser1 = new Organiser(*user, "NPTEL", "Host");
    new Conference("Sample Conference 1", DateTime ("12-04-2024", "08:00:00"), Venue("Anna Auditorium"), organiser1);
    Organiser* organiser2 = new Organiser(*user, "NPTEL", "Co-host");
    new Conference("Sample Conference 2", DateTime ("12-04-2024", "08:00:00"), Venue("Ambedkar Auditorium"), organiser2);

}
int main(void)
{
    initialiseData();
    page_1();
    deleteAllExit();

    return 0;
}
