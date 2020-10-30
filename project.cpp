#include<iostream>
#include<bits/stdc++.h>
#include <algorithm>
#include"cache.h"
#include"cache.cpp"

using namespace std;

vector<pair<int,float>> hits;
vector<pair<int,float>> misses;

template<int N> struct CacheGenerator{

void TheActualCalc(){
    if(N>1){
        CacheGenerator<N/2>a;
        a.TheActualCalc();
    }
        cache<N> uut;
        ifstream fin; 
        fin.open("twolf.trace");
        float miss=0,hit=0;
        while(fin)
        {
            string line;
            getline(fin,line);
            if(line[0]=='s')
            {
                int x=stoul(line.substr(2,10),0,16);
                if(uut.checkForAddress(x)==true)
                {
                    int tempPowerOf2 = pow(2,uut.get_offsetsize());
                    x/=tempPowerOf2;
                    Byte index= x%256;
                    hit++;
                    uut.setDirtyBit(index,true);
                }
                else
                {
                    miss++;
                    int tempPowerOf2 = pow(2,uut.get_offsetsize());
                    x/=tempPowerOf2;
                    Byte index= x%256;
                    int tag=x/(256);
                    uut.setTag(index,tag);
                    uut.setValidBit(index,1);
                    if(uut.getDirtyBit(index)==1 && uut.getValidBit(index)==1)
                    {
                        //store what is in cache to memory and change data
                    }
                    uut.setDirtyBit(index,1);
                }
            }
            if(line[0]=='l')
            {
                int x=stoul(line.substr(2,10),0,16);
                if(uut.checkForAddress(x)==true)
                {
                    hit++;
                }
                else
                {
                    miss++;
                    int tempPowerOf2 = pow(2,uut.get_offsetsize());
                    x/=tempPowerOf2;
                    Byte index= (Byte)(x%256);
                    x=x/256;
                    if(uut.getValidBit(index)==1 && uut.getDirtyBit(index)==1)
                    {
                        //store data in memory if memory is implemented
                    }         
                    uut.setTag(index,x);
                    uut.setValidBit(index,1);
                    uut.setDirtyBit(index,0);
                    //load the address into the location
                }

            }
        }   
        cout<<N<<" "<<hit/(miss+hit)<<endl;
        hits.push_back(make_pair(N,hit));
        misses.push_back(make_pair(N,miss));
}
};

int main(){
    CacheGenerator<4096> t;
    t.TheActualCalc();
    // the main calculations are done in the recursive call
    return 0;
}