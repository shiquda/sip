
#include "algo.h"

std::string read_str(std::string input_path)
{
    std::ifstream in(input_path, std::ios::in | std::ios::binary); // 二进制模式读取
    if (!in)
    {
        throw std::runtime_error("Could not open file.");
    }

    in.seekg(0, std::ios::end);    // 定位到文件末尾，获取文件大小
    size_t file_size = in.tellg(); // 获取文件大小
    in.seekg(0, std::ios::beg);    // 回到文件开头

    std::string result(file_size, '\0'); // 预分配内存
    in.read(&result[0], file_size);      // 一次性读取所有内容
    in.close();

    return result;
}

std::string normalize_line_endings(const std::string &s)
{
    std::string result = s;
    result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
    return result;
}

std::vector<int> lzw_encode(std::string s)
{

    // std::unordered_map<std::string, int> str_map;
    // // init ascii
    // for (int i = 1; i < 256; i++)
    // {
    //     std::string sub_str(1, (char)i); // 使用构造函数创建包含一个字符的字符串
    //     str_map[sub_str] = i;
    // }

    // int current_idx = 256;
    // std::vector<int> result;
    // std::string q;

    // for (int i = 0, l = s.size(); i < l; i++)
    // {
    //     char c = s[i];
    //     if (str_map.find(q + c) == str_map.end()) // not found
    //     {
    //         str_map[q + c] = current_idx++;
    //         result.push_back(str_map[q]);
    //         q = c;
    //     }
    //     else // found
    //     {
    //         q += c;
    //     }
    // }
    // if (!q.empty())
    // {
    //     result.push_back(str_map[q]);
    // }
    s = normalize_line_endings(s); // 统一处理换行符为 '\n'

    std::unordered_map<std::pair<int, char>, int, custom_hash> str_map;
    std::vector<int> result;

    // init ascii
    for (int i = 0; i < 256; i++)
    {
        str_map[std::make_pair(0, i)] = i;
    }

    int current_idx = 256;
    int q = 0; // 这里 q 作为整数来追踪前缀

    for (char c : s)
    {
        // 如果在map中找不到组合 (q, c)
        if (str_map.find(std::make_pair(q, c)) == str_map.end())
        {
            result.push_back(q);                           // 把前缀的编码放入结果
            str_map[std::make_pair(q, c)] = current_idx++; // 新组合加入字典
            q = c;                                         // 更新 q 为当前字符的编码
        }
        else
        {
            q = str_map[std::make_pair(q, c)]; // 更新 q 为新组合的编码
        }
    }

    // 如果q还包含剩余的未处理部分，推入结果
    if (q != 0)
    {
        result.push_back(q);
    }

    // output info, including map and result
    if (DEBUG)
    {
        for (auto it = str_map.begin(); it != str_map.end(); it++)
        {
            std::cout << '"' << it->first.first << '"' << " " << it->first.second << '\n';
        }
        for (int i = 0, l = (int)result.size(); i < l; i++)
        {
            std::cout << result[i] << " ";
        }
        std::cout << '\n';

        std::cout << "input_string_length: " << s.size() << '\n';
        std::cout << "result_numbers_length: " << result.size() << '\n';
    }

    return result;
}

void save_binary(std::vector<int> v, std::string output_path)
{
    std::ofstream out(output_path, std::ios::binary);
    unsigned char buffer = 0;
    int bit_count = 0;

    for (int i = 0, l = (int)v.size(); i < l; i++)
    {
        int code = v[i];

        for (int bit = 0; bit < BIT_LIMIT; bit++) // 假设最大编码值需要BIT_LIMIT位
        {
            buffer |= ((code >> bit) & 1) << bit_count;
            bit_count++;

            if (bit_count == 8) // 每满8位写入一个字节
            {
                out.put(buffer);
                buffer = 0;
                bit_count = 0;
            }
        }
    }

    if (bit_count > 0)
    {
        out.put(buffer); // 写入剩余不足8位的部分
    }

    out.close();
}

std::vector<int> read_binary(std::string input_path)
{
    std::ifstream in(input_path, std::ios::binary);
    std::vector<int> result;
    unsigned char buffer;
    int bit_count = 0;
    int code = 0;

    while (in.get((char &)buffer))
    {
        for (int bit = 0; bit < 8; bit++)
        {
            code |= ((buffer >> bit) & 1) << bit_count;
            bit_count++;

            if (bit_count == BIT_LIMIT)
            {
                result.push_back(code);
                code = 0;
                bit_count = 0;
            }
        }
    }

    in.close();
    return result;
}

std::string lzw_decode(std::vector<int> v)
{
    std::unordered_map<int, std::string> str_map;
    for (int i = 1; i < 256; i++)
    {
        std::string sub_str(1, (char)i);
        str_map[i] = sub_str;
    }

    int current_idx = 256;
    std::string result;
    std::string q = str_map[v[0]];
    result += q;

    for (int i = 1, l = (int)v.size(); i < l; i++)
    {
        int k = v[i];
        std::string entry;
        if (str_map.find(k) == str_map.end())
        {
            entry = q + q[0];
        }
        else
        {
            entry = str_map[k];
        }
        result += entry;
        str_map[current_idx++] = q + entry[0];
        q = entry;
    }

    return result;
}

void save_str(std::string s, std::string output_path)
{
    std::ofstream out(output_path);
    out << s;
    out.close();
}
