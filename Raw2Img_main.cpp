/*****************************************************************
Name :
Date : 2017/06/11
By   : CharlotteHonG
Final: 2017/06/14
*****************************************************************/
#include <iostream>
#include <vector>
#include "Raw2Img.hpp"
using namespace std;
//================================================================
int main(int argc, char const *argv[]) {
    vector<unsigned char> raw_pix;
    string rawName = "Seymour_Park_960x540_24bit.raw";
    Raw::read_raw(raw_pix, rawName);
    string bmpName = "Seymour_Park.bmp";

    // 存彩圖
    Raw::raw2bmp(bmpName, raw_pix, 960, 540);
    system(bmpName.c_str());
    // 存灰階
    Raw::raw2gray(raw_pix);
    Raw::raw2bmp(bmpName, raw_pix, 960, 540, 8);
    system(bmpName.c_str());

    // 讀取 Bmp
    // vector<unsigned char> raw_pix2;
    // Raw::read_bmp(raw_pix2, "conna.bmp");
    // Raw::write_raw("conna.raw", raw_pix2);

    // Raw::read_raw(raw_pix, "conna.raw");
    // Raw::raw2bmp("conna2.bmp", raw_pix, 850, 620);

    // Raw::raw2bmp("conna2.bmp", raw_pix2, 960, 540);
    // Raw::write_raw("test_960x540_24bit.raw", raw_pix2);
    
    // system("test_960x540_24bit.raw");
    return 0;
}
//================================================================
