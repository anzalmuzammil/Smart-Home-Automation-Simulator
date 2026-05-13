#include "SmartHome.h"
#include "ControlPanel.h"
#include "SecuritySystem.h"
#include "LightingSystem.h"
#include "WaterTankSystem.h"
#include "UsageReport.h"

using namespace std;

// ============================================================
//                APPLIANCE CLASS IMPLEMENTATION
// ============================================================

// Constructor: initializes appliance name and status
Appliance::Appliance(string n, string s)
{
    name = n;
    status = s;
}

// Displays appliance name with its status
void Appliance::display()
{
    cout << name << " " << status << endl;
}

// Destructor
Appliance::~Appliance()
{
}

// Getter: returns appliance name
string Appliance::getName()
{
    return name;
}

// Getter: returns appliance status
string Appliance::getStatus()
{
    return status;
}

// Setter: updates appliance status
void Appliance::setStatus(string s)
{
    status = s;
}

// ============================================================
//                CHILD CLASSES (INHERITANCE)
// ============================================================

// Light class inherits Appliance
Light::Light(string n, string s) : Appliance(n, s) {}

// Fan class inherits Appliance
Fan::Fan(string n, string s) : Appliance(n, s) {}

// AC class inherits Appliance
AC::AC(string n, string s) : Appliance(n, s) {}

// Heater class inherits Appliance
Heater::Heater(string n, string s) : Appliance(n, s) {}

// ============================================================
//                ROOM CLASS
// ============================================================

// Constructor: sets room name
Room::Room(string rn)
{
    roomName = rn;
}

// Returns room name
string Room::getRoomName()
{
    return roomName;
}

// Updates room name
void Room::setRoomName(string rn)
{
    roomName = rn;
}

// ============================================================
//                CONTROL PANEL LOGIC
// ============================================================

// Password validation rules:
// - 5 to 13 characters
// - at least 1 alphabet
// - at least 1 digit
// - at least 1 special character
bool ControlPanel::passwordValidation(string pass)
{
    bool alpha = false, digit = false, special = false;

    if(pass.length() < 5 || pass.length() > 13)
        return false;

    for(int i = 0; i < pass.length(); i++)
    {
        if(isalpha(pass[i]))// will check the ith number of index
            alpha = true;
        else if(isdigit(pass[i]))// will check the ith number of index
            digit = true;
        else
            special = true;
    }

    return alpha && digit && special;
}

// Checks string contains only alphabets (used for room names)
bool ControlPanel::onlyAlphabets(string str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(!isalpha(str[i]))
            return false;
    }
    return true;
}

// Change password using file handling
void ControlPanel::changePassword()
{
    string oldPass, filePass, newPass;

    ifstream fin("password.txt");// will open a file in read mode named as password.txt
    getline(fin, filePass);// will read the whole line
    fin.close();// close the file that was open in the read mode

    // Validate existing password
    do
    {
        cout << "Enter Existing Password: ";
        cin >> oldPass;

        if(oldPass != filePass)
            cout << "Incorrect Password\n";

    } while(oldPass != filePass);

    cout << "Password Correct\n";

    // Validate new password format
    do
    {
        cout << "Enter New Password: ";
        cin >> newPass;

        if(!passwordValidation(newPass))// we're passing the newpass to the function
            cout << "Invalid Password Format\n";

    } while(!passwordValidation(newPass));

    // Save new password
    ofstream fout("password.txt");// open the file named as password.txt as write mode
    fout << newPass; // it write  the newpass in that file
    fout.close();// the file that was open in write mode closes

    cout << "Password Updated Successfully\n";
}

// Add object into room file
void ControlPanel::addObject(string fileName, string objectName)
{
    ofstream fout(fileName.c_str(), ios::app);// will open the the file in write mode and c_str will convert the name into a 
    //c style string as in character array and ios::app just keeps the data safe and adds new data without
    // disturbing the previous one
    fout << objectName << " OFF" << endl;// this will write the object name in the file  and every object  
    // will have off status by default
    fout.close();

    cout << objectName << " Added Successfully\n";
}

