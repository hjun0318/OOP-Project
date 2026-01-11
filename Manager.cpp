#include "Manager.h"

void Manager::setID(string managerID) {this->managerID = managerID;}

string Manager::getID() {return managerID;}

void Manager::displayDetails()
{
    cout << "-----------------------------" << endl;
    cout << "ID: " << managerID << endl;
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Password: " << password << endl;
    cout << "-----------------------------" << endl;
}

void Manager::updateCustomer(Customer customer[], int customerCount)
{
    string targetID;
    int choice;
    cout << "Enter the customer ID to update: ";
    cin >> targetID;

    bool found = false;
    for (int i=0;i<customerCount;i++)
    {
        if (customer[i].getID() == targetID)
        {
            customer[i].displayDetails();
            cout << "1. Name" << endl
                << "2. Username" << endl
                << "3. Age" << endl
                << "4. Password" << endl
                << "5. Quit update" << endl;
            cout << "Enter the data want to update (1-4): ";
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
                            string newName;
                            while (true)
                            {
                                cout << "Enter new name: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, newName);

                                bool nameValidation = true;

                                if (newName.empty())
                                {
                                    cout << "Name cannot be empty!" << endl;
                                    nameValidation = false;
                                }

                                if (nameValidation==true)
                                {
                                    customer[i].setName(newName);
                                    break;
                                }
                            }

                            cout << "Update Successfully" << endl;
                            found = true;
                            Customer::saveCustomer(customer, customerCount);
                            break;
                        }

                        case 2:
                        {
                            string newUserName;
                            while (true)
                            {
                                cout << "Enter new username: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                getline(cin, newUserName);

                                bool nameValidation = true;

                                if (newUserName.empty())
                                {
                                    cout << "Name cannot be empty!" << endl;
                                    nameValidation = false;
                                }

                                if (nameValidation==true)
                                {
                                    customer[i].setName(newUserName);
                                    break;
                                }
                            }

                            cout << "Update Successfully" << endl;
                            found = true;
                            Customer::saveCustomer(customer, customerCount);
                            break;
                        }

                        case 3:
                        {
                            int newAge;
                            while (true)
                            {
                                cout << "Enter new age: ";
                                cin >> newAge;

                                if (cin.fail() || newAge <= 0 || newAge > 120)
                                {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "Age should be in the range of 1 to 120 and cannot be letter!\n";
                                }

                                else
                                {
                                    customer[i].setAge(newAge);
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    break;
                                }
                            }
                            cout << "Update Successfully" << endl;
                            found = true;
                            Customer::saveCustomer(customer, customerCount);
                            break;
                        }

                        case 4:
                        {
                            string newPassword;
                            while (true)
                            {
                                cout << "Create the password: ";
                                getline(cin, newPassword);

                                bool passwordValidation = true;

                                if (newPassword.empty())
                                    passwordValidation = false;

                                if (passwordValidation==true)
                                {
                                    customer[i].setPassword(newPassword);
                                    break;
                                }

                                cout << "Password cannot be empty!" << endl;
                            }
                            cout << "Update Successfully" << endl;
                            found = true;
                            Customer::saveCustomer(customer, customerCount);
                            break;
                        }

                        case 5:
                            return;

                        default:
                            cout << "Invalid Input";
                    }
                    break;
                }
            }
        }
    }
    if (!found)
        cout << "Customer ID not found" << endl;
}

void Manager::managerMenu(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount)
{
    int choice;
    while (true)
    {
        cout << "\n===== Manager Menu =====" << endl;
        cout << "1. Add customer" << endl
            << "2. Update customer" << endl
            << "3. Delete customer" << endl
            << "4. Update room" << endl
            << "5. Logout" << endl;
        cout << "Enter the action: ";
        cin >> choice;

        if (cin.fail())
        {
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(100, '\n');
        }
        else
        {
            switch(choice)
            {
                case 1:
                    customer[customerCount].registration();
                    customerCount++;
                    Customer::saveCustomer(customer, customerCount);
                    break;
                case 2:
                    Manager::updateCustomer(customer, customerCount);
                    break;
                case 3:
                    Manager::deleteCustomer(customer, customerCount);
                    break;
                case 4:
                    Manager::updateRoom(singleRoom, doubleRoom, roomCount);
                    break;
                case 5:
                    return;
                default:
                    cout << "Invalid input" << endl;
            }
        }
    }
}

int Manager::deleteCustomer(Customer customer[], int &customerCount)
{
    string targetID;
    cout << "Enter the customer ID to delete: ";
    cin >> targetID;

    int found = -1;
    for (int i=0;i<customerCount;i++)
    {
        if (customer[i].getID() == targetID)
        {
            found = i;
            break;
        }
    }

    if (found!=-1)
    {
        for (int i=found;i<customerCount-1;i++)
        {
            customer[i]=customer[i+1];
        }
        customerCount--;
        cout << "Customer deleted" << endl;

        Customer::saveCustomer(customer, customerCount);
    }
    else
    {
        cout << "Customer ID not found" << endl;
    }
    return customerCount;
}

bool Manager::managerLogin(Manager *manager, int managerCount)
{
    string id, password;
    cout << "Enter your ID: ";
    cin >> id;

    if (id == manager->getID())
    {
        cout << "Welcome " << manager->getName() << "!" << endl;

        cout << "Enter your password: ";
        cin >> password;

        if (password == manager->getPassword())
        {
            cout << "Manager " << manager->getName() << " login successfully" << endl;
            return true;
        }
        else
        {
            cout << "Password incorrect!" << endl;
            return false;
        }
        
    }
    else
    {
        cout << "ID " << id << " not found" << endl;
        return false;
    }
}

void Manager::updateRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount)
{
    string targetID;
    bool found;
    cout << "Enter room ID to update:";
    cin >> targetID;

    found = updateRoomHelper(singleRoom, roomCount, targetID);
    if (!found)
    {
        found = updateRoomHelper(doubleRoom, roomCount, targetID);
    }

    if (found)
        Room::saveRoom(singleRoom, doubleRoom, roomCount);
    else 
        cout << "Room ID " << targetID << " not found" << endl;  
}

void Manager::viewReport(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount)
{
    cout << "\n==== Customer Report ====" << endl;
    for (int i=0;i<customerCount;i++)
    {
        customer[i].displayDetails();
    }

    cout << "\n==== Single Room Report ====" << endl;
    for (int i=0;i<roomCount;i++)
    {
        singleRoom[i].displayDetails();
    }

    cout << "\n==== Double Room Report ====" << endl;
    for (int i=0;i<roomCount;i++)
    {
        doubleRoom[i].displayDetails();
    }
}