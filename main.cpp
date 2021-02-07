#include <iostream>
#include <iomanip>
#include "./src/Pay.h"
#include "./src/Pay.cpp"
#include "./src/Account.h"
#include "./src/Account.cpp"
using namespace std;

//Login, Sign in Menu
void userMenu();

//Display the principal menu
void mainMenu();

//User Input
int Input(int);

//Create an account
Account create_account(int Id_acc);


int main() {

    int Id_acc {0};
    int choice;
    Account a;

    userMenu();
    choice = Input(2);

    switch (choice){
        case 1:
            //Sign in
            //Creation of an account
            a = create_account(Id_acc);
            break;
        case 2:
            //Log in, needs DB
            //To do
            break;
    }

    //Needs to add an option if the account is already created (when DB working)

    if (0 == a.getId_acc()) return 0;
    while(true) {

        mainMenu();
        choice = Input(5);

        switch (choice) {

            case 1:
                a.addPay();
                break;

            case 2:
                a.printPaychecks();
                break;

            case 3:
                a.printTotal();
                break;

            case 4:
                a.deletePay();
                break;

            case 5:
                exit(0);
        }
    }
}


//Login, Sign in Menu
void userMenu(){
    //Header
    cout << "\n===============================\n";
    cout << "|" << setw(30) << "|" << endl;
    cout << "|" << "  Account Management System  " << "|" << endl;
    cout << "|" << setw(30) << "|" << endl;
    cout << "===============================\n\n";

    cout << "Select one of these options:" << endl;
    cout << "1. Sign in." << endl;
    cout << "2. Log in." << endl;
    cout << endl;
}


//Display the principal menu
void mainMenu(){
    //Header
    cout << "\n===============================\n";
    cout << "|" << setw(30) << "|" << endl;
    cout << "|" << "  Account Management System  " << "|" << endl;
    cout << "|" << setw(30) << "|" << endl;
    cout << "===============================\n\n";

    cout << "Select one of these options:" << endl;
    cout << "1. Add a pay." << endl;
    cout << "2. Display all paychecks." << endl;
    cout << "3. Display cumulative total." << endl;
    cout << "4. Delete a pay." << endl;
    cout << "5. Exit." << endl;
    cout << endl;
}

//User Input
int Input(int num){

    int choice;

    cout << "Choice: ";
    cin >> choice;

    //Check if the value is a int
    while(!cin.good() | (choice < 0 | choice > num)){
        cout << "Error, please enter a valid choice: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> choice;
    }
    cout << endl;
    return choice;
}

//Create an account
Account create_account(int Id_acc){

    string name_val;
    cout << "Creation of an account." << endl;
    cout << "=======================" << endl;
    cout << "Enter a name: ";
    cin >> name_val;

    while(!cin.good()){
        cout << "Error, please enter a valid choice: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> name_val;
    }

    Account a(++Id_acc, name_val);

    cout << endl;
    return a;
}