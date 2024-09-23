#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <array>
#include <conio.h>
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define CENTER cout << "\t\t\t\t\t\t\t"

using namespace std;

// Structure definition
struct userType {
    string username = "";
    string password = "";
    bool admin = 0;
};

struct bookingType {
    string customerName;
    int day = 0;  // Represents the day of the month
    int timeslot = 0; // Index of TIMESLOT[]
    int expert = 0; // Index of EXPERT[]
    int service = 0; // Index of SERVICE[]
    double cost = 0.0; // Cost of the service
    int payment_mode = 0; // Index of PAYMENTMODE[]
};

// FUNCTION PROTOTYPES------------------------------------------------------------------------------------------------------------------------------------------------------
void newPageLogo();
void pauseEnter();

void mainMenu();
void aboutUsPage();

void customerRegistration();
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
int selectExpert(int day, int timeslot, int service);
void printCalendar();
int selectDate();
int selectTimeSlot(int service);
int selectPaymentMode();
int autoAssignExpert(int day, int timeslot, int hour);
void generateReceipt(const bookingType& booking);
void displayBookingSummary(const bookingType& booking);

void printSchedule();
void adminLogin();
void adminPage(string username);
void adminLogout(string username);
void viewCustomerBookings(string username);
void viewSalesRecord(string username);
void viewBookingSlot(string username);
void viewFeedbackForm(string username);

// GLOBAL CONSTANT------------------------------------------------------------------------------------------------------------------------------------------------------
const string FILE_USERS = "users.dat";
const string FILE_BOOKINGS = "bookings.dat";
const string TREATMENT_TIMESLOT[3] = { "10:00AM - 12:00PM", "2:00PM - 4:00PM","4:00PM - 6:00PM" };
const string TIMESLOT_CONSULT[6] = { "10:00AM - 11:00AM", "11:00AM - 12:00PM", "2:00PM - 3:00PM", "3:00PM - 4:00PM" , "4:00PM - 5:00PM", "5:00PM - 6:00PM" };
const string HOURS[9] = { "10:00AM", "11:00AM", "12:00PM", " 1:00PM", " 2:00PM", " 3:00PM", " 4:00PM", " 5:00PM", " 6:00PM", };
const string EXPERT[3] = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
const string SERVICE[4] = { "Hair Cut", "Hair Wash", "Hair Dying", "Styling Consultation" };
const int DURATION[4] = { 2,2,2,1 };
const string PAYMENTMODE[3] = { "Credit Card", "Debit Card", "Cash" };
const double COST[4] = { 25.00, 15.00, 80.00, 15.00 };
const string MONTH = "10/2024";
const int MAX_DAYS = 31; // Supports up to 31 days
const int FIRST_MONDAY = -1;   // 29 Sep is Monday, 1 day before 1 Oct, hence 1-1=0

// Helper Functions
int getDayOfWeek(int day) {
    return ((day - FIRST_MONDAY - 1) % 7) + 1;
}


// Checks if a given day is a weekend (Saturday or Sunday)
bool isWeekend(int day) {
    int dayOfWeek = getDayOfWeek(day);
    return (dayOfWeek == 6 || dayOfWeek == 7); // 6: Saturday, 7: Sunday
}

