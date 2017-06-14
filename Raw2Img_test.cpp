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
#include <ctime>
#include "Raw2Img.hpp"
#include "Raw2Img.cpp"

#include "other/Bmp.hpp"
#include "other/Bmp.cpp"
using namespace std;

void pri_time(clock_t start, clock_t end){
    cout << "Runing Time : "
     << (double)(end-start) / CLOCKS_PER_SEC
     << " seconds" << endl;
}
//================================================================
int main(int argc, char const *argv[]) {
    vector<unsigned char> raw_pix;
    string rawName = "Gamma_1536x2048_24bit.raw";
    Raw::read_raw(raw_pix, rawName);
    string bmpName = "Gamma.bmp";
    clock_t start;

    size_t times=1;
    start = clock();
    for(unsigned i = 0; i < times; ++i) {
        Raw::raw2bmp(bmpName, raw_pix, 1536, 2048);
    }
    // Raw::raw2graybmp(bmpName, raw_pix, 1536, 2048);
    pri_time(start, clock());

    start = clock();
    for(unsigned i = 0; i < times; ++i) {
        RawToBmp(bmpName, raw_pix, 1536, 2048);
    }
    pri_time(start, clock());

    // system(bmpName.c_str());



    return 0;
}
//================================================================