// Delete object from room file
void ControlPanel::deleteObject(string fileName, string objectName)
{
    ifstream fin(fileName.c_str()); // will open the file whose name is entered in read mode 
    vector<string> lines;// it will create a temporary file of string datatype whose data will be read or writeline 
    // named as line

    string obj, status;

    while(fin >> obj >> status)
    {
        if(obj != objectName)
            lines.push_back(obj + " " + status);//line is a vector container and new data will be entered in the end of it
    }

    fin.close();

    ofstream fout(fileName.c_str());// will open the the file in write mode and c_str will convert the name into a 
    //c style string as in character array
    for(int i = 0; i < lines.size(); i++) // will grab every line or object at the ith index and and send 
    //the data in the file destination
        fout << lines[i] << endl;

    fout.close();

    cout << objectName << " Deleted Successfully\n";
}

// Modify existing rooms (add/delete appliances)
void ControlPanel::existingRoomModification()
{
    int roomChoice;

    cout << "\n===== EXISTING ROOM MODIFICATION =====\n";

    cout << "1. Bedroom1\n2. Bedroom2\n3. Washroom1\n4. Washroom2\n";
    cout << "5. Kitchen\n6. Lounge\n7. Garage\n8. Exit\n";

    cin >> roomChoice;

    string fileName;

    switch(roomChoice)
    {
        case 1: fileName = "Bedroom1.txt"; break;
        case 2: fileName = "Bedroom2.txt"; break;
        case 3: fileName = "Washroom1.txt"; break;
        case 4: fileName = "Washroom2.txt"; break;
        case 5: fileName = "Kitchen.txt"; break;
        case 6: fileName = "Lounge.txt"; break;
        case 7: fileName = "Garage.txt"; break;
        default: return;
    }

    int choice;
    cout << "\n1. Add\n2. Delete\n3. Exit\n";
    cin >> choice;

    if(choice == 1)
    {
        string obj;
        cout << "Enter Object Name: ";
        cin >> obj;
        addObject(fileName, obj); // This will add the object the the name of the textfile
    }
    else if(choice == 2)
    {
        string obj;
        cout << "Enter Object Name: ";
        cin >> obj;
        deleteObject(fileName, obj);// This will delete the object the the name of the textfile
    }
}

// Add new room dynamically
void ControlPanel::addNewRoom()
{
    string roomName;

    cout << "Enter Room Name: ";
    cin >> roomName;

    while(!onlyAlphabets(roomName))
    {
        cout << "Only Alphabets Allowed\n";
        cin >> roomName;
    }

    ofstream fout("home.txt", ios::app);// will open the the file in write mode and c_str will convert the name into a 
    //c style string as in character array and ios::app will save the data
    fout << roomName << endl;
    fout.close();

    ofstream roomFile((roomName + ".txt").c_str());
    roomFile.close();

    int choice;

    do
    {
        cout << "\n1. Add Lights\n2. Fan\n3. AC\n4. Heater\n5. Window\n6. Door\n7. Exit\n";
        cin >> choice;

        switch(choice)
        {
            case 1: addObject(roomName + ".txt", "Light"); break;
            case 2: addObject(roomName + ".txt", "Fan"); break;
            case 3: addObject(roomName + ".txt", "AC"); break;
            case 4: addObject(roomName + ".txt", "Heater"); break;
            case 5: addObject(roomName + ".txt", "Window"); break;
            case 6: addObject(roomName + ".txt", "Door"); break;
        }

    } while(choice != 7);

    cout << "Room Added Successfully\n";
}

// Appliances management
void ControlPanel::appliancesMenu()
{
    int choice;

    cout << "\n1. Add Appliance\n2. Exit\n";
    cin >> choice;

    if(choice == 1)
    {
        string appliance;
        cout << "Enter Appliance Name: ";
        cin >> appliance;

        ofstream fout("Appliances.txt", ios::app);// will open the the file in write mode and c_str will convert the name into a 
    //c style string as in character array
        fout << appliance << endl;
        fout.close();

        cout << "Appliance Added Successfully\n";
    }
}

