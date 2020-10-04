#pragma once
#include <string>



class Player {
public:
    std::string GHIN,
                name,
                firstName,
                middleName,
                lastName;

    //Setting these to 1000 to signify that they're "empty" since 0 is a possible handicap. 1001 means "NH" (no handicap)
    float handicap;

    int whiteteeStrokes,
        blueteeStrokes,
        tournamentteeStrokes,
        goldteeStrokes,
        blackteeStrokes;
    
    Player();
    void printPlayerInfo();
    
};

