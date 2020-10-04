#include "Player.h"
#include <iostream>


Player::Player()
{
    GHIN = "",
    name = "",
    firstName = "",
    middleName = "",
    lastName = "";

    handicap = 1000.f;

    whiteteeStrokes = 1000,
    blueteeStrokes = 1000,
    tournamentteeStrokes = 1000,
    goldteeStrokes = 1000,
    blackteeStrokes = 1000;


}

void Player::printPlayerInfo()
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