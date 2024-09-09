#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
//#include <conio.h>
//using namespace std;

// Structure definition
struct userType {
    std::string username = "";
    std::string password = "";
    bool admin = 0;
};

struct bookingType {
    int day = 0;
    int timeslot = 0;
    int expert = 0;
    int service = 0;
    double cost = 0.0;
    int payment_mode = 0;
};

// Function prototypes
void newPageLogo();
void pauseEnter();

void mainMenu();
void aboutUsPage();

void registerPage();
bool checkUsernameAvailable(std::string username);

void customerLogin();
void customerPage();
void customerLogout();

void makeBooking();
int selectService();
int selectExpert();
int selectDate();
int selectTimeSlot();
int selectPaymentMode();
int getChoice(const std::vector<std::string>& options);
int autoAssignExpert();

bookingType* readBookingsFile(int& lenBookings);
bool checkBookingAvailable(int day, int timeslot, int expert);
void saveBookingToFile(bookingType newBooking);


void adminLogin();
void adminPage();
void adminLogout();

// Global variables & constants (if any)
const std::string FILE_USERS = "user.dat";
const std::string FILE_BOOKINGS = "bookings.dat";
std::string CURRENT_USERNAME = "";    //using to display username on customerPage when login successful
std::string DAY[5] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
std::string TIMESLOT[3] = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
std::string EXPERT[3] = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
std::string SERVICE[4] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation"};
std::string PAYMENTMODE[3] = { "Credit Card", "Debit Card", "Cash" };
double COST[4] = {25.00, 15.00, 80.00, 15.00};

// Create a new page by clearing the screen and displaying a logo on top
void newPageLogo() {
    system("cls"); // Use "clear" on Unix-like systems
    std::cout << "=================================================================================================================\n";
    std::cout << "|| ##     ##    ###    ##     ## ######## ##    ##     ######     ###    ##        #######   #######  ##    ## ||\n";
    std::cout << "|| ##     ##   ## ##   ##     ## ##       ###   ##    ##    ##   ## ##   ##       ##     ## ##     ## ###   ## ||\n";
    std::cout << "|| ##     ##  ##   ##  ##     ## ##       ####  ##    ##        ##   ##  ##       ##     ## ##     ## ####  ## ||\n";
    std::cout << "|| ######### ##     ## ##     ## ######   ## ## ##     ######  ##     ## ##       ##     ## ##     ## ## ## ## ||\n";
    std::cout << "|| ##     ## #########  ##   ##  ##       ##  ####          ## ######### ##       ##     ## ##     ## ##  #### ||\n";
    std::cout << "|| ##     ## ##     ##   ## ##   ##       ##   ###    ##    ## ##     ## ##       ##     ## ##     ## ##   ### ||\n";
    std::cout << "|| ##     ## ##     ##    ###    ######## ##    ##     ######  ##     ## ########  #######   #######  ##    ## ||\n";
    std::cout << "=================================================================================================================\n\n";
}

// Pause by prompting an input (use std::string & std::getline in case user typed in anything)
void pauseEnter() {
    char pause;
    std::cin.get(pause); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // Ignore all characters up to the newline incase values are entered
}

// Menu page
void mainMenu() {
    // First Interface
    char option;
    newPageLogo();
    std::cout << "--------------------MAIN MENU--------------------\n";
    std::cout << "WELCOME TO HAVEN SALOON\n";
    std::cout << "Please choose your option.\n\n";
    // Main Menu options
    std::cout << "A\t: About Us\n";
    std::cout << "B\t: Customer Login\n";
    std::cout << "C\t: Register\n";
    std::cout << "D\t: Admin Login\n";
    std::cout << "E\t: Exit\n\n";

    std::cout << "Enter your choice:\t";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // Ignore all characters up to the newline

    switch (option) {
    case 'A': case 'a':
        aboutUsPage();
        break;
    case 'B': case 'b':
        customerLogin();
        break;
    case 'C': case 'c':
        registerPage();
        break;
    case 'D': case 'd':
        adminLogin();
        break;
    case 'E': case 'e':
        break;
    default:
        std::cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        mainMenu(); // Return to main menu for a retry
    }
}

