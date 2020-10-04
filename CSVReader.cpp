#include "CSVReader.h"
#include <stdlib.h>
#include <algorithm>  //Included for transform()
#include <map> //for column map
#include <Windows.h>
#include <cstdlib>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <locale>
#include "tinyfiledialogs/tinyfiledialogs.h"
#include <vector>
#include <sstream>

// 7/24/20 leaving off figuring out best way to store all player data


class Player {
public:
    std::string GHIN = "",
        name = "",
        firstName = "",
        middleName = "",
        lastName = "";

    //Setting these to 1000 to signify that they're "empty" since 0 is a possible handicap. 1001 means "NH" (no handicap)
    float handicap = 1000.f;

    int whiteteeStrokes = 1000,
        blueteeStrokes = 1000,
        tournamentteeStrokes = 1000,
        goldteeStrokes = 1000,
        blackteeStrokes = 1000;


    void printPlayerInfo()
    {
        std::cout << "GHIN #:" << GHIN << std::endl;
        std::cout << "Name:" << name << std::endl;
        std::cout << "First name:" << firstName << std::endl;
        if (!middleName.empty()) std::cout << "middleName:" << middleName << std::endl;
        std::cout << "Last name:" << lastName << std::endl;
        std::cout << "Handicap:" << handicap << std::endl;
        std::cout << "White tee strokes:" << whiteteeStrokes << std::endl;
        std::cout << "Blue tee strokes:" << blueteeStrokes << std::endl;
        std::cout << "Tournament tee strokes:" << tournamentteeStrokes << std::endl;
        std::cout << "Gold tee strokes:" << goldteeStrokes << std::endl;
        std::cout << "Black tee strokes:" << blackteeStrokes << std::endl;
        std::cout << std::endl;
    }
};


bool containsGHIN(char line[], int size);
bool containsGHIN(std::string const& line);
bool looksLikeName(std::string const& line);




