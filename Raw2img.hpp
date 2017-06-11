/*****************************************************************
Name :
Date : 2017/06/12
By   : CharlotteHonG
Final: 2017/06/12
*****************************************************************/
#pragma once

// 資料結構
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

// 






