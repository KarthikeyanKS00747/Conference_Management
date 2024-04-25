# Conference Management System

This project represents a console-based application for managing conferences, users, and venues with features like signing in, signing up, exploring conferences, organizing conferences, and more. It follows a modular structure with functions dedicated to specific tasks, enhancing code readability and maintainability.

## Steps to Run the Program

To install, build, and execute the `Conference.cpp` and `ConferenceManagementMain.cpp` files:

1. Place both files in your project directory.
2. Compile the `ConferenceManagementMain.cpp` file using your preferred C++ compiler and execute the resulting executable to run the program.

## Conference File

- **DateTime**: Represents a date and time with methods for parsing and displaying dates and times.
- **Venue**: Represents a venue for conferences, with methods for adding, deleting, and showing venues.
- **Conference**: Represents a conference with a specific date, time, venue, organisers, participants, sponsors, and generated amount. It has methods for organising, sponsoring, registering participants, and checking available time slots.
- **User**: Represents a user with basic information like name, age, registration number, gender, username, password, and email. It has methods for displaying user information, verifying login credentials, and updating user information.
- **Organiser**: Inherits from User and represents an organiser with additional information like organisation name and organiser title.
- **Participant**: Inherits from User and represents a participant with scheduled conferences and methods for scheduling and showing conferences.
- **Sponsor**: Inherits from User and represents a sponsor with information about the sponsored event and the sponsored amount.

## Main File

- **Function Declarations**: It starts with function declarations for `page_1()`, `page_2(User& user)`, `exploreConferences(User& user)`, and `createConferences(User& user)`. These functions handle different aspects of user interaction within the program.
- **Utility Functions**: Following the declarations are utility functions like `isDigits()` to check if a string consists of digits only, and `getIntegerInput()` to get integer input from the user.
- **Data Management Functions**: Functions like `deleteAllExit()` to clean up data and exit the program, and `initialiseData()` to set up initial data like venues and conferences.
- **User Interaction Functions**: Functions like `orgPortal()` to provide a portal for organizers, `exploreConferences()` to allow users to explore conferences and take actions like joining or organizing them, and `page_1()` which serves as the main menu for signing in, signing up, or exiting the program.
- **User Authentication**: `sign_in()` and `sign_up()` functions handle user authentication and registration respectively.
- **Main Function**: The `main()` function initializes data, presents the main menu, and handles program exit.
