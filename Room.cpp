#include "Room.h"
#include "SingleRoom.h"
#include "DoubleRoom.h"

Room::Room(string roomType, int price)
{
    this->roomType = roomType;
    roomID = "0";
    this->price = price;
    customerID = " ";
    availableStatus = 1;
}

void Room::setType(string roomType) {this->roomType = roomType;}
void Room::setID(string roomID) {this->roomID = roomID;}
void Room::setCustomerID(string customerID) {this->customerID = customerID;}
void Room::setPrice(double price) {this->price = price;}
void Room::setStatus(bool availableStatus) {this->availableStatus = availableStatus;}

string Room::getType() {return roomType;}
string Room::getID() {return roomID;}
double Room::getPrice() {return price;}
string Room::getCustomerID() {return customerID;}
bool Room::getAvailableStatus() {return availableStatus;}

void Room::displayDetails()
{
    cout << boolalpha; //used to change the original output of boolean type variable from 1 or 0 to true or false
    cout << "-----------------------------" << endl;
    cout << "Room type: " << roomType << endl;
    cout << "Room ID: " << roomID << endl;
    cout << fixed << setprecision(2) << "Room price: " << price << endl;
    cout << "Customer ID booked this room: " << customerID << endl;
    cout << "Available: " << availableStatus << endl;
    cout << "-----------------------------" << endl;
}

void Room::saveRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount)
{
    saveRoomHelper(singleRoom, roomCount, "singleRoom.txt");
    saveRoomHelper(doubleRoom, roomCount, "doubleRoom.txt");
}

int Room::loadRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[])
{
    loadRoomHelper(singleRoom, "singleRoom.txt");
    loadRoomHelper(doubleRoom, "doubleRoom.txt");
}

void Room::checkAvailableRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &singleAvailable, int &doubleAvailable)
{
    for (int i=0;i<roomCount;i++)
    {
        if (singleRoom[i].getAvailableStatus() == true)
            singleAvailable++;

        if (doubleRoom[i].getAvailableStatus() == true)
            doubleAvailable++;
    }
}