// About Us Page
void aboutUsPage() {
    newPageLogo();
    std::cout << "--------------------------------------------------------------------------ABOUT US--------------------------------------------------------------------------\n";
    std::cout << "Welcome to Haven Saloon, where we provide a comfortable environment to experience and enjoy high-quality haircut services.\n";
    std::cout << "Our high-quality services are designed to ensure your satisfaction.\n\n";
    std::cout << "At Haven Saloon, our team of professional hairstylists has many years of experience and is committed to using the latest sustainable techniques and trends.\n";
    std::cout << "We are fristd::endly and will listen to your needs to provide personalised advice, offering a range of stylish looks to meet your requirements.\n";
    std::cout << "Whether it's styling, colouring, or shampooing, we use high-quality products to ensure the best results.\n\n";
    std::cout << "Experience the warm and fristd::endly atmosphere at Haven Saloon and let us provide you with caring service. We strive to make every visit a relaxing and enjoyable experience.\n\n";
    std::cout << "Enter any key to return to the main menu:\t";
    pauseEnter();
    mainMenu();
}


// USER FILE READ/WRITE------------------------------------------------------------------------------------------------------------------------------------------------------
// Check if username met in registration
bool checkUsernameAvailable(std::string username) {
    userType users[100];

    std::ifstream infile(FILE_USERS);
    if (!infile) {
        std::cout << "\n\nUnable to login currently due to system error\nPress enter to return to main menu\t";
        pauseEnter();
        mainMenu();
    }

    std::string record;
    int counter = 0;
    while (std::getline(infile, record)) {
        std::stringstream ss(record);
        std::string username, password;
        userType user;

        std::getline(ss, username, ',');
        std::getline(ss, password, ',');

        user.username = username;
        user.password = password;

        users[counter] = user;
        counter++;
    }
    infile.close();

    for (int i = 0; i < counter; i++) {
        if (username == users[i].username) {
            return false;
        }
    }
    return true;
}

// Add user.username & user.password to savefile
void addNewUserToFile(userType new_user) {
    // Create a record in CSV-like format
    std::string record = new_user.username + ',' + new_user.password;
    std::cout << record << std::endl;  // Display the record for debugging

    std::ofstream outFile(FILE_USERS, std::ios::app); // Open file in append mode

    if (!outFile) {
        std::cout << "Sorry, an error occurred while opening the file.";
        return;
    }

    // Write the new user's data to the file
    outFile << record << "\n";  // Add a newline after the record
    outFile.close();
}


