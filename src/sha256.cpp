#include "sha256.h"

const uint32 k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

inline uint32 ROTRIGHT(uint32 a, uint32 b) {
    return ((a >> b) | (a << (32 - b)));
}

inline uint32 CH(uint32 x, uint32 y, uint32 z) {
    return ((x & y) ^ (~x & z));
}

inline uint32 MAJ(uint32 x, uint32 y, uint32 z) {
    return ((x & y) ^ (x & z) ^ (y & z));
}

inline uint32 EP0(uint32 x) {
    return ROTRIGHT(x, 2) ^ ROTRIGHT(x, 13) ^ ROTRIGHT(x, 22);
}

inline uint32 EP1(uint32 x) {
    return ROTRIGHT(x, 6) ^ ROTRIGHT(x, 11) ^ ROTRIGHT(x, 25);
}

inline uint32 SIG0(uint32 x) {
    return ROTRIGHT(x, 7) ^ ROTRIGHT(x, 18) ^ (x >> 3);
}

inline uint32 SIG1(uint32 x) {
    return ROTRIGHT(x, 17) ^ ROTRIGHT(x, 19) ^ (x >> 10);
}

SHA256::SHA256() {
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
    datalen = 0;
    bitlen = 0;
}

void SHA256::update(const uint8* data, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        buffer[datalen++] = data[i];
        if (datalen == 64) {
            transform(buffer);
            bitlen += 512;
            datalen = 0;
        }
    }
}

void SHA256::final(uint8 hash[32]) {
    size_t i = datalen;

    buffer[i++] = 0x80;
    if (datalen < 56) {
        while (i < 56) buffer[i++] = 0x00;
    } else {
        while (i < 64) buffer[i++] = 0x00;
        transform(buffer);
        memset(buffer, 0, 56);
    }

    bitlen += datalen * 8;
    for (int j = 0; j < 8; ++j)
        buffer[63 - j] = (uint8)(bitlen >> (j * 8));

    transform(buffer);

    for (i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 8; ++j)
            hash[i + j * 4] = (uint8)((h[j] >> (24 - i * 8)) & 0x000000ff);
    }
}

void SHA256::transform(const uint8* data) {
    uint32 m[64], a, b, c, d, e, f, g, h0, t1, t2;

    for (uint32 i = 0, j = 0; i < 16; ++i, j += 4)
        m[i] = (data[j] << 24) | (data[j + 1] << 16) |
               (data[j + 2] << 8) | (data[j + 3]);

    for (uint32 i = 16; i < 64; ++i)
        m[i] = SIG1(m[i - 2]) + m[i - 7] + SIG0(m[i - 15]) + m[i - 16];

    a = h[0];
    b = h[1];
    c = h[2];
    d = h[3];
    e = h[4];
    f = h[5];
    g = h[6];
    h0 = h[7];

    for (uint32 i = 0; i < 64; ++i) {
        t1 = h0 + EP1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = EP0(a) + MAJ(a, b, c);
        h0 = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += h0;
}

std::string toHexString(const uint8 hash[32]) {
    static const char hex_chars[] = "0123456789abcdef";
    std::string result;
    for (int i = 0; i < 32; ++i) {
        result += hex_chars[(hash[i] >> 4) & 0x0F];
        result += hex_chars[hash[i] & 0x0F];
    }
    return result;
}
