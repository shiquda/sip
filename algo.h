#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>


struct custom_hash // 自定义哈希函数：<int, char> -> size_t
{
    std::size_t operator()(const std::pair<int, char>& p) const {
        // 使用 std::hash 对各个成员分别哈希，并组合它们的哈希值
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<char>{}(p.second);
        // 组合哈希值，常用的方式是通过异或操作和位移
        return h1 ^ (h2 << 1); // h2 左移 1 位，避免简单的冲突
    }
};


const int BIT_LIMIT = 24;
const bool DEBUG = false;

std::string read_str(std::string input_path);
std::vector<int> lzw_encode(std::string s);
void save_binary(std::vector<int> v, std::string output_path);

std::vector<int> read_binary(std::string input_path);
std::string lzw_decode(std::vector<int> v);
void save_str(std::string s, std::string output_path);
