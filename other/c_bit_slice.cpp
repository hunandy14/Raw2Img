/*****************************************************************
Name : 
Date : 2017/05/07
By   : CharlotteHonG
Final: 2017/05/07
*****************************************************************/
#include <iostream>
#include <bitset>
using namespace std;

using uch = unsigned char;
union Bit{
    struct Bit_dev{
        uch:3;
        uch data:4;
        uch:1;
    } bit;
    uch raw;
    operator uch&(){return raw;}
    friend ostream & operator<<(ostream & str, Bit const & rhs);
};

ostream & operator<<(ostream & os, const Bit & rhs){
    // os << raw;
    return os;
}

union byte4_t{
    uint32_t raw;
    struct Bit_slice{
        uint32_t a:8;
        uint32_t b:8;
        uint32_t c:8;
        uint32_t d:8;
    } bit;

    byte4_t() = default;
    byte4_t(uint32_t i): raw(i){}
    operator uint32_t&(){return raw;}
    friend ostream & operator<<(ostream & str, byte4_t const & rhs);
};
ostream & operator<<(ostream & os, const byte4_t & rhs){
    os << hex << rhs.bit.a;
    os << hex << rhs.bit.b;
    os << hex << rhs.bit.c;
    os << hex << rhs.bit.d;
    return os;
}
//================================================================
int main(int argc, char const *argv[]){
    // Bit a;
    // a=0xf0;
    // a.raw=0xf0;
    // cout << "a.data=" << (bitset<4>)a.bit.data << endl;
    // cout << "a.raw=" << (bitset<8>)a << endl;

    byte4_t a=1555254;
    cout << a << endl;
    cout << hex << 1555254 << endl;
    return 0;
}
//================================================================
