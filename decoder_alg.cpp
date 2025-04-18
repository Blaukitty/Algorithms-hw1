﻿// decoder_alg.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <array>
#include <cstdint>
#include <sstream>
#include <string>
#include <stdexcept>
#include "decoder_h.h"

using namespace std;

string encode(istream& in) {
        array<char, 4> byte;
        ostringstream out;
        
    while (in) {

        in.read(byte.data(), byte.size());  // прочитали поток, поделили по 4 байта
        streamsize Bytes = in.gcount();
        if (Bytes == 0) // закончили считывать
            break;

        uint32_t val = 0; //переменная 32 бит т.е 4 байта
        for (int i = 0; i < Bytes; ++i) {  
            val |= static_cast<uint8_t>(byte[i]) << (24 - i * 8);  // побитно закинули в переменную 4 байта
        }
    

        if (Bytes == 4 and val == 0) {  // оптимизировали - заменили 4*0 на z
            out.put('z');
            continue;
        }

        char encoded[5];               // переводим в пятибайтовую систему ascii85
        for (int j = 4; j >= 0; --j) {
            encoded[j] = static_cast<char>(val % 85 + 33);  // static_cast - преобразование одного типа в другой при компеляции
            val /= 85;
        }

        for (int l = 0; l < Bytes + 1; ++l) {  // возвращаем по 5 бит закодированные ascii символы
            out.put(encoded[l]);
        }
    }

    out << "~>";  // стандарт кодировки
    return out.str();
}

void decode(const string& input, ostream& out) {
    if (input.empty()) {                                 // для поиска ошибок
        throw runtime_error("incorrect data for coding");
    }
    for (char c : input) {
        if (c < '!' || c > 'u') {
            throw runtime_error("Incorrect data for decoding: invalid character detected");
        }
    }
    size_t i = 0;
    string encoded = input;
    while (i < encoded.size()) {
        if (encoded[i] == 'z') {
            out.write("\0\0\0\0", 4);
            ++i;
            continue;
        }

        size_t block_len = min(size_t(5), encoded.size() - i);
        string block = encoded.substr(i, block_len);
        i += block_len;

        while (block.size() < 5) {
            block += 'u';
        }

        uint32_t val0 = 0;
        for (char c : block) {
            val0 = val0 * 85 + (static_cast<uint8_t>(c) - 33);
        }

        array<char, 4> decoded = {
            static_cast<char>((val0 >> 24) & 0xFF),
            static_cast<char>((val0 >> 16) & 0xFF),
            static_cast<char>((val0 >> 8) & 0xFF),
            static_cast<char>(val0 & 0xFF)
        };

        int my_bytes = block_len - 1;
        out.write(decoded.data(), my_bytes);
    }
    
}

int main()
{
    string result;
    try {     result = encode(cin); // кодируем
      cout << "Encode: -e " << result << "\n";
      cout << "Decoded: -d ";     decode(result, cout); // пробуем декодировать
  }
    catch (const exception& e) {     cerr << "Decoding error: " << e.what() << "\n";
      return 1; }
    return 0;
}
