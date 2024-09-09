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
using namespace std;

// Structure definition
struct userType {
    string username = "";
    string password = "";
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

// FUNCTION PROTOTYPES------------------------------------------------------------------------------------------------------------------------------------------------------
void newPageLogo();
void pauseEnter();

void mainMenu();
void aboutUsPage();

void registerPage();
bool checkUsernameAvailable(string username);

void customerLogin();
void customerPage();
void customerLogout();

bookingType* readBookingsFile(int& lenBookings);
bool checkBookingAvailable(int day, int timeslot, int expert);
void saveBookingToFile(bookingType newBooking);

void makeBooking();
int selectService();
int selectExpert();
int selectDate();
int selectTimeSlot();
int selectPaymentMode();
int getChoice(const vector<string>& options);
int autoAssignExpert();

void adminLogin();
void adminPage();
void adminLogout();

// GLOBAL CONSTANT & VARIABLES------------------------------------------------------------------------------------------------------------------------------------------------------
const string FILE_USERS = "user.dat";
const string FILE_BOOKINGS = "bookings.dat";
const string DAY[5] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
const string TIMESLOT[3] = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
const string EXPERT[3] = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
const string SERVICE[4] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation"};
const string PAYMENTMODE[3] = { "Credit Card", "Debit Card", "Cash" };
const double COST[4] = {25.00, 15.00, 80.00, 15.00};

string CURRENT_USERNAME = "";    //using to display username on customerPage when login successful

//------------------------------------------------------COMMON FUNCTIONS
// Create a new page by clearing the screen and displaying a logo on top
void newPageLogo() {
    system("cls"); // Use "clear" on Unix-like systems
    cout << "=================================================================================================================\n";
    cout << "|| ##     ##    ###    ##     ## ######## ##    ##     ######     ###    ##        #######   #######  ##    ## ||\n";
    cout << "|| ##     ##   ## ##   ##     ## ##       ###   ##    ##    ##   ## ##   ##       ##     ## ##     ## ###   ## ||\n";
    cout << "|| ##     ##  ##   ##  ##     ## ##       ####  ##    ##        ##   ##  ##       ##     ## ##     ## ####  ## ||\n";
    cout << "|| ######### ##     ## ##     ## ######   ## ## ##     ######  ##     ## ##       ##     ## ##     ## ## ## ## ||\n";
    cout << "|| ##     ## #########  ##   ##  ##       ##  ####          ## ######### ##       ##     ## ##     ## ##  #### ||\n";
    cout << "|| ##     ## ##     ##   ## ##   ##       ##   ###    ##    ## ##     ## ##       ##     ## ##     ## ##   ### ||\n";
    cout << "|| ##     ## ##     ##    ###    ######## ##    ##     ######  ##     ## ########  #######   #######  ##    ## ||\n";
    cout << "=================================================================================================================\n\n";
}

// Pause by prompting an input (use string & getline in case user typed in anything)
void pauseEnter() {
    char pause;
    cin.get(pause); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Ignore all characters up to the newline incase values are entered
}

//------------------------------------------------------MAIN MENU PAGE
void mainMenu() {
    // First Interface
    char option;
    newPageLogo();
    cout << "--------------------MAIN MENU--------------------\n";
    cout << "WELCOME TO HAVEN SALOON\n";
    cout << "Please choose your option.\n\n";
    // Main Menu options
    cout << "A\t: About Us\n";
    cout << "B\t: Customer Login\n";
    cout << "C\t: Register\n";
    cout << "D\t: Admin Login\n";
    cout << "E\t: Exit\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Ignore all characters up to the newline

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
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        mainMenu(); // Return to main menu for a retry
    }
}

