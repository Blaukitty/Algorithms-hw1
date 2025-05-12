#include "decoder_h.h"          // объявления encode / decode
#include <iostream>
#include <stdexcept>

int main() {
    try {
        std::string encoded = encode(std::cin);            // читаем stdin
        std::cout << "Encode: -e " << encoded << '\n';

        std::cout << "Decoded: -d ";
        decode(encoded, std::cout);                        // печатаем raw
    }
    catch (const std::exception& e) {
        std::cerr << "Decoding error: " << e.what() << '\n';
        return 1;                                          // важно для «bad input»
    }
    return 0;
}
