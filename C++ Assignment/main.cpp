#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// Function prototypes
void logo();
void mainMenu();
void aboutUs();
void customerLogin();
void viewServiceExpert();
void admin();

void logo() {
    // Logo for beauty service (hair salon)
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

void mainMenu() {
    char option;

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

    switch (option) {
    case 'A': case 'a':
        system("cls"); // Use "clear" on Unix-like systems
        logo();
        aboutUs();
        break;
    case 'B': case 'b':
        system("cls");
        logo();
        customerLogin();
        break;
    case 'C': case 'c':
        system("cls");
        logo();
        cout << "You chose an option of Admin Login\n";
        break;
    case 'D': case 'd':
        exit(0);
    default:
        system("cls");
        logo();
        mainMenu(); // Return to main menu for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

void aboutUs() {
    char returnMenu;

    // Implementation for About Us
    cout << "--------------------------------------------------------------------------ABOUT US--------------------------------------------------------------------------\n";
    cout << "Welcome to Haven Saloon, where we provide a comfortable environment to experience and enjoy high-quality haircut services.\n";
    cout << "Our high-quality services are designed to ensure your satisfaction.\n\n";
    cout << "At Haven Saloon, our team of professional hairstylists has many years of experience and is committed to using the latest sustainable techniques and trends.\n";
    cout << "We are friendly and will listen to your needs to provide personalized advice, offering a range of stylish looks to meet your requirements.\n";
    cout << "Whether it's styling, coloring, or shampooing, we use high-quality products to ensure the best results.\n\n";
    cout << "Experience the warm and friendly atmosphere at Haven Saloon and let us provide you with caring service. We strive to make every visit a relaxing and enjoyable experience.\n\n";
    cout << "Enter M return to the main menu:\t";
    cin >> returnMenu;

    if (returnMenu == 'M' || returnMenu == 'm') {
        system("cls");
        logo();
        mainMenu();
    }
    else {
        system("cls");
        logo();
        aboutUs(); // Return to About Us for a retry
        cout << "Invalid option, Please try again!";
    }
}

void customerLogin() {
    char option;

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

    switch (option) {
    case 'A': case 'a':
        system("cls");
        logo();
        viewServiceExpert();
        break;
    case 'B': case 'b':
        system("cls");
        logo();
        cout << "You chose an option of Make Bookings\n";
        break;
    case 'C': case 'c':
        system("cls");
        logo();
        cout << "You chose an option of My bookings\n";
        break;
    case 'D': case 'd':
        system("cls");
        logo();
        cout << "You chose an option of View Schedule\n";
        break;
    case 'E': case 'e':
        system("cls");
        logo();
        cout << "You chose an option of Feedback Form\n";
        break;
    case 'F': case 'f':
        system("cls");
        logo();
        mainMenu();
        break;
    default:
        system("cls");
        logo();
        customerLogin(); // Return to customer login for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

void viewServiceExpert() {
    char option;
    cout << "--------VIEW SERVICE & EXPERT--------\n";
    cout << "Please choose your option.\n";
    cout << "A\t: View Service\n";
    cout << "B\t: View Expert\n";
    cout << "C\t: Return to Customer Homepage\n";
    cout << "Enter your choice:\t";
    cin >> option;

    switch (option) {
    case 'A': case 'a':
        system("cls");
        logo();
        cout << "--------OUR SERVICE--------\n";
        cout << "1. Hair Cut\n";
        cout << "2. Hair Wash\n";
        cout << "3. Hair Dying\n\n";
        cout << "Enter M return to the MAIN MENU OR enter any key return to VIEW SERVICE & EXPERT:\t";
        char returnMenu;
        cin >> returnMenu;
        if (returnMenu == 'M' || returnMenu == 'm') {
            system("cls");
            logo();
            mainMenu();
        }
        else {
            system("cls");
            logo();
            viewServiceExpert(); // Return to viewServiceExpert for a retry
            cout << "Invalid option, Please try again!";
        }
        break;
    case 'B': case 'b':
        system("cls");
        logo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Enter M return to the MAIN MENU OR enter any key return to VIEW SERVICE & EXPERT:\t";
        cin >> returnMenu;
        if (returnMenu == 'M' || returnMenu == 'm') {
            system("cls");
            logo();
            mainMenu();
        }
        else {
            system("cls");
            logo();
            viewServiceExpert(); // Return to viewServiceExpert for a retry
            cout << "Invalid option, Please try again!";
        }
        break;
    case 'C': case 'c':
        system("cls");
        logo();
        customerLogin();
        break;
    default:
        system("cls");
        logo();
        viewServiceExpert(); // Return to viewServiceExpert for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

void admin() {

}

int main() {
    logo(); // Display the logo
    mainMenu(); // Start the menu
    return 0;
}
