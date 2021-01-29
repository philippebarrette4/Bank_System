#include <iostream>
#include <iomanip>
#include "./src/Pay.h"
#include "./src/Account.h"
using namespace std;

//Display the principal menu
void Menu();

//User Input
int mainInput();


int main() {


    /*
    int Id_acc{10};
    Account a(Id_acc);


    std::cout << "Hello, World!" << std::endl;
    std::cout << "Account: ";
    std::cout << a.getId_acc() << std::endl;
    a.addPay();
    a.addPay();
    a.addPay();
    std::cout << a.printPaychecks() << std::endl;
    */
    int choice;
    int Id_acc{10};
    Account a(Id_acc);

    while(1) {

        Menu();
        choice = mainInput();

        switch (choice) {
            case 1:
                a.addPay();
                break;

            case 2:
                a.printPaychecks();
                break;

            case 3:
                cout << "Cumulative total: "
                     << a.getTotal() << " $" << endl;
                break;

            case 4:
                exit(0);
        }
    }
    return 0;
}


//Display the principal menu
void Menu(){
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
    cout << "4. Exit." << endl;
    cout << endl;
}

//User Input
int mainInput(){

    int choice;

    cout << "Choice: ";
    cin >> choice;

    //Check if the value is a int
    while(!cin.good() | (choice < 0 | choice > 4)){
        cout << "Error, please enter a valid choice: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> choice;
    }
    cout << endl;
    return choice;
}