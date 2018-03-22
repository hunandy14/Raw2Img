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
    vector<unsigned char> raw_img;
    uint32_t weidth, heigh;
    uint16_t bits;
    /* 讀寫 Bmp */
    Raw2Img::read_bmp(raw_img, "kanna.bmp", &weidth, &heigh, &bits);
    Raw2Img::write_raw("kanna.raw", raw_img);
    Raw2Img::raw2bmp("kanna2.bmp", raw_img, weidth, heigh, bits);
    /* 轉灰階 */
    Raw2Img::raw2gray(raw_img);
    Raw2Img::raw2bmp("kanna2_gray.bmp", raw_img, weidth, heigh, 8);
    return 0;
}
//================================================================
