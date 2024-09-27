#pragma once
#include <iostream>
#include <string>
#include <chrono>

long long get_file_size(const std::string &file_path);
void calculate_compression_ratio(const std::string &original_file, const std::string &compressed_file);
