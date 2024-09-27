---
date: 2024-09-27 14:39:33
updated: 2024-09-27 14:46:47
---

# SIP 压缩工具

## 介绍

SIP是一款基于 LZW 算法的文件压缩和解压缩工具。它旨在通过高效的压缩算法减小文件大小，便于存储和传输。SIP 支持命令行操作，适用于各种操作系统，在 Windows 和 Linux均通过测试。

## 功能

- **文件压缩**：将指定文件压缩为 `.sip` 格式，显著减少文件大小。
- **文件解压缩**：将 `.sip` 格式的压缩文件还原为原始文件。
- **压缩率计算**：在压缩过程中自动计算并显示压缩率。
- **执行时间统计**：记录并显示压缩和解压缩操作的执行时间。

## 使用说明

本工具定义生成的二进制压缩文件的后缀为`.sip`。

### 压缩文件

```bash
sip zip <待压缩文件路径> [输出文件路径]
```

- **示例**：
  ```bash
  sip zip example.txt example.sip
  ```
  若未指定输出路径，默认生成 `example.txt.sip`。

### 解压缩文件

```bash
sip unzip <待解压文件路径> [输出文件路径]
```

- **示例**：
  ```bash
  sip unzip example.sip example_decoded.txt
  ```
  若未指定输出路径，默认生成 `example.sip.decoded`。

### 查看帮助

```bash
sip help
```

## 示例

压缩提供的web访问日志（大约10MB）：

```bash
E:\repo\!cpp\tj\sip\x64\Release>sip
用法:
sip help: 查看详细介绍
sip zip <待压缩文件路径> [输出文件路径]: 压缩文件
sip unzip <待解压文件路径> [输出文件路径]: 解压缩文件

E:\repo\!cpp\tj\sip\x64\Release>sip zip ser.log
正在压缩文件: ser.log
Reading file ends.
Encoding ends.
压缩完成，输出文件: ser.log.sip
Execution time: 1266 ms
Compression ratio: 8.70%

E:\repo\!cpp\tj\sip\x64\Release>sip unzip ser.log.sip
正在解压缩文件: ser.log.sip
解压缩完成，输出文件: ser.log.sip.decoded
Execution time: 249 ms
```

压缩服务器登录日志（大约40MB）：

```bash
E:\repo\!cpp\tj\sip\x64\Release>sip zip auth.log
正在压缩文件: auth.log
Reading file ends.
Encoding ends.
压缩完成，输出文件: auth.log.sip
Execution time: 7251 ms
Compression ratio: 17.23%

E:\repo\!cpp\tj\sip\x64\Release>sip unzip auth.log.sip
正在解压缩文件: auth.log.sip
解压缩完成，输出文件: auth.log.sip.decoded
Execution time: 2055 ms
```


## 项目结构

  - `sip.cpp`：主程序入口，处理命令行参数。
  - `command.cpp`：实现压缩和解压缩功能。
  - `utils.cpp`：实用工具函数，如文件大小获取和压缩率计算。
  - `algo.cpp`：实现 LZW 编码和解码算法。
  - `algo.h`：算法相关的头文件。
  - `command.h`：功能命令相关的头文件。
  - `utils.h`：工具函数的头文件。

