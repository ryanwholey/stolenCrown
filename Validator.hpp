/****************************************************************
 * Program: Lab 9
 * Name: Ryan Wholey
 * Date: 5/1/17
 * Description: Group of functions to help with user
 * input validation.
 * **************************************************************/

#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <iostream>
#include <string>

// checks if passed string can be int between a min & max
bool validateIntInRange(std::string, int, int);
// checks if passed string has valid int characters
bool isInt(std:: string);
// checks if passed string can be parsed like <int>,<int>
bool validateTwoInts(std::string);
// checks if passed is float
bool validatePrice(std::string);
// check if int (can be + or -)
bool validatePosOrNegInt(std::string);

#endif

