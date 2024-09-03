#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <conio.h>
using namespace std;

// Function prototypes
void newPageLogo();
void pauseEnter();
void mainMenu();
void aboutUs();
void regisPage();
void customerLogin();
void customerPage();
void adminLogin();
void viewServiceExpert();

// Global variables & constants (if any)
#define FILE_USER "users.dat"
#define FILE_SCHEDULE "schedule.dat"

struct userType {
    int id = 0;
    string username = "";
    string password = "";
    bool admin = 0;
};

void newPageLogo() {
    // Create a new page by clearing the screen and displaying a logo on top
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

void pauseEnter() {
    char pause;
    cin.get(pause); // Pause by prompting an input (use string & getline in case user typed in anything)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Ignore all characters up to the newline
}

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
    cout << "C\t: Admin Login\n";
    cout << "D\t: Exit\n\n";

    cout << "Enter your choice:\t";
    cin >> option;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // Ignore all characters up to the newline

    switch (option) {
    case 'A': case 'a':
        aboutUs();
        break;
    case 'B': case 'b':
        customerLogin();
        break;
    case 'C': case 'c':
        adminLogin();
        break;
    case 'D': case 'd':
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        mainMenu(); // Return to main menu for a retry
    }
}

void aboutUs() {
    newPageLogo();
    // About Us Page
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

void customerLogin() {
    newPageLogo();
    string inputUsername="", inputPassword="";
    cout << "Enter your username:\t";
    getline(cin, inputUsername);
    cout << "\nEnter your password:\t";
    char ch;
    ch = _getch();
    while (ch != 13) {//character 13 is enter
        inputPassword.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    const string filename = "users.dat";
    userType users[100];

    ifstream infile(filename);
    if (!infile) {
        cout << "File could not be opened!" << endl;
        return;
    }

    string record;
    int counter = 0;
    while (getline(infile, record)) {
        stringstream ss(record);
        string id, username, password, status;
        userType user;

        getline(ss, id, ',');
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, status, ',');

        user.id = stoi(id);
        user.username = username;
        user.password = password;
        user.admin = stoi(status);

        users[counter] = user;
        counter++;
    }
    infile.close();

    //for (int i = 0; i < counter; i++) {
        //cout << "User " << i + 1 << ":\n";
        //cout << "ID: " << users[i].id << endl;
        //cout << "Username: " << users[i].username << endl;
        //cout << "Password: " << users[i].password << endl;
        //cout << "Admin: " << users[i].admin << endl << endl;
    //}
    bool recordFound = 0;
    for (int i = 0; i < counter; i++) {
        if (inputUsername == users[i].username && inputPassword == users[i].password) {
            recordFound = 1;
            break;
        }
    }

    if (recordFound) {
        cout << "\n\nAccess granted";
    }
    else {
        cout << "\n\nAccess denied";
    }

}

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
        viewServiceExpert();
        break;
    case 'B': case 'b':
        cout << "You chose an option of Make Bookings\n";
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

void viewServiceExpert() {
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
        viewServiceExpert(); // Return to customer login for a retry
        break;
    case 'B': case 'b':
        newPageLogo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Press enter to return\t";
        pauseEnter();
        viewServiceExpert(); // Return to customer login for a retry
        break;
    case 'C': case 'c':
        customerPage();
        break;
    default:
        cout << "\nInvalid option, Please try again!\nPress enter to continue\t";
        pauseEnter();
        viewServiceExpert();
    }
}

void adminLogin() {
    newPageLogo();
    cout << "ADMIN LOGIN";
}

int main() {
    mainMenu(); // Start the menu
    return 0;
}