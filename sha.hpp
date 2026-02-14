#pragma once

#include <filesystem>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

class SHA {
    std::filesystem::path path;
    std::string content;
    std::string hash;

    static uint32_t leftRotate(uint32_t value, uint32_t bits) {
        return (value << bits) | (value >> (32 - bits));
    }

public:
    SHA(const std::filesystem::path& p) : path(p) {
        readFile();
        preprocess();
        compute();
    }

    std::string getHash() const {
        return hash;
    }

private:
    void readFile() {
        std::ifstream input(path, std::ios::binary);
        if (!input) {
            throw std::runtime_error("Failed to open file");
        }

        content.assign(
            std::istreambuf_iterator<char>(input),
            std::istreambuf_iterator<char>()
        );
    }
    void preprocess() {
        uint64_t bitLen = static_cast<uint64_t>(content.size()) * 8;

        content.push_back(static_cast<char>(0x80));

        while (content.size() % 64 != 56) {
            content.push_back(static_cast<char>(0x00));
        }

        // append original length (64-bit big-endian)
        for (int i = 7; i >= 0; --i) {
            content.push_back(static_cast<char>((bitLen >> (i * 8)) & 0xFF));
        }
    }
    void compute() {
        uint32_t h0 = 0x67452301;
        uint32_t h1 = 0xEFCDAB89;
        uint32_t h2 = 0x98BADCFE;
        uint32_t h3 = 0x10325476;
        uint32_t h4 = 0xC3D2E1F0;
        for (size_t i = 0; i < content.size(); i += 64) {

            uint32_t W[80]{};
            for (int j = 0; j < 16; ++j) {
                W[j] =
                    (static_cast<uint8_t>(content[i + j * 4]) << 24) |
                    (static_cast<uint8_t>(content[i + j * 4 + 1]) << 16) |
                    (static_cast<uint8_t>(content[i + j * 4 + 2]) << 8) |
                    (static_cast<uint8_t>(content[i + j * 4 + 3]));
            }
            for (int j = 16; j < 80; ++j) {
                W[j] = leftRotate(W[j - 3] ^ W[j - 8] ^ W[j - 14] ^ W[j - 16], 1);
            }
            uint32_t a = h0;
            uint32_t b = h1;
            uint32_t c = h2;
            uint32_t d = h3;
            uint32_t e = h4;

            // Main loop
            for (int j = 0; j < 80; ++j) {
                uint32_t f, k;

                if (j < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (j < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (j < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }

                uint32_t temp = leftRotate(a, 5) + f + e + k + W[j];
                e = d;
                d = c;
                c = leftRotate(b, 30);
                b = a;
                a = temp;
            }
            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
        }
        std::ostringstream oss;
        oss << std::hex << std::setfill('0')
            << std::setw(8) << h0
            << std::setw(8) << h1
            << std::setw(8) << h2
            << std::setw(8) << h3
            << std::setw(8) << h4;

        hash = oss.str();
    }
};