// CUSTOMER LOGIN/REGISTRATION------------------------------------------------------------------------------------------------------------------------------------------------------
// User (customer) Registration Page
void registerPage() {
    newPageLogo();
    // Read file
    bool loop = true;
    do {
        newPageLogo();
        std::string inputUsername = "", inputPassword = "", inputPassword2;
        std::cout << "Enter a new username:\t\t";
        std::getline(std::cin, inputUsername);
        std::cout << "\nEnter a new password:\t\t";
        std::getline(std::cin, inputPassword);
        std::cout << "\nEnter the new password again:\t";
        std::getline(std::cin, inputPassword2);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            std::cout << '*';
            ch = _getch();
        }
        */

        if (checkUsernameAvailable(inputUsername)) {
            if (inputPassword == inputPassword2) {
                userType new_user = { inputUsername, inputPassword };
                addNewUserToFile(new_user);
                CURRENT_USERNAME = inputUsername;
                std::cout << "\n\nRegistred successful\nPress enter to continue\t";
                loop = false;
                pauseEnter();
                customerPage();
                return;
            }
            else {
                char option;
                std::cout << "\n\nBoth password do not match\nDo you wish to continue? (Y/N):\t";
                std::cin >> option;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                loop = (toupper(option) == 'Y') ? true : false;
            }

        }
        else {
            char option;
            std::cout << "\n\nUsername taken\nDo you wish to continue? (Y/N):\t";
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();

}

// Customer Login Page
void customerLogin() {
    newPageLogo();
    // Read file
    userType users[100];

    std::ifstream infile(FILE_USERS);
    if (!infile) {
        std::cout << "\n\nUnable to login currently due to system error\nPress enter to return to main menu\t";
        pauseEnter();
        mainMenu();
    }
    // Get list of all records
    std::string record;
    int counter = 0;
    while (std::getline(infile, record)) {
        std::stringstream ss(record);
        std::string username, password;
        userType user;

        std::getline(ss, username, ',');
        std::getline(ss, password, ',');

        user.username = username;
        user.password = password;

        users[counter] = user;
        counter++;
    }
    infile.close();

    bool recordFound = false;
    bool loop = true;
    do {
        newPageLogo();
        std::string inputUsername = "", inputPassword = "";
        std::cout << "Enter your username:\t";
        std::getline(std::cin, inputUsername);
        std::cout << "\nEnter your password:\t";
        std::getline(std::cin, inputPassword);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            std::cout << '*';
            ch = _getch();
        }
        */

        // Check if username and password are in the record
        for (int i = 0; i < counter; i++) {
            if (inputUsername == users[i].username && inputPassword == users[i].password) {
                recordFound = true;
                break;
            }
        }
        if (recordFound) {
            std::cout << "\n\nAccess granted\nPress enter to continue\t";
            CURRENT_USERNAME = inputUsername; //display username on customerPage()
            loop = false;
            pauseEnter();
            customerPage();
            return;
        }
        else {
            char option;
            std::cout << "\n\nAccess denied\nDo you wish to retry? (Y/N):\t";
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();
}


//bookingType createBooking(int date, int timeslot, int expert, int service, int paymentMode) {}

// BOOKINGS FILE READ/WRITE------------------------------------------------------------------------------------------------------------------------------------------------------
// Read bookings from the file
bookingType* readBookingsFile(int& lenBookings) {
    static bookingType bookings[100]; // Store up to 100 bookings

    std::ifstream infile(FILE_BOOKINGS);
    if (!infile) {
        std::cout << "\n\nUnable to make booking currently due to system error\nPress enter to return to main menu\t";
        lenBookings = 0; // Set length to 0 if there's an error
        return nullptr;  // Return nullptr to indicate an error
    }

    std::string record;
    int counter = 0;

    while (std::getline(infile, record)) {
        std::stringstream ss(record);
        bookingType booking;

        // Extract integers for day, timeslot, expert, and service
        ss >> booking.day;
        ss.ignore(1);  // Skip the comma
        ss >> booking.timeslot;
        ss.ignore(1);  // Skip the comma
        ss >> booking.expert;
        ss.ignore(1);  // Skip the comma
        ss >> booking.service;
        ss.ignore(1);  // Skip the comma

        // Extract the cost as a float
        ss >> booking.cost;
        ss.ignore(1);  // Skip the comma

        // Extract payment_mode as an integer
        ss >> booking.payment_mode;

        bookings[counter] = booking;
        counter++;

        if (counter >= 100) {
            break; // Prevent overflow if too many records
        }
    }
    infile.close();
    lenBookings = counter; // Update the number of bookings read / length of array
    return bookings;
}

// Check if booking is available based on day, timeslot, and expert
bool checkBookingAvailable(int day, int timeslot, int expert) {
    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr) {
        return false;  // Handle error
    }

    // Check if the booking is available
    for (int i = 0; i < lenBookings; i++) {
        std::cout << bookingsArray[i].day << "\t" << bookingsArray[i].timeslot << "\t" << bookingsArray[i].expert << "\t" << bookingsArray[i].service << "\t" << bookingsArray[i].cost << "\t" << bookingsArray[i].payment_mode;
        if (bookingsArray[i].day == day && bookingsArray[i].timeslot == timeslot && bookingsArray[i].expert == expert) {
            return false; // Booking is already taken
        }
    }

    return true; // Booking is available
}

// Save the booking information to file
void saveBookingToFile(bookingType newBooking) {
    std::ofstream outFile(FILE_BOOKINGS, std::ios::app);

    if (!outFile) {
        std::cout << "Sorry, an error occurred while saving the booking.";
        return;
    }

    outFile << newBooking.day << ","
        << newBooking.timeslot << ","
        << newBooking.expert << ","
        << newBooking.service << ","
        << std::fixed << std::setprecision(2)
        << newBooking.cost << ","
        << newBooking.payment_mode << "\n";
    outFile.close();
}


// CUSTOMERS' INTERFACE----------------------------------------------------------------------------------------------------------------------------------------------
// Customer Main Page
void customerPage() {
    char option;
    newPageLogo();
    std::cout << "--------CUSTOMER HOMEPAGE--------\n";
    std::cout << "Welcome " << CURRENT_USERNAME << std::endl;
    std::cout << "Please choose your option.\n";

    std::cout << "A\t: View Service\n";
    std::cout << "B\t: View Expert\n";
    std::cout << "C\t: Make Booking\n";
    std::cout << "D\t: My bookings\n";
    std::cout << "E\t: View Schedule\n";
    std::cout << "F\t: Feedback Form\n";
    std::cout << "G\t: Log Out and Return to Main Menu\n\n";

    std::cout << "Enter your choice:\t";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        std::cout << "--------OUR SERVICE--------\n";
        std::cout << "1. Hair Cut\n";
        std::cout << "2. Hair Wash\n";
        std::cout << "3. Hair Dying\n\n";
        std::cout << "Press enter to return:\t";
        pauseEnter();
        customerPage();
        break;
    case 'B': case 'b':
        newPageLogo();
        std::cout << "--------OUR EXPERT--------\n";
        std::cout << "1. Alice Wong\n";
        std::cout << "2. Bernice Lim\n";
        std::cout << "3. Catherine Tan\n\n";
        std::cout << "Press enter to return\t";
        pauseEnter();
        customerPage();
    case 'C': case 'c':
        makeBooking();
        break;
    case 'D': case 'd':
        std::cout << "You chose an option of My bookings\n";
        break;
    case 'E': case 'e':
        std::cout << "You chose an option of View Schedule\n";
        break;
    case 'F': case 'f':
        std::cout << "You chose an option of Feedback Form\n";
        break;
    case 'G': case 'g':
        customerLogout();
        break;
    default:
        std::cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        customerPage(); // Return to customer login for a retry
    }
}

