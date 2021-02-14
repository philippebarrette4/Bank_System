//
// Created by Phil Barrette on 2021-01-27.
//
#include "Account.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

Account::Account()
    :Id_acc{0}, first_name{"NA"}, last_name{"NA"}, Id_pay{0}, total{0.0}, p{}{
}

Account::Account(int Id_val)
    :Id_pay{0}, first_name{"NA"}, last_name{"NA"}, total{0.0}, p{}{
    setId_acc(Id_val);
}

Account::Account(int Id_val ,std::string fn, std::string ln)
    :Id_pay{0}, first_name{fn}, last_name{ln}, total{0.0}, p{}{
    setId_acc(Id_val);
}

void Account::setId_acc(int Id_val){
    this->Id_acc = Id_val;
}

void Account::setTotal(double Total){
    this->total = Total;
}

void Account::printPaychecks(soci::session& sql) {

    // Retrieve all rows from users table
    soci::rowset<soci::row> rs = (sql.prepare << "SELECT * FROM paychecks WHERE Id_acc = :id", soci::use(this->getId_acc(), "id"));

    std::cout << "\nAccount ID: " << this->getId_acc() << endl
    << "======================" << std::endl;

    // Iterate through the result set
    for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {
        const soci::row& r = *it;

        std::cout << "Paycheck ID: " << r.get<int>(0) << endl
                  << "    => Date: " << r.get<string>(2) << endl
                  << "    => Amount: " << r.get<double>(1) << " $" << endl;
    }
}



void Account::printTotal(soci::session& sql){
    std::cout << "\nAccount ID: " << getId_acc() << std::endl;
    std::cout << "User name: " << getName() << std::endl;
    std::cout << "======================" << std::endl;

    soci::rowset<soci::row> rs = (sql.prepare << "SELECT Total FROM accounts WHERE Id_acc = :id", soci::use(this->getId_acc(), "id"));
    const soci::row& r = *rs.begin();

    std::cout << "Cumulative total (DB): " << r.get<double>(0) << "$" << endl << endl;
}



//Add a pay
void Account::addPay(soci::session& sql){

    double amount;
    cout << "\nEnter the pay amount: ";
    cin >> amount;

    //Check if the value is a float
    while(!cin.good() | (amount < 0.0)){
        cout << "Error, please enter a valid pay amount: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> amount;
    }

    this->total += amount;

    time_t now = time(0);
    tm *ltm = localtime(&now);

    std::string date = std::to_string(1900 + ltm->tm_year) + "/" +
                  std::to_string(1 + ltm->tm_mon) + "/" +
                  std::to_string(ltm->tm_mday);

    // Insert data into paychecks table
    sql << "INSERT INTO paychecks(amount, date, Id_acc) VALUES(:a, :d, :id)",
            soci::use(amount, "a"), soci::use(date, "d"), soci::use(this->getId_acc(), "id");

    //Update of the cumulative total in accounts table
    sql << "UPDATE accounts SET Total = '" << this->getTotal() << "' WHERE Id_acc = :id", soci::use(this->getId_acc(), "id");
    cout << endl << "> Successfully modified total in account." << endl;
    cout << "> Successfully inserted paycheck into paychecks." << endl << endl;



    // Retrieve all rows from users table
    soci::rowset<soci::row> rs = (sql.prepare << "SELECT Id_pay FROM paychecks "
                                                 "WHERE Id_acc = :id "
                                                 "ORDER BY Id_pay DESC", soci::use(this->getId_acc(), "id"));
    const soci::row& r = *rs.begin();

    cout << r.get<int>(0)
            << r.get<double>(1)
            << r.get<int>(3) << endl;

    int ID_PAY = r.get<int>(0);

    Pay pay(amount, ID_PAY, date);
    std::vector<Pay> v = this->p[date];
    v.push_back(pay);

    this->p[date] = v;


}


//Delete a pay
void Account::deletePay(soci::session& sql){

    int Id_val;
    cout << "Enter the pay ID: ";
    cin >> Id_val;

    //Check if the value is a float
    while(!cin.good() | (Id_val < 0)){
        cout << "Error, please enter a valid pay amount: ";
        cin.clear();
        cin.ignore(10000,'\n');
        cin >> Id_val;
    }

    //Loop through all keys "date"
    for (auto &x: p) {
        //Loop through all the paycheck in the same "date" key
        vector<Pay> t;
        t = x.second;
        //t.erase(t.begin()+6);
        for(int i=0; i < t.size(); i++){

            cout << Id_val << endl;
            cout << t[i].getID() << endl;



            if(Id_val == t[i].getID()){
                this->total -= t[i].getAmount();
                t.erase(t.begin() + i);
                //Update account's total in db (accounts table)
                sql << "UPDATE accounts SET Total = '" << this->total << "' WHERE Id_acc = :id", soci::use(this->getId_acc(), "id");
                cout << "> Successfully updated cumulative total from accounts table." << endl;
                //Delete paychecks from paychecks table
                sql << "DELETE FROM paychecks WHERE Id_pay = :id", soci::use(Id_val, "id");
                cout << endl << "> Successfully deleted paycheck from paychecks table." << endl << endl;
            }
        }
        x.second = t;
    }


}