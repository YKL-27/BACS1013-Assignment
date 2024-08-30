#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

// Function prototypes
void logo();
void MainMenu();
void AboutUs();
void customerlogin();
void viewServiceExpert();

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

void MainMenu() {
    char option;

    cout << "--------------------MAIN MENU--------------------\n";
    cout << "WELCOME TO RSD HAIR SALOON\n";
    cout << "Please choose your option.\n\n";
    // Main Menu options
    cout << "A\t: About Us\n";
    cout << "B\t: Customer Login\n";
    cout << "C\t: Admin Login\n";
    cout << "D\t: Exit\n\n";

    cout << "Enter your choice:\t";
    cin >> option;

    switch (option) {
    case 'A':
    case 'a':
        system("cls"); // Use "clear" on Unix-like systems
        logo();
        AboutUs();
        break;
    case 'B':
    case 'b':
        system("cls");
        logo();
        customerlogin();
        break;
    case 'C':
    case 'c':
        system("cls");
        logo();
        cout << "You chose an option of Admin Login\n";
        break;
    case 'D':
    case 'd':
        exit(0);
    default:
        system("cls");
        logo();
        MainMenu(); // Return to main menu for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

void AboutUs() {
    char mainMenu;

    // Implementation for About Us
    cout << "--------------------------------------------------------------------------ABOUT US--------------------------------------------------------------------------\n";
    cout << "Welcome to Haven Saloon, where we provide a comfortable environment to experience and enjoy high-quality haircut services.\n";
    cout << "Our high-quality services are designed to ensure your satisfaction.\n\n";
    cout << "At Haven Saloon, our team of professional hairstylists has many years of experience and is committed to using the latest sustainable techniques and trends.\n";
    cout << "We are friendly and will listen to your needs to provide personalized advice, offering a range of stylish looks to meet your requirements.\n";
    cout << "Whether it's styling, coloring, or shampooing, we use high-quality products to ensure the best results.\n\n";
    cout << "Experience the warm and friendly atmosphere at Haven Saloon and let us provide you with caring service. We strive to make every visit a relaxing and enjoyable experience.\n\n";
    cout << "Enter M return to the main menu:\t";
    cin >> mainMenu;

    if (mainMenu == 'M' || mainMenu == 'm') {
        system("cls");
        logo();
        MainMenu();
    }
    else {
        system("cls");
        logo();
        AboutUs(); // Return to About Us for a retry
        cout << "Invalid option, Please try again!";
    }
}

void customerlogin() {
    char option2;

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
    cin >> option2;

    switch (option2) {
    case 'A':
    case 'a':
        system("cls");
        logo();
        viewServiceExpert();
        break;
    case 'B':
    case 'b':
        system("cls");
        logo();
        cout << "You chose an option of Make Bookings\n";
        break;
    case 'C':
    case 'c':
        system("cls");
        logo();
        cout << "You chose an option of My bookings\n";
        break;
    case 'D':
    case 'd':
        system("cls");
        logo();
        cout << "You chose an option of View Schedule\n";
        break;
    case 'E':
    case 'e':
        system("cls");
        logo();
        cout << "You chose an option of Feedback Form\n";
        break;
    case 'F':
    case 'f':
        system("cls");
        logo();
        MainMenu();
        break;
    default:
        system("cls");
        logo();
        customerlogin(); // Return to customer login for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

void viewServiceExpert() {
    char option3;
    cout << "--------VIEW SERVICE & EXPERT--------\n";
    cout << "Please choose your option.\n";
    cout << "A\t: View Service\n";
    cout << "B\t: View Expert\n";
    cout << "C\t: Return to Customer Homepage\n";
    cout << "Enter your choice:\t";
    cin >> option3;

    switch (option3) {
    case 'A':
    case 'a':
        system("cls");
        logo();
        cout << "--------OUR SERVICE--------\n";
        cout << "1. Hair Cut\n";
        cout << "2. Hair Wash\n";
        cout << "3. Hair Dying\n\n";
        cout << "Enter M return to the MAIN MENU OR enter any key return to VIEW SERVICE & EXPERT:\t";
        char mainMenu;
        cin >> mainMenu;
        if (mainMenu == 'M' || mainMenu == 'm') {
            system("cls");
            logo();
            MainMenu();
        }
        else {
            system("cls");
            logo();
            viewServiceExpert(); // Return to viewServiceExpert for a retry
            cout << "Invalid option, Please try again!";
        }
        break;
    case 'B':
    case 'b':
        system("cls");
        logo();
        cout << "--------OUR EXPERT--------\n";
        cout << "1. Alice Wong\n";
        cout << "2. Bernice Lim\n";
        cout << "3. Catherine Tan\n\n";
        cout << "Enter M return to the MAIN MENU OR enter any key return to VIEW SERVICE & EXPERT:\t";
        char mainMenu2;
        cin >> mainMenu2;
        if (mainMenu2 == 'M' || mainMenu2 == 'm') {
            system("cls");
            logo();
            MainMenu();
        }
        else {
            system("cls");
            logo();
            viewServiceExpert(); // Return to viewServiceExpert for a retry
            cout << "Invalid option, Please try again!";
        }
        break;
    case 'C':
    case 'c':
        system("cls");
        logo();
        customerlogin();
        break;
    default:
        system("cls");
        logo();
        viewServiceExpert(); // Return to viewServiceExpert for a retry
        cout << "Invalid option, Please try again!";
        break;
    }
}

int main() {
    logo(); // Display the logo
    MainMenu(); // Start the menu
    return 0;
}
