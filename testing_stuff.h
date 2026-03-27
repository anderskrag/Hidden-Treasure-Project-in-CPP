#pragma once
#include "AnimationWindow.h"
#include <filesystem>
#include "fstream"
#include "map"
#include "string"


void loadBoard(std::filesystem::path filename);

const std::map<char, TDT4102::Color> charToColor {
    {'E', TDT4102::Color::maroon},          //Empty
    {'W', TDT4102::Color::purple},          //Wall
    {'#', TDT4102::Color::saddle_brown},    //Rock  
    {' ', TDT4102::Color::transparent},     //No rock
    {'S', TDT4102::Color::deep_skyblue},
    {'L', TDT4102::Color::green},    
};