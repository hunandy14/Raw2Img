/*****************************************************************
Name :
Date : 2017/06/11
By   : CharlotteHonG
Final: 2017/06/14
*****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Raw2Img.hpp"
using namespace std;
//================================================================
int main(int argc, char const *argv[]) {
    // vector<unsigned char> raw_pix;
    // string rawName = "Seymour_Park_960x540_24bit.raw";
    // Raw::read_raw(raw_pix, rawName);
    string bmpName = "Seymour_Park.bmp";

    // 彩圖存彩圖
    // Raw::raw2bmp(bmpName, raw_pix, 960, 540);
    // system(bmpName.c_str());
    // 彩圖存灰階
    // Raw::raw2graybmp(bmpName, raw_pix, 960, 540);
    // system(bmpName.c_str());
    // 灰階存灰階
    // Raw::raw2gray(raw_pix);
    // Raw::raw2graybmp(bmpName, raw_pix, 960, 540, 8);
    // system(bmpName.c_str());

    fstream file(bmpName.c_str(), ios::in | ios::binary);
    file.seekg(0, ios::beg);

    Raw::FileHeader rhs;
    file >> rhs;
    Raw::InfoHeader rhs2;
    file >> rhs2;

    fstream file2("test.bmp", ios::out | ios::binary);
    file2 << rhs;    
    file2 << rhs2;    


    // Raw::byte2_t b2, b3;
    // file >> b2;
    // file >> b3;
    // cout << "b2=" << (int)b2 << endl;
    // cout << "file.tellg()=" << file.tellg() << endl;


    return 0;
}
//================================================================
