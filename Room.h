#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

class SingleRoom;
class DoubleRoom;

//base class
class Room
{
protected:
    string roomType;
    string roomID;
    string customerID;
    double price;
    bool availableStatus;

public:
    Room(string roomType = "Generic", int price = 0);

    void setType(string roomType);
    void setID(string roomID);
    void setCustomerID(string customerID);
    void setPrice(double price);
    void setStatus(bool availableStatus);

    string getType();
    string getID();
    double getPrice();
    string getCustomerID();
    bool getAvailableStatus();

    void displayDetails();
    
    static void displayRoomDetails(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount);
    static void saveRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount);
    static int loadRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[]);
    static void checkAvailableRoom(SingleRoom singleRoom[], DoubleRoom doubleRoom[], int roomCount, int &singleAvailable, int &doubleAvailable);
    
    template <typename templateRoom>
    static void saveRoomHelper(templateRoom room[], int roomCount, string fileName)
    {
        ofstream file(fileName);

        if (file.is_open())
        {
            for (int i=0;i<roomCount;i++)
            {
                file << room[i].getType() << "|"
                    << room[i].getID() << "|"
                    << room[i].getPrice() << "|"
                    << room[i].getCustomerID() << "|"
                    << room[i].getAvailableStatus() << endl;
            }

            file.close();
            cout << fileName << " saved successfully" << endl;
        }

        else
        {
            cout << "Unable to open " << fileName << endl;
        }
    }

    template <typename templateRoom>
    static int loadRoomHelper(templateRoom room[], string fileName)
    {
        fstream file(fileName);
        int roomCount = 0;
        string temp;

        if (file.is_open())
        {
            while (getline(file, temp))
            {
                stringstream ss(temp);
                string segment;
                string data[5];
                bool status;
                int i = 0;

                while (getline(ss, segment, '|'))
                {
                    data[i] = segment;
                    i++;
                }

                room[roomCount].setType(data[0]);
                room[roomCount].setID(data[1]);
                room[roomCount].setPrice(stod(data[2]));
                room[roomCount].setCustomerID(data[3]);
                room[roomCount].setStatus(data[4] == "1");

                roomCount++;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open " << fileName << endl;
        }
        return roomCount;
    }
    
};

#endif