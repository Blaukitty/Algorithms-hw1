// decoder_alg.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#pragma once

#include <iostream>
#include <string>

// Кодирует данные из входного потока в строку ASCII85
std::string encode(std::istream& in);

// Декодирует строку ASCII85 и записывает результат в выходной поток
void decode(const std::string& encoded, std::ostream& out);
