// demos.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

std::string leftTrim(std::string s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c); }));
	return s;
}

int main()
{
	std::cout << leftTrim("some example bytes as text");
}

