#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
//#include <conio.h>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

// Function prototypes
void newPageLogo();
void pauseEnter();

void mainMenu();
void aboutUsPage();

void registerPage();
bool registerUsernameAvailable(string username);
void customerLogin();

void customerPage();
void adminLogin();
void adminPage();
void serviceExpertPage();

void makeBooking();
string selectService();
string selectExpert();
string selectTimeSlot();
string selectPaymentMode();
int getChoice(const vector<string>& options);
string autoAssignExpert();


// Global variables & constants (if any)
#define FILE_USER "users.dat"
#define FILE_SCHEDULE "schedule.dat"

struct userType {
    string username = "";
    string password = "";
    bool admin = 0;
};

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

// Menu page
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

// About Us Page
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


// FILE READ------------------------------------------------------------------------------------------------------------------------------------------------------
// Check if username met in registration
bool registerUsernameAvailable(string username) {
    userType users[100];

    ifstream infile(FILE_USER);
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

void addNewUserToFile(userType new_user) {
    // Create a record in CSV-like format
    string record = new_user.username + ',' + new_user.password;
    cout << record << endl;  // Display the record for debugging

    ofstream outFile(FILE_USER, ios::app); // Open file in append mode

    if (!outFile) {
        cout << "Sorry, an error occurred while opening the file.";
        return;
    }

    // Write the new user's data to the file
    outFile << record << "\n";  // Add a newline after the record
    outFile.close();
}

// User (customer) Registration Page
void registerPage() {
    newPageLogo();
    // Read file
    bool loop = true;
    do {
        newPageLogo();
        string inputUsername = "", inputPassword = "";
        cout << "Enter a new username:\t";
        getline(cin, inputUsername);
        cout << "\nEnter a new password:\t";
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

        if (registerUsernameAvailable(inputUsername)) {

            userType new_user = {inputUsername, inputPassword};
            addNewUserToFile(new_user);
            cout << "\n\nRegistred successful\nPress enter to continue\t";
            loop = false;
            pauseEnter();
            customerPage();
        }
        else {
            char option;
            cout << "\n\nUsername taken\nDo you wish to continue? (Y/N)\n\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    ifstream infile(FILE_USER);
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


        for (int i = 0; i < counter; i++) {
            cout << endl << users[i].username << "       " << users[i].password;
            if (inputUsername == users[i].username && inputPassword == users[i].password) {
                recordFound = true;
                break;
            }
        }
        if (recordFound) {
            cout << "\n\nAccess granted\nPress enter to continue\t";
            loop = false;
            pauseEnter();
            customerPage();
        }
        else {
            char option;
            cout << "\n\nAccess denied\nDo you wish to continue? (Y/N)\n\t";
            cin >> option;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            loop = (toupper(option) == 'Y') ? true : false;
        }
    } while (loop);
    mainMenu();
}


// CUSTOMER INTERFACE----------------------------------------------------------------------------------------------------------------------------------------------
// Customer Main Page
void customerPage() {
    char option;
    newPageLogo();
    cout << "--------CUSTOMER HOMEPAGE--------\n";
    cout << "Welcome User!\n";
    cout << "Please choose your option.\n";

    cout << "A\t: View Service & Expert\n";
    cout << "B\t: Make Booking\n";
    cout << "C\t: My bookings\n";
    cout << "D\t: View Schedule\n";
    cout << "E\t: Feedback Form\n";
    cout << "F\t: Return to Main Menu\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (option) {
    case 'A': case 'a':
        serviceExpertPage();
        break;
    case 'B': case 'b':
        makeBooking();
        break;
    case 'C': case 'c':
        cout << "You chose an option of My bookings\n";
        break;
    case 'D': case 'd':
        cout << "You chose an option of View Schedule\n";
        break;
    case 'E': case 'e':
        cout << "You chose an option of Feedback Form\n";
        break;
    case 'F': case 'f':
        mainMenu();
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        customerPage(); // Return to customer login for a retry
    }
}

// Customer > view Service & Expert
void serviceExpertPage() {
    char option;
    newPageLogo();
    cout << "--------VIEW SERVICE & EXPERT--------\n";
    cout << "Please choose your option.\n";
    cout << "A\t: View Service\n";
    cout << "B\t: View Expert\n";
    cout << "C\t: Return to Customer Homepage\n";
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
        serviceExpertPage(); // Return to customer login for a retry
        break;
    case 'B': case 'b':
        newPageLogo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Press enter to return\t";
        pauseEnter();
        serviceExpertPage(); // Return to customer login for a retry
        break;
    case 'C': case 'c':
        customerPage();
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        serviceExpertPage();
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
string selectService() {
    newPageLogo();
    vector<string> services = { "Hair Cut", "Hair Wash", "Hair Dying" };
    cout << "--------SELECT A SERVICE--------\n";
    int choice = getChoice(services);
    return services[choice - 1];
}

// Customer > Make Booking > Select Service > Select Expert
string selectExpert() {
    newPageLogo();
    vector<string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan", "Auto-assign" };
    cout << "--------SELECT AN EXPERT--------\n";
    int choice = getChoice(experts);
    if (choice == 4) {
        return autoAssignExpert();
    }
    return experts[choice - 1];
}

// Customer > Make Booking > Select Service > Select Expert (random assign expert function)
string autoAssignExpert() {
    vector<string> experts = { "Alice Wong", "Bernice Lim", "Catherine Tan" };
    srand(time(0));
    int index = rand() % experts.size();
    return experts[index];
}

// Customer > Make Booking > Select Service > Select Expert > Select Time Slot
string selectTimeSlot() {
    newPageLogo();
    vector<string> timeSlots = { "10:00 AM", "12:00 PM", "2:00 PM", "4:00 PM" };
    cout << "--------SELECT A TIME SLOT--------\n";
    int choice = getChoice(timeSlots);
    return timeSlots[choice - 1];
}

// Customer > Make Booking > Select Service > Select Expert > Select Time Slot > Select Payment Mode
string selectPaymentMode() {
    newPageLogo();
    vector<string> paymentModes = { "Credit Card", "Debit Card", "Cash" };
    cout << "--------SELECT A PAYMENT MODE--------\n";
    int choice = getChoice(paymentModes);
    return paymentModes[choice - 1];
}

// Customer > Make Booking
void makeBooking() {
    string service, expert, timeSlot, paymentMode;
    service = selectService();
    expert = selectExpert();
    timeSlot = selectTimeSlot();
    paymentMode = selectPaymentMode();

    //Summary of the booking 
    newPageLogo();
    cout << "--------BOOKING CONFIRMATION--------\n";
    cout << "Service: " << service << endl;
    cout << "Expert: " << expert << endl;
    cout << "Time Slot: " << timeSlot << endl;
    cout << "Payment Mode: " << paymentMode << endl;
    cout << "Confirm your booking (Y/N): ";
    char confirm;
    cin >> confirm;

    //Confirm the booking 
    if (confirm == 'Y' || confirm == 'y') {
        cout << "Your booking has been confirmed!" << endl;
        cout << "Press Enter For going back to customer page...";
    }
    else {
        cout << "Booking canceled." << endl;
        cout << "Press Enter For going back to customer page...";
    }
    pauseEnter();
    customerPage();
}

void adminLogin() {
    newPageLogo();
    cout << "ADMIN LOGIN";
}

int main() {
    mainMenu(); // Start the menu
    return 0;
}


//user.dat (put in the same directory as the cpp file)
/*
yk,123
qx,456
*/


