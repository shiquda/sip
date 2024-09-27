#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "utils.h"
#include "algo.h"

long long get_file_size(const std::string &file_path)
{
    std::ifstream file(file_path, std::ios::binary | std::ios::ate); // 以二进制模式打开文件，并将指针设置到文件末尾
    if (DEBUG)
        std::cout << "size of " << file_path << " :" << file.tellg() << std::endl;
    return (long long)file.tellg(); // 返回文件大小
}

void calculate_compression_ratio(const std::string &original_file, const std::string &compressed_file)
{
    long long original_size = get_file_size(original_file);
    long long compressed_size = get_file_size(compressed_file);

    // 使用 double 强制转换以确保正确计算浮点结果
    double compression_ratio = static_cast<double>(compressed_size) / original_size * 100;

    std::cout << "Compression ratio: " << std::fixed << std::setprecision(2) << compression_ratio << "%" << std::endl;
}
