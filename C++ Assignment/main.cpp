//OVERALL CODE
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

//#include <conio.h>
using namespace std;
#include <array>

// Structure definition
struct userType {
    string username = "";
    string password = "";
    bool admin = 0;
};

struct bookingType {
    string customerName;
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
void customerPage(string username, string currentPassword);
void customerLogout(string username, string currentPassword);
void mybookingsDetail(string username, string currentPassword);
void viewReceipt(string username, bookingType* bookingsArray, int* bookingIndices, int bookingCount);
void cancelBooking(string username, string currentPassword, bookingType* bookingsArray, int lenBookings, int* bookingIndices, int bookingCount);
void viewTimeslotAvailable(string username, string currentPassword);
void feedbackForm(string username, string currentPassword);

bookingType* readBookingsFile(int& lenBookings);
bool checkBookingAvailable(int day, int timeslot, int expert, bool isConsultation);
void saveBookingToFile(bookingType newBooking);

void makeBooking(string username, string currentPassword);
int selectService();
int selectExpert(int day, int timeslot, bool isConsultation);
int selectDate();
int selectTimeSlot();
int selectPaymentMode();
int autoAssignExpert(int day, int timeslot, bool isConsultation);
void generateReceipt(const bookingType& booking);

void adminLogin();
void adminPage(string username);
void adminLogout(string username);
void viewCustomerBookings(string username);
void viewSalesRecord(string username);
void viewExpertSchedule(string username);
void viewFeedbackForm(string username);

// GLOBAL CONSTANT & VARIABLES------------------------------------------------------------------------------------------------------------------------------------------------------
const string FILE_USERS = "user.dat";
const string FILE_BOOKINGS = "bookings.dat";
const string DAY[5] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
const string TIMESLOT[3] = { "10:00AM - 12:00PM", "2:00PM - 4:00PM", "4:00PM - 6:00PM" };
const string TIMESLOT_CONSULT[6] = { "10:00AM - 11:00AM", "11:00AM - 12:00PM", "2:00PM - 3:00PM", "3:00PM - 4:00PM" , "4:00PM - 5:00PM", "5:00PM - 6:00PM" };
const string EXPERT[3] = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
const string SERVICE[4] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation" };
const string PAYMENTMODE[3] = { "Credit Card", "Debit Card", "Cash" };
const double COST[4] = { 25.00, 15.00, 80.00, 15.00 };

//------------------------------------------------------COMMON FUNCTIONS
// Create a new page by clearing the screen and displaying a logo on top
void newPageLogo() {
    system("cls"); // Use "clear" on Unix-like systems

    // Start with the desired color
    cout << GREEN; // You can choose any color you like

    cout << "=================================================================================================================\n";
    cout << "|| ##     ##    ###    ##     ## ######## ##    ##     ######     ###    ##        #######   #######  ##    ## ||\n";
    cout << "|| ##     ##   ## ##   ##     ## ##       ###   ##    ##    ##   ## ##   ##       ##     ## ##     ## ###   ## ||\n";
    cout << "|| ##     ##  ##   ##  ##     ## ##       ####  ##    ##        ##   ##  ##       ##     ## ##     ## ####  ## ||\n";
    cout << "|| ######### ##     ## ##     ## ######   ## ## ##     ######  ##     ## ##       ##     ## ##     ## ## ## ## ||\n";
    cout << "|| ##     ## #########  ##   ##  ##       ##  ####          ## ######### ##       ##     ## ##     ## ##  #### ||\n";
    cout << "|| ##     ## ##     ##   ## ##   ##       ##   ###    ##    ## ##     ## ##       ##     ## ##     ## ##   ### ||\n";
    cout << "|| ##     ## ##     ##    ###    ######## ##    ##     ######  ##     ## ########  #######   #######  ##    ## ||\n";
    cout << "=================================================================================================================\n\n";

    // Reset to default color
    cout << RESET;
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
    newPageLogo();;
    cout << CYAN << "----------------------------------------MAIN MENU---------------------------------------------------" << RESET << endl;
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
        exit(0);
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

    // Print the header in magenta
    cout << MAGENTA << "---------------------------------------------------------ABOUT US----------------------------------------------------------------\n" << RESET;

    ifstream aboutUsFile("aboutUs.txt");

    if (!aboutUsFile) {
        cerr << "Error: Could not open aboutUs.txt" << endl;
        return;
    }

    // read files
    string line;
    cout << MAGENTA;
    while (getline(aboutUsFile, line)) {
        cout << line << endl;
    }
    cout << RESET;

    // close files
    aboutUsFile.close();

    cout << "Press Enter to return:\t";
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

//Validation Register username and password
bool isValidUsername(const string& username) {
    if (username.length() < 5 || username.length() > 20) {
        return false;
    }

    for (char ch : username) {
        if (!((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))) {
            return false;
        }
    }

    return true;
}

bool isValidPassword(const string& password) {
    return password.length() >= 8 && password.length() <= 16;
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
        cout << "==========REGISTER PAGE==========\n\n";
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
            if (isValidUsername(inputUsername)) {
                if (isValidPassword(inputPassword)) {
                    if (inputPassword == inputPassword2) {
                        userType new_user = { inputUsername, inputPassword };
                        addNewUserToFile(new_user);
                        cout << "\n\nRegistered successfully\n";
                        pauseEnter();
                        customerPage(inputUsername, inputPassword);
                        return;
                    }
                    else {
                        char option;
                        cout << "\n\nBoth passwords do not match\nDo you wish to continue? (Y/N):\t";
                        cin >> option;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        loop = (toupper(option) == 'Y');
                    }
                }
                else {
                    char option;
                    cout << "\n\nPassword length must be between 8 and 16 characters\nDo you wish to continue? (Y/N):\t";
                    cin >> option;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    loop = (toupper(option) == 'Y');
                }
            }
            else {
                char option;
                cout << "\n\nUsername must be between 5 and 20 characters and can only contain letters and numbers\nDo you wish to continue? (Y/N):\t";
                cin >> option;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loop = (toupper(option) == 'Y');
            }
        }
        else {
            char option;
            cout << "\n\nUsername taken\nDo you wish to continue? (Y/N):\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y');
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
    string currentPassword; // Store the correct password after successful login

    do {
        newPageLogo();
        string inputUsername = "", inputPassword = "";
        cout << "----------CUSTOMER LOGIN----------\n\n";
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
                currentPassword = inputPassword;  // Store the correct password
                break;
            }
        }
        if (recordFound) {
            cout << "\n\nAccess granted\nPress enter to continue\t";
            loop = false;
            pauseEnter();
            customerPage(inputUsername, currentPassword); // Pass username and password to the customer page
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

        string dayStr, timeslotStr, expertStr, serviceStr, paymentModeStr;

        getline(ss, booking.customerName, ',');
        getline(ss, dayStr, ',');
        getline(ss, timeslotStr, ',');
        getline(ss, expertStr, ',');
        getline(ss, serviceStr, ',');
        ss >> booking.cost;
        ss.ignore(1); //skip comma
        getline(ss, paymentModeStr, ',');


        for (int i = 0; i < 5; i++) {
            if (DAY[i] == dayStr) {
                booking.day = i;
                break;
            }
        }

        if (serviceStr == "Styling Consultation") {
            for (int i = 0; i < 6; i++) {
                if (TIMESLOT_CONSULT[i] == timeslotStr) {
                    booking.timeslot = i;
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < 3; i++) {
                if (TIMESLOT[i] == timeslotStr) {
                    booking.timeslot = i;
                    break;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            if (EXPERT[i] == expertStr) {
                booking.expert = i;
                break;
            }
        }

        for (int i = 0; i < 4; i++) {
            if (SERVICE[i] == serviceStr) {
                booking.service = i;
                break;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (PAYMENTMODE[i] == paymentModeStr) {
                booking.payment_mode = i;
                break;
            }
        }

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
bool checkBookingAvailable(int day, int timeslot, int expert, bool isConsultation) {
    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr) {
        return false;  // Return unavailable if file reading fails
    }

    // Iterate through all booking records and check for conflicts
    for (int i = 0; i < lenBookings; i++) {
        // Check if the booking is for the same day and same expert
        if (bookingsArray[i].day == day && bookingsArray[i].expert == expert) {
            int bookedTimeslot = bookingsArray[i].timeslot;
            bool bookedIsConsultation = bookingsArray[i].service == 3;  // If the booked service is consultation

            if (isConsultation) {
                // Handling Consultation booking request
                if (bookedIsConsultation) {
                    // Both are consultations, check for exact overlap
                    if (bookedTimeslot == timeslot) {
                        return false;  // Conflict with the same consultation timeslot
                    }
                }
                else {
                    // Existing booking is a treatment (2-hour)
                    if ((bookedTimeslot == 0 && (timeslot == 0 || timeslot == 1)) ||  // 10:00 AM - 12:00 PM treatment conflicts with any 1-hour consultation in that range
                        (bookedTimeslot == 1 && (timeslot == 2 || timeslot == 3)) ||  // 2:00 PM - 4:00 PM treatment conflicts with 2:00 PM - 3:00 PM or 3:00 PM - 4:00 PM consultation
                        (bookedTimeslot == 2 && (timeslot == 4 || timeslot == 5))) {  // 4:00 PM - 6:00 PM treatment conflicts with 4:00 PM - 5:00 PM or 5:00 PM - 6:00 PM consultation
                        return false;
                    }
                }
            }
            else {
                // Handling Treatment booking request
                if (bookedIsConsultation) {
                    // Existing booking is a consultation (1-hour)
                    if ((timeslot == 0 && (bookedTimeslot == 0 || bookedTimeslot == 1)) ||  // 10:00 AM - 12:00 PM treatment conflicts with any consultation between 10:00 AM - 12:00 PM
                        (timeslot == 1 && (bookedTimeslot == 2 || bookedTimeslot == 3)) ||  // 2:00 PM - 4:00 PM treatment conflicts with any consultation between 2:00 PM - 4:00 PM
                        (timeslot == 2 && (bookedTimeslot == 4 || bookedTimeslot == 5))) {  // 4:00 PM - 6:00 PM treatment conflicts with any consultation between 4:00 PM - 6:00 PM
                        return false;
                    }
                }
                else {
                    // Both are treatments, check for exact overlap
                    if (bookedTimeslot == timeslot) {
                        return false;  // Conflict with the same treatment timeslot
                    }
                }
            }
        }
    }

    return true;  // Return available if no conflicts
}


// Save the booking information to file
void saveBookingToFile(bookingType newBooking) {
    ofstream outFile(FILE_BOOKINGS, ios::app);

    if (!outFile) {
        cout << "Sorry, an error occurred while saving the booking.";
        return;
    }

    outFile << newBooking.customerName << ","
        << DAY[newBooking.day] << ","
        << (newBooking.service == 3 ? TIMESLOT_CONSULT[newBooking.timeslot] : TIMESLOT[newBooking.timeslot]) << ","
        << EXPERT[newBooking.expert] << ","
        << SERVICE[newBooking.service] << ","
        << fixed << setprecision(2) << newBooking.cost << ","
        << PAYMENTMODE[newBooking.payment_mode] << "\n";
    outFile.close();
}

//------------------------------------------------------CUSTOMERS INTERFACE
// Customer Main Page
void customerPage(string username, string currentPassword) {
    char option;
    char option2;
    newPageLogo();
    cout << "--------CUSTOMER HOMEPAGE--------\n";
    cout << "Welcome " << username << endl;
    cout << "Please choose your option.\n";

    cout << "A\t: View Service\n";
    cout << "B\t: View Expert\n";
    cout << "C\t: Make Booking\n";
    cout << "D\t: My bookings\n";
    cout << "E\t: View Time Slot Available\n";
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
        cout << "3. Hair Dying\n";
        cout << "4. Styling Consultation\n\n";
        cout << "Press enter to return:\t";
        pauseEnter();
        customerPage(username, currentPassword);
        break;
    case 'B': case 'b':
        newPageLogo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Press enter to return\t";
        pauseEnter();
        customerPage(username, currentPassword);
        break;
    case 'C': case 'c':
        makeBooking(username, currentPassword);
        break;
    case 'D': case 'd':
        mybookingsDetail(username, currentPassword);
        break;
    case 'E': case 'e':
        viewTimeslotAvailable(username, currentPassword);
        break;
    case 'F': case 'f':
        cout << "\nYou wish to write down your feedback?(Y/N):\t";
        cin >> option2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(option2) == 'Y') {
            feedbackForm(username, currentPassword);
        }
        else {
            customerPage(username, currentPassword);
        }
        break;
    case 'G': case 'g':
        customerLogout(username, currentPassword);
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        customerPage(username, currentPassword); // Return to customer login for a retry
    }
}

// Customer > My Bookings (Display all bookings made by the current user)
void mybookingsDetail(string username, string currentPassword) {
    char option;
    int lenBookings = 0;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr || lenBookings == 0) {
        cout << "No bookings available or file error.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    while (true) {
        newPageLogo();
        cout << "\t\t\tMy Bookings\n";
        cout << "========================================================================================================================\n";
        cout << setw(4) << left << "No" << setw(15) << left << "Day" << setw(30) << left << "Time Slot"
            << setw(25) << left << "Expert" << setw(22) << left << "Service" << setw(10) << left << "Cost"
            << setw(15) << left << "Payment Mode" << endl;
        cout << "========================================================================================================================\n";

        int bookingCount = 0;
        bookingType userBookings[100];
        int bookingIndices[100];  // Indices of user's bookings in bookingsArray

        for (int i = 0; i < lenBookings; i++) {
            if (bookingsArray[i].customerName == username) {
                userBookings[bookingCount] = bookingsArray[i];
                bookingIndices[bookingCount] = i;
                cout << setw(4) << left << bookingCount + 1
                    << setw(15) << left << DAY[bookingsArray[i].day];

                if (bookingsArray[i].service == 3) {  // Consultation (1-hour slots)
                    cout << setw(30) << left << TIMESLOT_CONSULT[bookingsArray[i].timeslot];
                }
                else {  // Other services (2-hour slots)
                    cout << setw(30) << left << TIMESLOT[bookingsArray[i].timeslot];
                }

                cout << setw(25) << left << EXPERT[bookingsArray[i].expert]
                    << setw(22) << left << SERVICE[bookingsArray[i].service]
                    << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
                    << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;

                bookingCount++;
            }
        }

        if (bookingCount == 0) {
            cout << "You have no bookings.\n";
            cout << "========================================================================================================================\n";
            cout << "Press Enter to return:";
            pauseEnter();
            customerPage(username, currentPassword);
            return;
        }

        cout << "========================================================================================================================\n\n";
        cout << "Please choose your option\n";
        cout << "A\t: Cancel Booking\n";
        cout << "B\t: View Receipt\n";  // Add an option to view the receipt
        cout << "C\t: Return to Customer Page\n\n";
        cout << "Enter your choice: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
        case 'A': case 'a':
            cancelBooking(username, currentPassword, bookingsArray, lenBookings, bookingIndices, bookingCount);
            break;
        case 'B': case 'b':
            viewReceipt(username, bookingsArray, bookingIndices, bookingCount);  // Call the viewReceipt function
            break;
        case 'C': case 'c':
            customerPage(username, currentPassword);
            return;
        default:
            cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
            pauseEnter();
        }
    }
}

void cancelBooking(string username, string currentPassword, bookingType* bookingsArray, int lenBookings, int* bookingIndices, int bookingCount) {
    // authentication with password same as login password
    string inputPassword;
    cout << "Please enter your password again to confirm: ";
    getline(cin, inputPassword);

    if (inputPassword != currentPassword) {
        cout << "Authentication failed. Incorrect password.\n";
        cout << "Press Enter to Try Again:";
        pauseEnter();
        return;
    }

    // display user's booking details
    cout << "\nAvailable bookings for cancellation:\n";
    for (int i = 0; i < bookingCount; i++) {
        int idx = bookingIndices[i];
        cout << setw(4) << left << i + 1
            << setw(15) << left << DAY[bookingsArray[idx].day];

        if (bookingsArray[idx].service == 3) {  // Consultation (1-hour slots)
            cout << setw(30) << left << TIMESLOT_CONSULT[bookingsArray[idx].timeslot];
        }
        else {  // Other services (2-hour slots)
            cout << setw(30) << left << TIMESLOT[bookingsArray[idx].timeslot];
        }

        cout << setw(25) << left << EXPERT[bookingsArray[idx].expert]
            << setw(22) << left << SERVICE[bookingsArray[idx].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[idx].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[idx].payment_mode] << endl;
    }

    if (bookingCount == 0) {
        cout << "No active bookings to cancel.\n";
        pauseEnter();
        return;
    }

    // ask customer to cancel booking
    int bookingToCancel = 0;
    cout << "Enter the number of the booking you want to cancel: ";
    cin >> bookingToCancel;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (bookingToCancel == 0 || bookingToCancel > bookingCount) {
        cout << "Invalid selection. Returning to My Bookings page.";
        pauseEnter();
        return;
    }

    int selectedUserBookingIndex = bookingToCancel - 1;
    int selectedBookingIndex = bookingIndices[selectedUserBookingIndex];

    // delete cancelled booking from bookings.dat
    ofstream outFile(FILE_BOOKINGS);

    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < lenBookings; i++) {
        if (i != selectedBookingIndex) {  //skip the cancelled booking
            outFile << bookingsArray[i].customerName << ","
                << bookingsArray[i].day << ","
                << bookingsArray[i].timeslot << ","
                << bookingsArray[i].expert << ","
                << bookingsArray[i].service << ","
                << fixed << setprecision(2) << bookingsArray[i].cost << ","
                << bookingsArray[i].payment_mode << "\n";
        }
    }

    outFile.close();

    cout << "Booking cancelled successfully.\n";
    cout << "Press Enter to return:";
    pauseEnter();

    // return and update My bookings
    mybookingsDetail(username, currentPassword);
}

// Function to view a receipt for a specific booking
void viewReceipt(string username, bookingType* bookingsArray, int* bookingIndices, int bookingCount) {
    int bookingToView;

    // Ask the user to select the booking they want to view the receipt for
    cout << "\nSelect the booking number to view the receipt (0 to return): ";
    cin >> bookingToView;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (bookingToView == 0 || bookingToView > bookingCount) {
        cout << "Invalid selection. Returning to bookings page.\n";
        pauseEnter();
        return;
    }

    int selectedBookingIndex = bookingIndices[bookingToView - 1];
    const bookingType& booking = bookingsArray[selectedBookingIndex];

    // Display the receipt details on the console
    cout << "==================================================================\n";
    cout << "||                    Haven Saloon - Receipt                    ||\n";
    cout << "==================================================================\n";
    cout << "Customer Name\t\t: " << booking.customerName << endl;
    cout << "Date\t\t\t: " << DAY[booking.day] << endl;

    // Check if the service is a consultation and adjust the time slot accordingly
    if (booking.service == 3) {  // Consultation (1-hour slots)
        cout << "Time\t\t\t: " << TIMESLOT_CONSULT[booking.timeslot] << endl;
    }
    else {  // Other services (2-hour slots)
        cout << "Time\t\t\t: " << TIMESLOT[booking.timeslot] << endl;
    }

    cout << "Expert\t\t\t: " << EXPERT[booking.expert] << endl;
    cout << "Service\t\t\t: " << SERVICE[booking.service] << endl;
    cout << "Cost\t\t\t: RM " << fixed << setprecision(2) << COST[booking.service] << endl;
    cout << "Payment Method\t: " << PAYMENTMODE[booking.payment_mode] << endl;
    cout << "==================================================================\n";
    cout << "||                Thank you for choosing Haven Saloon!          ||\n";
    cout << "==================================================================\n\n";

    // Pause after viewing the receipt
    cout << "Press Enter to Return:";
    pauseEnter();
}



// Customer > View Time Slot Available (Display available time slots for all experts)
void viewTimeslotAvailable(string username, string currentPassword) {
    newPageLogo();

    // Header for the schedule
    cout << "\t\t\t\t\t\t\t\tVIEW AVAILABLE TIME SLOT\n";
    cout << "==========================================================================================================================================\n";

    // First Table for 2-Hour Treatment Slots
    cout << "Treatment (2-hour slots)\n";
    cout << "==========================================================================================================================================\n";
    cout << setw(15) << left << "EXPERTS" << setw(15) << "DAY" << setw(20) << "timeslot1" << setw(20) << "timeslot2" << setw(20) << "timeslot3" << endl;
    cout << "==========================================================================================================================================\n";

    // Iterate over experts for treatment slots (2-hour)
    for (int i = 0; i < 3; i++) {  // Three experts
        cout << setw(15) << left << EXPERT[i] << endl;

        for (int j = 0; j < 5; j++) { // Iterate over days (Monday to Friday)
            cout << setw(15) << "" << setw(15) << DAY[j];

            // Display availability for each 2-hour timeslot
            for (int k = 0; k < 3; k++) { // Three treatment slots (2-hour each)
                if (checkBookingAvailable(j, k, i, false)) {  // Check availability for 2-hour slots
                    cout << GREEN << setw(20) << TIMESLOT[k] << RESET;  // If available, print the timeslot in green
                }
                else {
                    cout << RED << setw(20) << "NO AVAILABLE" << RESET;  // If booked, print "NO AVAILABLE" in red
                }
            }

            cout << endl;
        }
        cout << "==========================================================================================================================================\n";
    }

    // Second Table for 1-Hour Consultation Slots
    cout << "\nConsultation (1-hour slots)\n";
    cout << "====================================================================================================================================================\n";
    cout << setw(15) << left << "EXPERTS" << setw(15) << "DAY" << setw(20) << "timeslot1" << setw(20) << "timeslot2" << setw(20) << "timeslot3" << setw(20) << "timeslot4" << setw(20) << "timeslot5" << setw(20) << "timeslot6" << endl;
    cout << "====================================================================================================================================================\n";

    // Iterate over experts for consultation slots (1-hour)
    for (int i = 0; i < 3; i++) {  // Three experts
        cout << setw(15) << left << EXPERT[i] << endl;

        for (int j = 0; j < 5; j++) { // Iterate over days (Monday to Friday)
            cout << setw(15) << "" << setw(15) << DAY[j];

            // Display availability for each 1-hour timeslot
            for (int k = 0; k < 6; k++) { // Six consultation slots (1-hour each)
                if (checkBookingAvailable(j, k, i, true)) {  // Check availability for 1-hour consultation slots
                    cout << GREEN << setw(20) << TIMESLOT_CONSULT[k] << RESET;  // If available, print the timeslot in green
                }
                else {
                    cout << RED << setw(20) << "NO AVAILABLE" << RESET;  // If booked, print "NO AVAILABLE" in red
                }
            }

            cout << endl;
        }
        cout << "====================================================================================================================================================\n";
    }

    // Footer for the schedule
    cout << "====================================================================================================================================================\n";
    cout << "Press Enter to return:";
    pauseEnter();
    customerPage(username, currentPassword);
}



// Customer > Feedback Form (Allow customers to provide feedback)
void feedbackForm(string username, string currentPassword) {
    newPageLogo();

    ofstream feedbackFile("feedback.dat", ios::app); // Open in append mode

    if (!feedbackFile) {
        cout << "Error: Could not open feedback file.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    string name;
    string feedback;
    cout << "-----------------Feedback Form-----------------\n";
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Please enter your feedback:\n";
    getline(cin, feedback);  // Get feedback from customer

    // Save feedback to file
    feedbackFile << "Customer Name: " << name << endl;
    feedbackFile << "Feedback: " << feedback << endl;
    feedbackFile << "------------------------------------------\n";
    feedbackFile.close();

    cout << "Thank you for your feedback!\n";
    cout << "Press enter to return:";
    pauseEnter();
    customerPage(username, currentPassword);
}

// Ask confirm logout and go to main menu
void customerLogout(string username, string currentPassword) {
    char confirmLogout = 'Y';
    cout << "\nDo you wish to log out? (Y/N):\t";
    cin >> confirmLogout;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        customerPage(username, currentPassword);
    }
}

// For the customer menu interface
template<size_t N>
int getChoice(const array<string, N>& options) {
    int choice;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i] << endl;
    }
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > options.size()) {
        cout << "Invalid choice. Please enter a number between 1 and " << options.size() << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

// Customer > Make Booking > Select Service
int selectService() {
    newPageLogo();

    ifstream inFile("services.dat");

    if (!inFile) {
        cerr << "Error: Could not open the services file." << endl;
        return -1;
    }

    string service;
    double price;
    int count = 0;

    // Temporary arrays to hold services and prices
    array<string, 4> services;
    array<double, 4> prices;

    // Display header
    cout << "------------------------------------------" << endl;
    cout << setw(30) << left << "Service" << setw(10) << "Price (RM)" << endl;
    cout << "------------------------------------------" << endl;

    // Read services and prices from the file and store them
    while (inFile >> service >> price && count < 4) {
        services[count] = service;
        prices[count] = price;

        // Display the service and price
        cout << setw(30) << left << service << setw(10) << right << fixed << setprecision(2) << price << endl;
        count++;
    }

    inFile.close();
    cout << "------------------------------------------" << endl;
    cout << "Please select a service you want to book" << endl;

    // Let the user choose a service
    int choice = getChoice(services);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert
int selectExpert(int day, int timeslot, bool isConsultation) {
    newPageLogo();
    array<string, 4> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };

    cout << "--------SELECT AN EXPERT--------\n";
    int choice = getChoice(experts);

    // If user selects auto-assign option
    if (choice == 4) {
        int assignedExpert = autoAssignExpert(day, timeslot, isConsultation);  // Use the modified autoAssignExpert to check availability
        if (assignedExpert != -1) {
            cout << "Expert " << experts[assignedExpert] << " has been auto-assigned.\n";
            return assignedExpert;
        }
        else {
            return -1;  // Return -1 if no expert is available
        }
    }

    // Return selected expert index (adjust for array offset)
    return choice - 1;
}


// Customer > Make Booking > Select Service > Select Expert (random assign expert function)
int autoAssignExpert(int day, int timeslot, bool isConsultation) {
    array<string, 3> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
    srand(time(0));

    int availableExperts[3];  // Array to store indices of available experts
    int countAvailable = 0;   // Counter for the number of available experts

    // Check availability of each expert
    for (int i = 0; i < experts.size(); i++) {
        if (checkBookingAvailable(day, timeslot, i, isConsultation)) {
            availableExperts[countAvailable] = i;  // Add available expert's index
            countAvailable++;  // Increment the counter
        }
    }

    if (countAvailable > 0) {
        // Randomly select one of the available experts
        int randomIndex = rand() % countAvailable;
        return availableExperts[randomIndex];
    }
    else {
        // No available experts
        cout << "No available expert for the selected time slot." << endl;
        cout << "Press Enter to return:";
        return -1;  // Indicate no expert is available
    }
}


// Customer > Make Booking > Select Service > Select Date >Select Expert
int selectDate() {
    newPageLogo();
    array<string, 5> date = { "Monday", "Tuesday", "Wednesday" , "Thursday" , "Friday" };
    cout << "--------SELECT A RESERVATION DATE--------\n";
    int choice = getChoice(date);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot
int selectTimeSlot(int service) {
    newPageLogo();
    array<string, 3> regularTimeSlots = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
    array<string, 6> consultTimeSlots = { "Timeslot 1 (10:00AM - 11:00PM)", "Timeslot 2 (11:00PM - 12:00PM)", "Timeslot 3 (2:00PM - 3:00PM)", "Timeslot 4 (3:00PM - 4:00PM)", "Timeslot 5 (4:00PM - 5:00PM)", "Timeslot 6 (5:00PM - 6:00PM)" };
    // Declare a pointer for timeSlots and an integer for availableSlots
    const string* timeSlots;
    int availableSlots = 0;

    // Select the appropriate time slots based on the service
    if (service == 3) { // Consultation service
        cout << "--------SELECT A TIME SLOT (Consultation)--------\n";
        timeSlots = consultTimeSlots.data();  // Point to consultation time slots
        availableSlots = consultTimeSlots.size();
    }
    else {
        cout << "--------SELECT A TIME SLOT--------\n";
        timeSlots = regularTimeSlots.data();  // Point to regular time slots
        availableSlots = regularTimeSlots.size();
    }

    // Display available time slots
    for (int i = 0; i < availableSlots; ++i) {
        cout << i + 1 << ". " << timeSlots[i] << endl;
    }

    // Input validation
    int choice;
    cout << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > availableSlots) {
        cout << "Invalid choice. Please enter a number between 1 and " << availableSlots << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert > Select Date > Select Time Slot > Select Payment Mode
int selectPaymentMode() {
    newPageLogo();
    array<string, 3> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    cout << "--------SELECT A PAYMENT MODE--------\n";
    int choice = getChoice(paymentModes);
    return choice - 1;
}

// Customer > Make Booking
// Customer > Make Booking
void makeBooking(string username, string currentPassword) {
    int service, expert, date, timeSlot, paymentMode;

    // Use the username as the customer name
    string customerName = username;

    service = selectService();      // Choose a service
    date = selectDate();            // Choose a date
    timeSlot = selectTimeSlot(service); // Choose a time slot

    bool isConsultation = (service == 3); // Check if it's a consultation

    expert = selectExpert(date, timeSlot, isConsultation); // Select expert
    if (expert == -1) {
        // If no available expert, return to customer page
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    paymentMode = selectPaymentMode(); // Choose payment method

    bool available = checkBookingAvailable(date, timeSlot, expert, isConsultation);

    if (available) {
        char confirm;
        cout << "Booking Summary:\n";
        cout << "\nUsername:\t" << customerName;
        cout << "\nDay:\t\t" << DAY[date];
        if (isConsultation) {
            cout << "\nTime Slot:\t" << TIMESLOT_CONSULT[timeSlot];
        }
        else {
            cout << "\nTime Slot:\t" << TIMESLOT[timeSlot];
        }

        cout << "\nService:\t" << SERVICE[service];
        cout << "\nExpert:\t\t" << EXPERT[expert];
        cout << "\nCost:\t\tRM " << fixed << setprecision(2) << COST[service];
        cout << "\nPayment Method:\t" << PAYMENTMODE[paymentMode];
        cout << "\n\nConfirm your booking (Y/N): ";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (confirm == 'Y' || confirm == 'y') {
            bookingType newBooking = { customerName, date, timeSlot, expert, service, COST[service], paymentMode };
            saveBookingToFile(newBooking);
            generateReceipt(newBooking); // Generate the receipt
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
    customerPage(username, currentPassword);
}


// Function to generate a printable receipt
void generateReceipt(const bookingType& booking) {
    // Open a file to append the receipt
    ofstream receiptFile("receipt.txt", ios::app);  // Open in append mode

    // Define the receipt format
    string serviceNames[] = { "HairCut", "HairWash", "HairDye", "Consultation" };
    double servicePrices[] = { 25.00, 15.00, 80.00, 15.00 };

    // Write the receipt header and details
    receiptFile << "==================================================================\n";
    receiptFile << "||                    Haven Saloon - Receipt                    ||\n";
    receiptFile << "==================================================================\n";
    receiptFile << "Customer Name\t\t: " << booking.customerName << endl;
    receiptFile << "Date\t\t\t: " << DAY[booking.day] << endl;

    // Check if the service is a consultation and adjust the time slot accordingly
    if (booking.service == 3) {  // Consultation (1-hour slots)
        receiptFile << "Time\t\t\t: " << TIMESLOT_CONSULT[booking.timeslot] << endl;
    }
    else {  // Other services (2-hour slots)
        receiptFile << "Time\t\t\t: " << TIMESLOT[booking.timeslot] << endl;
    }

    receiptFile << "Expert\t\t\t: " << EXPERT[booking.expert] << endl;
    receiptFile << "Service\t\t\t: " << serviceNames[booking.service] << endl;
    receiptFile << "Cost\t\t\t: RM " << fixed << setprecision(2) << servicePrices[booking.service] << endl;
    receiptFile << "Payment Method\t: " << PAYMENTMODE[booking.payment_mode] << endl;
    receiptFile << "==================================================================\n";
    receiptFile << "||                Thank you for choosing Haven Saloon!          ||\n";
    receiptFile << "==================================================================\n\n";  // Add extra newlines to separate receipts

    receiptFile.close();  // Close the file after appending the receipt

    cout << "Receipt has been saved to 'receipt.txt'.\n";
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
            loop = false;
            pauseEnter();
            adminPage(inputUsername);
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
void adminPage(string username) {
    char option;
    newPageLogo();
    cout << "--------ADMIN HOMEPAGE--------\n";
    cout << "Welcome " << username << endl;
    cout << "Please choose your option.\n";

    cout << "A\t: View Customer Bookings\n";
    cout << "B\t: View Sales Record\n";
    cout << "C\t: View Schedule\n";
    cout << "D\t: View Feedback Form\n";
    cout << "E\t: Log Out and Return to Main Menu\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        viewCustomerBookings(username);
        break;
    case 'B': case 'b':
        newPageLogo();
        viewSalesRecord(username);
        break;
    case 'C': case 'c':
        newPageLogo();
        viewExpertSchedule(username);
        break;
    case 'D': case 'd':
        newPageLogo();
        viewFeedbackForm(username);
        break;
    case 'E': case 'e':
        adminLogout(username);
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        adminPage(username); // Return to admin page for a retry
    }
}
//view customer Bookings
void viewCustomerBookings(string username) {
    newPageLogo();

    int lenBookings = 0;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr) {
        cout << "No customer bookings available (file error or empty).\n";
        pauseEnter();
        return;
    }

    // Display table headers
    cout << "\t\t\t\t\t\tView Customer Bookings\n";
    cout << "==========================================================================================================================================\n";
    cout << setw(4) << left << "No" << setw(20) << left << "Customer Name" << setw(15) << left << "Day" << setw(30) << left << "Time Slot"
        << setw(25) << left << "Expert" << setw(22) << left << "Service" << setw(10) << left << "Cost"
        << setw(15) << left << "Payment Mode" << endl;
    cout << "==========================================================================================================================================\n";

    // Loop through the bookings array and display each booking
    for (int i = 0; i < lenBookings; i++) {
        cout << setw(4) << left << i + 1
            << setw(20) << left << bookingsArray[i].customerName  // Display the customer name
            << setw(15) << left << DAY[bookingsArray[i].day]
            << setw(30) << left << TIMESLOT[bookingsArray[i].timeslot]
            << setw(25) << left << EXPERT[bookingsArray[i].expert]
            << setw(22) << left << SERVICE[bookingsArray[i].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;
    }

    if (lenBookings == 0) {
        cout << "No customer bookings found.\n";
    }

    cout << "==========================================================================================================================================\n";
    cout << "Press Enter to return:";
    pauseEnter();
    adminPage(username);
}

// Admin > View Sales Record
void viewSalesRecord(string username) {
    newPageLogo();

    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr || lenBookings == 0) {
        cout << "Error: Could not retrieve booking data." << endl;
        pauseEnter();
        return;
    }

    double totalSales = 0;
    cout << "===============SALES RECORD===================\n";
    cout << left << setw(10) << "Day" << setw(25) << "Service" << setw(15) << "Cost (RM)" << endl;
    cout << "==============================================\n";

    // Loop through all bookings and calculate total sales
    for (int i = 0; i < lenBookings; i++) {
        totalSales += bookingsArray[i].cost;

        cout << left << setw(10) << DAY[bookingsArray[i].day]
            << setw(25) << SERVICE[bookingsArray[i].service]
            << setw(15) << bookingsArray[i].cost << endl;
    }

    cout << "==============================================\n";
    cout << "Total Sales: RM " << fixed << setprecision(2) << totalSales << endl;

    cout << "\nPress enter to return:";
    pauseEnter();
    adminPage(username);
}


// Admin > View Schedule
void viewExpertSchedule(string username) {
    newPageLogo();

    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr || lenBookings == 0) {
        cout << "Error: Could not retrieve booking data." << endl;
        pauseEnter();
        return;
    }

    const int MAX_SCHEDULES = 100;
    array<string, MAX_SCHEDULES> aliceSchedules;
    array<string, MAX_SCHEDULES> berniceSchedules;
    array<string, MAX_SCHEDULES> catherineSchedules;
    int aliceCount = 0, berniceCount = 0, catherineCount = 0;

    cout << "--------EXPERT SCHEDULES--------\n";

    // Loop through all bookings and assign schedules to each expert
    for (int i = 0; i < lenBookings; i++) {
        string schedule;
        if (bookingsArray[i].service == 3) {  // Consultation (1??)
            schedule = DAY[bookingsArray[i].day] + " - " + TIMESLOT_CONSULT[bookingsArray[i].timeslot] + " | Service: " + SERVICE[bookingsArray[i].service];
        }
        else {  // ???? (2??)
            schedule = DAY[bookingsArray[i].day] + " - " + TIMESLOT[bookingsArray[i].timeslot] + " | Service: " + SERVICE[bookingsArray[i].service];
        }

        if (bookingsArray[i].expert == 0 && aliceCount < MAX_SCHEDULES) {
            aliceSchedules[aliceCount++] = schedule;
        }
        else if (bookingsArray[i].expert == 1 && berniceCount < MAX_SCHEDULES) {
            berniceSchedules[berniceCount++] = schedule;
        }
        else if (bookingsArray[i].expert == 2 && catherineCount < MAX_SCHEDULES) {
            catherineSchedules[catherineCount++] = schedule;
        }
    }

    // Display Alice Wong's Schedule
    cout << "\nExpert: Alice Wong\n";
    for (int i = 0; i < aliceCount; i++) {
        cout << "- " << aliceSchedules[i] << endl;
    }

    // Display Bernice Lim's Schedule
    cout << "\nExpert: Bernice Lim\n";
    for (int i = 0; i < berniceCount; i++) {
        cout << "- " << berniceSchedules[i] << endl;
    }

    // Display Catherine Tan's Schedule
    cout << "\nExpert: Catherine Tan\n";
    for (int i = 0; i < catherineCount; i++) {
        cout << "- " << catherineSchedules[i] << endl;
    }

    cout << "\nPress enter to return:";
    pauseEnter();
    adminPage(username);
}

// Admin > View Feedback (Reads and displays all feedback entries)
void viewFeedbackForm(string username) {
    newPageLogo();

    ifstream feedbackFile("feedback.dat");

    if (!feedbackFile) {
        cout << "Error: Could not open feedback file.\n";
        pauseEnter();
        adminPage(username);
        return;
    }

    string line;
    cout << "---------------------FEEDBACK ENTRIES---------------------\n";

    bool feedbackExists = false;

    while (getline(feedbackFile, line)) {
        cout << line << endl;  // Display each line from the feedback file
        feedbackExists = true;
    }

    feedbackFile.close();

    if (!feedbackExists) {
        cout << "No feedback available.\n";
    }

    cout << "\n---------------------------------------------------------\n";
    cout << "Press Enter to return:";
    pauseEnter();
    adminPage(username);
}

// Ask confirm logout and go to main menu
void adminLogout(string username) {
    char confirmLogout = 'Y';
    cout << "\nDo you wish to log out? (Y/N):\t";
    cin >> confirmLogout;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(confirmLogout) == 'Y') {
        mainMenu();
    }
    else {
        adminPage(username);
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

//service.dat(put in the same directory as the cpp file)
/*
HairCut 25.00
HairWash 15.00
HairDying 80.00
Consultation 15.00

*/

//bookings.dat (put in the same directory as the cpp file)
/*


*/

//receipt.txt(put in the same directory as the cpp file)
/*

*/ //The \n under last record is necessary!
