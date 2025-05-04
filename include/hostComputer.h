#ifndef HOST_COMPUTER_H
#define HOST_COMPUTER_H

#include <string>

class HostComputer {
private:
    std::string password;
    std::string passwordSha256;
    std::string passwordBase64;
    std::string passwordBase64Sha256;

    bool passwordCompare;

public:
    HostComputer();
    
    void setPassword(const std::string& pwd);
    void computeHashes();
    bool comparePassword(const std::string& input);

    std::string getPasswordSha256() const;
    std::string getPasswordBase64() const;
    std::string getPasswordBase64Sha256() const;
};

#endif // HOST_COMPUTER_H
