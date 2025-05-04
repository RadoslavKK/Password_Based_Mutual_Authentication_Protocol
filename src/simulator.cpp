#include "simulator.h"

#include "hostComputer.h"
#include "clientDevice.h"
#include "fakeClientDevice.h"

#include "sha256.h"
#include "base64Encoder.h"

#include <iostream>
#include <string>

void Simulator::run() {
    std::string input;
    std::cout << "Enter message: ";
    std::getline(std::cin, input);

    SHA256 sha256;
    sha256.update(reinterpret_cast<const uint8*>(input.c_str()), input.length());

    uint8 hash[32];
    sha256.final(hash);

    std::string hex = toHexString(hash);
    std::cout << "SHA-256: " << hex << std::endl;
}
