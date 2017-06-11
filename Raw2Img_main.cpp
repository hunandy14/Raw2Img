/*****************************************************************
Name :
Date : 2017/06/11
By   : CharlotteHonG
Final: 2017/06/11
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include "Raw2Img.hpp"
using namespace std;
using uch = unsigned char;

// total 14 bytes
struct FileHeader {
    char type[2]= {'B', 'M'};
    byte4_t size;
    byte2_t reserved1=0;
    byte2_t reserved2=0;
    byte4_t headSize=54;
    friend ostream & operator<<(ostream & os, FileHeader const & rhs) {
        os << rhs.type[0] << rhs.type[1];
        os << rhs.size;
        os << rhs.reserved1 << rhs.reserved2;
        os << rhs.headSize;
        return os;
    }
};
// total 40 bytes
struct InfoHeader {
    byte4_t size=40;
    byte4_t width;
    byte4_t height;
    byte2_t planes=1;
    byte2_t bits;
    byte4_t compression=0;
    byte4_t imagesize;
    byte4_t xresolution=0;
    byte4_t yresolution=0;
    byte4_t ncolours=0;
    byte4_t importantcolours=0;
    friend ostream & operator<<(ostream & os, InfoHeader const & rhs) {
        os << rhs.size;
        os << rhs.width << rhs.height;
        os << rhs.planes << rhs.bits;
        os << rhs.compression << rhs.imagesize;
        os << rhs.xresolution << rhs.yresolution;
        os << rhs.ncolours << rhs.importantcolours;
        return os;
    }
};
//================================================================
int main(int argc, char const *argv[]) {
    FileHeader fh;
    InfoHeader ih;
    vector<uch> v;
    // 讀檔
    fstream raw("pic.raw", ios::in | ios::binary | ios::ate);
    v.resize(raw.tellg());
    raw.seekg(0, ios::beg);
    raw.read((char*)v.data(), v.size());
    raw.close();
    // 檔頭
    size_t w=960, h=540;
    fh.size = w*h*3+54;
    ih.width = w;
    ih.height = h;
    ih.bits = 24;
    ih.imagesize = w*h*3;
    fstream img("Bitmap.bmp", ios::out | ios::binary);
    img << fh << ih;
    return 0;
}
//================================================================