//------------------------------------------------------ABOUT US PAGE
void aboutUsPage() {
    newPageLogo();
    cout << "--------------------------------------------------------------------------ABOUT US--------------------------------------------------------------------------\n";
    cout << "Welcome to Haven Saloon, where we provide a comfortable environment to experience and enjoy high-quality haircut services.\n";
    cout << "Our high-quality services are designed to ensure your satisfaction.\n\n";
    cout << "At Haven Saloon, our team of professional hairstylists has many years of experience and is committed to using the latest sustainable techniques and trends.\n";
    cout << "We are friendly and will listen to your needs to provide personalised advice, offering a range of stylish looks to meet your requirements.\n";
    cout << "Whether it's styling, colouring, or shampooing, we use high-quality products to ensure the best results.\n\n";
    cout << "Experience the warm and friendly atmosphere at Haven Saloon and let us provide you with caring service. We strive to make every visit a relaxing and enjoyable experience.\n\n";
    cout << "Enter any key to return to the main menu:\t";
    pauseEnter();
    mainMenu();
}


//------------------------------------------------------USERS FILE
// Check if username met in registration
bool checkUsernameAvailable(string username) {
    userType users[100];

    ifstream infile(FILE_USERS);
    if (!infile) {
        cout << "\n\nUnable to login currently due to system error\nPress enter to return to main menu\t";
        pauseEnter();
        mainMenu();
    }

    string record;
    int counter = 0;
    while (getline(infile, record)) {
        stringstream ss(record);
        string username, password;
        userType user;

        getline(ss, username, ',');
        getline(ss, password, ',');

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
    string record = new_user.username + ',' + new_user.password;
    cout << record << endl;  // Display the record for debugging

    ofstream outFile(FILE_USERS, ios::app); // Open file in append mode

    if (!outFile) {
        cout << "Sorry, an error occurred while opening the file.";
        return;
    }

    // Write the new user's data to the file
    outFile << record << "\n";  // Add a newline after the record
    outFile.close();
}


//------------------------------------------------------CUSTOMERS REGISTER
void registerPage() {
    newPageLogo();
    // Read file
    bool loop = true;
    do {
        newPageLogo();
        string inputUsername = "", inputPassword = "", inputPassword2;
        cout << "Enter a new username:\t\t";
        getline(cin, inputUsername);
        cout << "\nEnter a new password:\t\t";
        getline(cin, inputPassword);
        cout << "\nEnter the new password again:\t";
        getline(cin, inputPassword2);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        */

        if (checkUsernameAvailable(inputUsername)) {
            if (inputPassword == inputPassword2) {
                userType new_user = { inputUsername, inputPassword };
                addNewUserToFile(new_user);
                CURRENT_USERNAME = inputUsername;
                cout << "\n\nRegistred successful\nPress enter to continue\t";
                loop = false;
                pauseEnter();
                customerPage();
                return;
            }
            else {
                char option;
                cout << "\n\nBoth password do not match\nDo you wish to continue? (Y/N):\t";
                cin >> option;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loop = (toupper(option) == 'Y') ? true : false;
            }

        }
        else {
            char option;
            cout << "\n\nUsername taken\nDo you wish to continue? (Y/N):\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();

}

//------------------------------------------------------CUSTOMERS LOGIN
void customerLogin() {
    newPageLogo();
    // Read file
    userType users[100];

    ifstream infile(FILE_USERS);
    if (!infile) {
        cout << "\n\nUnable to login currently due to system error\nPress enter to return to main menu\t";
        pauseEnter();
        mainMenu();
    }
    // Get list of all records
    string record;
    int counter = 0;
    while (getline(infile, record)) {
        stringstream ss(record);
        string username, password;
        userType user;

        getline(ss, username, ',');
        getline(ss, password, ',');

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
        string inputUsername = "", inputPassword = "";
        cout << "Enter your username:\t";
        getline(cin, inputUsername);
        cout << "\nEnter your password:\t";
        getline(cin, inputPassword);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            cout << '*';
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
            cout << "\n\nAccess granted\nPress enter to continue\t";
            CURRENT_USERNAME = inputUsername; //display username on customerPage()
            loop = false;
            pauseEnter();
            customerPage();
            return;
        }
        else {
            char option;
            cout << "\n\nAccess denied\nDo you wish to retry? (Y/N):\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();
}


//------------------------------------------------------BOOKINGS FILE
// Read bookings from the file
bookingType* readBookingsFile(int& lenBookings) {
    static bookingType bookings[100]; // Store up to 100 bookings

    ifstream infile(FILE_BOOKINGS);
    if (!infile) {
        cout << "\n\nUnable to make booking currently due to system error\nPress enter to return to main menu\t";
        lenBookings = 0; // Set length to 0 if there's an error
        return nullptr;  // Return nullptr to indicate an error
    }

    string record;
    int counter = 0;

    while (getline(infile, record)) {
        stringstream ss(record);
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
        if (bookingsArray[i].day == day && bookingsArray[i].timeslot == timeslot && bookingsArray[i].expert == expert) {
            return false; // Booking is already taken
        }
    }

    return true; // Booking is available
}

// Save the booking information to file
void saveBookingToFile(bookingType newBooking) {
    ofstream outFile(FILE_BOOKINGS, ios::app);

    if (!outFile) {
        cout << "Sorry, an error occurred while saving the booking.";
        return;
    }

    outFile << newBooking.day << ","
        << newBooking.timeslot << ","
        << newBooking.expert << ","
        << newBooking.service << ","
        << fixed << setprecision(2)
        << newBooking.cost << ","
        << newBooking.payment_mode << "\n";
    outFile.close();
}


//------------------------------------------------------CUSTOMERS INTERFACE
// Customer Main Page
void customerPage() {
    char option;
    newPageLogo();
    cout << "--------CUSTOMER HOMEPAGE--------\n";
    cout << "Welcome " << CURRENT_USERNAME << endl;
    cout << "Please choose your option.\n";

    cout << "A\t: View Service\n";
    cout << "B\t: View Expert\n";
    cout << "C\t: Make Booking\n";
    cout << "D\t: My bookings\n";
    cout << "E\t: View Schedule\n";
    cout << "F\t: Feedback Form\n";
    cout << "G\t: Log Out and Return to Main Menu\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        cout << "--------OUR SERVICE--------\n";
        cout << "1. Hair Cut\n";
        cout << "2. Hair Wash\n";
        cout << "3. Hair Dying\n\n";
        cout << "Press enter to return:\t";
        pauseEnter();
        customerPage();
        break;
    case 'B': case 'b':
        newPageLogo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Press enter to return\t";
        pauseEnter();
        customerPage();
    case 'C': case 'c':
        makeBooking();
        break;
    case 'D': case 'd':
        cout << "You chose an option of My bookings\n";
        break;
    case 'E': case 'e':
        cout << "You chose an option of View Schedule\n";
        break;
    case 'F': case 'f':
        cout << "You chose an option of Feedback Form\n";
        break;
    case 'G': case 'g':
        customerLogout();
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        customerPage(); // Return to customer login for a retry
    }
}

// Ask confirm logout and go to main menu
void customerLogout() {
    char confirmLogout = 'Y';
    cout << "\nDo you wish to log out? (Y/N):\t";
    cin >> confirmLogout;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        customerPage();
    }
}

//For the customer menu interface
int getChoice(const vector<string>& options) {
    int choice;
    for (int i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > options.size()) {
        cout << "Invalid choice. Please enter a number between 1 and " << options.size() << ": ";
    }
    return choice;
}

// Customer > Make Booking > Select Service
int selectService() {
    newPageLogo();
    vector<string> services = { "Hair Cut", "Hair Wash", "Hair Dying" };
    cout << "--------SELECT A SERVICE--------\n";
    int choice = getChoice(services);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert
int selectExpert() {
    newPageLogo();
    vector<string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };
    cout << "--------SELECT AN EXPERT--------\n";
    int choice = getChoice(experts);
    if (choice == 4) {
        return autoAssignExpert();
    }
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert (random assign expert function)
int autoAssignExpert() {
    vector<string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
    srand(time(0));
    int index = rand() % experts.size();
    return index;
}

// Customer > Make Booking > Select Service > Select Date >Select Expert
int selectDate() {
    newPageLogo();
    vector<string> date = { "Monday", "Tuesday", "Wednesday" , "Thursday" , "Friday" };
    cout << "--------SELECT A RESERVATION DATE--------\n";
    int choice = getChoice(date);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot
int selectTimeSlot() {
    newPageLogo();
    vector<string> timeSlots = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
    //cout << "Available time slots for a " << serviceDuration << "-hour service:\n";
    cout << "--------SELECT A TIME SLOT--------\n";
    int availableSlots = timeSlots.size();

    for (int i = 0; i < availableSlots; ++i) {
        cout << i + 1 << ". " << timeSlots[i] << endl;
    }

    int choice;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > availableSlots) {
        cout << "Invalid choice. Please enter a number between 1 and " << availableSlots << ": ";
    }

    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot > Select Payment Mode
int selectPaymentMode() {
    newPageLogo();
    vector<string> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    cout << "--------SELECT A PAYMENT MODE--------\n";
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
    //cout << bool;

    if (available) {
        char confirm;
        //newPageLogo();
        cout << "Booking Summary:\n";
        cout << "\nDay:\t\t" << DAY[date];
        cout << "\nTime Slot\t" << TIMESLOT[timeSlot];
        cout << "\nService:\t" << SERVICE[service];
        cout << "\nExpert:\t\t" << EXPERT[expert];
        cout << "\nCost:\t\t" << COST[service];
        cout << "\nPayment Method:\t" << PAYMENTMODE[paymentMode];
        cout << "\n\nConfirm your booking (Y/N): ";
        cin >> confirm;

        if (confirm == 'Y' || confirm == 'y') {
            //createBooking(date, timeSlot, expert, service, paymentMode);
            bookingType newBooking = { date, timeSlot, expert, service, COST[service], paymentMode};
            saveBookingToFile(newBooking);
            cout << "Your booking has been confirmed!\n";
        }
        else {
            cout << "Booking canceled.\n";
        }
    }
    else {
        cout << "Sorry, the selected slot is not available.\n";
    }
    pauseEnter();
    customerPage();
}

//------------------------------------------------------ADMIN LOGIN
void adminLogin() {
    bool loop = true;
    do {
        newPageLogo();
        cout << "\nADMIN LOGIN";
        string inputUsername = "", inputPassword = "";
        cout << "\nEnter your username:\t";
        getline(cin, inputUsername);
        cout << "\nEnter your password:\t";
        getline(cin, inputPassword);
        /*
        char ch;
        ch = _getch();
        while (ch != 13) {//character 13 is enter
            inputPassword.push_back(ch);
            cout << '*';
            ch = _getch();
        }
        */
        if (inputUsername == "havensadmin" && inputPassword == "haven1234") {
            cout << "\n\nAccess granted\nPress enter to continue\t";
            CURRENT_USERNAME = inputUsername;
            loop = false;
            pauseEnter();
            adminPage();
            return;
        }
        else {
            char option;
            cout << "\n\nAccess denied\nDo you wish to retry? (Y/N):\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();
}

//------------------------------------------------------ADMIN INTERFACE
void adminPage() {
    char option;
    newPageLogo();
    cout << "--------ADMIN HOMEPAGE--------\n";
    cout << "Welcome " << CURRENT_USERNAME << endl;
    cout << "Please choose your option.\n";

    cout << "A\t: View Customer\n";
    cout << "B\t: View Sales Record\n";
    cout << "C\t: View Schedule\n";
    cout << "D\t: Log Out and Return to Main Menu\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        cout << "You choose view customer!";
        break;
    case 'B': case 'b':
        newPageLogo();
        cout << "You choose view sales record";
    case 'C': case 'c':
        newPageLogo();
        cout << "you choose view schedule";
        break;
    case 'D': case 'd':
        adminLogout();
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        adminPage(); // Return to admin page for a retry
    }
}

// Ask confirm logout and go to main menu
void adminLogout() {
    char confirmLogout = 'Y';
    cout << "\nDo you wish to log out? (Y/N):\t";
    cin >> confirmLogout;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        adminPage();
    }
}


//------------------------------------------------------RUN PROGRAM
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