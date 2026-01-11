#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "People.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"

class Customer: public People, public SingleRoom, public DoubleRoom 
{
protected:
    string customerID;
    string userName;
    static int num;

public:
    Customer();

    void setID(string customerID);
    void setUserName(string userName);

    string getID();
    string getUserName();

    //static function for ID
    static void setStaticNum(int n);

    static int getStaticNum();

    void registration();
    string generateID();
    void displayDetails();
    static void saveCustomer(Customer customer[], int customerCount);
    static int loadCustomer(Customer customer[]);
    static void customerMenu(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable);
    static int customerLogin(Customer customer[], int customerCount);
    static void bookingRoom(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable);
    static void viewBookedRoom(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer);
    static void viewReceipt(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer);
    static void checkout(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable);
};
#endif