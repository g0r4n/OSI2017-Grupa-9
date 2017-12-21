#pragma once
#include <fstream>
#include <iostream>
#include <cctype>
#include <conio.h>
#include <algorithm>
#include <stdlib.h>
#include <tuple>
#include <Windows.h>
#include <functional>
#include <string>
#include <vector>

#define UserDataFile "UserDataFile.txt" //po sklapanju programa, direktorijume fajlova regulisati
#define LogFile "InvalidLog.txt"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;

void writeInvalidLogin(string, string);
std::tuple<string, string, string, string, bool> logInCheck(std::fstream& file, string n, string p);
std::tuple<string, string, string, string, bool> logIn();