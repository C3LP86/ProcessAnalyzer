# ProcessAnalyzer
____

***Warning: This code is present for the sole purpose of learning programming in C language.***

ProcessAnalyzer is a tool for displaying running processes.

First, I used EnumProcesses to enumerate the processes by retrieving their IDs, then used OpenProcess and GetModuleBaseNameA to extract the information by retrieving the process handle and their names.

The result is as follows:

![](./Screen/Final_Result.png)
