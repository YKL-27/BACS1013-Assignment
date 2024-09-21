#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
//#include <conio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

using namespace std;

// Structure definition
struct userType {
    string username = "";
    string password = "";
    bool admin = 0;
};

struct bookingType {
    string customerName;
    int day = 0; // Represents the day of the month (1-30)
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
bool checkBookingAvailable(int day, int timeslot, int expert);
void saveBookingToFile(bookingType newBooking);

void makeBooking(string username, string currentPassword);
int selectService();
int selectExpert(int day, int timeslot);
int selectWeek();
int selectDayOfWeek();
int selectDate();
int selectTimeSlot(int service);
int selectPaymentMode();
int autoAssignExpert(int day, int timeslot);
void generateReceipt(const bookingType& booking);

void adminLogin();
void adminPage(string username);
void adminLogout(string username);
void viewCustomerBookings(string username);
void viewSalesRecord(string username);
void viewBookingSlot(string username);
void viewFeedbackForm(string username);

// GLOBAL CONSTANT & VARIABLES------------------------------------------------------------------------------------------------------------------------------------------------------
const string FILE_USERS = "user.dat";
const string FILE_BOOKINGS = "bookings.dat";
const int MAX_DAYS = 30; // Supports up to 30 days
const string TREATMENT_TIMESLOT[3] = { "10:00AM - 12:00PM", "2:00PM - 4:00PM","4:00PM - 6:00PM" };
const string TIMESLOT_CONSULT[6] = { "10:00AM - 11:00AM", "11:00AM - 12:00PM", "2:00PM - 3:00PM", "3:00PM - 4:00PM" , "4:00PM - 5:00PM", "5:00PM - 6:00PM" };
const string EXPERT[3] = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
const string SERVICE[4] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation" };
const string PAYMENTMODE[3] = { "Credit Card", "Debit Card", "Cash" };
const double COST[4] = { 25.00, 15.00, 80.00, 15.00 };

// Helper Functions
int getDayOfWeek(int day) {
    // Assuming day 1 is Monday
    return ((day - 1) % 7) + 1;
}


// Checks if a given day is a weekend (Saturday or Sunday)
bool isWeekend(int day) {
    int dayOfWeek = getDayOfWeek(day);
    return (dayOfWeek == 6 || dayOfWeek == 7); // 6: Saturday, 7: Sunday
}

// Function to get the day name from day number
string getDayName(int day) {
    int dayOfWeek = getDayOfWeek(day);
    switch (dayOfWeek) {
    case 1: return "Monday";
    case 2: return "Tuesday";
    case 3: return "Wednesday";
    case 4: return "Thursday";
    case 5: return "Friday";
    case 6: return "Saturday";
    case 7: return "Sunday";
    default: return "Invalid Day";
    }
}

// COMMON FUNCTIONS
// Create a new page by clearing the screen and displaying a logo on top
void newPageLogo() {
    // Clear screen
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Start with the desired color
    cout << GREEN; // You can choose any color you like

    cout << "\t\t  =======================================================================================================\n";
    cout << "\t\t  || ##     ##    ###    ##     ## ######## ##    ##     ######     ###    ##        #######  ##    ## ||\n";
    cout << "\t\t  || ##     ##   ## ##   ##     ## ##       ###   ##    ##    ##   ## ##   ##       ##     ## ###   ## ||\n";
    cout << "\t\t  || ##     ##  ##   ##  ##     ## ##       ####  ##    ##        ##   ##  ##       ##     ## ####  ## ||\n";
    cout << "\t\t  || ######### ##     ## ##     ## ######   ## ## ##     ######  ##     ## ##       ##     ## ## ## ## ||\n";
    cout << "\t\t  || ##     ## #########  ##   ##  ##       ##  ####          ## ######### ##       ##     ## ##  #### ||\n";
    cout << "\t\t  || ##     ## ##     ##   ## ##   ##       ##   ###    ##    ## ##     ## ##       ##     ## ##   ### ||\n";
    cout << "\t\t  || ##     ## ##     ##    ###    ######## ##    ##     ######  ##     ## ########  #######  ##    ## ||\n";
    cout << "\t\t  =======================================================================================================\n\n";

    // Reset to default color
    cout << RESET;
}

// Pause by prompting an input (use string & getline in case user typed in anything)
void pauseEnter() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// MAIN MENU PAGE
void mainMenu() {
    // First Interface
    char option;
    newPageLogo();
    cout << CYAN << "----------------------------------------MAIN MENU---------------------------------------------------" << RESET << endl;
    cout << "WELCOME TO HAVEN SALON\n";
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
        cout << "\nInvalid option, Please try again!\n";
        pauseEnter();
        mainMenu(); // Return to main menu for a retry
    }
}