// Ask confirm logout and go to main menu
void customerLogout() {
    char confirmLogout = 'Y';
    std::cout << "\nDo you wish to log out? (Y/N):\t";
    std::cin >> confirmLogout;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        customerPage();
    }
}

//For the customer menu interface
int getChoice(const std::vector<std::string>& options) {
    int choice;
    for (int i = 0; i < options.size(); ++i) {
        std::cout << i + 1 << ". " << options[i] << std::endl;
    }
    std::cout << "Enter your choice: ";
    while (!(std::cin >> choice) || choice < 1 || choice > options.size()) {
        std::cout << "Invalid choice. Please enter a number between 1 and " << options.size() << ": ";
    }
    return choice;
}

//Define the service duration
/*int getServiceDuration(const int& service) {
    if (service == 1 || service == 2 || service == 3) {
        return 2; // Duration in hours
    }
    else if (service == 4) {
        return 1; // Duration in hours
    }
    return 1;
}*/

// Customer > Make Booking > Select Service
int selectService() {
    newPageLogo();
    std::vector<std::string> services = { "Hair Cut", "Hair Wash", "Hair Dying" };
    std::cout << "--------SELECT A SERVICE--------\n";
    int choice = getChoice(services);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert
int selectExpert() {
    newPageLogo();
    std::vector<std::string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };
    std::cout << "--------SELECT AN EXPERT--------\n";
    int choice = getChoice(experts);
    if (choice == 4) {
        return autoAssignExpert();
    }
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert (random assign expert function)
int autoAssignExpert() {
    std::vector<std::string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
    srand(time(0));
    int index = rand() % experts.size();
    return index;
}

// Customer > Make Booking > Select Service > Select Date >Select Expert
int selectDate() {
    newPageLogo();
    std::vector<std::string> date = { "Monday", "Tuesday", "Wednesday" , "Thursday" , "Friday" };
    std::cout << "--------SELECT A RESERVATION DATE--------\n";
    int choice = getChoice(date);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot
//int selectTimeSlot(int serviceDuration) {
int selectTimeSlot() {
    newPageLogo();
    std::vector<std::string> timeSlots = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
    //std::cout << "Available time slots for a " << serviceDuration << "-hour service:\n";
    std::cout << "--------SELECT A TIME SLOT--------\n";
    int availableSlots = timeSlots.size();
    /*
    if (serviceDuration == 2) {
        // Remove the last slot for services that take 2 hours
        availableSlots--;
    }
    */

    for (int i = 0; i < availableSlots; ++i) {
        std::cout << i + 1 << ". " << timeSlots[i] << std::endl;
    }

    int choice;
    std::cout << "Enter your choice: ";
    while (!(std::cin >> choice) || choice < 1 || choice > availableSlots) {
        std::cout << "Invalid choice. Please enter a number between 1 and " << availableSlots << ": ";
    }

    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot > Select Payment Mode
int selectPaymentMode() {
    newPageLogo();
    std::vector<std::string> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    std::cout << "--------SELECT A PAYMENT MODE--------\n";
    int choice = getChoice(paymentModes);
    return choice - 1;
}

// Customer > Make Booking
void makeBooking() {
    int service, expert, date, timeSlot, paymentMode;
    //int serviceDuration;

    service = selectService();
    //serviceDuration = getServiceDuration(service);
    expert = selectExpert();
    date = selectDate();
    timeSlot = selectTimeSlot();
    //timeSlot = selectTimeSlot(serviceDuration);
    paymentMode = selectPaymentMode();

    bool available = checkBookingAvailable(date, timeSlot, expert);
    //std::cout << bool;

    if (available) {
        char confirm;
        //newPageLogo();
        std::cout << "Booking Summary:\n";
        std::cout << "\nDay:\t\t" << DAY[date];
        std::cout << "\nTime Slot\t" << TIMESLOT[timeSlot];
        std::cout << "\nService:\t" << SERVICE[service];
        std::cout << "\nExpert:\t\t" << EXPERT[expert];
        std::cout << "\nCost:\t\t" << COST[service];
        std::cout << "\nPayment Method:\t" << PAYMENTMODE[paymentMode];
        std::cout << "\n\nConfirm your booking (Y/N): ";
        std::cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            //createBooking(date, timeSlot, expert, service, paymentMode);
            bookingType newBooking = { date, timeSlot, expert, service, COST[service], paymentMode};
            saveBookingToFile(newBooking);
            std::cout << "Your booking has been confirmed!\n";
        }
        else {
            std::cout << "Booking canceled.\n";
        }
    }
    else {
        std::cout << "Sorry, the selected slot is not available.\n";
    }
    pauseEnter();
    customerPage();
}

// ADMIN----------------------------------------------------------------------------------------------------------------------------------------------
// Admin Login Page
void adminLogin() {
    bool loop = true;
    do {
        newPageLogo();
        std::cout << "\nADMIN LOGIN";
        std::string inputUsername = "", inputPassword = "";
        std::cout << "\nEnter your username:\t";
        std::getline(std::cin, inputUsername);
        std::cout << "\nEnter your password:\t";
        std::getline(std::cin, inputPassword);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            std::cout << '*';
            ch = _getch();
        }
        */
        if (inputUsername == "havensadmin" && inputPassword == "haven1234") {
            std::cout << "\n\nAccess granted\nPress enter to continue\t";
            CURRENT_USERNAME = inputUsername;
            loop = false;
            pauseEnter();
            adminPage();
            return;
        }
        else {
            char option;
            std::cout << "\n\nAccess denied\nDo you wish to retry? (Y/N):\t";
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();
}

// Admin Interface
// Admin Interface
void adminPage() {
    char option;
    newPageLogo();
    std::cout << "--------ADMIN HOMEPAGE--------\n";
    std::cout << "Welcome " << CURRENT_USERNAME << std::endl;
    std::cout << "Please choose your option.\n";

    std::cout << "A\t: View Customer\n";
    std::cout << "B\t: View Sales Record\n";
    std::cout << "C\t: View Schedule\n";
    std::cout << "D\t: Log Out and Return to Main Menu\n\n";

    std::cout << "Enter your choice:\t";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        std::cout << "You choose view customer!";
        break;
    case 'B': case 'b':
        newPageLogo();
        std::cout << "You choose view sales record";
    case 'C': case 'c':
        newPageLogo();
        std::cout << "you choose view schedule";
        break;
    case 'D': case 'd':
        adminLogout();
        break;
    default:
        std::cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        adminPage(); // Return to admin page for a retry
    }
}

// Ask confirm logout and go to main menu
void adminLogout() {
    char confirmLogout = 'Y';
    std::cout << "\nDo you wish to log out? (Y/N):\t";
    std::cin >> confirmLogout;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        adminPage();
    }
}


// MAIN PROGRAM STARTS HERE----------------------------------------------------------------------------------------------------------------------------------------------
int main() {
    mainMenu(); // Start the menu
    return 0;
}


//user.dat (put in the same directory as the cpp file)
/*
ykliang,yk123
qxwong,qx456
wssoh,ws789
zqwang,zq000

*/

//bookings.dat (put in the same directory as the cpp file)
/*
1,1,1,1,25.00,1
1,2,2,3,80.00,2

*/

// *The \n under last record is necessary!