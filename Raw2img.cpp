/*****************************************************************
Name : 
Date : 2017/06/14
By   : CharlotteHonG
Final: 2017/06/14
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Raw2img.hpp"

using namespace std;
using uch = unsigned char;
//----------------------------------------------------------------
// 寫檔
void Raw::raw2bmp(
    string name, vector<uch>& raw, size_t width, size_t height)
{
    size_t bits = 24;
    // 檔案資訊
    FileHeader file_h = makeFH(width, height, bits);
    // 圖片資訊
    InfoHeader info_h = makeIH(width, height, bits);
    // 寫檔
    fstream img(name, ios::out | ios::binary);
    img << file_h << info_h;
    size_t alig = (4 - width%4)%4;
    for(int j = height-1; j >= 0; --j) {
        for(unsigned i = 0; i < width; ++i) {
            img << raw[(j*width+i)*3 + 2];
            img << raw[(j*width+i)*3 + 1];
            img << raw[(j*width+i)*3 + 0];
        }
        // 對齊4byte
        for(unsigned i = 0; i < alig; ++i)
            img << uch(0);
    }
    img.close();
}
void Raw::raw2graybmp(
    string name, vector<uch>& raw, size_t width, size_t height,
    size_t raw_bit, size_t img_bits)
{
    size_t bits = img_bits;
    // 檔頭
    FileHeader file_h = makeFH(width, height, bits, 54+1024);
    InfoHeader info_h = makeIH(width, height, bits);
    // 寫檔頭
    fstream img(name, ios::out | ios::binary);
    img << file_h << info_h;
    // 寫調色盤
    for(unsigned i = 0; i < 256; ++i) {
        img << uch(i) << uch(i) << uch(i) << uch(0);
    }
    // RAW檔
    size_t alig = (4 - width%4)%4;
    for(int j = height-1; j >= 0; --j) {
        for(unsigned i = 0; i < width; ++i) {
            for(unsigned k = 0; k < bits/8; ++k) {
                if(raw_bit == 24) { // 來源是 rgb
                    img << rgb2gray(&raw[j*width*3+i*3]);
                } else if (raw_bit == 8) { // 來源是 gray
                    img << raw[j*width+i];
                }
            }
        }
        // 對齊4byte
        for(unsigned i = 0; i < alig; ++i)
            img << uch(0);
    }
    img.close();
}
//----------------------------------------------------------------
