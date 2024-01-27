# IR

## 3AC 三地址码

    等号右边只有一个操作符

## SSA 静态单赋值

    变量新名字 传播用 每个变量定义一次

![1706340963247](image/IR/1706340963247.png)

## Control Flow Analysis 控制流分析

    Control Flow Graph CFG 控制流程图

## Basic  Blocks BB

    Basic blocks (BB) are maximal sequences of consecutive three-address instructions with the properties thatIt can be entered only at the beginning, i.e., the first instruction in the blockIt can be exited only at the end, i.e., the last instruction in the block

    基本块(BB)是连续三地址指令的最大序列，其性质为它只能在开头输入，即在块中的第一条指令它只能在结束时退出，即块中的最后一条指令

## 一个完整的CFG

    ![1706345172045](image/IR/1706345172045.png)

# Data Flow Analysis

## Overview

    Preliminaries of Data Flow Analysis

    Reaching Definitions Analysis

    Live Variables Analysis

    Available Expressions Analysis

## DFA基础
