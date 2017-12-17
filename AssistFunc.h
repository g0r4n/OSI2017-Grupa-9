#pragma once
#include<string>
#include<fstream>
#include<iostream>
#include<cctype>
#include<conio.h>
#include<algorithm>
#include<stdlib.h>
#include<tuple>
#include<Windows.h>

#define UserDataFile "C:\\Users\\Kot\\Desktop\\UserDataFile.txt" //po sklapanju programa, direktorijume fajlova regulisati
#define LogFile "C:\\Users\\Kot\\Desktop\\InvalidLog.txt"

void writeInvalidLogin(std::string n, std::string ln, std::string p);
int logInCheck(std::fstream& file, std::string n, std::string ln, std::string p);
std::tuple<std::string, std::string, std::string, int> logIn();