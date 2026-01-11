#include <iostream>
#include "Room.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"
#include "People.h"
#include "Customer.h"
#include "Manager.h"

using namespace std;

//prototype of functions
void roomSetID(SingleRoom singleRoom[], DoubleRoom doubleRoom[]);
int readManagerInformation(Manager *manager);
int login(Customer customer[], Manager *manager, int &customerCount, int &managerCount, int &activeIndexCustomer);

int main ()
{
    SingleRoom singleRoom[100];
    DoubleRoom doubleRoom[100];
    Manager manager;
    Customer customer[100];
    int loginStatus;

    int customerCount = 0; //track number of users
    int managerCount = 0;
    int roomCount = 10;
    int activeIndexCustomer = -1; //logged in customer index
    int singleAvailable = 0;
    int doubleAvailable = 0;

    customerCount = Customer::loadCustomer(customer);
    managerCount = readManagerInformation(&manager);
    Room::loadRoom(singleRoom, doubleRoom);

    // roomSetID(singleRoom, doubleRoom);
    // saveRoom(singleRoom, doubleRoom, roomCount);

    Room::checkAvailableRoom(singleRoom, doubleRoom, roomCount, singleAvailable, doubleAvailable);
    cout << "System loaded, " << customerCount << " customers loaded" << endl;

    //Login status decision to decide user will go to which menu
    bool systemRunning = true;
    while (systemRunning)
    {
        loginStatus = login(customer, &manager, customerCount, managerCount, activeIndexCustomer);

        switch (loginStatus)
        {
            case 1:
                Manager::managerMenu(customer, customerCount, singleRoom, doubleRoom, roomCount);
                // systemRunning = false;
                break;
            case 2:
                Customer::customerMenu(customer, customerCount, singleRoom, doubleRoom, roomCount, activeIndexCustomer, singleAvailable, doubleAvailable);
                // systemRunning = false;
                break;
            case 3:
                cout << "Exiting..." << endl;
                systemRunning = false;
                break;
        }
    }
    roomSetID(singleRoom, doubleRoom);
    // saveRoom(singleRoom, doubleRoom, roomCount);
    // Room::displayRoomDetails(singleRoom, doubleRoom, roomCount);
}

void roomSetID(SingleRoom singleRoom[], DoubleRoom doubleRoom[])
{
    int singleRoomDigit = 100;
    int doubleRoomDigit = 200;
    
    for (int i=0;i<100;i++)
    {
        string normalID = "a" + to_string(singleRoomDigit);
        string standardID = "b" + to_string(doubleRoomDigit);
        
        singleRoom[i].setID(normalID);
        doubleRoom[i].setID(standardID);

        singleRoomDigit++;
        doubleRoomDigit++;
    }
}

int readManagerInformation(Manager *manager)
{
    fstream readManager("manager.txt");
    int lineCount = 1, age;
    string temp, ID, name, password;
    int count = 0;


    if (readManager.is_open())
    {
        while (getline(readManager, temp))
        {
            switch (lineCount)
            {
                case 1:
                    ID = temp;
                    break;
                case 2:
                    name = temp;
                    break;
                case 3:
                    age = stoi(temp);
                    break;
                case 4:
                    password = temp;
            }
            lineCount++;
        }
    }

    else
    {
        cout << "Unable to open file.";
    }
    
    manager->setID(ID);
    manager->setName(name);
    manager->setAge(age);
    manager->setPassword(password);
    return count;
}

int login(Customer customer[], Manager *manager, int &customerCount, int &managerCount, int &activeIndexCustomer)
{
    int choice, i;

    while (true)
    {
        cout << "\n1. Manager login" << endl
             << "2. Customer login" << endl
             << "3. Register as New Customer" << endl
             << "4. Quit" << endl;
        cout << "Welcome, what you want to do?: ";
        cin >> choice;
        if (cin.fail())
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
        {
            switch (choice)
            {
                case 1:
                    if (Manager::managerLogin(manager, managerCount))
                        return 1;
                        break;
                case 2:
                    activeIndexCustomer = Customer::customerLogin(customer, customerCount);
                    if (activeIndexCustomer != -1)
                        return 2;
                        break;
                case 3:
                    cin.clear();
                    customer[customerCount].registration();
                    customerCount++;
                    Customer::saveCustomer(customer, customerCount);
                    break;
                case 4:
                    return 3;
                // case 5:
                //     for (i=0;i<customerCount;i++)
                //     {
                //         // cout << "-----------------------------" << endl;
                //         customer[i].displayDetails();
                //     }
                //     // cout << "-----------------------------" << endl;
                //     break;
                default:
                    break;
            }
        }
    }
}