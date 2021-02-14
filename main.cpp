#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
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

//Sign in - Creation of account
Account insert_account(session&);
//Login - retrive account
Account login_account(session&);

//Display the accounts
//void display_accounts(session&);


//Enter paycheck into db








int main() {

    // Connect to MySQL database
    session sql(mysql, "db=bank_db user=bank_dev1 password=Secure123");

    int choice;
    Account a;

    userMenu();
    cout << "Choice: ";
    //Validation of the input
    choice = Input(choice);

    //First loop
    switch (choice){
        case 1:
            //Sign in
            //Creation of an account
            //Insert to DB
            a = insert_account(sql);
            break;
        case 2:
            //Log in
            //Creation of an account
            //Retrieve from DB
            a = login_account(sql);
            break;
        default:
            cout << "Enter correct choice.";
            exit(0);
    }

    //Main (second) loop
    while(true) {

        mainMenu();
        cout << "Choice: ";
        //Validation of the input
        choice = Input(choice);

        switch (choice) {

            //Done
            case 1:
                a.addPay(sql);
                break;
            //Done
            case 2:
                //display_accounts(sql);
                a.printPaychecks(sql);
                break;

            case 3:
                /*
                 * To Do
                 */
                a.printTotal(sql);
                break;

            case 4:
                a.deletePay(sql);
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

    cin >> choice;

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
Account insert_account(session& sql) {

    string first_name, last_name;
    cout << "\nCreation of an account." << endl;
    cout << "=======================" << endl;

    cout << "Enter your first name: ";
    first_name = Input(first_name);
    cout << "Enter your last name: ";
    last_name = Input(last_name);

    // Insert data into accounts table
    sql << "INSERT INTO accounts(first_name, last_name, Total) VALUES(:fn, :ln, :t)",
            use(first_name, "fn"), use(last_name, "ln"), use(0.0, "t");

    cout << endl << "> Successfully inserted account." << endl << endl;

    int ID_ACC;
    //Select the id of the account in the database
    sql << "SELECT Id_acc FROM accounts ORDER BY Id_acc DESC LIMIT 1", into(ID_ACC);

    //Creation of the account object
    Account a(ID_ACC, first_name, last_name);

    return a;
}

//Creation of an account
Account login_account(session& sql) {

    int ID_ACC;
    double total;
    string first_name, last_name;
    vector<int> v;
    Account a;


    cout << "\nLogin." << endl;
    cout << "=======================" << endl;
    cout << "Enter your account's ID: ";
    ID_ACC = Input(ID_ACC);

    // Retrieve all rows from users table
    soci::rowset<soci::row> rs = (sql.prepare << "SELECT Id_acc FROM accounts");



    // Iterate through the result set
    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const soci::row& r = *it;
         v.push_back(r.get<int>(0));
    }

    if ((find(v.begin(), v.end(), ID_ACC) != v.end()) & (ID_ACC != 0)){
        // Retrieve data from accounts table
        rs = (sql.prepare << "SELECT * FROM accounts WHERE Id_acc = :id", use(ID_ACC, "id"));
        rowset<row>::const_iterator it = rs.begin();
        const row& r = *it;

        ID_ACC = r.get<int>(0);
        first_name = r.get<string>(1);
        last_name = r.get<string>(2);
        total = r.get<double>(3);

        cout << endl << "> Successfully retrieved account." << endl << endl;

        //Creation of the account object on the head
        //with a smart pointer
        unique_ptr<Account> a2(new Account(ID_ACC, first_name, last_name));
        a2->setTotal(total);
        a = *a2;
    }
    else{
        int again;
        cout << endl << "> Account not found." << endl << endl;
        cout << "To Try again press 1, else 0: ";
        cin >> again;

        if(again == 1)
            login_account(sql); //Recursive
        else
            exit(0);
    }
    return a;
}