// ABOUT US PAGE
void aboutUsPage() {
    newPageLogo();

    // Print the header in magenta
    cout << MAGENTA << "---------------------------------------------------------ABOUT US----------------------------------------------------------------\n" << RESET;

    ifstream aboutUsFile("aboutUs.txt");

    if (!aboutUsFile) {
        cerr << "Error: Could not open aboutUs.txt" << endl;
        cout << "Press Enter to return to main menu.";
        pauseEnter();
        mainMenu();
    }

    // Read and display the file content
    string line;
    cout << MAGENTA;
    while (getline(aboutUsFile, line)) {
        cout << line << endl;
    }
    cout << RESET;

    // Close the file
    aboutUsFile.close();

    cout << "Press Enter to return to main menu:\t";
    pauseEnter();
    mainMenu();
}

// USERS FILE
// Check if username is available during registration
bool checkUsernameAvailable(string username) {
    userType users[100];

    ifstream infile(FILE_USERS);
    if (!infile) {
        cout << "\n\nUnable to access user data currently.\nPress enter to return to main menu\t";
        pauseEnter();
        mainMenu();
    }

    string record;
    int counter = 0;
    while (getline(infile, record)) {
        stringstream ss(record);
        string usernameFile, passwordFile;
        userType user;

        getline(ss, usernameFile, ',');
        getline(ss, passwordFile, ',');

        user.username = usernameFile;
        user.password = passwordFile;

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

// Validation for username and password
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

// Add new user to file
void addNewUserToFile(userType new_user) {
    // Create a record in CSV-like format
    string record = new_user.username + ',' + new_user.password;
    // cout << record << endl;  // Display the record for debugging (commented out)

    ofstream outFile(FILE_USERS, ios::app); // Open file in append mode

    if (!outFile) {
        cout << "Sorry, an error occurred while opening the file.";
        return;
    }

    // Write the new user's data to the file
    outFile << record << "\n";  // Add a newline after the record
    outFile.close();
}

// CUSTOMERS REGISTER
void registerPage() {
    newPageLogo();
    // Registration loop
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

// CUSTOMERS LOGIN
void customerLogin() {
    newPageLogo();
    // Read user data
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
        string usernameFile, passwordFile;
        userType user;

        getline(ss, usernameFile, ',');
        getline(ss, passwordFile, ',');

        user.username = usernameFile;
        user.password = passwordFile;

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

// BOOKINGS FILE
// Read bookings from the file
bookingType* readBookingsFile(int& lenBookings) {
    static bookingType bookings[100]; // Store up to 100 bookings

    ifstream infile(FILE_BOOKINGS);
    if (!infile) {
        cout << "\n\nUnable to access booking data currently.\nPress enter to return to main menu\t";
        pauseEnter();
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
        booking.day = stoi(dayStr); // Directly convert day to integer

        getline(ss, timeslotStr, ',');
        booking.timeslot = stoi(timeslotStr); // Assuming timeslot is stored as integer

        getline(ss, expertStr, ',');
        booking.expert = stoi(expertStr); // Assuming expert is stored as integer index

        getline(ss, serviceStr, ',');
        booking.service = stoi(serviceStr); // Assuming service is stored as integer index

        ss >> booking.cost;
        ss.ignore(1); // Skip comma

        getline(ss, paymentModeStr, ',');
        booking.payment_mode = stoi(paymentModeStr); // Assuming payment_mode is stored as integer index

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
    if (isWeekend(day)) {
        return false; // Salon is closed on weekends
    }

    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr) {
        return false;
    }

    // Iterate through all existing bookings
    for (int i = 0; i < lenBookings; i++) {
        // Check if the booking is for the same day and expert
        if (bookingsArray[i].day == day && bookingsArray[i].expert == expert) {
            // Handle conflict between 2-hour treatment slots and 1-hour consultation slots

            // Check for treatment service conflicts (2-hour slots)
            if (bookingsArray[i].service != 3) {  // Treatment service (2-hour slot)
                if ((bookingsArray[i].timeslot == 0 && (timeslot == 0 || timeslot == 1)) ||   // 10:00AM - 12:00PM overlaps with 10:00AM - 11:00AM or 11:00AM - 12:00PM
                    (bookingsArray[i].timeslot == 1 && (timeslot == 2 || timeslot == 3)) ||   // 2:00PM - 4:00PM overlaps with 2:00PM - 3:00PM or 3:00PM - 4:00PM
                    (bookingsArray[i].timeslot == 2 && (timeslot == 4 || timeslot == 5))) {   // 4:00PM - 6:00PM overlaps with 4:00PM - 5:00PM or 5:00PM - 6:00PM
                    return false;
                }
            }

            // Check for consultation service conflicts (1-hour slots)
            if (bookingsArray[i].service == 3) {  // Consultation service (1-hour slot)
                if (timeslot == bookingsArray[i].timeslot) {  // Exact time slot overlap
                    return false;
                }
                if ((bookingsArray[i].timeslot == 1 && timeslot == 0) ||  // Consultation 11:00AM - 12:00PM prevents 10:00AM - 12:00PM treatment
                    (bookingsArray[i].timeslot == 3 && timeslot == 2) ||  // Consultation 3:00PM - 4:00PM prevents 2:00PM - 4:00PM treatment
                    (bookingsArray[i].timeslot == 5 && timeslot == 4)) {  // Consultation 5:00PM - 6:00PM prevents 4:00PM - 6:00PM treatment
                    return false;
                }
            }
        }
    }
    return true;  // No conflict found, the slot is available
}

// Save the booking information to file
void saveBookingToFile(bookingType newBooking) {
    ofstream outFile(FILE_BOOKINGS, ios::app);

    if (!outFile) {
        cout << "Sorry, an error occurred while saving the booking.";
        return;
    }

    // Save day as integer
    outFile << newBooking.customerName << ","
        << newBooking.day << ","
        << newBooking.timeslot << ","
        << newBooking.expert << ","
        << newBooking.service << ","
        << fixed << setprecision(2) << newBooking.cost << ","
        << newBooking.payment_mode << "\n";
    outFile.close();
}

// CUSTOMERS INTERFACE
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
    cout << "D\t: My Bookings\n";
    cout << "E\t: View Available Time Slots\n";
    cout << "F\t: Feedback Form\n";
    cout << "G\t: Log Out and Return to Main Menu\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();
        cout << "--------OUR SERVICES--------\n";
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
        cout << "--------OUR EXPERTS--------\n";
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
        cout << "\nDo you wish to write down your feedback? (Y/N):\t";
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
        cout << "\nInvalid option, Please try again!\n";
        pauseEnter();
        customerPage(username, currentPassword); // Return to customer page for a retry
    }
}
// Helper Function to Format Date
// Helper Function to Format Date
string formatDate(int day) {
    return to_string(day) + "-10-2024"; // Formats as "Day-10-2024"
}


// Helper Function to Get Full Date with Day Name
string getFullDate(int day) {
    return getDayName(day) + ", " + formatDate(day); // e.g., "Monday, 1-10-2024"
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
        cout << setw(4) << left << "No"
            << setw(15) << left << "Day" // Adjusted Width
            << setw(25) << left << "Time Slot"
            << setw(20) << left << "Expert"
            << setw(20) << left << "Service"
            << setw(10) << left << "Cost(RM)"
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
                    << setw(15) << left << formatDate(bookingsArray[i].day) // Updated Line

                    << setw(25) << left
                    << (bookingsArray[i].service == 3 ? TIMESLOT_CONSULT[bookingsArray[i].timeslot] : TREATMENT_TIMESLOT[bookingsArray[i].timeslot]);

                cout << setw(20) << left << EXPERT[bookingsArray[i].expert]
                    << setw(20) << left << SERVICE[bookingsArray[i].service]
                    << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
                    << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;

                bookingCount++;
            }
        }

        if (bookingCount == 0) {
            cout << "You have no bookings.\n";
            cout << "========================================================================================================================\n";
            cout << "Press Enter to return:\t";
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
            cout << "\nInvalid option, Please try again!\n";
            pauseEnter();
        }
    }
}


