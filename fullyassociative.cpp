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
#include <list>
#include "memoryline.cpp"
#include "utitties.cpp"

using namespace std;


class fullyCache{
private:
/* helpful data */

    int numblocks =0;
    int cachesize = 0;
    int bytesinblock = 0;
    int numlines = 0;
    bool LRU;

    int OffW;
    int lineWid;
    int tagWidth;
    vector<Datafilee*> tracesss; // vector to keep track cache
    vector<Datafilee*> allcache; // vector to keep track of main memory
    pair<int, int> hitmiss;
        float hitratio = 0;
        float missratio = 0;
    

/* types of cache */
   
    
public:
    fullyCache(int cachesize, int bytesperblock,bool lru){
        numblocks = cachesize/(int)bytesperblock;
        OffW = log2(numblocks);
        tagWidth = (32 - (OffW));
        cout<<numblocks<<endl<<endl<<OffW<<endl<<endl<<tagWidth;
        LRU = lru;

        for(int i = 0; i<numblocks;i++){
                Datafilee* temp = new Datafilee();
                allcache.push_back(temp);
        }
        
    }

    void clearcache(){
        for (int i = 0; i < allcache.size(); i++)
        {
            tracesss.at(i)->data = "";
            tracesss.at(i)->memBlock = "";
            tracesss.at(i)->offset = "";
            tracesss.at(i)->tag = "";
            tracesss.at(i)->index = "";
            tracesss.at(i)->valid = "";
            tracesss.at(i)->count = 0;
        }
    }

    void changecache(int num, Datafilee* newdataobj){
            allcache.at(num)->data = newdataobj->data;
            allcache.at(num)->memBlock = newdataobj->memBlock;
            allcache.at(num)->offset = newdataobj->offset;
            allcache.at(num)->tag = newdataobj->tag;
            allcache.at(num)->set = newdataobj->set;
            allcache.at(num)->setform = newdataobj->setform;
            allcache.at(num)->valid = newdataobj->valid;
            allcache.at(num)->count = newdataobj->count;
            allcache.at(num)->timepassed = newdataobj->timepassed;
            allcache.at(num)->linenum = newdataobj->linenum;
    }

    int getlastused(){
        int o = INT_MIN;
        int index = 0;
        for (int i =0; i <allcache.size(); i++)
        {
            if(o>allcache.at(i)->timepassed){
                o = allcache.at(i)->timepassed;
                index = i;
            }
        }
        return index;
    }

    int getlowest(){
        int o = INT_MIN;
        int index = 0;
        for (int i =0; i <allcache.size(); i++)
        {
            if(o < allcache.at(i)->count){
                o = allcache.at(i)->count;
                index = i;
            }
        }
        return index;
    }

    

    void runtest(){
        vector<string> filenames;
        filenames = {"read01.trace"};
        //filenames = {"write01.trace", "write02.trace", "read01.trace", "read02.trace", "read03.trace", "gcc.trace", "swim.trace"};
        for(string x : filenames){
            cout<<x<<endl;
            read_trace(x, tracesss, tagWidth,OffW);
        }
        int jjj = 0;

        int hits = 0;
        int miss = 0;
        int counter = 0;

        for (int i = 0; i < tracesss.size(); i++){ // for every line of main memory 
            bool found = false;
           for (int j = 0; j <allcache.size(); j++) // we check everyline of cache memory 
           {
              allcache.at(j)->timepassed = allcache.at(j)->timepassed +1; // as we check each cache address we update the time passed
              if(tracesss.at(i)->tag  == allcache.at(j)->tag){  // if tags 
                    allcache.at(j)->timepassed = 0;
                    found = true;
               }
           }

           if(found){
               hits = hits + 1;
           }else{
               miss = miss +1;
               

           if(LRU){
               jjj = getlastused();
           }else{
               jjj = getlowest();
           }

                if(counter >= numlines){
                    changecache(jjj,tracesss.at(i));
                }else{
                    changecache(counter,tracesss.at(i));
                    counter = counter + 1;
                }
           }
        }

        cout<<"total hits: "<<hits<<endl;
        cout<<"total miss: "<<miss<<endl;
    }


};