int main()
{
    std::ifstream inFile("TestHandicapCSV.csv");

    std::string titleLine; //Title line that column row gets appended to
    const int MAXLINE = 256;
    char oneline[MAXLINE]; //oneline contains an entire row
    char* lineToken; //lineToken is used to contain a single token from a row

    int lineNumber = 0,
        columnNumber = 0,
        tokenCount = 0;

    bool titleLineWritten = false;
    std::map<int, std::string> columns; //Map to save column # and name in
    std::vector<std::string> playerlineTokens; //Vector for GHIN line tokens
    std::vector<Player> players;

    std::vector<std::string> nametokens;

    //If first line of stream, check for BOM marker and move beginning of stream past it
    if (titleLine.empty())
    {
        char a, b, c;
        a = inFile.get();
        b = inFile.get();
        c = inFile.get();
        if (a != (char)0xEF || b != (char)0xBB || c != (char)0xBF)
        {
            inFile.seekg(0);
        }
        else
        {
            inFile.seekg(3);
            std::cerr << "Warning: file contains the so-called 'UTF-8 signature'\n";
        }
    }

    while (inFile)
    {
        //Gets info from fstream until a \n is met, writes it to 'oneline'
        inFile.getline(oneline, MAXLINE);


        //Creates first row string of the columns titles by appending to titleLine until 'oneline' contains a GHIN number
        if ((lineNumber == 0) && !titleLineWritten && !containsGHIN(oneline, MAXLINE))  //This should probably come after the else if, since it will be checked less often
        {
            titleLine.append(oneline);
        }
        //If containsGHIN returns true, it means end of title line. Checking if titleLineWritten is false to see if it is first GHIN line
        else if (!titleLineWritten && containsGHIN(oneline, MAXLINE))
        {
            titleLineWritten = true;
            lineNumber++;
            std::cout << "Title line:" << titleLine << std::endl << std::endl;


            // Tokenizing the title line and saving the column # and column name to a map
            std::vector<std::string> titleLineTokens; // Vector of string to save tokens in

            std::stringstream titlelineSStream(titleLine);
            std::string intermediate;

            // Tokenizing 
            while (getline(titlelineSStream, intermediate, ','))
            {
                titleLineTokens.push_back(intermediate);
            }
            //Write tokens to columns map and assign column#
            for (int i = 0; i < titleLineTokens.size(); i++)
            {
                columns[i] = titleLineTokens.at(i);
            }
        }




        if (containsGHIN(oneline, MAXLINE))
        {
            Player player;
            lineToken = strtok(oneline, ","); //priming read
            playerlineTokens.clear();
            while (lineToken != NULL)
            {
                playerlineTokens.push_back(lineToken);
                lineToken = strtok(NULL, ","); //Sets lineToken to next token, or to NULL if there isn't one
            }


            for (int i = 0; i < playerlineTokens.size(); i++)
            {

                if (player.GHIN.empty() && containsGHIN(playerlineTokens.at(i)))
                {
                    //If "GHIN" is found in the column of the tokens index on that line
                    if (player.GHIN.empty() && (columns[i].find("GHIN") != std::string::npos)) //Need to find good way to convert 
                    {                                                                           //compared strings to lowercase before find()
                        player.GHIN = playerlineTokens.at(i);
                    }
                }
                else if (player.name.empty() && (columns[i].find("Name") != std::string::npos)) //Need to find good way to convert 
                {                                                                                //compared strings to lowercase before find()
                    if (looksLikeName(playerlineTokens.at(i)))
                    {
                        std::stringstream nameSStream(playerlineTokens.at(i));  //Try to declare this and intermediate string somewhere else at some point
                        std::string intermediate = "";
                        nametokens.clear();

                        //Tokenizing full name
                        while (getline(nameSStream, intermediate, ' '))
                        {
                            if (intermediate.empty() || (intermediate.find(" ") != std::string::npos))
                            {
                                std::cout << "Continuing" << std::endl;
                                continue;
                            }
                            else nametokens.push_back(intermediate);
                        }

                        //size of 2 should be first/last name, 3 is first/middle/last
                        if (nametokens.size() == 2)
                        {
                            player.firstName = nametokens.at(0);
                            std::cout << "First name:" << player.firstName << std::endl;
                            player.lastName = nametokens.at(1);
                            std::cout << "Last name:" << player.lastName << std::endl;
                            player.name = player.firstName + " " + player.lastName;
                        }
                        else if (nametokens.size() == 3)
                        {
                            player.firstName = nametokens.at(0);
                            std::cout << "First name:" << player.firstName << std::endl;
                            player.middleName = nametokens.at(1);
                            std::cout << "Middle name:" << player.middleName << std::endl;
                            player.lastName = nametokens.at(2);
                            std::cout << "Last name:" << player.lastName << std::endl;
                            player.name = player.firstName + " " + player.middleName + " " + player.lastName;
                        }
                        else if (nametokens.size() == 1)
                        {
                            player.firstName = nametokens.at(0);
                            std::cout << "First AND ONLY name:" << player.firstName << std::endl;
                            player.name = player.firstName;
                        }
                        else if (nametokens.size() > 3)
                        {
                            std::cout << "PROBLEM: Should not have more than 3 names. " << "Problem is around line " << __LINE__ << std::endl;
                        }






                    }
                }
                else if (player.handicap == 1000.f && ((columns[i].find("H.I") != std::string::npos) || (columns[i].find("Handicap") != std::string::npos)
                    || (columns[i].find("handicap") != std::string::npos) || (columns[i].find("Index") != std::string::npos)
                    || (columns[i].find("index") != std::string::npos)))
                {   //Would like to check if numbers in this column are a float somehow
                    //Check if player has no handicap(NH), if so, set to 1001
                    try
                    {
                        player.handicap = stof(playerlineTokens.at(i));
                    }
                    catch (...)
                    {
                        if ((playerlineTokens.at(i).find("NH") != std::string::npos) ||
                            playerlineTokens.at(i).find("nh") != std::string::npos) //Figure out how to check if there is a not a 
                        {                                                             //number (int or decimal) in this token
                            player.handicap = 1001.f;  //This means no handicap
                        }
                        else std::cout << "Problem near line " << __LINE__;
                    }

                }
                else if (player.whiteteeStrokes == 1000 && (columns[i].find("White") != std::string::npos))
                {
                    player.whiteteeStrokes = stoi(playerlineTokens.at(i));
                }
                else if (player.blueteeStrokes == 1000 && (columns[i].find("Blue") != std::string::npos))
                {
                    player.blueteeStrokes = stoi(playerlineTokens.at(i));
                }
                else if (player.tournamentteeStrokes == 1000 && (columns[i].find("Tour") != std::string::npos))
                {
                    player.tournamentteeStrokes = stoi(playerlineTokens.at(i));
                }
                else if (player.goldteeStrokes == 1000 && (columns[i].find("Gold") != std::string::npos))
                {
                    player.goldteeStrokes = stoi(playerlineTokens.at(i));
                }
                else if (player.blackteeStrokes == 1000 && (columns[i].find("Black") != std::string::npos))
                {
                    player.blackteeStrokes = stoi(playerlineTokens.at(i));
                }
            }
            //Add player to vector of players
            players.push_back(player);
        }
    }

    inFile.close();

    //Prints column names
    for (auto elem : columns)
    {
        std::cout << "Columns: " << elem.first << " " << elem.second << "\n";
    }

    //Print info for every player in players vector
    for (auto player : players)
    {
        player.printPlayerInfo();
    }



    return 0;
}



//Returns true if the line has a sequence of 5 digits
bool containsGHIN(char line[], int size)
{

    for (int i = 0; line[i] != '\0' && i < size - 6; i++)
    {
        if (isdigit(line[i]) && isdigit(line[i + 1]) && isdigit(line[i + 2]) && isdigit(line[i + 3]) && isdigit(line[i + 4]))
        {
            return true;
        }
    }
    return false;
}

bool containsGHIN(std::string const& line)
{
    for (int i = 0; i < line.size() - 4; i++)
    {
        if (isdigit(line[i]) && isdigit(line[i + 1]) && isdigit(line[i + 2]) && isdigit(line[i + 3]) && isdigit(line[i + 4]))
        {
            return true;
        }
    }
    return false;
}

bool looksLikeName(std::string const& line)  //Potential problem with this is if someone has a number in their name
{
    for (int i = 0; i < line.size(); i++)
    {
        if (isdigit(line.at(i)))
        {
            return false;
        }
    }
    return true;
}



