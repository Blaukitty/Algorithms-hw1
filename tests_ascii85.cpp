#include <gtest/gtest.h>
#include <sstream>
#include "decoder_h.h"  // если реализуешь отдельно encode/decode

// Если реализация в одном cpp-файле — просто подключи encode и decode напрямую

TEST(Ascii85Test, EncodeSimpleText) {
    std::string input = "Hello";
    std::stringstream ss(input);

    std::string result = encode(ss);

    // Проверим, что строка начинается с 5 ascii85-символов + "~>"
    ASSERT_TRUE(result.size() > 5);
    ASSERT_EQ(result.substr(result.size() - 2), "~>");
}

TEST(Ascii85Test, EncodeAllZeroBytes) {
    std::string input = "\0\0\0\0";
    std::stringstream ss(input);

    std::string result = encode(ss);

    ASSERT_EQ(result, "z~>");  // "z" означает 4 нулевых байта
}

TEST(Ascii85Test, DecodeSimpleBlock) {
    std::string encoded = "87cURD_*#TDfTZ)+T";
    std::stringstream out;

    decode(encoded, out);

    ASSERT_EQ(out.str(), "Hello, world!");
}

TEST(Ascii85Test, EncodeDecodeRoundTrip) {
    std::string original = "Test 123456789 abcdefghij";
    std::stringstream in(original);

    std::string encoded = encode(in);

    std::stringstream decoded;
    decode(encoded.substr(0, encoded.size() - 2), decoded);  // удаляем "~>"

    ASSERT_EQ(decoded.str(), original);
}

TEST(Ascii85Test, EmptyInput) {
    std::stringstream ss("");
    std::string result = encode(ss);

    ASSERT_EQ(result, "~>");
}
