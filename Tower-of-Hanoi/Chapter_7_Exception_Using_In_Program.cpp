/******************************************************
Name: Thomas Liu
Teacher: Dr. Noukhovitch
Class: ICS4U1-4A
Assignment: Chapter 7 Exception: Using in program
Date: Apr 20, 2022
******************************************************/

#include <iostream>
#include <exception>
#include <string>

using namespace std;

// 3 exception
// not in range
class NotInRange : public std::exception{
private:
    string mess;
public:
    // return message
    string error()
    {
        return this->mess;
    }
    // assign message
    NotInRange(string mess)
    {
        this->mess = mess;
    }
};

// incorrect size
class IncorrectSize : public std::exception{
private:
    string mess;
public:
    // return message
    string error()
    {
        return this->mess;
    }
    // assign message
    IncorrectSize(string mess)
    {
        this->mess = mess;
    }
};

// no disks
class NoDisks : public std::exception{
private:
    string mess;
public:
    // return message
    string error()
    {
        return this->mess;
    }
    // assign message
    NoDisks(string mess)
    {
        this->mess = mess;
    }
};

class TowerOfHanoi{
private:
    // store the disk
    int tower[3][3];
public:
    // set initial tower
    void InitialTower();
    // move the disk following command
    int MoveDisk(int m1, int m2);
    // output the tower condition
    void PrintStatement();
    // check if the move match the result
    bool Check();
};

// set initial tower
void TowerOfHanoi::InitialTower()
{
    // initial three disk position
    this->tower[0][0] = 3;
    this->tower[0][1] = 2;
    this->tower[0][2] = 1;
    // other towers are empty (0)
    for (int counter1 = 1; counter1 < 3; counter1++)
    {
        for (int counter2 = 0; counter2 < 3; counter2++)
        {
            this->tower[counter1][counter2] = 0;
        }

    }
} 

// move the disk following command
int TowerOfHanoi::MoveDisk(int m1, int m2)
{
    // if the source or target tower is not in the range
    if (m1 < 1 || m1 > 3 || m2 < 1 || m2 > 3)
        throw NotInRange("Tower is not in the range.");
    // if the source tower is empty
    if (this->tower[m1-1][0] == 0)
        throw NoDisks("This is no disk in the source tower.");
    // move disk
    for (int counter1 = 0; counter1 < 3; counter1++)
    {
        // find the top empty space in target tower
        if (this->tower[m2-1][counter1] == 0)
        {
            // count from top to bottom
            for (int counter2 = 2; counter2 >= 0; counter2--)
            {
                // find the top disk for the original tower
                if (this->tower[m1-1][counter2] != 0)
                {
                    // if the source disk is bigger than the disk in the target tower
                    if (this->tower[m1-1][counter2] > this->tower[m2-1][0] && this->tower[m2-1][0] != 0)
                        throw IncorrectSize("Incorrect disk size.");
                    else if (this->tower[m1-1][counter2] > this->tower[m2-1][1] && this->tower[m2-1][1] != 0)
                        throw IncorrectSize("Incorrect disk size.");
                    else
                    {
                        // move the disk to the target tower
                        this->tower[m2-1][counter1] = this->tower[m1-1][counter2];
                        this->tower[m1-1][counter2] = 0;
                        return 0;
                    }
                }
            }
        }
    }
}

// output the tower condition
void TowerOfHanoi::PrintStatement()
{
    for (int counter1 = 0; counter1 < 3; counter1++)
    {
        // if there is no disk, output empty
        if (this->tower[counter1][0] == 0 && this->tower[counter1][1] == 0 && this->tower[counter1][2] == 0)
        {
            cout << "tower_" << counter1+1 << ": empty" << endl;
        }
        // if there is disk, output what's in the tower
        else
        {
            cout << "tower_" << counter1+1 << ": ";
            for (int counter2 = 0; counter2 < 3; counter2++)
            {
                if (this->tower[counter1][counter2] != 0)
                {
                    cout << this->tower[counter1][counter2] << " ";
                }
            }
            cout << endl;
        }
    }
}

// check if the move match the result
bool TowerOfHanoi::Check()
{
    if (this->tower[2][0] == 3 && this->tower[2][1] == 2 && this->tower[2][2] == 1)
        return true;
    else
        return false;
}

// main function
int main()
{
    TowerOfHanoi tower;
    // set initial
    tower.InitialTower();
    // set input variable, move 1 and move 2 variable
    int input;
    int move1;
    int move2;
    string command = "";
    // print initial tower
    tower.PrintStatement();

    while (command != "Quit")
    {
        
        try
        {
            // ask for move
            cout << "Enter Move: ";
            cin >> input;
            move1 = input/10;
            move2 = input%10;
            
            // if moving in the same tower
            if (move1 == move2)
                return false;
            // move
            else
                tower.MoveDisk(move1, move2);
            // if the player finished the tower
            if (tower.Check() == true)
            {
                cout << "Congratulation! You have finished the Tower of Hanoi. Type 'Quit' to quit: " << endl;
                cin >> command;
            }
        }
        // catch not in range error
        catch (NotInRange &err)
        {
            // output error message
            cout << err.error() << endl;
        }
        // catch no disks error
        catch (NoDisks &err)
        {
            // output error message
            cout << err.error() << endl;
        }
        // catch incorrect size errror
        catch (IncorrectSize &err)
        {
            // output error message
            cout << err.error() << endl;
        }
        // show the tower position after the move
        tower.PrintStatement();
    }

    return 0;
}
