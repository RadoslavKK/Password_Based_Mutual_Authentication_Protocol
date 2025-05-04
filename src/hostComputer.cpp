#include "hostComputer.h"
#include "sha256.h"
#include "base64Encoder.h"

HostComputer::HostComputer() : passwordCompare(false) {}

void HostComputer::setPassword(const std::string& pwd) {
    password = pwd;
}

std::string HostComputer::getPasswordSha256() const {
    return passwordSha256;
}

std::string HostComputer::getPasswordBase64() const {
    return passwordBase64;
}

std::string HostComputer::getPasswordBase64Sha256() const {
    return passwordBase64Sha256;
}
