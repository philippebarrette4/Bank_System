#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include "./src/Pay.h"
#include "./src/Pay.cpp"
#include "./src/Account.h"
#include "./src/Account.cpp"

using namespace soci;
using std::cin;
using std::cout;
using std::endl;
using std::string;


//Login, Sign in Menu
void userMenu();
//Display the principal menu
void mainMenu();

//Validation function
template <typename T> T Input(T&);

//Creation of the account
Account insert_account(session&, int);
//Display the accounts
void display_accounts(session&);




int main() {

    // Connect to MySQL database
    session sql(mysql, "db=bank_db user=bank_dev1 password=Secure123");


    int Id_acc {0};
    int choice;
    Account a;

    userMenu();
    cout << "Choice: ";
    cin >> choice;
    //Validation of the input
    choice = Input(choice);

    switch (choice){
        case 1:
            //Sign in
            //Creation of an account
            //Insert to DB
            a = insert_account(sql, Id_acc);
            break;
        case 2:
            //Log in, needs DB
            //To do
            break;
        default:
            cout << "Enter correct choice.";
            exit(0);
    }

    //Needs to add an option if the account is already created (when DB working)

    if (0 == a.getId_acc()) return 0;
    while(true) {

        mainMenu();
        cout << "Choice: ";
        cin >> choice;
        //Validation of the input
        choice = Input(choice);

        switch (choice) {

            case 1:
                a.addPay();
                // Insert data into users table
                sql << "UPDATE accounts SET Total = '" << a.getTotal() << "' WHERE Id_acc = 1";
                cout << endl << "> Successfully inserted account." << endl << endl;
                break;

            case 2:
                display_accounts(sql);
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

            default:
                cout << "Enter correct choice.";
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
    cout << "2. Display all paychecks and db." << endl;
    cout << "3. Display cumulative total." << endl;
    cout << "4. Delete a pay." << endl;
    cout << "5. Exit." << endl;
    cout << endl;
}

//Validation function
template <typename T> T Input(T& choice){

    //Check if the value is a int
    while(!cin.good()){
        cout << "Error, please enter a valid choice: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> choice;
    }
    return choice;
}

//Creation of an account
Account insert_account(session& sql, int Id_acc) {

    string first_name, last_name;
    cout << "Creation of an account." << endl;
    cout << "=======================" << endl;
    cout << "Enter your first name: ";
    cin >> first_name;

    first_name = Input(first_name);

    cout << "Enter your last name: ";
    cin >> last_name;

    last_name = Input(last_name);

    Account a(++Id_acc, first_name, last_name);

    // Insert data into users table
    sql << "INSERT INTO accounts(first_name, last_name, Total) VALUES(:fn, :ln, :t)",
            use(first_name, "fn"), use(last_name, "ln"), use(0.0, "t");

    cout << endl << "> Successfully inserted account." << endl << endl;
    return a;
}


//Print accounts informations from dbs
void display_accounts(session& sql) {

    // Retrieve all rows from users table
    rowset<row> rs = (sql.prepare << "SELECT * FROM accounts");

    // Iterate through the result set
    for (rowset<row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const row& r = *it;

        std::cout << "ID: " << r.get<int>(0) << endl
                  << "First Name: " << r.get<string>(1) << endl
                  << "Last Name: " << r.get<string>(2) << endl;
        if (r.get<double>(4) == false){
            cout << "Total: " << "0.0" << endl;
        } else {
            cout << "Total: " << r.get<double>(4) << endl;
        }
    }
}