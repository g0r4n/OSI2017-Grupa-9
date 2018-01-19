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
#include <iomanip>
#include <string>
#include <experimental\filesystem>
#include <ctime>
#include <exception>
#include <locale>
#include <cctype>
#include <cstdlib>

#define UserDataFile "Program Files//UserDataFile.txt" //po sklapanju programa, direktorijume fajlova regulisati
#define LogFile "Program Files//InvalidLog.txt"
#define ConfigFile "Program Files//ConfigFile.txt"
#define CurrenciesFile "Program Files//Currencies.txt" //spojiti currencies i config, nema potrebe za dva fajla sa po jednom linijom
#define PDV 0.17

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::getline;

void writeInvalidLogin(string, string);
std::tuple<string, string, string, string, bool> logInCheck(std::fstream& file, string n, string p);
std::tuple<string, string, string, string, bool> logIn();
bool isDateValid(int, int, int); //americki redoslijed (mm,dd,gggg)
bool leapYear(int);
int runIt();
