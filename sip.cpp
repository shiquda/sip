

#include "command.h"
#include "utils.h"
#include "algo.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        help();
        return 1;
    }
    std::string operation = argv[1];
    std::string input_path = argv[2];
    std::string output_path = "";

    if (argc == 4)
        output_path = argv[3];

    if (operation == "zip")
    {
        if (input_path == "")
        {
            help();
            return 1;
        }
        if (output_path == "")
        {
            output_path = input_path + ".sip";
        }
        // 获取当前时间作为起点
        auto start = std::chrono::high_resolution_clock::now();
        compress(input_path, output_path);
        // 获取当前时间作为终点
        auto end = std::chrono::high_resolution_clock::now();
        // 计算时间差，单位是微秒
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Execution time: " << duration / 1000 << " ms" << std::endl;
        // 计算前后文件压缩率，保留2位小数
        calculate_compression_ratio(input_path, output_path);
    }
    else if (operation == "unzip")
    {
        if (input_path == "")
        {
            help();
            return 1;
        }
        // 获取当前时间作为起点
        auto start = std::chrono::high_resolution_clock::now();
        decompress(input_path, output_path);
        auto end = std::chrono::high_resolution_clock::now();
        // 计算时间差，单位是微秒
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Execution time: " << duration / 1000 << " ms" << std::endl;
    }
    else
    {
        std::cout << "无效的操作。请使用 'zip' 或 'unzip'。" << std::endl;
        help();
        return 1;
    }

    return 0;
}
