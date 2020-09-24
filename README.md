## Introduction
Refers to these documents: 
https://zhuanlan.zhihu.com/p/66958390
https://github.com/flame/how-to-optimize-gemm/wiki
This repo includes the step-to-step optimization of GEMM

## Result on My Desktop
M = 200
N = 200
K = 200

### Baeline
按照计算逻辑的顺序去做计算 耗时: 160 ms

### loop unroll 1x4小块计算
一次性计算4个相邻的数据结果，将大循环展开成4个的小循环，这样有重复使用的数据，将这个数据放入到寄存器里面
主要的优化点就是减小对内存的访问，重复使用的数据放到寄存器里面
optimization1 大幅提高性能到 63ms

### loop unroll 4x4小块计算
* 进一步减小对内存的访问
optimization2 大幅提高性能到 30ms

### 向量化运算
* SIMD向量化运算 利用128位寄存器进行运算           
optimization3 提高性能到 27ms

### 并行化运算 在optimization3的基础上利用多核特性 4 core
optimization4 提高性能到 7ms, 相对于最初提高了将近22倍

### 在optimization3 基础上 沿着reduction 维度展开并使用AVX512 指令
* 利用256位寄存器进行运算   AVX2 on my I7 CPU, 16 YMM register


## 下一步
* 256位进一步向量化 对 矩阵内存排布的要求
* 并行化的粒度选择


## Check Memory Leak
```
apt install valgrind

valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1
```
