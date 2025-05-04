#ifndef SHA256_H
#define SHA256_H

#include <string>
#include <cstring>
#include <iostream>

typedef unsigned int uint32;
typedef unsigned char uint8;

class SHA256 {
public:
    SHA256();
    void update(const uint8* data, size_t len);
    void final(uint8 hash[32]);

private:
    void transform(const uint8* chunk);

    uint32 h[8];
    uint8 buffer[64];
    uint32 datalen;
    unsigned long long bitlen;
};

std::string toHexString(const uint8 hash[32]);

#endif // SHA256_H
