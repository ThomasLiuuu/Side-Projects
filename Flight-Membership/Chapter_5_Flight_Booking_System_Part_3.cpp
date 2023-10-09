/******************************************************
Name: Thomas Liu
Teacher: Dr. Noukhovitch
Class: ICS4U1-4A
Assignment: Chapter 5 Flight Booking System Part 3
Date: Mar 03, 2022
******************************************************/

#include <iostream>

using namespace std;

// identify FlightBooking class
class FlightBooking {
// identify public function
public: 
    //give initial value
    void initialValue();
    // print result
    void printStatus();
    // create flight
    int create(int id, int capacity, int reserved);
    // add seats
    bool reserveSeats(int id, int seats);
    // cancel seats
    bool cancelSeats(int id, int seats);
    // delete flight
    int deleteId(int id);
// identify private variable
private:
    int Flight[10][3];
};

// set all initial values in the "Flight" dynamic array to 0
void FlightBooking::initialValue()
{
    for (int count1 = 0; count1 < 10; count1++)
    {
        for (int count2 = 0; count2 < 10; count2++)
        {
            this->Flight[count1][count2] = 0;
        }
    }
}

// function to output status
void FlightBooking::printStatus()
{
    int flight = 0;
    for (int count = 0; count < 10; count++)
    {
        if (this->Flight[count][0] != 0)
        {
            int id = this->Flight[count][0];
            int capacity = this->Flight[count][1];
            int reserved = this->Flight[count][2];
            int percent = 100 * reserved / capacity;
            // output the flight id, reserved, and capacity
            cout << "Flight " << id << ": " << reserved << "/" << capacity << "(" << percent << "%) seats reserved" << endl;
            flight += 1;
        }
    }
    if (flight == 0)
    {
        // output no flights in the list
        cout << "No such flight in the system" << endl;
    }
}

// allow user to create a new flight with capacity in the list
int FlightBooking::create(int id, int capacity, int reserved)
{
    for (int count = 0; count < 10; count++)
    {
        if (this->Flight[count][0] == 0)
        {
            this->Flight[count][0] = id;
            this->Flight[count][1] = capacity;
            this->Flight[count][2] = 0;
            return false;
        }
    }
}

// allow user to book seats
bool FlightBooking::reserveSeats(int id, int seats)
{
    for (int count = 0; count < 10; count++)
    {
        if (this->Flight[count][0] == id)
        {
            // when it does not exceed 105%
            if ((this->Flight[count][2]+seats) <= (this->Flight[count][1]*1.05))
            {
                this->Flight[count][2] += seats;
                return false;
            }
            // when it exceeds 105%
            else
            {
                cout << "Cannot perform this operation" << endl;
                return false;
            }
        }
    }
    cout << "No such flight in the system" << endl;
    return false;
}

// allow user to cancel number of reserved seats they booked
bool FlightBooking::cancelSeats(int id, int seats)
{
    for (int count = 0; count < 10; count++)
    {
        if (this->Flight[count][0] == id)
        {
            // when it does not exceed 105%
            if ((this->Flight[count][2]-seats) >= 0)
            {
                this->Flight[count][2] -= seats;
                return false;
            }
            // when cancel reserve less the what's booked
            else
            {
                cout << "Cannot perform this operation" << endl;
                return false;
            }
        }
    }
    cout << "No such flight in the system" << endl;
    return false;
}

// allow user to delete the flight
int FlightBooking::deleteId(int id)
{
    for (int count = 0; count < 10; count++)
    {
        if (this->Flight[count][0] == id)
        {
            this->Flight[count][0] = 0;
            this->Flight[count][1] = 0;
            this->Flight[count][2] = 0;
            return false;
        }
    }
}

// main function
int main()
{
    // set up three variable to take id, capacity, reserved
    int id;
    int capacity;
    int reserved;
    FlightBooking BookingSystem;
    // set up initial value to 0
    BookingSystem.initialValue();
    string command = "";
    while (command != "quit")
    {
        // print status
        BookingSystem.printStatus();
        // ask user what he would like to do
        cout << "What would you like to do?: ";
        cin >> command;
        // create flight
        if (command == "create")
        {
            cin >> id;
            cin >> capacity;
            BookingSystem.create(id, capacity, 0);
        }
        // add seats
        else if (command == "add")
        {
            cin >> id;
            cin >> reserved;
            BookingSystem.reserveSeats(id, reserved);
        }
        // cancel seats
        else if (command == "cancel")
        {
            cin >> id;
            cin >> reserved;
            BookingSystem.cancelSeats(id, reserved);
        }
        // delete flight
        else if (command == "delete")
        {
            cin >> id;
            BookingSystem.deleteId(id);
        }
        // error input
        else if (command != "quit")
        {
            cout << "Invalid input" << endl;
        }
    }

    // end the booking system
    cout << "Thank you for booking!" << endl;

    return 0;
}