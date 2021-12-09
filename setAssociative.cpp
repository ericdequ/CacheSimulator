#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <map>
#include <set>
#include <queue>
#include <iterator>
#include <algorithm>
#include "memoryline.cpp"
#include "utitties.cpp"
using namespace std;


class setAssociativeCache{
private:
/* helpful data */
    int OffW =0;
    int set_Wid =0;
    int tagWidth = 0;
    int numsets = 0;
    int numInSet = 0;
    int blocknum = 0;
    vector<Datafilee*> tracesss; // memory addresses from main memory 
    bool LRU = false;

/* types of cache */
    vector<vector<Datafilee*>> setcache; // Cache memory 
    int row1 = 0;
    int row2 = 0;
    
public:
    setAssociativeCache(int cachesize, int num_set, int blocksize,bool lru){
        OffW = log2(blocksize);
        numsets = cachesize / (blocksize*num_set);
        set_Wid = log2(numsets);
        LRU = lru;
        numsets = numsets -1;
        cout<<"numsets"<<numsets<<endl;
        tagWidth = (32 - (set_Wid + OffW));
        cout<<OffW<<endl<<set_Wid<<endl<<tagWidth;

for (int j = 0; j < num_set; j++)
{
    /* code */
        vector<Datafilee*> templine;
        for (int i = 0; i < numsets; i++)
        {
            Datafilee* temp = new Datafilee();
            templine.push_back(temp);
        }
        setcache.push_back(templine);
}
}

void changecache(Datafilee* newdataobj, int setnum, int q){
    /*
            cout<<"changecache"<<endl;
            cout<<setnum<<endl;
            cout<<q<<endl;
            cout<<newdataobj->linenum<<endl;
            */
            setcache.at(newdataobj->linenum).at(setnum)->data = newdataobj->data;
            setcache.at(newdataobj->linenum).at(setnum)->memBlock = newdataobj->memBlock;
            setcache.at(newdataobj->linenum).at(setnum)->offset = newdataobj->offset;
            setcache.at(newdataobj->linenum).at(setnum)->tag = newdataobj->tag;
            setcache.at(newdataobj->linenum).at(setnum)->index = newdataobj->index;
            setcache.at(newdataobj->linenum).at(setnum)->valid = newdataobj->valid;
        }

    int getlowest(int setttnummm){
        if(LRU){
                int o = INT_MIN;
                int index = 0;
                for (int i = 0; i < numsets; i++)
                {
                    if(o > setcache.at(setttnummm).at(i)->timepassed){
                        o = setcache.at(setttnummm).at(i)->timepassed;
                        index = i;
                }
            }
            return index;
        }else{
            int o = INT_MAX;
            int index = 0;
            for (int i = 0; i < numsets; i++)
            {
                if(o < setcache.at(setttnummm).at(i)->count){
                   o = setcache.at(setttnummm).at(i)->count;
                   index = i;
                }
            }
            return index;
        }
    }

    bool checkset(Datafilee* mem){
        bool found = false;
        
        /*
        cout<<"memline: "<<mem->linenum<<endl;
        cout<<"mem set form = "<<mem->setform<<endl;
        cout<<"set = "<<mem->set<<endl;
        cout<<"tag = "<<mem->tag<<endl;
        cout<<"data = "<<mem->data<<endl;
        */
        if(mem->setform < numsets){
            //cout<<"mem set form = "<<mem->setform<<endl;
            for (int q = 0; q < setcache.at(mem->linenum).size(); q++)
            {
                setcache.at(mem->linenum).at(q)->timepassed = setcache.at(mem->linenum).at(q)->timepassed + 1;
                if(mem->tag == setcache.at(mem->linenum).at(q)->tag){
                    if(mem->data == setcache.at(mem->linenum).at(q)->data){
                         setcache.at(mem->linenum).at(q)->timepassed = 0;
                         found = true;
                         return true;
                    }
                }
            }
        
            if(mem->linenum == 0){
                
                if(row1<numsets){
                    //cout<<"adding to row 0 this line is not full"<<endl;
                    changecache(mem,0,row1);
                    row1 = row1 + 1;
                }else{
                    changecache(mem,0,getlowest(mem->linenum));
                }
            }else if(mem->linenum == 1){
                
                if(row2<numsets){
                    //cout<<"adding to row 1 this line is not full"<<endl;
                    changecache(mem,1,row2);
                    row2 = row2 + 1;
                }else{
                    changecache(mem,1,getlowest(mem->linenum));
                }

            }
        }
            return false;
    }


    void showtraces(){
         for (int i = 0; i < tracesss.size(); i++){
             tracesss.at(i)->printall();
         }
    }

    

    void runtest(){
        vector<string> filenames;
        //filenames = {"write01.trace", "write02.trace"};
        filenames = {"write01.trace", "write02.trace", "read01.trace", "read02.trace", "read03.trace","gcc.trace", "swim.trace"};
        for(string x : filenames){
            cout<<x<<endl;
            gettracedata_set(x,tracesss,tagWidth,set_Wid,OffW);
        }
        //showtraces();
        cout<<"gathered data"<<endl;
        int hits = 0;
        int miss = 0;

        for (int i = 0; i < tracesss.size(); i++)
        {
            if(checkset(tracesss.at(i))){
                hits = hits +1;
            }else{
                miss = miss +1;
            }
        }
        cout<<"total hits: "<<hits<<endl;
        cout<<"total miss: "<<miss<<endl;
    }

};