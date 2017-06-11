/*****************************************************************
Name : 
Date : 2017/06/11
By   : CharlotteHonG
Final: 2017/06/11
*****************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "Bmp.hpp"
#include "Bmp.cpp"
//================================================================
int main(int argc, char const *argv[]){
    vector<BYTE> v;
    fstream img("pic.raw", ios::in | ios::binary | ios::ate);
    v.resize(img.tellg());
    img.seekg(0, ios::beg);
    img.read((char*)v.data(), v.size());
    img.close();

    RawToBmp("pic", v, 960, 540);
    return 0;
}
//================================================================
