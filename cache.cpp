#include"cache.h"

template<size_t _N>
cache<_N>::cache():_blockSize(_N),_tagSize(24-log2(4*_N)),_offsetSize(log2(4*_N)){
    _cacheData = new Byte*[256];
    for(int i=0;i<256;i++)
        _cacheData[i] = new Byte[4*_N];
    _tagBits = new Tag[256];
    _valid = new bool[256];
    _dirty = new bool[256];
    // void template changeData<int*>;
}

template<size_t _N>
void cache<_N>::setTag(Byte index,int x){
    _tagBits[(int)index]=x;
}

template<size_t _N>
void cache<_N>::setTag(Byte index,Tag x){
    _tagBits[(int)index]=x;
}

template<size_t _N>
Tag cache<_N>::getTag(Byte index){
    return _tagBits[(int)index];
}

template<size_t _N>
Byte* cache<_N>::getData(Byte index){
    return _cacheData[(int)index];
}

template<size_t _N>
Byte cache<_N>::getByte(Byte index,Offset s){
    return _cacheData[(int)index][s.to_ulong()];
}

template<size_t _N>
void cache<_N>::setValidBit(Byte index,bool valid){
    _valid[(int)index] = valid;
}

template<size_t _N>
bool cache<_N>::getValidBit(Byte index){
    return _valid[(int)index];
}

template<size_t _N>
void cache<_N>::setDirtyBit(Byte index,bool dirty){
    _dirty[(int)index] = dirty;
}

template<size_t _N>
bool cache<_N>::getDirtyBit(Byte index){
    return _dirty[(int)index];
}

template<size_t _N>
void cache<_N>::setData(Byte index,Byte* data){
    _valid[(int)index]=true;
    for(int i=0;i<4*_N;i++)
        _cacheData[(int)index][i] = data[i];
}

template<size_t _N>
int cache<_N>::get_offsetsize(){
    return _offsetSize;
}

template<size_t _N>
void cache<_N>::setData(Byte index,int* data){
    _valid[(int)index]=true;
    for(int i=0;i<_N;i++)
    {
        int temp = data[i];
        _cacheData[(int)index][4*i+0]=temp%256;
        temp/=256;
        _cacheData[(int)index][4*i+1]=temp%256;
        temp/=256;
        _cacheData[(int)index][4*i+2]=temp%256;
        temp/=256;
        _cacheData[(int)index][4*i+3]=temp%256;
    }
}

template<size_t _N>
bool cache<_N>::checkForAddress(int add){
    Tag tempTag;
    Byte tempIndex;
    Offset tempOffset;
    int tempPowerOf2 = pow(2,_offsetSize);
    tempOffset = add%tempPowerOf2;
    add/=tempPowerOf2;
    tempIndex=add%256;
    add/=256;
    tempTag=add;
    if(getValidBit(tempIndex))
    {
        if(getTag(tempIndex)==tempTag)
            return true;
    }
    return false;
}

template<size_t _N>
Byte cache<_N>:: getIndex(int add)
{
    int tempPowerOf2 = pow(2,_offsetSize);
    add/=tempPowerOf2;
    Byte index= (Byte)(add%256);
    return index;
}

template<size_t _N>
template<typename T>
void cache<_N>::changeData(int add,T data){
    Tag tempTag;
    Byte tempIndex;
    Offset tempOffset;
    int tempPowerOf2 = pow(2,_offsetSize);
    tempOffset = add%tempPowerOf2;
    add/=tempPowerOf2;
    tempIndex=add%256;
    add/=256;
    tempTag=add;

    if(std::is_same<T,int*>::value){
        setData(tempIndex,data);
        setTag(tempIndex,tempTag);
        setValidBit(tempIndex,true);
    }
    if(std::is_same<T,Byte*>::value){
        setData(tempIndex,data);
        setTag(tempIndex,tempTag);
        setValidBit(tempIndex,true);
    }
}

template<size_t _N>
cache<_N>::~cache(){
    for(int i=1;i<256;i++)
        delete(_cacheData[i]);
    delete(_cacheData);
    delete(_tagBits);
    delete(_valid);
    delete(_dirty);
}
#include"instantiation.h"