#ifndef CACHE_H
#define CACHE_H

#include<cstdint>
#include<cstdlib>
#include<bitset>
#include<cmath>

constexpr std::size_t log2(std::size_t N)
{
    return N <= 1 ? 0 : 1+log2(N/2);
}

#define Byte uint8_t
#define Tag std::bitset<32-8-log2(4*_N)>
#define Offset std::bitset<log2(4*_N)>

template<size_t _N> //blocksize
class cache{
private:
    int _blockSize;
    int _tagSize;
    int _offsetSize;
    Byte** _cacheData;
    Tag* _tagBits;
    bool* _valid;
    bool* _dirty;
public:
    cache();
    void setTag(Byte index,int tag);
    void setTag(Byte index,Tag x);
    Tag getTag(Byte index);
    Byte* getData(Byte index);
    Byte getByte(Byte index,Offset s);
    void setValidBit(Byte index,bool valid);
    bool getValidBit(Byte index);
    void setDirtyBit(Byte index,bool dirty);
    bool getDirtyBit(Byte index);
    void setData(Byte index,Byte* data);
    void setData(Byte index,int* data);
    template<typename T> void changeData(int add,T data);
    bool checkForAddress(int add);
    int get_offsetsize();
    Byte getIndex(int address);
    ~cache();
};
#endif