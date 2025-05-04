#include "base64Encoder.h"

#include <iostream>
#include <bitset>
#include <string>

std::string base64Encoder(const std::string& data, const std::string& key)
{
    std::string inputText = data;

    // Logs Switch
    bool userLogs = false;
    bool adminLogs = false;

    char inputCharacther = ' ';
    std::string binaryStream = "";

    // Convert each character to its binary (ASCII) representation
    for (unsigned short i = 0; i < inputText.length(); ++i)
    {
        inputCharacther = inputText[i];
        if (adminLogs) std::cout << inputCharacther << "\n";

        std::bitset<8> binary(inputCharacther);
        if (adminLogs) std::cout << binary << "\n";

        binaryStream += binary.to_string();
    }

    if (userLogs) std::cout << binaryStream << "\n";

    unsigned short paddingCount = binaryStream.length() % 6;
    unsigned short charPadding = paddingCount;
    unsigned short padCount = 6;

    if (paddingCount > 0)
    {
        if (userLogs)
        {
            std::cout << "\nBinary Padding is : "
                      << (padCount - paddingCount)
                      << ((padCount - paddingCount) > 1 ? " bits\n" : " bit\n");
        }

        for (; paddingCount < padCount; ++paddingCount)
        {
            binaryStream.append("0");
        }

        if (userLogs)
        {
            std::cout << "\n" << binaryStream << "\n\n";
        }
    }

    std::string base64CharacterSet = key;
    std::string finalStream = "";
    std::string shortBinaryStream = "";

    unsigned short binaryStreamSize = 6;
    unsigned int decimalNumber = 0;
    char app = ' ';

    for (unsigned short i = 0; i < binaryStream.length(); i += 6)
    {
        shortBinaryStream = binaryStream.substr(i, binaryStreamSize);

        if (adminLogs)
        {
            std::cout << " = " << shortBinaryStream << "\n";
        }

        decimalNumber = std::stoi(shortBinaryStream, nullptr, 2);

        if (adminLogs)
        {
            std::cout << " == " << decimalNumber << "\n\n";
        }

        app = base64CharacterSet[decimalNumber];
        finalStream += app;
    }

    // Append '=' padding
    if (charPadding == 2)
    {
        finalStream.append("==");
    }
    else if (charPadding == 4)
    {
        finalStream.append("=");
    }

    return finalStream;
}