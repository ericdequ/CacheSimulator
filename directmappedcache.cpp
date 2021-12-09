#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <queue>
#include <map>
#include "utitties.cpp"
using namespace std;




class DirectMappedCache{
    public:
        /* initilizes variables for Direct Cache */
        double mainmem = pow(2,32);

        int cachesize = 0;
        int numlines = 0;
        int numbytesaddress = 4;
        int BlockSize = 0;
        int linesize = 0;
        
        int numbBitsTag = 0;
        int numbBitsLine = 0;
        int numbBitOffset = 0;

        bool LRU;
        pair<int, int> hitmiss;
        float hitratio = 0;
        float missratio = 0;
        vector<Datafilee*> allcache; // vector to keep track of cache
        vector<Datafilee*> memadd; // vector to keep track of main memory

        

        DirectMappedCache(int cachesiz, bool lru, int block_size){
            cachesize = cachesiz;
            BlockSize = block_size;
            numlines = cachesize / BlockSize;
            linesize = BlockSize; 

            numbBitOffset = round(log2(BlockSize));
            numbBitsLine = log2(numlines);
            numbBitsTag = 32 - (numbBitOffset + numbBitsLine);
            LRU = lru;

            for(int i = 0; i<numlines;i++){
                Datafilee* temp = new Datafilee();
                allcache.push_back(temp);
            }
    
            cout<<"Cache size = "<<cachesize<<endl;
            cout<<"number of bits in physical address = "<<32<<endl;
            cout<<"number of bits in offset = "<<numbBitOffset<<endl;
            cout<<"number of bits in line = "<<numbBitsLine<<endl;
            cout<<"number of bits in tag = "<<numbBitsTag<<endl;
            cout<<"NUM LINES IN CACHE = "<<numlines<<endl;

            if(LRU){
               cout<<"Replacement policy LRU chosen"<<endl;
            }else{
                cout<<"Replacement policy FIFO chosen"<<endl;
            }
        }

        void changecache(Datafilee* &data, Datafilee* newdataobj){
            data->data = newdataobj->data;
            data->memBlock = newdataobj->memBlock;
            data->offset = newdataobj->offset;
            data->tag = newdataobj->tag;
            data->index = newdataobj->index;
            data->valid = newdataobj->valid;
        }

        bool checkcache(Datafilee* data){
            int checklinenum = stringbinarytodecimal(data->index);
            if(data->index == allcache.at(checklinenum)->index){
                if(data->tag == allcache.at(checklinenum)->tag){
                    if(data->data == allcache.at(checklinenum)->data){
                        return true;
                    }else{
                        changecache(allcache.at(checklinenum),data);
                        return false;  
                    }
                }else{
                    changecache(allcache.at(checklinenum),data);
                    return false;  
                }
            }else{
                changecache(allcache.at(checklinenum),data);
                return false;            
            }
        }

        void runsimplleTest(){
            cout<<"Starting test"<<endl;
            vector<string> filenames;
            filenames = {"write01.trace","write02.trace", "read01.trace", "read02.trace", "read03.trace", "gcc.trace", "swim.trace"};
            for(string x : filenames){
                read_direct(x,memadd,numbBitsTag,numbBitsLine,numbBitOffset);
            }
                for(unsigned int tt = 0; tt<memadd.size(); tt++){
                    if(checkcache(memadd.at(tt))){
                        
                        hitmiss.first = hitmiss.first + 1;
                    }else{
                        hitmiss.second = hitmiss.second+1;
                    }
                }
                printresults();
        }
        
        void printresults(){
            cout<<"Test Completed Results are:"<<endl;
            cout<<"hit = "<<hitmiss.first<<endl;
            cout<<"miss = "<<hitmiss.second<<endl<<endl<<endl;
        }
};