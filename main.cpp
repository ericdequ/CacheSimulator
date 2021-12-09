#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <set>
#include "directmappedcache.cpp"
#include "fullyassociative.cpp"
#include "setAssociative.cpp"
#include <cstdlib>
using namespace std;

  int main(){
  cout<<"started program"<<endl<<endl;
        int option;
        //string cachesize;
        string replacementpolicy;
        vector<vector<string>>content;
        string filetotest;
        cout<<"Pick what type of cache"<<endl<<"1 = Direct , 2 = FullyAssociative , 3 = SetAssociative"<<endl<<endl;
        cin>>option;

        cout<<"Select the Cache replacement Policy"<<endl<<"1 = LRU  2 = FIFO"<<endl<<endl;
        cin>>replacementpolicy;

        bool lru;
        if(replacementpolicy == "1"){
            lru = true;
        }else{
            lru = false;
        }
            int blocksize = 8;
            int cachesizeee = pow(2,7);

        if(option == 1){
            cout<<"Direct Mapped Cache Simulation Begin"<<endl;
            DirectMappedCache cache = DirectMappedCache(cachesizeee,lru,blocksize);
            cout<<"Successfully created DirectedMappedCache "<<endl<<
            "DirectedMappedCache size = "<<cache.cachesize<<endl<<
            "DirectedMappedCache line width = "<<cache.linesize<<endl<<
            "DirectedMappedCache number of lines = "<<cache.numlines<<endl<<endl;
            cache.runsimplleTest();

        }else if(option == 2 ){

            cout<<"FullyAssocitive Mapped Cache Simulation Begin"<<endl;
            fullyCache cache = fullyCache(cachesizeee, blocksize,lru);
            cache.runtest();

        }else if(option == 3){
            cout<<"SetAssocitive Mapped Cache Simulation Begin"<<endl;
            setAssociativeCache cache = setAssociativeCache(cachesizeee,2,blocksize,true);
            cache.runtest();
            setAssociativeCache cache2 = setAssociativeCache(cachesizeee,2,blocksize,false);
            cache2.runtest();
        }else{
            cout<<"invalid option selected terminating program";
        }

    return 0;
  }