// ============================================================
//                SECURITY SYSTEM
// ============================================================

// Update door/window status in file
void SecuritySystem::updateSecurity(string fileName, string status)
{
    ifstream fin(fileName.c_str()); // open file in read mode
    vector<string> lines; // a file that stores data temporarily

    string obj, stat;

    while(fin >> obj >> stat) // variables, object and status variables
    {
        if(obj == "Door" || obj == "Window" || obj == "MD1") // checking security items
            stat = status; // updating status

        lines.push_back(obj + " " + stat); // updated data is storing in vector
    }

    fin.close(); // reading compleleted and file is closed

    ofstream fout(fileName.c_str()); // same file is opend in write mode
    for(int i = 0; i < lines.size(); i++) // looping through every element of vector
        fout << lines[i] << endl; // writing updated data in file

    fout.close(); // save and close file
}

// Arm whole house
void SecuritySystem::armWholeHouse()
{
    vector<string> files // making list of all rooms from txt file
	 = {
        "Bedroom1.txt","Bedroom2.txt","Washroom1.txt",
        "Washroom2.txt","Kitchen.txt","Lounge.txt","Garage.txt"
    };

    for(int i = 0; i < files.size(); i++) // operation on all rooms
        updateSecurity(files[i], "LOCKED");  // locking all windows and door

    cout << "Whole House Secured\n"; // message dispaly
}

// Disarm whole house
void SecuritySystem::disarmWholeHouse()
{
    vector<string> files = {
        "Bedroom1.txt","Bedroom2.txt","Washroom1.txt",
        "Washroom2.txt","Kitchen.txt","Lounge.txt","Garage.txt"
    };

    for(int i = 0; i < files.size(); i++)
        updateSecurity(files[i], "UNLOCKED"); //unlocking all windows and doors

    cout << "Whole House Disarmed\n";
}

// Arm specific room
void SecuritySystem::armSpecificArea()
{
    vector<string> rooms; // making list of rooms
    string roomName;

    ifstream home("home.txt"); // home file opens

    while(home >> roomName)
        rooms.push_back(roomName); // storing in vector

    home.close();

    int choice;

    cout << "\n===== SELECT ROOM =====\n";
    for(int i = 0; i < rooms.size(); i++)
        cout << i+1 << ". " << rooms[i] << endl;

    cin >> choice;

    string fileName = rooms[choice-1] + ".txt"; // making file of selected room
    updateSecurity(fileName, "LOCKED"); // selected room is locked

    cout << "Specific Area Secured\n";
}

// Disarm specific room
void SecuritySystem::disarmSpecificArea()
{
    vector<string> rooms;
    string roomName;

    ifstream home("home.txt"); // home file open

    while(home >> roomName)
        rooms.push_back(roomName); // storing in vector

    home.close();

    int choice;

    cout << "\n===== SELECT ROOM =====\n";
    for(int i = 0; i < rooms.size(); i++)
        cout << i+1 << ". " << rooms[i] << endl;

    cin >> choice;

    string fileName = rooms[choice-1] + ".txt";
    updateSecurity(fileName, "UNLOCKED"); // selected room unlocked 

    cout << "Specific Area Disarmed\n";
}

// ============================================================
//                LIGHTING SYSTEM
// ============================================================

// Update light status
void LightingSystem::updateLight(string fileName, string lightName, string status)
{
    ifstream fin(fileName.c_str());
    vector<string> lines;

    string obj, stat;

    while(fin >> obj >> stat)
    {
        if(obj == lightName)
            stat = status;

        lines.push_back(obj + " " + stat);
    }

    fin.close();

    ofstream fout(fileName.c_str());
    for(int i = 0; i < lines.size(); i++)
        fout << lines[i] << endl;

    fout.close();
}

