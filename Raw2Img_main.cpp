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
using uch = unsigned char;

inline uch& r3dim(vector<uch>& pix, size_t idx, RGB_t rgb) {
    return pix[(idx*3)+rgb];
}
class Raw {
public:
    // 讀檔
    static void read_raw(vector<uch>& raw, string name) {
        fstream file(name.c_str(), ios::in | ios::binary | ios::ate);
        raw.resize(file.tellg());
        file.seekg(0, ios::beg);
        file.read((char*)raw.data(), raw.size());
        file.close();
    }
    // 寫檔
    static void raw2bmp(string name, vector<uch>& v, size_t w, size_t h) {
        // 檔案資訊
        size_t alig = 0;
        FileHeader file_h;
        file_h.size = w*h*3+54;
        // 圖片資訊
        InfoHeader info_h;
        info_h.width = w;
        info_h.height = h;
        info_h.bits = 24;
        info_h.imagesize = w*h*3;
        // 寫檔
        fstream img("Bitmap.bmp", ios::out | ios::binary);
        img << file_h << info_h;
        for(int j = h-1; j >= 0; --j) {
            for(unsigned i = 0; i < w; ++i) {
                img << static_cast<char>(r3dim(v, j*w+i, B));
                img << static_cast<char>(r3dim(v, j*w+i, G));
                img << static_cast<char>(r3dim(v, j*w+i, R));
            }
            // 對齊4byte

        }
        img.close();
    }
};
//================================================================
int main(int argc, char const *argv[]) {
    vector<uch> v;
    // 讀檔
    Raw::read_raw(v, "pic.raw");
    // 檔頭
    size_t w=960, h=540;
    // 寫檔
    Raw::raw2bmp("Bitmap.bmp", v, w, h);
    system("Bitmap.bmp");
    return 0;
}
//================================================================
