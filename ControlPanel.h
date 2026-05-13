#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

// ControlPanel class manages overall system control like rooms, password, and appliances
class ControlPanel
{
public:
    // Allows user to change system password
    void changePassword();

    // Modifies existing room settings (add/remove/update rooms or devices)
    void existingRoomModification();

    // Adds a new room into the system
    void addNewRoom();

    // Opens menu for managing appliances in rooms
    void appliancesMenu();

    // Validates password input (checks correctness/format)
    bool passwordValidation(string);

    // Checks whether a string contains only alphabets
    bool onlyAlphabets(string);

    // Adds an object (e.g., appliance) to a specific room or system
    void addObject(string, string);

    // Deletes an object (e.g., appliance) from a specific room or system
    void deleteObject(string, string);
};

#endif