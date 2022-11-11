#pragma once
#include <d3dcompiler.h>
#include <iostream>
//在头文件定义函数要加inline，否则会有重定义问题//
inline void OutputDebugPrintf(const char* strOutputString, ...)
{
#define PUT_PUT_DEBUG_BUF_LEN   1024
    char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
    va_list vlArgs;
    va_start(vlArgs, strOutputString);
    _vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);  //_vsnprintf_s  _vsnprintf
    //vsprintf(strBuffer,strOutputString,vlArgs);
    va_end(vlArgs);
    OutputDebugStringA(strBuffer);  //OutputDebugString    // OutputDebugStringW
}