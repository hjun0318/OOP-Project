#include "Customer.h"
#include <limits>

int Customer:: num = 100000;
Customer::Customer() {}

void Customer::setID(string customerID) {this->customerID = customerID;}
void Customer::setUserName(string userName) {this->userName = userName;}

string Customer::getID() {return customerID;}
string Customer::getUserName() {return userName;}

//static function for ID
void Customer::setStaticNum(int n) {num = n;}

int Customer::getStaticNum() {return num;}

void Customer::registration()
{
    string name, userName, password;
    int age;

    while (true)
    {
        cout << "Enter your name: ";
        cin.ignore();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);

        if (name.empty())
            cout << "Name cannot be empty!" << endl;
        else
        {
            setName(name);
            break;
        }
    }

    while (true)
    {
        cout << "Create your username: ";
        // cin.ignore();
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, userName);

        if (userName.empty())
            cout << "username cannot be empty!" << endl;
        else
        {
            setUserName(userName);
            break;
        }
    }

    while (true)
    {
        cout << "Enter your age: ";
        cin >> age;

        if (cin.fail() || age <= 0 || age > 120)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Age should be in the range of 1 to 120 and cannot be letter!\n";
        }

        else
        {
            setAge(age);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }

    while (true)
    {
        cout << "Create the password: ";
        getline(cin, password);

        if (password.empty())
            cout << "Password cannot be empty!" << endl;
        else
        {
            setPassword(password);
            break;
        }
    }

    setID(generateID());
}

string Customer::generateID()
{
    return "c" + to_string(num++);
}

void Customer::displayDetails()
{
    cout << "-----------------------------" << endl;
    cout << "ID: " << customerID << endl;
    cout << "Name: " << name << endl;
    cout << "Username: " << userName << endl;
    cout << "Age: " << age << endl;
    cout << "Password: " << password << endl;
    cout << "-----------------------------" << endl;
}

void Customer::saveCustomer(Customer customer[], int customerCount)
{
    ofstream saveCustomer("customer.txt", ios::out | ios::trunc);

    if (saveCustomer.is_open())
    {
        for (int i=0;i<customerCount;i++)
        {
            saveCustomer << customer[i].getID() << "|"
                            << customer[i].getName() << "|"
                            << customer[i].getUserName() << "|"
                            << customer[i].getAge() << "|"
                            << customer[i].getPassword() << endl;
        }

        saveCustomer.close();
        cout << "Customer's data saved successfully" << endl;
    }

    else
    {
        cout << "Unable to open customer.txt" << endl;
    }
}

int Customer::loadCustomer(Customer customer[])
{
    fstream readCustomer("customer.txt");
    int customerCount = 0;
    string temp;


    if (readCustomer.is_open())
    {
        while (getline(readCustomer, temp))
        {
            stringstream ss(temp);
            string segment;
            string data[5];
            int i = 0;

            while (getline(ss, segment, '|'))
            {
                data[i] = segment;
                i++;
            }

            customer[customerCount].setID(data[0]);
            customer[customerCount].setName(data[1]);
            customer[customerCount].setUserName(data[2]);
            customer[customerCount].setAge(stoi(data[3]));
            customer[customerCount].setPassword(data[4]);

            customerCount++;
        }
        readCustomer.close();

        //update static ID counter, avoid ID collision
        if (customerCount > 0)
        {
            string lastID = customer[customerCount-1].getID();
            string numberPart = lastID.substr(1);
            Customer::setStaticNum(stoi(numberPart) + 1);
        }
    }
    else
    {
        cout << "Unable to open customer.txt" << endl;
    }
    return customerCount;
}

void Customer::customerMenu(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable)
{
    int choice;
    // cout << activeIndexCustomer << endl;
    while (true)
    {
        cout << "\n===== Customer Menu =====" << endl;
        cout << "1. View profile" << endl
            << "2. View available room" << endl
            << "3. Book a room" << endl
            << "4. View booked room" << endl
            << "5. View receipt" << endl
            << "6. Checkout" << endl
            << "7. Logout" << endl;
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
                    customer[activeIndexCustomer].displayDetails();
                    break;
                case 2:
                    cout << "-------------------------------------------" << endl;
                    cout << "|   Room Type   |  Number Room Available  |" << endl;
                    cout << "-------------------------------------------" << endl;
                    cout << "|  Single room  |           " << singleAvailable << "            |" << endl;
                    cout << "-------------------------------------------" << endl;
                    cout << "|  Double room  |           " << doubleAvailable << "            |" << endl;
                    cout << "-------------------------------------------" << endl;
                    break;
                case 3:
                    bookingRoom(customer, customerCount, singleRoom, doubleRoom, roomCount, activeIndexCustomer, singleAvailable, doubleAvailable);
                    break;
                case 4:
                    viewBookedRoom(customer, customerCount, singleRoom, doubleRoom, roomCount, activeIndexCustomer);
                    break;
                case 5:
                    viewReceipt(customer, customerCount, singleRoom, doubleRoom, roomCount, activeIndexCustomer);
                    break;
                case 6:
                    checkout(customer, customerCount, singleRoom, doubleRoom, roomCount, activeIndexCustomer, singleAvailable, doubleAvailable);
                    break;
                case 7:
                    return;
                default:
                    cout << "Invalid input" << endl;
            }
        }
    }
}