void cancelBooking(string username, string currentPassword, bookingType* bookingsArray, int lenBookings, int* bookingIndices, int bookingCount) {
    // Authentication with password same as login password
    string inputPassword;
    cout << "Please enter your password again to confirm: ";
    getline(cin, inputPassword);

    if (inputPassword != currentPassword) {
        cout << "Authentication failed. Incorrect password.\n";
        cout << "Press Enter to Try Again:";
        pauseEnter();
        return;
    }

    // Display user's booking details
    cout << "\nAvailable bookings for cancellation:\n";
    for (int i = 0; i < bookingCount; i++) {
        int idx = bookingIndices[i];
        cout << setw(4) << left << i + 1
            << setw(25) << left << getFullDate(bookingsArray[idx].day)
            << setw(25) << left
            << (bookingsArray[idx].service == 3 ? TIMESLOT_CONSULT[bookingsArray[idx].timeslot] : TREATMENT_TIMESLOT[bookingsArray[idx].timeslot])
            << setw(20) << left << EXPERT[bookingsArray[idx].expert]
            << setw(20) << left << SERVICE[bookingsArray[idx].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[idx].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[idx].payment_mode] << endl;
    }

    if (bookingCount == 0) {
        cout << "No active bookings to cancel.\n";
        pauseEnter();
        return;
    }

    // Ask customer to cancel booking
    int bookingToCancel = 0;
    cout << "Enter the number of the booking you want to cancel: ";
    cin >> bookingToCancel;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (bookingToCancel <= 0 || bookingToCancel > bookingCount) {
        cout << "Invalid selection. Returning to My Bookings page.";
        pauseEnter();
        return;
    }

    int selectedUserBookingIndex = bookingToCancel - 1;
    int selectedBookingIndex = bookingIndices[selectedUserBookingIndex];

    // Delete cancelled booking from bookings.dat
    ofstream outFile(FILE_BOOKINGS);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < lenBookings; i++) {
        if (i != selectedBookingIndex) {  // Skip the cancelled booking
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
    cout << "Press Enter to return:\t";
    pauseEnter();

    // Return and update My Bookings
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
    cout << "||                    Haven Salon - Receipt                     ||\n";
    cout << "==================================================================\n";
    cout << "Customer Name\t\t: " << booking.customerName << endl;

    // **Modified Line: Use formatDate to display the date properly**
    cout << "Date\t\t\t: " << formatDate(booking.day) << endl;

    // Check if the service is a consultation and adjust the time slot accordingly
    if (booking.service == 3) {  // Consultation (1-hour slots)
        cout << "Time\t\t\t: " << TIMESLOT_CONSULT[booking.timeslot] << endl;
    }
    else {  // Other services (2-hour slots)
        cout << "Time\t\t\t: " << TREATMENT_TIMESLOT[booking.timeslot] << endl;
    }

    cout << "Expert\t\t\t: " << EXPERT[booking.expert] << endl;
    cout << "Service\t\t\t: " << SERVICE[booking.service] << endl;
    cout << "Cost\t\t\t: RM " << fixed << setprecision(2) << COST[booking.service] << endl;
    cout << "Payment Method\t\t: " << PAYMENTMODE[booking.payment_mode] << endl;
    cout << "==================================================================\n";
    cout << "||                Thank you for choosing Haven Salon!          ||\n";
    cout << "==================================================================\n\n";

    // Pause after viewing the receipt
    cout << "Press Enter to Return:";
    pauseEnter();
}


int selectWeek() {
    newPageLogo();
    cout << "--------SELECT A WEEK--------\n";
    cout << "Please select a week (1 = first week, 2 = second week, ..., 5 = fifth week): ";

    int week;
    while (true) {
        cin >> week;
        if (cin.fail() || week < 1 || week > 5) {  // Valid weeks are between 1 and 5
            cout << "Invalid week. Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            break;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    return week;  // Return the selected week number
}



// Customer > View Time Slot Available (Display available time slots for all experts)
void viewTimeslotAvailable(string username, string currentPassword) {
    newPageLogo();
    cout << "\t\t\t\t\t\t\t\tVIEW AVAILABLE TIME SLOTS\n";


    int selectedWeek = selectWeek();

    cout << "==========================================================================================================================================\n";
    cout << setw(10) << left << "DAY"
        << setw(18) << "EXPERT"
        << setw(18) << "10:00AM-11:00AM"
        << setw(18) << "11:00AM-12:00PM"
        << setw(18) << "2:00PM-3:00PM"
        << setw(18) << "3:00PM-4:00PM"
        << setw(18) << "4:00PM-5:00PM"
        << setw(18) << "5:00PM-6:00PM" << endl;
    cout << "==========================================================================================================================================\n";


    for (int weekday = 1; weekday <= 5; weekday++) {
        int day = (selectedWeek - 1) * 7 + weekday;

        cout << setw(10) << left << getDayName(day);

        for (int i = 0; i < 3; i++) {
            cout << setw(18) << EXPERT[i];
            for (int k = 0; k < 6; k++) {
                if (checkBookingAvailable(day, k, i)) {
                    cout << GREEN << setw(18) << "A" << RESET;
                }
                else {
                    cout << RED << setw(18) << "N" << RESET;
                }
            }
            cout << endl;
        }
        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    cout << GREEN << "A = AVAILABLE\t" << RED << "N = UNAVAILABLE\n" << RESET;
    cout << "Press Enter to return:\t";
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
    cout << "Press enter to return:\t";
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
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
    while (inFile >> ws && getline(inFile, service, ' ') && inFile >> price && count < 4) {
        services[count] = service;
        prices[count] = price;

        // Display the service and price
        cout << setw(30) << left << service << setw(10) << right << fixed << setprecision(2) << price << endl;
        count++;
    }

    inFile.close();
    cout << "------------------------------------------" << endl;
    cout << "Please select a service you want to book:" << endl;

    // Let the user choose a service
    int choice = getChoice(services);
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Expert
int selectExpert(int day, int timeslot) {
    newPageLogo();
    array<string, 4> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };

    cout << "--------SELECT AN EXPERT--------\n";
    int choice = getChoice(experts);

    // If user selects auto-assign option
    if (choice == 4) {
        int assignedExpert = autoAssignExpert(day, timeslot);  // Use the modified autoAssignExpert to check availability
        if (assignedExpert != -1) {
            cout << "Expert " << EXPERT[assignedExpert] << " has been auto-assigned.\n";
            pauseEnter();
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
int autoAssignExpert(int day, int timeslot) {
    array<string, 3> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
    srand(time(0));

    int availableExperts[3];  // Array to store indices of available experts
    int countAvailable = 0;   // Counter for the number of available experts

    // Check availability of each expert
    for (int i = 0; i < experts.size(); i++) {
        if (checkBookingAvailable(day, timeslot, i)) {
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
        pauseEnter();
        return -1;  // Indicate no expert is available
    }
}

// Customer > Make Booking > Select Service > Select Date > Select Time Slot
int selectDayInWeek(int selectedWeek) {
    newPageLogo();
    array<string, 5> weekdays = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };
    int maxDayInWeek = 7; // Default maximum days in a week

    // If it's the 5th week, only allow Days 29 and 30
    if (selectedWeek == 5) {
        weekdays = { "Monday", "Tuesday" };
        maxDayInWeek = 2;
    }

    cout << "--------SELECT A DAY IN WEEK " << selectedWeek << "--------\n";
    int choice = getChoice(weekdays);

    // Calculate the actual day
    int day = (selectedWeek - 1) * 7 + choice;
    cout << "Selected date is: " << day << " (" << getDayName(day) << ")\n";
    return day; // Return the selected date
}


// Customer > Make Booking > Select Service > Select Date > Select Time Slot
int selectTimeSlot(int service) {
    newPageLogo();
    array<string, 3> treatmentTimeSlots = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
    array<string, 6> consultTimeSlots = { "Timeslot 1 (10:00AM - 11:00AM)", "Timeslot 2 (11:00AM - 12:00PM)", "Timeslot 3 (2:00PM - 3:00PM)", "Timeslot 4 (3:00PM - 4:00PM)", "Timeslot 5 (4:00PM - 5:00PM)", "Timeslot 6 (5:00PM - 6:00PM)" };

    const string* timeSlots;
    int availableSlots = 0;

    // Select the appropriate time slots based on the service
    if (service == 3) { // Consultation service
        cout << "--------SELECT A TIME SLOT (Consultation)--------\n";
        timeSlots = consultTimeSlots.data();  // Point to consultation time slots
        availableSlots = static_cast<int>(consultTimeSlots.size());
    }
    else {
        cout << "--------SELECT A TIME SLOT--------\n";
        timeSlots = treatmentTimeSlots.data();  // Point to regular time slots
        availableSlots = static_cast<int>(treatmentTimeSlots.size());
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

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    return choice - 1;
}

// Customer > Make Booking > Select Service > Select Date > Select Time Slot > Select Payment Mode
int selectPaymentMode() {
    newPageLogo();
    array<string, 3> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    cout << "--------SELECT A PAYMENT MODE--------\n";
    int choice = getChoice(paymentModes);
    return choice - 1;
}

// Customer > Make Booking
void makeBooking(string username, string currentPassword) {
    int service, expert, week, day, timeSlot, paymentMode;

    // Use the username as the customer name
    string customerName = username;

    service = selectService();       // Choose a service
    if (service == -1) { // Error in selecting service
        cout << "Error in selecting service. Returning to customer page.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    week = selectWeek();             // Choose a week
    day = selectDayInWeek(week);     // Choose a specific day in that week

    // Validate the day
    if (day > MAX_DAYS) {
        cout << "Invalid day selected. Returning to customer page.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    timeSlot = selectTimeSlot(service); // Choose a time slot

    bool isConsultation = (service == 3); // Check if it's a consultation

    expert = selectExpert(day, timeSlot); // Select expert
    if (expert == -1) {
        // If no available expert, return to customer page
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    paymentMode = selectPaymentMode(); // Choose payment method

    bool available = checkBookingAvailable(day, timeSlot, expert);

    if (available) {
        char confirm;
        cout << "Booking Summary:\n";
        cout << "\nUsername:\t" << customerName;
        cout << "\nDay:\t\t" << formatDate(day); // Updated Line
        if (isConsultation) {
            cout << "\nTime Slot:\t" << TIMESLOT_CONSULT[timeSlot];
        }
        else {
            cout << "\nTime Slot:\t" << TREATMENT_TIMESLOT[timeSlot];
        }

        cout << "\nService:\t" << SERVICE[service];
        cout << "\nExpert:\t\t" << EXPERT[expert];
        cout << "\nCost:\t\tRM " << fixed << setprecision(2) << COST[service];
        cout << "\nPayment Method:\t" << PAYMENTMODE[paymentMode];
        cout << "\n\nConfirm your booking (Y/N): ";
        cin >> confirm;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        if (confirm == 'Y' || confirm == 'y') {
            bookingType newBooking = { customerName, day, timeSlot, expert, service, COST[service], paymentMode };
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
    string serviceNames[] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation" };
    double servicePrices[] = { 25.00, 15.00, 80.00, 15.00 };

    // Write the receipt header and details
    receiptFile << "==================================================================\n";
    receiptFile << "||                    Haven Salon - Receipt                     ||\n";
    receiptFile << "==================================================================\n";
    receiptFile << "Customer Name\t\t: " << booking.customerName << endl;
    receiptFile << "Date\t\t\t: " << formatDate(booking.day) << endl; // Updated Line

    // Check if the service is a consultation and adjust the time slot accordingly
    if (booking.service == 3) {  // Styling Consultation (1-hour slots)
        receiptFile << "Time\t\t\t: " << TIMESLOT_CONSULT[booking.timeslot] << endl;
    }
    else {  // Other services (2-hour slots)
        receiptFile << "Time\t\t\t: " << TREATMENT_TIMESLOT[booking.timeslot] << endl;
    }

    receiptFile << "Expert\t\t\t: " << EXPERT[booking.expert] << endl;
    receiptFile << "Service\t\t\t: " << serviceNames[booking.service] << endl;
    receiptFile << "Cost\t\t\t: RM " << fixed << setprecision(2) << servicePrices[booking.service] << endl;
    receiptFile << "Payment Method\t\t: " << PAYMENTMODE[booking.payment_mode] << endl;
    receiptFile << "==================================================================\n";
    receiptFile << "||                Thank you for choosing Haven Salon!          ||\n";
    receiptFile << "==================================================================\n\n";  // Add extra newlines to separate receipts

    receiptFile.close();  // Close the file after appending the receipt

    cout << "Receipt has been saved to 'receipt.txt'.\n";
}


// ADMIN LOGIN
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

// ADMIN INTERFACE
void adminPage(string username) {
    char option;
    newPageLogo();
    cout << "--------ADMIN HOMEPAGE--------\n";
    cout << "Welcome " << username << endl;
    cout << "Please choose your option.\n";

    cout << "A\t: View Customer Bookings\n";
    cout << "B\t: View Sales Record\n";
    cout << "C\t: View Expert Booking Slot\n";
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
        viewBookingSlot(username);
        break;
    case 'D': case 'd':
        newPageLogo();
        viewFeedbackForm(username);
        break;
    case 'E': case 'e':
        adminLogout(username);
        break;
    default:
        cout << "\nInvalid option, Please try again!\n";
        pauseEnter();
        adminPage(username); // Return to admin page for a retry
    }
}

// Admin > View Customer Bookings
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
    cout << setw(4) << left << "No"
        << setw(20) << left << "Customer Name"
        << setw(15) << left << "Day" // Adjusted Width
        << setw(25) << left << "Time Slot"
        << setw(20) << left << "Expert"
        << setw(20) << left << "Service"
        << setw(10) << left << "Cost(RM)"
        << setw(15) << left << "Payment Mode" << endl;
    cout << "==========================================================================================================================================\n";

    // Loop through the bookings array and display each booking
    for (int i = 0; i < lenBookings; i++) {
        cout << setw(4) << left << i + 1
            << setw(20) << left << bookingsArray[i].customerName  // Display the customer name
            << setw(15) << left << formatDate(bookingsArray[i].day); // Updated Line

        // Check if the service is a consultation or a treatment
        if (bookingsArray[i].service == 3) {  // Styling Consultation (1-hour slots)
            cout << setw(25) << left << TIMESLOT_CONSULT[bookingsArray[i].timeslot];  // Display consultation time slot
        }
        else {  // Other services (2-hour slots)
            cout << setw(25) << left << TREATMENT_TIMESLOT[bookingsArray[i].timeslot];  // Display treatment time slot
        }

        cout << setw(20) << left << EXPERT[bookingsArray[i].expert]
            << setw(20) << left << SERVICE[bookingsArray[i].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;
    }

    if (lenBookings == 0) {
        cout << "No customer bookings found.\n";
    }

    cout << "==========================================================================================================================================\n";
    cout << "Press Enter to return:\t";
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

        cout << left << setw(10) << bookingsArray[i].day
            << setw(25) << SERVICE[bookingsArray[i].service]
            << setw(15) << fixed << setprecision(2) << bookingsArray[i].cost << endl;
    }

    cout << "==============================================\n";
    cout << "Total Sales: RM " << fixed << setprecision(2) << totalSales << endl;

    cout << "\nPress enter to return:\t";
    pauseEnter();
    adminPage(username);
}

// Admin > View Expert Booking Slot
void viewBookingSlot(string username) {
    newPageLogo();

    // Read booking data
    int lenBookings = 0;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr || lenBookings == 0) {
        cout << "No bookings available or file error.\n";
        pauseEnter();
        adminPage(username);
        return;
    }

    cout << "=====================================================================================================================================\n";
    cout << setw(10) << left << "DAY"
        << setw(15) << "EXPERT"
        << setw(18) << "10:00AM-11:00AM"
        << setw(18) << "11:00AM-12:00PM"
        << setw(18) << "2:00PM-3:00PM"
        << setw(18) << "3:00PM-4:00PM"
        << setw(18) << "4:00PM-5:00PM"
        << setw(18) << "5:00PM-6:00PM" << endl;
    cout << "=====================================================================================================================================\n";

    for (int day = 1; day <= 30; day++) {  // Loop through all the days (1-30)
        if (isWeekend(day)) {
            continue;  // Skip weekends
        }

        for (int i = 0; i < 3; i++) {  // 3 experts per day
            cout << setw(10) << left << (i == 0 ? formatDate(day) : "")  // Print day for the first expert only
                << setw(15) << EXPERT[i];  // Print expert name

            for (int k = 0; k < 6; k++) {  // 6 time slots per day
                bool isBooked = false;

                // Check if the current expert has a booking for this time slot
                for (int b = 0; b < lenBookings; b++) {
                    if (bookingsArray[b].expert == i && bookingsArray[b].day == day && bookingsArray[b].timeslot == k) {
                        isBooked = true;
                        break;
                    }
                }

                // Output the booking status for the current expert and time slot
                if (isBooked) {
                    cout << RED << setw(18) << "B" << RESET;
                }
                else {
                    cout << GREEN << setw(18) << "A" << RESET;
                }
            }

            cout << endl;
        }

        // Add a separator between different days
        cout << "-------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    cout << GREEN << "A = AVAILABLE\t" << RED << "B = BOOKED\n" << RESET;
    cout << "Press Enter to return:\t";
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





