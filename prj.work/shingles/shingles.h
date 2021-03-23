// Copyright 2021 by Mikhail Ivanov under Free Public License 1.0.0
#pragma once
#ifndef SHINGLES_H
#define SHINGLES_H
#include<iostream>
#include<string>
#include<locale>
#include<functional>
#include<cctype>
#include<algorithm>
#include<vector>
#include <chrono>
#include<fstream>
std::vector<std::string> canonize(std::string sh);
std::string readFile(const std::string& fileName);
unsigned int CRC32(std::string source);
std::vector<unsigned int> genshingle(std::vector<std::string> source, int shingleLen);
double compaire(std::vector<unsigned int>cmp1, std::vector<unsigned int>cmp2);

#endif
