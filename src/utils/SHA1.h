#pragma once

#include <iomanip>
#include <sstream>

namespace CarbonLab {
    class SHA1 {
    public:
        SHA1() { reset(); }

        void update(const std::string &data) {
            update(reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
        }

        void update(const uint8_t *data, size_t len) {
            totalLength += len;
            for (size_t i = 0; i < len; ++i) {
                buffer[bufferOffset++] = data[i];
                if (bufferOffset == 64) {
                    transform(buffer);
                    bufferOffset = 0;
                }
            }
        }

        std::string final() {
            uint64_t totalBits = totalLength * 8;

            // Append 0x80
            update((uint8_t*)"\x80", 1);

            // Pad with zeros until 56 bytes mod 64
            uint8_t zero = 0;
            while (bufferOffset != 56) {
                update(&zero, 1);
            }

            // Append length in bits (big-endian)
            uint8_t lengthBytes[8];
            for (int i = 0; i < 8; ++i) {
                lengthBytes[7 - i] = totalBits >> (i * 8);
            }
            update(lengthBytes, 8);

            // Output hash as hex
            std::ostringstream result;
            for (int i = 0; i < 5; ++i) {
                result << std::hex << std::setw(8) << std::setfill('0') << state[i];
            }
            return result.str();
        }

    private:
        uint32_t state[5]{};
        uint64_t totalLength{};
        uint8_t buffer[64]{};
        size_t bufferOffset{};

        void reset() {
            state[0] = 0x67452301;
            state[1] = 0xEFCDAB89;
            state[2] = 0x98BADCFE;
            state[3] = 0x10325476;
            state[4] = 0xC3D2E1F0;
            totalLength = 0;
            bufferOffset = 0;
        }

        static uint32_t rol(uint32_t value, size_t bits) {
            return (value << bits) | (value >> (32 - bits));
        }

        void transform(const uint8_t block[64]) {
            uint32_t w[80];
            for (int i = 0; i < 16; ++i) {
                w[i] = (block[i*4] << 24) |
                    (block[i*4 + 1] << 16) |
                    (block[i*4 + 2] << 8) |
                    (block[i*4 + 3]);
            }
            for (int i = 16; i < 80; ++i) {
                w[i] = rol(w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16], 1);
            }

            uint32_t a = state[0];
            uint32_t b = state[1];
            uint32_t c = state[2];
            uint32_t d = state[3];
            uint32_t e = state[4];

            for (int i = 0; i < 80; ++i) {
                uint32_t f, k;
                if (i < 20) {
                    f = (b & c) | ((~b) & d);
                    k = 0x5A827999;
                } else if (i < 40) {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if (i < 60) {
                    f = (b & c) | (b & d) | (c & d);
                    k = 0x8F1BBCDC;
                } else {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }
                uint32_t temp = rol(a, 5) + f + e + k + w[i];
                e = d;
                d = c;
                c = rol(b, 30);
                b = a;
                a = temp;
            }

            state[0] += a;
            state[1] += b;
            state[2] += c;
            state[3] += d;
            state[4] += e;
        }
    };

}