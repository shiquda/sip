#include <iostream>
#include <string>

#include "command.h"
#include "algo.h"

void compress(std::string input_path, std::string output_path)
{
    // 实现压缩功能
    std::cout << "正在压缩文件: " << input_path << std::endl;
    std::string s = read_str(input_path);
    std::cout << "Reading file ends.\n";
    std::vector<int> v = lzw_encode(s);
    std::cout << "Encoding ends.\n";
    save_binary(v, output_path);
    std::cout << "压缩完成，输出文件: " << output_path << std::endl;

    // TODO: 添加压缩逻辑
}

void decompress(std::string input_path, std::string output_path)
{
    // 实现解压缩功能
    if (output_path == "")
    {
        output_path = input_path + ".decoded";
    }

    std::cout << "正在解压缩文件: " << input_path << std::endl;
    std::vector<int> v = read_binary(input_path);
    std::string s = lzw_decode(v);
    save_str(s, output_path);
    std::cout << "解压缩完成，输出文件: " << output_path << std::endl;

    // TODO: 添加解压缩逻辑
}

void help()
{
    std::cout << "用法:\nsip help: 查看详细介绍\nsip zip <待压缩文件路径> [输出文件路径]: 压缩文件\nsip unzip <待解压文件路径> [输出文件路径]: 解压缩文件" << std::endl;
}

