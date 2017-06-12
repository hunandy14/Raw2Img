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
    // 讀取三維
    static uch& r3dim(vector<uch>& pix, size_t idx, RGB_t rgb) {
        return pix[(idx*3)+rgb];
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
    // 寫檔
    static void raw2bmp(string name, vector<uch>& v, size_t w, size_t h) {
        // 檔案資訊
        size_t alig = (4 - w%4)%4;
        FileHeader file_h;
        file_h.size = w*h*3+54;
        // 圖片資訊
        InfoHeader info_h;
        info_h.width = w;
        info_h.height = h;
        info_h.bits = 24;
        info_h.imagesize = w*h*3;
        // 寫檔
        fstream img(name, ios::out | ios::binary);
        img << file_h << info_h;
        for(int j = h-1; j >= 0; --j) {
            for(unsigned i = 0; i < w; ++i) {
                img << static_cast<uch>(r3dim(v, j*w+i, B));
                img << static_cast<uch>(r3dim(v, j*w+i, G));
                img << static_cast<uch>(r3dim(v, j*w+i, R));
            }
            // 對齊4byte
            for(unsigned i = 0; i < alig; ++i) {
                img << uch(0);
            }
        }
        img.close();
    }
};
//================================================================
int main(int argc, char const *argv[]) {
    vector<unsigned char> v;
    const char* rawName="Seymour_Park_960x540_24bit.raw";
    const char* bmpName="Seymour_Park.bmp";

    Raw::read_raw(v, rawName);
    Raw::raw2bmp(bmpName, v, 960, 540);
    system(bmpName);
    return 0;
}
//================================================================
