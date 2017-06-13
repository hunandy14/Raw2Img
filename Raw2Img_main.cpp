/*****************************************************************
Name :
Date : 2017/06/11
By   : CharlotteHonG
Final: 2017/06/11
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Raw2Img.hpp"
using namespace std;

class Raw {
private:
    using uch = unsigned char;
    static uch rgb2gray(uch* p){
        return static_cast<uch>(
            0.299 * static_cast<float>(*(p+R))+
            0.587 * static_cast<float>(*(p+G))+
            0.114 * static_cast<float>(*(p+B))
        );
    }
public:
    // 讀檔
    static void read_raw(vector<uch>& raw, string name) {
        fstream file(name.c_str(), ios::in | ios::binary | ios::ate);
        raw.resize(file.tellg());
        file.seekg(0, ios::beg);
        file.read((char*)raw.data(), raw.size());
        file.close();
    }
    // 轉灰階
    static void raw2gray(vector<uch>& raw){
        raw2gray(raw, raw);
    }
    static void raw2gray(vector<uch>& gray, vector<uch>& raw){
        // 判定相等
        if(&gray!=&raw)
            gray.resize(raw.size()/3);
        // 轉換
        for(unsigned i = 0; i < raw.size()/3; ++i)
            gray[i] = rgb2gray(&raw[i*3]);
        gray.resize(raw.size()/3);
    }

    // 寫檔
    static void raw2bmp(
        string name, vector<uch>& raw, size_t width, size_t height)
    {
        size_t bits = 24;
        size_t ch = bits/8;
        // 檔案資訊
        size_t alig = (4 - width%4)%4;
        FileHeader file_h;
        file_h.size = file_h.headSize + width*height*ch;
        // 圖片資訊
        InfoHeader info_h;
        info_h.width = width;
        info_h.height = height;
        info_h.bits = bits;
        info_h.imagesize = 0;
        info_h.xresolution=0;
        info_h.yresolution=0;
        // 二維讀取RGB
        auto at2d3c = [&](size_t y, size_t x, RGB_t rgb)-> uch& {
            return raw[(y*width+x)*3 + rgb];
        };
        // 寫檔
        fstream img(name, ios::out | ios::binary);
        img << file_h << info_h;
        for(int j = height-1; j >= 0; --j) {
            for(unsigned i = 0; i < width; ++i) {
                img << at2d3c(j, i, B);
                img << at2d3c(j, i, G);
                img << at2d3c(j, i, R);
            }
            // 對齊4byte
            for(unsigned i = 0; i < alig; ++i)
                img << uch(0);
        }
        img.close();
    }

    static void raw2graybmp2(
        string name, vector<uch>& raw, size_t width, size_t height,
        size_t raw_bit=24, size_t img_bit=8)
    {
        size_t bits = img_bit;
        size_t ch = bits/8;
        // 檔案資訊
        size_t alig = (4 - width%4)%4;
        FileHeader file_h;
        file_h.size = file_h.headSize + width*height*ch;
        // 圖片資訊
        InfoHeader info_h;
        info_h.width = width;
        info_h.height = height;
        info_h.bits = bits;
        info_h.imagesize = 0;
        info_h.xresolution=0;
        info_h.yresolution=0;
        // 來源如果是 24bit
        // vector<uch> gray_raw;
        // vector<uch>* rawp = &gray_raw;
        // if(raw_bit == 24) {
        //     raw2gray(gray_raw, raw);
        // } else if (raw_bit == 8) {
        //     rawp = &raw;
        // }
        // 寫檔頭
        fstream img(name, ios::out | ios::binary);
        img << file_h << info_h;
        // 調色盤
        for(unsigned i = 0; i < 256; ++i) {
            img << uch(i) << uch(i) << uch(i) << uch(0);
        }
        // RAW檔
        for(int j = height-1; j >= 0; --j) {
            for(unsigned i = 0; i < width; ++i) {
                for(unsigned k = 0; k < img_bit/8; ++k) {
                    if(raw_bit == 24) {
                        img << rgb2gray(&raw[j*width*3+i*3]);
                    } else if (raw_bit == 8) {
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

    static void raw2graybmp(
        string name, vector<uch>& raw, size_t width, size_t height)
    {
        size_t bits = 8;
        size_t ch = bits/8;
        // 檔案資訊
        size_t alig = (4 - width%4)%4;
        FileHeader file_h;
        file_h.size = file_h.headSize + width*height*ch;
        // 圖片資訊
        InfoHeader info_h;
        info_h.width = width;
        info_h.height = height;
        info_h.bits = bits;
        info_h.imagesize = 0;
        info_h.xresolution=0;
        info_h.yresolution=0;
        // 二維讀取RGB
        auto at2d3c = [&](size_t y, size_t x, RGB_t rgb)-> uch& {
            return raw[(y*width+x)*3 + rgb];
        };
        // 轉灰階
        auto gray = [&](size_t y, size_t x)-> uch {
            double gray = 0;
            gray += 0.299*(float)at2d3c(y, x, R);
            gray += 0.587*(float)at2d3c(y, x, G);
            gray += 0.114*(float)at2d3c(y, x, B);
            return gray;
        };
        // 寫檔
        fstream img(name, ios::out | ios::binary);
        img << file_h << info_h;
        // 著色盤
        for(unsigned i = 0; i < 256; ++i) {
            img << uch(i);
            img << uch(i);
            img << uch(i);
            img << uch(0);
        }
        // RAW檔
        for(int j = height-1; j >= 0; --j) {
            for(unsigned i = 0; i < width; ++i) {
                img << gray(j, i);
            }
            // 對齊4byte
            for(unsigned i = 0; i < alig; ++i)
                img << uch(0);
        }
        img.close();
    }
};
//================================================================
int main(int argc, char const *argv[]) {
    vector<unsigned char> raw;

    // const char* rawName="Seymour_Park_960x540_24bit.raw";
    // const char* bmpName="Seymour_Park.bmp";
    // Raw::read_raw(raw, rawName);
    // Raw::raw2bmp(bmpName, raw, 960, 540, 24);
    // system(bmpName);

    // fstream file("Seymour_Park_g.bmp", ios::in | ios::binary | ios::ate);
    // raw.resize(file.tellg());
    // file.seekg(0, ios::beg);
    // file.read((char*)raw.data(), raw.size());
    // file.close();

    

    // fstream file2("pla.txt", ios::out | ios::binary);
    // file2.write((char*)raw.data()+36, 1024);
    
    const char* rawName2="Seymour_Park_960x540_24bit.raw";
    const char* bmpName2="Seymour_Park_gray.bmp";
    Raw::read_raw(raw, rawName2);

    // Raw::raw2gray(raw);

    Raw::raw2graybmp2(bmpName2, raw, 960, 540, 24, 24);
    system(bmpName2);
    return 0;
}
//================================================================