// Function to get the day name from day number
string getDayName(int day) {
    // Assuming day 1 is Monday
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

string getPasswordInput() {
    string password;
    char ch;

    while (true) {
        ch = _getch();
        if (ch == 13) {
            break;
        }
        else if (ch == 8) {
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
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
    cout << "\t\t  =======================================================================================================\n";
    cout << "\t\t  ||" << YELLOW << "##     ##    ###   " << RESET << BLUE << " ##     ##  #######  ##    ## " << RESET << RED  "    ######     ###    " << RESET << GREEN"##        #######  ##    ## " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "##     ##   ## ##  " << RESET << BLUE << " ##     ##  ##       ###   ## " << RESET << RED  "   ##    ##   ## ##   " << RESET << GREEN"##       ##     ## ###   ## " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "##     ##  ##   ## " << RESET << BLUE << " ##     ##  ##       ####  ## " << RESET << RED  "   ##        ##   ##  " << RESET << GREEN"##       ##     ## ####  ## " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "######### ##     ##" << RESET << BLUE << " ##     ##  ######   ## ## ## " << RESET << RED  "    ######  ##     ## " << RESET << GREEN"##       ##     ## ## ## ## " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "##     ## #########" << RESET << BLUE << "  ##   ##   ##       ##  #### " << RESET << RED  "         ## ######### " << RESET << GREEN"##       ##     ## ##  #### " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "##     ## ##     ##" << RESET << BLUE << "   ## ##    ##       ##   ### " << RESET << RED  "   ##    ## ##     ## " << RESET << GREEN"##       ##     ## ##   ### " << RESET "||\n";
    cout << "\t\t  ||" << YELLOW << "##     ## ##     ##" << RESET << BLUE << "    ###     #######  ##    ## " << RESET << RED  "    ######  ##     ## " << RESET << GREEN"########  #######  ##    ## " << RESET "||\n";
    cout << "\t\t  =======================================================================================================\n\n";

    // Reset to default color
    cout << RESET;
}

// Pause by prompting an input (use string & getline in case user typed in anything)
void pauseEnter() {
    cout << YELLOW << "\t\tPress Enter to continue..." << RESET;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// MAIN MENU PAGE
void mainMenu() {
    // First Interface
    char option;
    newPageLogo();
    cout << CYAN << "\t\t-------------------------------------------------MAIN MENU------------------------------------------------\n\n" << RESET << endl;
    CENTER << "WELCOME TO HAVEN SALON\n";
    CENTER << "Please choose your option.\n\n";
    // Main Menu options
    CENTER << "A\t: About Us\n";
    CENTER << "B\t: Customer Registration\n";
    CENTER << "C\t: Customer Login\n";
    CENTER << "D\t: Admin Login\n";
    CENTER << "E\t: Exit\n\n";
    CENTER << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Ignore all characters up to the newline

    switch (option) {
    case 'A': case 'a':
        aboutUsPage();
        break;
    case 'B': case 'b':
        customerRegistration();
        break;
    case 'C': case 'c':
        customerLogin();
        break;
    case 'D': case 'd':
        adminLogin();
        break;
    case 'E': case 'e':
        exit(0);
        break;
    default:
        cout << RED << "\t\tInvalid option, Please try again!\n" << RESET;
        pauseEnter();
        mainMenu(); // Return to main menu for a retry
    }
}

// ABOUT US PAGE
void aboutUsPage() {
    newPageLogo();
    cout << CYAN << "\t\t-------------------------------------------------ABOUT US-------------------------------------------------\n" << RESET;

    ifstream aboutUsFile("aboutUs.txt");

    if (!aboutUsFile) {
        cout << RED << "\t\tError: Could not open aboutUs.txt" << endl;
        pauseEnter();
        mainMenu();
    }

    // Read and display the file content
    string line;
    cout << MAGENTA;
    while (getline(aboutUsFile, line)) {
        cout << "\t\t" << line << endl;
    }
    cout << RESET;

    // Close the file
    aboutUsFile.close();
    cout << "\n";
    pauseEnter();
    mainMenu();
}

// USERS FILE
// Check if username is available during registration
bool checkUsernameAvailable(string username) {
    userType users[100];

    ifstream infile(FILE_USERS);
    if (!infile) {
        cout << RED << "\t\t\n\nUnable to access user data currently.\n";
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
        cout << RED << "\t\tSorry, an error occurred while opening the file.";
        return;
    }

    // Write the new user's data to the file
    outFile << record << "\n";  // Add a newline after the record
    outFile.close();
}

// CUSTOMERS REGISTER
void customerRegistration() {
    newPageLogo();
    // Registration loop
    bool loop = true;
    do {
        newPageLogo();
        string inputUsername = "", inputPassword = "", inputPassword2;
        cout << CYAN << "\t\t------------------------------------------CUSTOMER REGISTRATION------------------------------------------\n\n" << RESET;
        cout << "\t\t\tEnter a new username:\t";
        getline(cin, inputUsername);
        cout << "\n\t\t\tEnter a new password:\t";
        inputPassword = getPasswordInput();
        cout << "\n\t\t\tEnter the new password again:\t";
        inputPassword2 = getPasswordInput();

        if (checkUsernameAvailable(inputUsername)) {
            if (isValidUsername(inputUsername)) {
                if (isValidPassword(inputPassword)) {
                    if (inputPassword == inputPassword2) {
                        userType new_user = { inputUsername, inputPassword };
                        addNewUserToFile(new_user);
                        cout << GREEN << "\n\n\t\tRegistered successfully\n";
                        pauseEnter();
                        customerPage(inputUsername, inputPassword);
                        return;
                    }
                    else {
                        char option;
                        cout << RED << "\n\n\t\tBoth passwords do not match\n" << RESET << "\t\tDo you wish to continue? (Y/N):\t";
                        cin >> option;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        loop = (toupper(option) == 'Y');
                    }
                }
                else {
                    char option;
                    cout << RED << "\n\n\t\tPassword length must be between 8 and 16 characters\n" << RESET << "\t\tDo you wish to continue? (Y/N):\t";
                    cin >> option;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    loop = (toupper(option) == 'Y');
                }
            }
            else {
                char option;
                cout << RED << "\n\n\t\tUsername must be between 5 and 20 characters and can only contain letters and numbers\n" << RESET << "\t\tDo you wish to continue ? (Y / N) : \t";
                cin >> option;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                loop = (toupper(option) == 'Y');
            }
        }
        else {
            char option;
            cout << RED << "\n\n\t\tUsername taken\n\t\t" << RESET << "Do you wish to continue ? (Y / N) : \t";
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
        cout << RED << "\n\n\t\tUnable to login currently due to system error\n";
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
        cout << CYAN << "\t\t---------------------------------------------CUSTOMER LOGIN----------------------------------------------\n\n" << RESET;
        cout << "\t\t\tEnter your username:\t";
        getline(cin, inputUsername);
        cout << "\n\t\t\tEnter your password:\t";
        inputPassword = getPasswordInput();

        // Check if username and password are in the record
        for (int i = 0; i < counter; i++) {
            if (inputUsername == users[i].username && inputPassword == users[i].password) {
                recordFound = true;
                currentPassword = inputPassword;  // Store the correct password
                break;
            }
        }
        if (recordFound) {
            cout << GREEN << "\n\n\t\tAccess granted\n";
            pauseEnter();
            customerPage(inputUsername, currentPassword); // Pass username and password to the customer page
            return;
        }
        else {
            char option;
            cout << RED << "\n\n\t\tAccess denied\n" << RESET << "\t\tDo you wish to retry ? (Y / N) : \t";
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
        cout << RED << "\n\n\t\tUnable to access booking data currently.\n";
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

            // Check the duration of the service, (1 or 2 hour)
            if (DURATION[bookingsArray[i].service] == 2) {
                // If 2 hours, check the second hour
                if (bookingsArray[i].timeslot == (timeslot - 1)) {
                    return false;
                }
            }

            // By default, the starting hour is not available
            if ((bookingsArray[i].timeslot) == timeslot) {
                return false;
            }

        }
    }
    return true;  // No conflict found, the slot is available
}


// Save the booking information to file
void saveBookingToFile(bookingType newBooking) {
    ofstream outFile(FILE_BOOKINGS, ios::app);

    if (!outFile) {
        cout << RED << "\t\tSorry, an error occurred while saving the booking.";
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
    cout << CYAN << "\t\t--------------------------------------------CUSTOMER HOMEPAGE--------------------------------------------\n\n" << RESET;
    CENTER << "Welcome " << username << endl;
    CENTER << "Please choose your option.\n";

    CENTER << "A\t: View Service and Expert\n";
    CENTER << "B\t: View Available Time Slots\n";
    CENTER << "C\t: Make Booking\n";
    CENTER << "D\t: My Bookings\n";
    CENTER << "E\t: Feedback Form\n";
    CENTER << "F\t: Log Out and Return to Main Menu\n\n";

    CENTER << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        newPageLogo();

        // Display Services 
        cout << CYAN << "\t\t-----------------------------------------------OUR SERVICES----------------------------------------------\n\n" << RESET;
        CENTER << setw(30) << left << "Service" << setw(10) << "Price (RM)\n";
        cout << "\t\t----------------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < 4; i++) {
            CENTER << setw(30) << left << SERVICE[i]
                << setw(10) << right << fixed << setprecision(2) << COST[i] << endl;
        }
        cout << "\t\t----------------------------------------------------------------------------------------------------------\n\n";

        // Display Experts 
        cout << CYAN << "\t\t-----------------------------------------------OUR EXPERTS-----------------------------------------------\n\n" << RESET;
        CENTER << setw(10) << left << "Expert Name\n";
        cout << "\t\t----------------------------------------------------------------------------------------------------------\n";
        for (int i = 0; i < 3; i++) {
            CENTER << setw(20) << left << EXPERT[i] << endl;
        }
        cout << "\t\t----------------------------------------------------------------------------------------------------------\n";
        pauseEnter();
        customerPage(username, currentPassword);
        break;
    case 'B': case 'b':
        newPageLogo();
        viewTimeslotAvailable(username, currentPassword);
        break;
    case 'C': case 'c':
        makeBooking(username, currentPassword);
        break;
    case 'D': case 'd':
        mybookingsDetail(username, currentPassword);
        break;
    case 'E': case 'e':
        cout << "\n\t\tDo you wish to write down your feedback? (Y/N):\t";
        cin >> option2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (toupper(option2) == 'Y') {
            feedbackForm(username, currentPassword);
        }
        else {
            customerPage(username, currentPassword);
        }
        break;
    case 'F': case 'f':
        customerLogout(username, currentPassword);
        break;
    default:
        cout << RED << "\t\tInvalid option, Please try again!\n" << RESET;
        pauseEnter();
        customerPage(username, currentPassword); // Return to customer page for a retry
    }
}
// Helper Function to Format Date
string formatDate(int day) {
    return to_string(day) + "/" + MONTH; // Formats as "dd-mm-yyyy"
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
        cout << RED << "\t\tNo bookings available or file error.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    while (true) {
        newPageLogo();
        CENTER << CYAN << "\tMy Bookings\n" << RESET;
        cout << "\t========================================================================================================================\n";
        cout << "\t" << setw(4) << left << "No"
            << setw(15) << left << "Date" // Adjusted Width
            << setw(25) << left << "Time Slot"
            << setw(20) << left << "Expert"
            << setw(20) << left << "Service"
            << setw(10) << left << "Cost(RM)"
            << setw(15) << left << "Payment Mode" << endl;
        cout << "\t========================================================================================================================\n";

        int bookingCount = 0;
        bookingType userBookings[100];
        int bookingIndices[100];  // Indices of user's bookings in bookingsArray

        for (int i = 0; i < lenBookings; i++) {
            if (bookingsArray[i].customerName == username) {
                userBookings[bookingCount] = bookingsArray[i];
                bookingIndices[bookingCount] = i;
                cout << "\t" << setw(4) << left << bookingCount + 1
                    << setw(15) << left << formatDate(bookingsArray[i].day); // Updated Line
                if (bookingsArray[i].service == 3) {  // Styling Consultation (1-hour slots)
                    cout << setw(25) << left << TIMESLOT_CONSULT[bookingsArray[i].timeslot];  // Display consultation time slot
                    }
                else {  // Other services (2-hour slots)
                        cout << setw(25) << left << TREATMENT_TIMESLOT[bookingsArray[i].timeslot / 2];  // Display treatment time slot
                    }

                cout << setw(20) << left << EXPERT[bookingsArray[i].expert]
                    << setw(20) << left << SERVICE[bookingsArray[i].service]
                    << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
                    << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;

                bookingCount++;
            }
        }

        if (bookingCount == 0) {
            cout << RED << "\t\tYou have no bookings.\n" << RESET;
            cout << "\t========================================================================================================================\n";
            pauseEnter();
            customerPage(username, currentPassword);
            return;
        }

        cout << "\t========================================================================================================================\n\n";
        CENTER << "Please choose your option\n";
        CENTER << "A\t: Cancel Booking\n";
        CENTER << "B\t: View Receipt\n";  // Add an option to view the receipt
        CENTER << "C\t: Return to Customer Page\n\n";
        CENTER << "Enter your choice: ";
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
            cout << RED << "\t\tInvalid option, Please try again!\n" << RESET;
            pauseEnter();
        }
    }
}


void cancelBooking(string username, string currentPassword, bookingType* bookingsArray, int lenBookings, int* bookingIndices, int bookingCount) {
    // Authentication with password same as login password
    string inputPassword;
    cout << "\t\tPlease enter your password again to confirm: ";
    inputPassword = getPasswordInput();

    if (inputPassword != currentPassword) {
        cout << RED << "\t\tAuthentication failed. Incorrect password.\n" << RESET;
        pauseEnter();
        return;
    }

    // Display user's booking details
    CENTER << CYAN << "\n\t\tAvailable bookings for cancellation\n" << RESET;
    cout << "\t\t==========================================================================================================\n";
    cout << "\t\t" << setw(4) << left << "No"
        << setw(15) << left << "Date" // Adjusted Width
        << setw(25) << left << "Time Slot"
        << setw(20) << left << "Expert"
        << setw(20) << left << "Service"
        << setw(10) << left << "Cost(RM)"
        << setw(15) << left << "Payment Mode" << endl;
    cout << "\t\t==========================================================================================================\n";
    for (int i = 0; i < bookingCount; i++) {
        int idx = bookingIndices[i];
        cout << "\t\t" << setw(4) << left << i + 1
            << setw(15) << left << formatDate(bookingsArray[i].day)
            << setw(25) << left
            << (bookingsArray[idx].service == 3 ? TIMESLOT_CONSULT[bookingsArray[idx].timeslot] : TREATMENT_TIMESLOT[bookingsArray[idx].timeslot])
            << setw(20) << left << EXPERT[bookingsArray[idx].expert]
            << setw(20) << left << SERVICE[bookingsArray[idx].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[idx].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[idx].payment_mode] << endl;
    }

    if (bookingCount == 0) {
        cout << RED << "\t\tNo active bookings to cancel.\n";
        pauseEnter();
        return;
    }
    cout << "\t\t==========================================================================================================\n\n";

    // Ask customer to cancel booking
    int bookingToCancel = 0;
    cout << "\t\tEnter the number of the booking you want to cancel: ";
    cin >> bookingToCancel;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (bookingToCancel <= 0 || bookingToCancel > bookingCount) {
        cout << RED << "\t\tInvalid selection. Returning to My Bookings page.\n" << RESET;
        pauseEnter();
        return;
    }

    int selectedUserBookingIndex = bookingToCancel - 1;
    int selectedBookingIndex = bookingIndices[selectedUserBookingIndex];

    // Delete cancelled booking from bookings.dat
    ofstream outFile(FILE_BOOKINGS);
    if (!outFile) {
        cout << RED << "\t\tError opening file for writing.\n";
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

    cout << GREEN << "\t\tBooking cancelled successfully.\n";
    pauseEnter();

    // Return and update My Bookings
    mybookingsDetail(username, currentPassword);
}

// Function to view a receipt for a specific booking
void viewReceipt(string username, bookingType* bookingsArray, int* bookingIndices, int bookingCount) {
    int bookingToView;

    // Ask the user to select the booking they want to view the receipt for
    cout << "\n\t\tSelect the booking number to view the receipt (0 to return): ";
    cin >> bookingToView;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (bookingToView == 0 || bookingToView > bookingCount) {
        cout << RED << "\t\tInvalid selection. Returning to bookings page.\n" << RESET;
        pauseEnter();
        return;
    }

    int selectedBookingIndex = bookingIndices[bookingToView - 1];
    const bookingType& booking = bookingsArray[selectedBookingIndex];

    // Display the receipt details on the console
    cout << "\t\t\t\t\t==================================================================\n";
    cout << "\t\t\t\t\t||                    Haven Salon - Receipt                     ||\n";
    cout << "\t\t\t\t\t==================================================================\n";
    cout << "\t\t\t\t\tCustomer Name\t\t: " << booking.customerName << endl;

    // **Modified Line: Use formatDate to display the date properly**
    cout << "\t\t\t\t\tDate\t\t\t: " << formatDate(booking.day) << endl;

    // Check if the service is a consultation and adjust the time slot accordingly
    if (booking.service == 3) {  // Consultation (1-hour slots)
        cout << "\t\t\t\t\tTime\t\t\t: " << TIMESLOT_CONSULT[booking.timeslot] << endl;
    }
    else {  // Other services (2-hour slots)
        cout << "\t\t\t\t\tTime\t\t\t: " << TREATMENT_TIMESLOT[booking.timeslot] << endl;
    }

    cout << "\t\t\t\t\tExpert\t\t\t: " << EXPERT[booking.expert] << endl;
    cout << "\t\t\t\t\tService\t\t\t: " << SERVICE[booking.service] << endl;
    cout << "\t\t\t\t\tCost\t\t\t: RM " << fixed << setprecision(2) << COST[booking.service] << endl;
    cout << "\t\t\t\t\tPayment Method\t\t: " << PAYMENTMODE[booking.payment_mode] << endl;
    cout << "\t\t\t\t\t==================================================================\n";
    cout << "\t\t\t\t\t||                Thank you for choosing Haven Salon!          ||\n";
    cout << "\t\t\t\t\t==================================================================\n\n";

    // Pause after viewing the receipt
    pauseEnter();
}




// Customer > View Time Slot Available (Display available time slots for all experts)
void viewTimeslotAvailable(string username, string currentPassword) {
    printSchedule();
    customerPage(username, currentPassword);
}

void printSchedule() {
    newPageLogo();
    CENTER << CYAN << "AVAILABLE TIME SLOTS FOR " << MONTH << RESET << endl;

    cout << "==========================================================================================================================================\n";
    cout << setw(12) << left << "DAY"
        << setw(18) << "EXPERT"
        << setw(18) << "10:00AM-11:00AM"
        << setw(18) << "11:00AM-12:00PM"
        << setw(18) << "2:00PM-3:00PM"
        << setw(18) << "3:00PM-4:00PM"
        << setw(18) << "4:00PM-5:00PM"
        << setw(18) << "5:00PM-6:00PM" << endl;
    cout << "==========================================================================================================================================\n";

    int counter = 0;
    for (int date = 1; date <= MAX_DAYS; date++) {
        for (int exp = 0; exp < 3; exp++) {
            if (exp == 0) {
                cout << setw(12) << left << formatDate(date);
            }
            else if (exp == 1) {
                cout << setw(12) << left << getDayName(date);
            }
            else {
                cout << "            ";
            }
            cout << setw(18) << left << EXPERT[exp];
            for (int tms = 0; tms < 6; tms++) {
                if (checkBookingAvailable(date, tms, exp)) {
                    cout << GREEN << setw(18) << "A" << RESET;
                }
                else {
                    if (isWeekend(date)) {
                        cout << RED << setw(18) << "C" << RESET;
                    }
                    else {
                        cout << YELLOW << setw(18) << "B" << RESET;
                    }

                }
            }
            cout << endl;
        }
        counter++;
        if (counter == 5) {
            counter = 0;
            pauseEnter();
        }

        cout << "------------------------------------------------------------------------------------------------------------------------------------------\n";
    }

    CENTER << GREEN << "A = AVAILABLE\t" << YELLOW << "B = BOOKED\t" << RED << "C = CLOSED\n\n" << RESET;
    cout << "\n";
    pauseEnter();
}

// Customer > Feedback Form (Allow customers to provide feedback)
void feedbackForm(string username, string currentPassword) {
    newPageLogo();

    ofstream feedbackFile("feedback.dat", ios::app); // Open in append mode

    if (!feedbackFile) {
        cout << RED << "\t\tError: Could not open feedback file.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    string name;
    string feedback;
    cout << CYAN << "--------------------------------------------FEEDBACK FORM--------------------------------------------------\n\n" << RESET;
    cout << "\t\tEnter your name: ";
    getline(cin, name);
    cout << "\t\tPlease enter your feedback: ";
    getline(cin, feedback);  // Get feedback from customer

    // Save feedback to file
    feedbackFile << "Customer Name: " << name << endl;
    feedbackFile << "Feedback: " << feedback << endl;
    feedbackFile << "------------------------------------------------------------------------------------------------------------\n";
    feedbackFile.close();

    cout << "\t\tThank you for your feedback!\n";
    pauseEnter();
    customerPage(username, currentPassword);
}

// Ask confirm logout and go to main menu
void customerLogout(string username, string currentPassword) {
    char confirmLogout = 'Y';
    cout << "\n\t\tDo you wish to log out? (Y/N):\t";
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
        CENTER << i + 1 << ". " << options[i] << endl;
    }
    CENTER << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > options.size()) {
        cout << RED << "\t\tInvalid choice. Please enter a number between 1 and " << options.size() << ": " << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    return choice;
}

// Customer > Make Booking > Select Service
// Customer > Make Booking > Select Service
int selectService() {
    newPageLogo();

    ifstream inFile("services.dat");

    if (!inFile) {
        cerr << RED << "Error: Could not open the services file." << endl;
        return -1;
    }

    string service;
    double price;
    int count = 0;

    // Temporary arrays to hold services and prices
    array<string, 4> services;
    array<double, 4> prices;

    // Display header
    cout << CYAN << "\t\t---------------------------------------------SELECT AN SERVICE-----------------------------------------------\n\n" << RESET;
    CENTER << "------------------------------------------" << endl;
    CENTER << setw(30) << left << "Service" << setw(10) << "Price (RM)" << endl;
    CENTER << "------------------------------------------" << endl;

    // Read services and prices from the file and store them
    while (inFile >> ws && getline(inFile, service, ' ') && inFile >> price && count < 4) {
        services[count] = service;
        prices[count] = price;

        // Display the service and price
        CENTER << setw(30) << left << service << setw(10) << right << fixed << setprecision(2) << price << endl;
        count++;
    }

    inFile.close();
    CENTER << "------------------------------------------" << endl;
    CENTER << "Please select a service you want to book:" << endl;

    // Let the user choose a service
    int choice = getChoice(services);
    return choice - 1;
}

void printCalendar() {
    CENTER << "MON TUE WED THU FRI SAT SUN\n";

    // Assuming each week starts from a specific day (e.g., Monday = 1)
    int currentDay = 1;
    int startDay = getDayOfWeek(currentDay) - 1;

    // Add padding for the start day
    CENTER;
    for (int i = 0; i < startDay; ++i) {
        cout << "    "; // Space for days before the 1st
    }

    // Print all the days of the month
    while (currentDay <= MAX_DAYS) {
        cout << setw(3) << currentDay << " "; // Width to space days out

        startDay++; // Move to the next day
        currentDay++;

        // Start a new line after Sunday (6th index)
        if (startDay % 7 == 0) {
            cout << endl;
            CENTER;
        }
    }
    cout << endl; // Final new line at the end of the calendar
}



// Customer > Make Booking >  Select Date
int selectDate() {
    newPageLogo();
    cout << CYAN << "\t\t---------------------------------------------SELECT A DATE-----------------------------------------------\n\n" << RESET;
    CENTER << "--------SELECT A DAY IN " << MONTH << "--------\n\n";
    printCalendar();  // Print the calendar in the center

    int day;
    // Manually center the input prompt
    do {
        cout << setw(76) << "Enter a day (1-" << MAX_DAYS << "): "; // Ensure it's between 1 and MAX_DAYS (31)
        cin >> day;
        if (cin.fail())
        {
            cin.clear(); cin.ignore(512, '\n');
            day = 999;
        }

        if (day < 1 || day > MAX_DAYS) {
            cout << RED << "\t\tInvalid input! The date should be between 1 and " << MAX_DAYS << ". Please try again.\n"<< RESET;
        }
    } while (day < 1 || day > MAX_DAYS);  // Repeat until the user enters a valid day

    return day;
}

// Customer > Make Booking > Select Timeslot
int selectTimeSlot(int service) {
    newPageLogo();
    array<string, 3> treatmentTimeSlots = { "Timeslot 1 (10:00AM - 12:00PM)", "Timeslot 2 (2:00PM - 4:00PM)", "Timeslot 3 (4:00PM - 6:00PM)" };
    array<string, 6> consultTimeSlots = { "Timeslot 1 (10:00AM - 11:00AM)", "Timeslot 2 (11:00AM - 12:00PM)", "Timeslot 3 (2:00PM - 3:00PM)", "Timeslot 4 (3:00PM - 4:00PM)", "Timeslot 5 (4:00PM - 5:00PM)", "Timeslot 6 (5:00PM - 6:00PM)" };

    const string* timeSlots;
    int availableSlots = 0;

    if (service == 3) { // Consultation service
        CENTER << "--------SELECT A TIME SLOT (Consultation)--------\n";
        timeSlots = consultTimeSlots.data();
        availableSlots = static_cast<int>(consultTimeSlots.size());
    }
    else {
        cout << CYAN << "\t\t---------------------------------------------SELECT A TIMESLOT-----------------------------------------------\n\n" << RESET;
        timeSlots = treatmentTimeSlots.data();
        availableSlots = static_cast<int>(treatmentTimeSlots.size());
    }

    for (int i = 0; i < availableSlots; ++i) {
        CENTER << i + 1 << ". " << timeSlots[i] << endl;
    }

    int choice;
    CENTER << "Enter your choice: ";
    while (!(cin >> choice) || choice < 1 || choice > availableSlots) {
        cout << RED << "\t\tInvalid choice. Please enter a number between 1 and " << availableSlots << ": " << RESET;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (service == 3) { // Consultation service
        return choice - 1;
    }
    else {
        return (choice - 1) * 2;
    }
}

// Customer > Make Booking > Select Expert
int selectExpert(int day, int timeslot, int service) {
    newPageLogo();
    array<string, 4> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };

    cout << CYAN << "\t\t---------------------------------------------SELECT AN EXPERT-----------------------------------------------\n\n" << RESET;
    int choice = getChoice(experts);

    // If user selects auto-assign option
    if (choice == 4) {
        int assignedExpert = autoAssignExpert(day, timeslot, DURATION[service]);  // Use the modified autoAssignExpert to check availability
        if (assignedExpert != -1) {
            cout << "\t\tExpert " << EXPERT[assignedExpert] << " has been auto-assigned.\n";
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

// Customer > Make Booking > Select Expert (random assign expert function)
int autoAssignExpert(int day, int timeslot, int hour) {
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
        cout << RED << "\t\tNo available expert for the selected time slot." << endl;
        pauseEnter();
        return -1;  // Indicate no expert is available
    }
}

// Customer > Make Booking > Select Payment Mode
int selectPaymentMode() {
    newPageLogo();
    array<string, 3> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    cout << CYAN << "\t\t------------------------------------------SELECT A PAYMENT MODE--------------------------------------------\n\n" << RESET;
    int choice = getChoice(paymentModes);
    cout << GREEN << "\n\t\tPayment method selected: " << paymentModes[choice - 1] << RESET << endl;
    return choice - 1;
}

// Customer > Make Booking
void makeBooking(string username, string currentPassword) {
    int service, expert, day, timeSlot, paymentMode;

    // Use the username as the customer name
    string customerName = username;

    // Step 1: Select a service
    service = selectService();
    if (service == -1) {
        cout << RED << "\t\tError in selecting service.\n";
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    // Step 2: Select a date directly (no need for week selection)
    day = selectDate();  // This will let the user pick a day in the month

    // Step 3: Select a time slot based on the selected service
    timeSlot = selectTimeSlot(service);

    // Step 4: Select an expert or auto-assign
    expert = selectExpert(day, timeSlot, service);
    if (expert == -1) {
        pauseEnter();
        customerPage(username, currentPassword);
        return;
    }

    // Step 5: Select payment mode
    paymentMode = selectPaymentMode();

    // Step 6: Check availability and finalize booking
    bool available = checkBookingAvailable(day, timeSlot, expert);

    if (available) {
        // Create a new booking
        bookingType newBooking = { customerName, day, timeSlot, expert, service, COST[service], paymentMode };

        // Display booking summary and confirm
        displayBookingSummary(newBooking);
    }
    else {
        cout << RED << "\t\tSorry, the selected slot is not available.\n";
        pauseEnter();
    }
    customerPage(username, currentPassword);
}


void displayBookingSummary(const bookingType& booking) {
    cout << CYAN << "\n\t\t-----------------------------------------BOOKING SUMMARY---------------------------------------------------\n\n" << RESET;
    CENTER << setw(15) << left << "Username:" << "\t" << booking.customerName << endl;
    CENTER << setw(15) << left << "Day:" << "\t" << formatDate(booking.day) << endl;
    CENTER << setw(15) << left << "Time Slot:" << "\t" << (booking.service == 3 ? TIMESLOT_CONSULT[booking.timeslot] : TREATMENT_TIMESLOT[booking.timeslot/2]) << endl;
    CENTER << setw(15) << left << "Service:" << "\t" << SERVICE[booking.service] << endl;
    CENTER << setw(15) << left << "Expert:" << "\t" << EXPERT[booking.expert] << endl;
    CENTER << setw(15) << left << "Cost:" << "\tRM " << fixed << setprecision(2) << COST[booking.service] << endl;
    CENTER << setw(15) << left << "Payment Method:" << "\t" << PAYMENTMODE[booking.payment_mode] << endl;

    cout << CYAN << "\n\t\t-----------------------------------------------------------------------------------------------------------\n" << RESET;

    // Confirm Booking
    char confirm;
    CENTER << "Confirm your booking (Y/N): ";
    cin >> confirm;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    if (toupper(confirm) == 'Y') {
        saveBookingToFile(booking);
        generateReceipt(booking); // Ensure receipt is generated correctly
        cout << GREEN << "\t\tYour booking has been confirmed!\n" << RESET;
        cout << YELLOW << "\t\tReceipt has been saved to 'receipt.txt'.\n" << RESET;
    }
    else {
        cout << RED << "\t\tBooking canceled.\n" << RESET;
    }

    pauseEnter();
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

    cout << "\t\tReceipt has been saved to 'receipt.txt'.\n";
}


// ADMIN LOGIN
void adminLogin() {
    bool loop = true;
    do {
        newPageLogo();
        cout << CYAN << "\n\t\t----------------------------------------------ADMIN LOGIN---------------------------------------------------\n" << RESET;
        string inputUsername = "", inputPassword = "";
        cout << "\n\t\t\tEnter your username:\t";
        getline(cin, inputUsername);
        cout << "\n\t\t\tEnter your password:\t";
        inputPassword = getPasswordInput();

        if (inputUsername == "havensadmin" && inputPassword == "haven1234") {
            cout << GREEN << "\n\n\t\tAccess granted\n";
            loop = false;
            pauseEnter();
            adminPage(inputUsername);
            return;
        }
        else {
            char option;
            cout << RED << "\n\n\t\tAccess denied\n" << RESET << "\t\tDo you wish to retry? (Y/N):\t";
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
    cout << CYAN << "\t\t------------------------------------------ADMIN HOMEPAGE--------------------------------------------------\n\n" << RESET;
    CENTER << "Welcome " << username << endl;
    CENTER << "Please choose your option.\n";

    CENTER << "A\t: View Customer Bookings\n";
    CENTER << "B\t: View Sales Record\n";
    CENTER << "C\t: View Expert Booking Slot\n";
    CENTER << "D\t: View Feedback Form\n";
    CENTER << "E\t: Log Out and Return to Main Menu\n\n";

    CENTER << "Enter your choice:\t";
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
        cout << endl;
        cout << RED << "\t\tInvalid option, Please try again!\n" << RESET;
        pauseEnter();
        adminPage(username); // Return to admin page for a retry
    }
}

// Admin > View Customer Bookings
void viewCustomerBookings(string username) {
    newPageLogo();
    char option;
    char option2;

    int lenBookings = 0;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr) {
        cout << RED << "\t\tNo customer bookings available (file error or empty).\n";
        pauseEnter();
        return;
    }

    // Display table headers
    CENTER << CYAN << "VIEW CUSTOMER BOOKINGS\n" << RESET;
    cout << "\t==========================================================================================================================================\n";
    cout << "\t" << setw(4) << left << "No"
        << setw(20) << left << "Customer Name"
        << setw(15) << left << "Date" // Adjusted Width
        << setw(25) << left << "Time Slot"
        << setw(20) << left << "Expert"
        << setw(22) << left << "Service"
        << setw(10) << left << "Cost(RM)"
        << setw(15) << left << "Payment Mode" << endl;
    cout << "\t==========================================================================================================================================\n";

    // Loop through the bookings array and display each booking
    for (int i = 0; i < lenBookings; i++) {
        cout << "\t" << setw(4) << left << i + 1
            << setw(20) << left << bookingsArray[i].customerName  // Display the customer name
            << setw(15) << left << formatDate(bookingsArray[i].day); // Updated Line

        // Check if the service is a consultation or a treatment
        if (bookingsArray[i].service == 3) {  // Styling Consultation (1-hour slots)
            cout << setw(25) << left << TIMESLOT_CONSULT[bookingsArray[i].timeslot];  // Display consultation time slot
        }
        else {  // Other services (2-hour slots)
            cout << setw(25) << left << TREATMENT_TIMESLOT[bookingsArray[i].timeslot/2];  // Display treatment time slot
        }

        cout << setw(20) << left << EXPERT[bookingsArray[i].expert]
            << setw(22) << left << SERVICE[bookingsArray[i].service]
            << setw(10) << left << fixed << setprecision(2) << bookingsArray[i].cost
            << setw(15) << left << PAYMENTMODE[bookingsArray[i].payment_mode] << endl;
    }

    if (lenBookings == 0) {
        cout << RED << "\tNo customer bookings found.\n" << RESET;
    }

    cout << "\t==========================================================================================================================================\n\n";
    pauseEnter();
    adminPage(username);

}

// Admin > View Sales Record
void viewSalesRecord(string username) {
    newPageLogo();

    int lenBookings;
    bookingType* bookingsArray = readBookingsFile(lenBookings);

    if (bookingsArray == nullptr || lenBookings == 0) {
        cout << RED << "\t\tError: Could not retrieve booking data." << endl;
        pauseEnter();
        return;
    }

    double totalSales = 0;
    CENTER << CYAN << "\tSALES RECORD FOR " << MONTH << RESET << endl;
    CENTER << "==============================================\n";
    CENTER << left << setw(10) << "Date" << setw(25) << "Service" << setw(15) << "Cost (RM)" << endl;
    CENTER << "==============================================\n";

    // Loop through all bookings and calculate total sales
    for (int i = 0; i < lenBookings; i++) {
        totalSales += bookingsArray[i].cost;

        CENTER << left << setw(10) << formatDate(bookingsArray[i].day)
            << setw(25) << SERVICE[bookingsArray[i].service]
            << setw(15) << fixed << setprecision(2) << bookingsArray[i].cost << endl;
    }

    CENTER << "==============================================\n";
    CENTER << "Total Sales: RM " << fixed << setprecision(2) << totalSales << endl;
    cout << "\n";
    pauseEnter();
    adminPage(username);
}

// Admin > View Expert Booking Slot
void viewBookingSlot(string username) {
    printSchedule();
    adminPage(username);
}


// Admin > View Feedback (Reads and displays all feedback entries)
void viewFeedbackForm(string username) {
    newPageLogo();

    ifstream feedbackFile("feedback.dat");

    if (!feedbackFile) {
        cout << RED << "\t\tError: Could not open feedback file.\n";
        pauseEnter();
        adminPage(username);
        return;
    }

    string line;
    cout << CYAN << "\t\t---------------------------------------------FEEDBACK ENTRIES---------------------------------------------\n\n" << RESET;

    bool feedbackExists = false;

    while (getline(feedbackFile, line)) {
        cout << "\t\t" << line << endl;  // Display each line from the feedback file
        feedbackExists = true;
    }

    feedbackFile.close();

    if (!feedbackExists) {
        cout << RED << "\t\tNo feedback available.\n";
    }
    pauseEnter();
    adminPage(username);
}

// Ask confirm logout and go to main menu
void adminLogout(string username) {
    char confirmLogout = 'Y';
    cout << "\n\t\tDo you wish to log out? (Y/N):\t";
    //cin >> confirmLogout;
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