int Customer::customerLogin(Customer customer[], int customerCount)
{
    string userName, password;
    int choice;
    cout << "Enter your username: ";
    cin >> userName;

    for (int i=0;i<customerCount;i++)
    {
        if (userName == customer[i].getUserName())
        {
            cout << "Welcome " << customer[i].getName() << endl;
            cout << "Enter your password: ";
            cin >> password;

                if (password == customer[i].getPassword())
                {
                    cout << "Customer " << customer[i].getName() << " login successful!" << endl;
                    return i;
                }
                else
                {
                    cout << "Password incorrect!" << endl;
                    return -1;
                }
        }
    }
        cout << "ID " << userName << " not found" << endl;
        while (true)
        {
            cout << "Want to register as a new customer? (1 for Yes, 2 for No): ";
            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Number only" << endl;
                continue;
            }

            if (choice == 1)
            {
                customer[customerCount].registration();
                customerCount++;
                Customer::saveCustomer(customer, customerCount);
                return -1;
                break;
            }
            else if (choice == 2)
            {
                return -1;
                break;
            }
            else
                cout << "Invalid choice!" << endl;
        }
}

void Customer::bookingRoom(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable)
{
    int choice;
    while (true)
    {
        cout << "--------------------------------------------------------" << endl;
        cout << "|   Room Type   |   Price    |  Number Room Available  |" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "|  Single room  |  RM100.00  |           " << singleAvailable << "            |" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "|  Double room  |  RM175.00  |           " << doubleAvailable << "            |" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "1. Single room" << endl
            << "2. Double room" << endl
            << "3. Cancel" << endl;
        cout << "What type of room you would like to book?: ";
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
                    if (singleAvailable == 0)
                    {
                        cout << "No single room able to book" << endl;
                    }
                    else
                    {
                        for (int i=0;i<roomCount;i++)
                        {
                            if (singleRoom[i].getAvailableStatus() == true)
                            {
                                singleRoom[i].setStatus(false);
                                singleRoom[i].setCustomerID(customer[activeIndexCustomer].getID());
                                Room::saveRoom(singleRoom, doubleRoom, roomCount);
                                singleAvailable--;
                                break;
                            }
                        }
                    }
                    break;

                case 2:
                    if (doubleAvailable == 0)
                    {
                        cout << "No double room able to book" << endl;
                    }
                    else
                    {
                        for (int i=0;i<roomCount;i++)
                        {
                            if (doubleRoom[i].getAvailableStatus() == true)
                            {
                                doubleRoom[i].setStatus(false);
                                doubleRoom[i].setCustomerID(customer[activeIndexCustomer].getID());
                                Room::saveRoom(singleRoom, doubleRoom, roomCount);
                                doubleAvailable--;
                                break;
                            }
                        }
                    }
                    break;

                case 3:
                    return;
                default:
                    cout << "Invalid input" << endl;
            }
        }
        break;
    }
}

void Customer::viewBookedRoom(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer)
{
    int singleBooked = 0, doubleBooked = 0, totalBooked = 0;

    cout << "\nRoom Details:" << endl;
    cout << "---------------------------------------" << endl;
    for (int i=0;i<roomCount;i++)
    {
        if (singleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
        {
            singleBooked++;
            cout << "|  Single room  |  RM" << singleRoom[i].getPrice() << "  |   " << singleRoom[i].getID() << "    |" << endl;
            cout << "---------------------------------------" << endl;
        }
        if (doubleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
        {
            doubleBooked++;
            cout << "|  Double room  |  RM" << doubleRoom[i].getPrice() << "  |   " << doubleRoom[i].getID() << "    |" << endl;
            cout << "---------------------------------------" << endl;
        }
    }

    cout << "\nTotal Room Booked: " << endl;
    totalBooked = singleBooked + doubleBooked;
    cout << "----------------------------------------" << endl;
    cout << "|   Room Type   |  Number Room Booked  |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "|  Single room  |          " << singleBooked << "           |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "|  Double room  |          " << doubleBooked << "           |" << endl;
    cout << "----------------------------------------" << endl;
    cout << "|     Total     |          " << totalBooked << "           |" << endl;
    cout << "----------------------------------------\n" << endl;
}

void Customer::viewReceipt(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer)
{
    cout << "\n===== Receipt =====" << endl;
    double totalPrice = 0.0;
    cout << fixed << setprecision(2);
    cout << "---------------------------------------" << endl;
    cout << "|   Room Type   |   Price   | Room ID  |" << endl;
    cout << "---------------------------------------" << endl;

    for (int i=0;i<roomCount;i++)
    {
        if (singleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
        {
            cout << "|  Single room  |  RM" << singleRoom[i].getPrice() << "  |   " << singleRoom[i].getID() << "    |" << endl;
            cout << "---------------------------------------" << endl;
            totalPrice += singleRoom[i].getPrice();
        }
        if (doubleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
        {
            cout << "|  Double room  |  RM" << doubleRoom[i].getPrice() << "  |   " << doubleRoom[i].getID() << "    |" << endl;
            cout << "---------------------------------------" << endl;
            totalPrice += doubleRoom[i].getPrice();
        }
    }
}

void Customer::checkout(Customer customer[], int &customerCount, SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &activeIndexCustomer, int &singleAvailable, int &doubleAvailable)
{
    string confirm;
    cout << "Are you sure want to checkout? (Y/N): ";
    cin >> confirm;

    if (confirm == "Y" || confirm == "y")
    {
        for (int i=0;i<roomCount;i++)
        {
            if (singleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
            {
                singleRoom[i].setStatus(true);
                singleRoom[i].setCustomerID(" ");
                singleAvailable++;
            }
            if (doubleRoom[i].getCustomerID() == customer[activeIndexCustomer].getID())
            {
                doubleRoom[i].setStatus(true);
                doubleRoom[i].setCustomerID(" ");
                doubleAvailable++;
            }
        }
        Room::saveRoom(singleRoom, doubleRoom, roomCount);
        cout << "Checkout successful!" << endl;
    }
    else
    {
        cout << "Checkout cancelled!" << endl;
    }
}