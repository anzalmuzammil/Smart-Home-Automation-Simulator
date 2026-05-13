#ifndef SECURITYSYSTEM_H
#define SECURITYSYSTEM_H

// SecuritySystem class handles arming/disarming of home security
class SecuritySystem
{
public:
    // Arms the security system for the entire house
    void armWholeHouse();

    // Disarms the security system for the entire house
    void disarmWholeHouse();

    // Arms the security system for a specific area/room
    void armSpecificArea();

    // Disarms the security system for a specific area/room
    void disarmSpecificArea();

    // Updates security settings based on given parameters (e.g., area name, status)
    void updateSecurity(string, string);
};

#endif