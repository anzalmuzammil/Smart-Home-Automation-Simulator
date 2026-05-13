#include "SmartHome.h"
#include "ControlPanel.h"
#include "SecuritySystem.h"
#include "LightingSystem.h"
#include "WaterTankSystem.h"
#include "UsageReport.h"
#include<iostream>
#include<vector>
int loginSystem();// it will give acess to the user by asking the password

int main()
{
// -----------login check---------------
//if password is not correct three times the program closes
    if(!loginSystem())
    {
        return 0;
    }
// object creation
    ControlPanel cp;
    SecuritySystem ss;
    LightingSystem ls;
    WaterTankSystem ws;
    UsageReport ur;

    int choice;

    do
    { //this loop will keep the main panel running until user choose exit
        cout<<"\n===== SMART HOME AUTOMATION =====\n";

        cout<<"1. Control Panel\n";
        cout<<"2. Security System\n";
        cout<<"3. Lighting System\n";
        cout<<"4. Water Tank System\n";
        cout<<"5. Usage Report\n";
        cout<<"6. Exit\n";

        cin>>choice;
// for main menu we use switche to get the choices
        switch(choice)
        {
        case 1:
        {
            int cpChoice;
// control panel loop
            do
            {
                cout<<"\n===== CONTROL PANEL =====\n";

                cout<<"1. Change Password\n";
                cout<<"2. Existing Rooms Modification\n";
                cout<<"3. Add New Room\n";
                cout<<"4. Appliances\n";
                cout<<"5. Exit\n";

                cin>>cpChoice;
// switch for control panel choices
                switch(cpChoice)
                { 
                //change password option
                case 1:
                    cp.changePassword();
                    break;

                case 2:
                    cp.existingRoomModification();
                    break;

                case 3:
                    cp.addNewRoom();
                    break;

                case 4:
                    cp.appliancesMenu();
                    break;
                    
                }

            }while(cpChoice!=5);// the program will exit from the current panel and shift to previous ones

            break;
        }
//---------security system---------
        case 2:
        {
            int secChoice;

            do
            {
                cout<<"\n===== SECURITY SYSTEM =====\n";

                cout<<"1. Arm\n";
                cout<<"2. Disarm\n";
                cout<<"3. Exit\n";

                cin>>secChoice;
// ARM option 
                if(secChoice==1)
                {
                    int armChoice;

                    cout<<"\n1. Whole House\n";
                    cout<<"2. Specific Area\n";
                    cout<<"3. Exit\n";

                    cin>>armChoice;

                    if(armChoice==1)
                    {
                        ss.armWholeHouse();// it will arm( locked) the whole house
                    }

                    else if(armChoice==2)
                    {
                        ss.armSpecificArea();
                    }
                }
// disarm option
                else if(secChoice==2)
                {
                	// this choice will disarm (un-locked) house
                    int disarmChoice;

                    cout<<"\n1. Whole House\n";
                    cout<<"2. Specific Area\n";
                    cout<<"3. Exit\n";

                    cin>>disarmChoice;

                    if(disarmChoice==1)
                    {
                        ss.disarmWholeHouse();
                    }

                    else if(disarmChoice==2)
                    {
                        ss.disarmSpecificArea();
                    }
                }

            }while(secChoice!=3);// the program will exit from the current panel and shift to previous ones

            break;
        }
// ----------lightning system ----------
        case 3:
            ls.lightingMenu();// whole menu is in a function
            break;
//-----------water tank system------------
        case 4:
        {
            int waterChoice;

            do
            {
                cout<<"\n===== WATER TANK SYSTEM =====\n";

                cout<<"1. Motor ON\n";
                cout<<"2. Motor OFF\n";
                cout<<"3. Exit\n";

                cin>>waterChoice;

                switch(waterChoice)
                {
                case 1:
                    ws.motorON();// this option will turn motor on
                    break;

                case 2:
                    ws.motorOFF();// this option will turn motor off
                    break;
                }

            }while(waterChoice!=3);// the program will exit from the current panel and shift to previous ones

            break;
        }
// ----------------usage report--------------
        case 5:
        {
            int reportChoice;

            do
            {
                cout<<"\n===== USAGE REPORT =====\n";

                cout<<"1. ON Devices\n";
                cout<<"2. OFF Devices\n";
                cout<<"3. Exit\n";

                cin>>reportChoice;

                switch(reportChoice)
                {
                case 1:
                    ur.showONDevices();// will show all the devices that are on in all the txt files
                    break;

                case 2:
                    ur.showOFFDevices(); //will show all the devices that are off in all the txt files
                    break;
                }

            }while(reportChoice!=3);// the program will exit from the current panel and shift to previous ones

            break;
        }

        case 6:
            cout<<"Program Closed\n";// the program will stop its termination as whole
            break;
        }

    }while(choice!=6);

    return 0;
}