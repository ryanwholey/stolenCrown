/****************************************************************
 * Program: Lab 9
 * Name: Ryan Wholey
 * Date: 5/1/17
 * Description: Group of functions to help with user
 * input validation.
 * **************************************************************/

#include "Validator.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::string;


/***************************************************************
 *						validateIntInRange
 *
 * Use to see if the string passed (when converted to an int) is
 * between the passed min and max. returns findings.
 * ************************************************************/
bool validateIntInRange(string in, int min, int max)
{
    if (!isInt(in))
    {
        return false;
    }

    int choice = stoi(in);

    if (choice < min || choice > max)
    {
        cout << "Your input is out of range" << endl;
        return false;
    }

    return true;
}

/***************************************************************
 *						isInt
 *
 * Takes string and checks that it has only valid int characters
 * then returns findings
 * ************************************************************/
bool isInt(string in)
{
    string nums = "0123456789";
    int inLength = in.length();

    if (inLength == 0) {
        cout << "Empty entry is not an integer" << endl;
        return false;
    }

    for (int i = 0; i < inLength; i++)
    {
        if (nums.find(in.at(i)) == string::npos)
        {
            cout << "Invalid input"	 << endl;
            return false;
        }
    }

    return true;
}


/***************************************************************
 *						validateTwoInts
 *
 * Take string and looks to see if it can parsed into two
 * integers split by a comma. returns findings
 * ************************************************************/
bool validateTwoInts(string in )
{
    string numsAndComma = "0123456789,";
    bool isClean = true;
    int commaCount = 0;
    int inLength = in.length();

    // looks at each char to see if its in numsAndComma
    for (int i = 0; i < inLength; i++)
    {
        if (isClean)
        {
            char c = in.at(i);
            if (c == ',' && (i != 0 && i != inLength -1))
            {
                commaCount++;
            }
            if (numsAndComma.find(c) == string::npos)
            {
                isClean = false;
            }
        }
    }
    // if 1 comma found and clean so far, checks that
    // strings on each side of comma are valid potential ints
    if (isClean && commaCount == 1) {
        int comma = in.find(',');
        string xString = in.substr(0, comma);
        string yString = in.substr(comma+1);

        if (
                (xString.length() > 1 && xString.at(0) == '0') ||
                (yString.length() > 1 && yString.at(0) == '0')
           )
        {
            isClean = false;
        }
    }

    return isClean && commaCount == 1;
}

/**************************************************************
 *						validatePrice
 * Takes a string and determines whether it can be converted
 * to a float properly
 * ***********************************************************/
bool validatePrice(std::string in)
{
    string numsAndDot = "0123456789.";
    bool isClean = true;
    int dotCount = 0;
    int inLength = in.length();

    // looks at each char to see if its in numsAndDot
    for (int i = 0; i < inLength; i++)
    {
        if (isClean)
        {
            char c = in.at(i);
            if (c == '.')
            {
                dotCount++;
            }
            if (numsAndDot.find(c) == string::npos)
            {
                isClean = false;
            }
        }
    }

    if (dotCount > 1)
    {
        isClean = false;
    }

    return isClean;
}

/***************************************************************
 *						validatePosOrNegInt
 *
 * takes a string and determines whether or not the number
 * can be safely converted into an integer (positive or negative)
 * Doubles are not accepted
 * ************************************************************/
bool validatePosOrNegInt(std::string in)
{
    if (in.find('-') != string::npos)
    {
        return isInt(in.substr(1));
    }

    return isInt(in);
}

