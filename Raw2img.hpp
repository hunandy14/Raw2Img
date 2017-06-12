/*****************************************************************
Name :
Date : 2017/06/12
By   : CharlotteHonG
Final: 2017/06/12
*****************************************************************/
#pragma once


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
        os << static_cast<char>(rhs.bit.a);
        os << static_cast<char>(rhs.bit.b);
        os << static_cast<char>(rhs.bit.c);
        os << static_cast<char>(rhs.bit.d);
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
        os << static_cast<char>(rhs.bit.a);
        os << static_cast<char>(rhs.bit.b);
        return os;
    }
};
// RGB 型別
enum RGB {R, G, B};
class RGB_t {
public:
    RGB_t(size_t rgb): rgb(RGB(rgb)) {
        if(rgb>2) {throw std::range_error("range only 0~2");}
    }
    inline operator RGB() {return rgb;}
private:
    RGB rgb;
};
//----------------------------------------------------------------
// 檔案檔頭型別(共 14 bytes)
struct FileHeader {
    char type[2]= {'B', 'M'};
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
    byte4_t imagesize;
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
//----------------------------------------------------------------






