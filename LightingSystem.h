#ifndef LIGHTINGSYSTEM_H
#define LIGHTINGSYSTEM_H

// Lighting System class
class LightingSystem
{
public:

    // Function to display lighting system menu
    void lightingMenu();

    // Function to update light status
    // Parameters:
    // 1. Room name
    // 2. Light name
    // 3. Updated status (ON/OFF)
    void updateLight(string,string,string);
};

#endif