// Lighting menu
void LightingSystem::lightingMenu()
{
    vector<string> rooms;
    string room;

    ifstream fin("home.txt");

    while(fin >> room)
        rooms.push_back(room);

    fin.close();

    int roomChoice;

    cout << "\n===== LIGHTING SYSTEM =====\n";

    for(int i = 0; i < rooms.size(); i++)
        cout << i+1 << ". " << rooms[i] << endl;

    cout << rooms.size()+1 << ". Exit\n";
    cin >> roomChoice;

    if(roomChoice == rooms.size()+1)
        return;

    string fileName = rooms[roomChoice-1] + ".txt";

    ifstream roomFile(fileName.c_str());

    vector<string> lights;
    string obj, status;

    while(roomFile >> obj >> status)
    {
        if(obj.find("Light") != string::npos)
            lights.push_back(obj);
    }

    roomFile.close();

    int lightChoice;

    cout << "\n===== LIGHTS =====\n";

    for(int i = 0; i < lights.size(); i++)
        cout << i+1 << ". " << lights[i] << endl;

    cout << lights.size()+1 << ". Exit\n";
    cin >> lightChoice;

    if(lightChoice == lights.size()+1)
        return;

    int onOff;

    cout << "\n1. ON\n2. OFF\n";
    cin >> onOff;

    if(onOff == 1)
        updateLight(fileName, lights[lightChoice-1], "ON");
    else
        updateLight(fileName, lights[lightChoice-1], "OFF");
}

// ============================================================
//                WATER TANK SYSTEM
// ============================================================

void WaterTankSystem::motorON()
{
    ofstream fout("motor.txt");
    fout << "Motor ON";
    fout.close();
}

void WaterTankSystem::motorOFF()
{
    ofstream fout("motor.txt");
    fout << "Motor OFF";
    fout.close();
}

// ============================================================
//                USAGE REPORT
// ============================================================

void UsageReport::showONDevices()
{
    vector<string> rooms; // making dynamic list to store rooms
    string room;

    ifstream home("home.txt"); // opening home.txt file

    while(home >> room)
        rooms.push_back(room);

    home.close();

    string obj, status;// variables store status of objects

    cout << "\n===== ON DEVICES =====\n";

    for(int i = 0; i < rooms.size(); i++) // loop for every room
    {
        string fileName = rooms[i] + ".txt";
        ifstream fin(fileName.c_str()); // file open in read mode

        while(fin >> obj >> status)
            if(status == "ON") // only show on devices
                cout << rooms[i] << " -> " << obj << " is ON\n";

        fin.close();
    }

    ifstream motor("motor.txt"); // motor.txt opens
    motor >> obj >> status; // reading motor status

    if(status == "ON") // if motor is on
        cout << "Motor is ON\n";

    motor.close(); 
}

void UsageReport::showOFFDevices()
{
    vector<string> rooms;
    string room;

    ifstream home("home.txt");

    while(home >> room)
        rooms.push_back(room);

    home.close();

    string obj, status;

    cout << "\n===== OFF DEVICES =====\n";

    for(int i = 0; i < rooms.size(); i++)
    {
        string fileName = rooms[i] + ".txt";
        ifstream fin(fileName.c_str());

        while(fin >> obj >> status)
            if(status == "OFF")
                cout << rooms[i] << " -> " << obj << " is OFF\n";

        fin.close();
    }

    ifstream motor("motor.txt");
    motor >> obj >> status;

    if(status == "OFF")
        cout << "Motor is OFF\n";

    motor.close();
}

// ============================================================
//                LOGIN SYSTEM
// ============================================================

int loginSystem()
{
    string pass, filePass;

    ifstream fin("password.txt");
    getline(fin, filePass);
    fin.close();

    int attempts = 3;

    while(attempts--)
    {
        cout << "Enter Password: ";
        cin >> pass;

        if(pass == filePass)
        {
            cout << "Access Granted\n";
            return 1;
        }
        else
            cout << "Wrong Password\n";
    }

    cout << "ALARM ACTIVATED\n";
    return 0;
}