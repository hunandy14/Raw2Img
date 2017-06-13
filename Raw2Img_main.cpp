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
    // byte4 型別
    union byte4_t {
        uint32_t raw;
        struct Bit_slice {
            uint32_t a:8;
            uint32_t b:8;
            uint32_t c:8;
            uint32_t d:8;
        } bit;
        byte4_t() = default;
        byte4_t(uint32_t i): raw(i) {}
        operator uint32_t&() {return raw;}
        friend std::ostream & operator<<(
            std::ostream & os, byte4_t const & rhs)
        {
            os << static_cast<unsigned char>(rhs.bit.a);
            os << static_cast<unsigned char>(rhs.bit.b);
            os << static_cast<unsigned char>(rhs.bit.c);
            os << static_cast<unsigned char>(rhs.bit.d);
            return os;
        }
    };
    // byte2 型別
    union byte2_t {
        uint16_t raw;
        struct Bit_slice {
            uint16_t a:8;
            uint16_t b:8;
        } bit;
        byte2_t() = default;
        byte2_t(uint16_t i): raw(i) {}
        operator uint16_t&() {return raw;}
        friend std::ostream & operator<<(
            std::ostream & os, byte2_t const & rhs)
        {
            os << static_cast<unsigned char>(rhs.bit.a);
            os << static_cast<unsigned char>(rhs.bit.b);
            return os;
        }
    };

    // 檔案檔頭型別(共 14 bytes)
    struct FileHeader {
        unsigned char type[2]= {'B', 'M'};
        byte4_t size;
        byte2_t reserved1=0;
        byte2_t reserved2=0;
        byte4_t headSize=54;
        friend std::ostream & operator<<(
            std::ostream & os, FileHeader const & rhs)
        {
            os << rhs.type[0] << rhs.type[1];
            os << rhs.size;
            os << rhs.reserved1 << rhs.reserved2;
            os << rhs.headSize;
            return os;
        }
    };
    // 資訊檔頭型別 (共 40 byte)
    struct InfoHeader {
        byte4_t size=40;
        byte4_t width;
        byte4_t height;
        byte2_t planes=1;
        byte2_t bits;
        byte4_t compression=0;
        byte4_t imagesize=0;
        // 72dpi=2835, 96dpi=3780, 120dpi=4724, 300dpi=11811
        byte4_t xresolution=0;
        byte4_t yresolution=0;
        byte4_t ncolours=0;
        byte4_t importantcolours=0;

        friend std::ostream & operator<<(
            std::ostream & os, InfoHeader const & rhs)
        {
            os << rhs.size;
            os << rhs.width << rhs.height;
            os << rhs.planes << rhs.bits;
            os << rhs.compression << rhs.imagesize;
            os << rhs.xresolution << rhs.yresolution;
            os << rhs.ncolours << rhs.importantcolours;
            return os;
        }
    };
private:
    using uch = unsigned char;
    // RGB 轉灰階公式
    static uch rgb2gray(uch* p){
        return static_cast<uch>(
            0.299 * static_cast<float>(*(p+R))+
            0.587 * static_cast<float>(*(p+G))+
            0.114 * static_cast<float>(*(p+B))
        );
    }
    // 創建檔頭
    static FileHeader makeFH(
        size_t width, size_t height, size_t bits, size_t headSize=54)
    {
        FileHeader file_h;
        file_h.size = file_h.headSize + width*height * bits/8;
        file_h.headSize = headSize;
        return file_h;
    }
    static InfoHeader makeIH(
        size_t width, size_t height, size_t bits)
    {
        InfoHeader info_h;
        info_h.width = width;
        info_h.height = height;
        info_h.bits = bits;
        info_h.imagesize = 0;
        return info_h;
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
    // 讀取三維
    static uch& r3dim(vector<uch>& pix, size_t idx, RGB_t rgb) {
        return pix[(idx*3)+rgb];
    }
public:
    // 寫檔
    static void raw2bmp(
        string name, vector<uch>& raw, size_t width, size_t height)
    {
        size_t bits = 24;
        // 檔案資訊
        FileHeader file_h = makeFH(width, height, bits);
        // 圖片資訊
        InfoHeader info_h = makeIH(width, height, bits);
        // 二維讀取RGB
        auto at2d3c = [&](size_t y, size_t x, RGB_t rgb)-> uch& {
            return raw[(y*width+x)*3 + rgb];
        };
        // 寫檔
        fstream img(name, ios::out | ios::binary);
        img << file_h << info_h;
        size_t alig = (4 - width%4)%4;
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
    static void raw2graybmp(
        string name, vector<uch>& raw, size_t width, size_t height,
        size_t raw_bit=24, size_t img_bits=8)
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
};
//================================================================
int main(int argc, char const *argv[]) {
    vector<unsigned char> raw_pix;
    string rawName = "Seymour_Park_960x540_24bit.raw";
    Raw::read_raw(raw_pix, rawName);
    string bmpName = "Seymour_Park.bmp";

    // 彩圖存彩圖
    Raw::raw2bmp(bmpName, raw_pix, 960, 540);
    system(bmpName.c_str());
    // 彩圖存灰階
    Raw::raw2graybmp(bmpName, raw_pix, 960, 540);
    system(bmpName.c_str());
    // 灰階存灰階
    Raw::raw2gray(raw_pix);
    Raw::raw2graybmp(bmpName, raw_pix, 960, 540, 8);
    system(bmpName.c_str());
    return 0;
}
//================================================================
