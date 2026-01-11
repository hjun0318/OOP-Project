#ifndef MANAGER_H
#define MANAGER_H

#include "People.h"
#include "Customer.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"

class Manager: public People, public SingleRoom, public DoubleRoom 
{
protected:
    string managerID;

public:
    void setID(string managerID);

    string getID();
    void displayDetails();
    static void updateCustomer(Customer customer[], int customerCount);
    static void managerMenu(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount);
    static int deleteCustomer(Customer customer[], int &customerCount);
    static bool managerLogin(Manager *manager, int managerCount);
    static void updateRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount);
    
    static void viewReport(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount);

    template <typename templateRoom>
    static bool updateRoomHelper(templateRoom room[], int roomCount, string targetID)
    {
        for(int i=0;i<roomCount;i++)
        {
            if (room[i].getID() == targetID)
            {
                int choice;
                cout << "\nRoom id " << targetID << " found" << endl;
                room[i].displayDetails();
                cout << "\n1. Price" << endl
                    << "2. Status" << endl
                    << "3. Cancel" << endl;
                cout << "Enter the data you want to update: ";
                cin >> choice;

                if (cin.fail())
                {
                    cout << "Invalid input" << endl;
                    cin.clear();
                    cin.ignore(100, '\n');
                }
                else
                {
                    while (true)
                    {
                        switch (choice)
                        {
                            case 1:
                            {
                                double newPrice;
                                while (true)
                                {
                                    cout << "Enter new price: ";
                                    cin >> newPrice;

                                    if (cin.fail() || newPrice <= 0)
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Price cannot be negative!" << endl;
                                    }

                                    else
                                    {
                                        room[i].setPrice(newPrice);
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Update Successfully" << endl;
                                        return true;
                                        break;
                                    }
                                }
                            }

                            case 2:
                            {
                                int newStatus;
                                while (true)
                                {
                                    cout << "Enter status (1 for Available, 0 for Booked): ";
                                    cin >> newStatus;

                                    if (choice != 1 || choice != 0)
                                    {
                                        cout << "Invalid input" << endl;
                                    }
                                    else
                                    {
                                        cout << "Update Successfully" << endl;
                                        return true;
                                        break;
                                    }
                                }
                            }

                            case 3:
                                cout << "Update cancel" << endl;
                                return false;
                                break;

                            default:
                                cout << "Invalid Input";
                        }
                    }
                }
            }
        }
        return false;
    }
};
#endif