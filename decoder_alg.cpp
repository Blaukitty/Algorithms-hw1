// decoder_alg.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "decoder_h.h"
#include <iostream>
#include <array>
#include <cstdint>
#include <sstream>
#include <string>
#include <stdexcept>

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

void decode(const std::string& input, std::ostream& out)
{
    // 1.  отделяем тело и проверяем, есть ли "~>"
    std::string body;
    if (input.size() >= 2 && input.substr(input.size()-2) == "~>")
        body = input.substr(0, input.size()-2);      // отбрасываем
    else
        body = input;                               

    if (body.empty())
        throw std::runtime_error("empty input");

    // 2.  проверка что все символы корректны и не z
    for (char c : body)
        if (c!='z' && (c<'!' || c>'u'))
            throw std::runtime_error("invalid character detected");

    
    //  проверка z  
    size_t i = 0;
    while (i < body.size()) {
        if (body[i] == 'z') {
            out.write("\0\0\0\0", 4);
            ++i;
            continue;
        }

        size_t block_len = std::min<size_t>(5, body.size() - i);  // разбили строку по 5
        std::string block = body.substr(i, block_len);
        i += block_len;

        while (block.size() < 5) block += 'u';

        uint32_t val = 0;
        for (char c : block)
            val = val * 85 + (static_cast<uint8_t>(c) - 33);

        char bytes[4] = {
            static_cast<char>((val >> 24) & 0xFF),
            static_cast<char>((val >> 16) & 0xFF),
            static_cast<char>((val >>  8) & 0xFF),
            static_cast<char>( val        & 0xFF)
        };
        out.write(bytes, block_len - 1);
    }
}

//int main()
//{
//    string result;
//     try {     result = encode(cin); // кодируем
//       cout << "Encode: -e " << result << "\n";
//       cout << "Decoded: -d ";     decode(result, cout); // пробуем декодировать
//   }
//     catch (const exception& e) {     cerr << "Decoding error: " << e.what() << "\n";
//       return 1; }
//     return 0;
// }
