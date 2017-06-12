//***********************************************************//
//Company       :   KUAS                                     //
//***********************************************************//
//File          :   Bmp.hpp                                  //
//Author        :   YAN,RUI-YING                             //
//Language      :   C++                                      //
//IDE           :   Microsoft Visual Studio 2017             //
//OS            :   Windows 10                               //
//Date          :   2017/05/09                               //
//***********************************************************//
#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
// total 14 bytes
struct FILE_HEADER 
{
	WORD type;
	DWORD size;
	WORD reserved1;
	WORD reserved2;
	DWORD offset;
};
// total 40 bytes
struct INFO_HEADER 
{
	DWORD size;
	int width;
	int height;
	WORD planes;
	WORD bits;
	DWORD compression;
	DWORD imagesize;
	int xresolution;
	int yresolution;
	DWORD ncolours;
	DWORD importantcolours;
};
/*************************** Function Prototypes *****************************/
extern void RawToBmp(std::string filename, std::vector<BYTE> &data, int width, int height);
extern void RawToBmpGray(std::string filename, std::vector<BYTE> &data, int width, int height);