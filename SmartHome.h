#ifndef SMARTHOME_H
#define SMARTHOME_H

// Header files
#include<iostream>   // For input and output
#include<fstream>    // For file handling
#include<string>     // For string class
#include<vector>     // For vector container
#include<cctype>     // For character handling functions

using namespace std;

// Base class for all appliances
class Appliance
{
protected:
    string name;      // Stores appliance name
    string status;    // Stores appliance status (ON/OFF)

public:
    // Constructor
    Appliance(string="", string="OFF");

    // Virtual display function for polymorphism
    virtual void display();

    // Virtual destructor for proper object cleanup
    virtual ~Appliance();

    // Getter function for appliance name
    string getName();

    // Getter function for appliance status
    string getStatus();

    // Setter function to change status
    void setStatus(string);
};

// Derived class for Light appliance
class Light : public Appliance
{
public:
    // Constructor
    Light(string="", string="OFF");
};

// Derived class for Fan appliance
class Fan : public Appliance
{
public:
    // Constructor
    Fan(string="", string="OFF");
};

// Derived class for AC appliance
class AC : public Appliance
{
public:
    // Constructor
    AC(string="", string="OFF");
};

// Derived class for Heater appliance
class Heater : public Appliance
{
public:
    // Constructor
    Heater(string="", string="OFF");
};

// Room class
class Room
{
private:
    string roomName;   // Stores room name

public:
    // Constructor
    Room(string="");

    // Getter function for room name
    string getRoomName();

    // Setter function for room name
    void setRoomName(string);

    // Friend class declaration
    friend class UsageReport;
};

#endif