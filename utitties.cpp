#include <fstream>
#include <iostream>
#include <sstream>
#include <bitset>
#include <string>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <set>
#include <cstdlib>
#include "memoryline.cpp"
#pragma once
using namespace std;

int stringbinarytodecimal(string binaryString){
    int value = 0;
    int indexCounter = 0;
    for(int i=binaryString.length()-1;i>=0;i--){

    if(binaryString[i]=='1'){
        value += pow(2, indexCounter);
    }
    indexCounter++;
    }
    return value;
}

void print_data(vector<vector<string>> data){
    cout<<"enter print"<<endl;
    cout<<data.size()<<endl;
    for(int i =0;i<data.size();i++){
        for (int j = 0; j < 7; j++)
        {
            cout<<data.at(i).at(j)<<endl;
        }
            //cout<<"finished j "<<endl;
            cout<<endl;
    }
            //cout<<"finished 1   "<<endl<<endl;
            //cout<<"after";
            //return;
}


string GetBinaryStringFromHexString (string sHex, int offset)
		{
			string sReturn = "";
			for (int i = 0; i < sHex.length()+1; ++i)
			{
				switch (sHex [i]){
					case '0': sReturn = sReturn + ("0000"); break;
					case '1': sReturn = sReturn + ("0001"); break;
					case '2': sReturn = sReturn + ("0010"); break;
					case '3': sReturn = sReturn + ("0011"); break;
					case '4': sReturn = sReturn + ("0010"); break;
					case '5': sReturn = sReturn + ("0101"); break;
					case '6': sReturn = sReturn + ("0110"); break;
					case '7': sReturn = sReturn + ("0111"); break;
					case '8': sReturn = sReturn + ("1000"); break;
					case '9': sReturn = sReturn + ("1001"); break;
					case 'A': sReturn = sReturn + ("1010"); break;
					case 'B': sReturn = sReturn + ("1011"); break;
					case 'C': sReturn = sReturn + ("1100"); break;
					case 'D': sReturn = sReturn + ("1101"); break;
					case 'E': sReturn = sReturn + ("1110"); break;
					case 'F': sReturn = sReturn + ("1111"); break;
				}
			}
            while(sReturn.size() < 32-offset){
                sReturn.insert(0,"0");
            }

			return sReturn;
		}


void read_trace(string filename, vector<Datafilee*> &all, double bits_tag, double bits_Offset){
    string line;
    fstream myfile(filename);
    if (myfile.is_open())  
    {
        int countt = 0;
        while (getline(myfile, line )){
           Datafilee* temp = new Datafilee();
           string binaryrep = GetBinaryStringFromHexString(line.substr(4,8),0);
           temp->data = binaryrep;
           temp->index =  binaryrep.substr(0,bits_tag);
           temp->tag =  binaryrep.substr(0,bits_tag);
           temp->memBlock = temp->tag + temp->index;
           temp->count = countt;
           countt = countt + 1;
           temp->timepassed = 0;
           all.push_back(temp);
        }
        cout<<"closing_file"<<endl;
        myfile.close();
    }else{ 
        cout << "File did not open";
    }
    
}

 void read_direct(string filename, vector<Datafilee*> &all, int bits_tag, int bitsinline,int numoffset){
     cout<<"read dir open"<<endl;
    string line;
    fstream myfile(filename);
    if (myfile.is_open())  
    {
        cout<<"reading file:  "<<filename<<endl;
        int count = 0;
        while (getline(myfile, line)){
           Datafilee* temp = new Datafilee();
           temp->valid = true;
           string binaryrep = GetBinaryStringFromHexString(line.substr(4,8),numoffset);
           temp->data = binaryrep;
           temp->tag =binaryrep.substr(0,bits_tag);
           temp->index = binaryrep.substr(bits_tag,bitsinline);
           temp->memBlock = binaryrep.substr(0,bits_tag+bitsinline);
           count = count+1;
           all.push_back(temp);
        }
        myfile.close();
        cout<<"closing file: "<<filename<<endl;
        return;
    }else{ 
        cout << "File did not open";
    }
    return;
}

void gettracedata_set(string filename, vector<Datafilee*> &memlines,int tagsize,int linesize, int offsetsize){
    string line;
    ifstream myfile(filename);
    if (myfile){
        int count =0;
        while (getline(myfile, line)){
           Datafilee* temp = new Datafilee();
           string binaryhelp = GetBinaryStringFromHexString(line.substr(4,8),0);
           temp->data = (binaryhelp);
           temp->tag = binaryhelp.substr(0,tagsize);
           temp->set = binaryhelp.substr(tagsize,linesize);
           temp->setform = stringbinarytodecimal(binaryhelp.substr(tagsize,linesize));
           temp->offset = binaryhelp.substr(tagsize+linesize,offsetsize);
           temp->linenum = stringbinarytodecimal(temp->set.substr(0,1));
           memlines.push_back(temp);
        }
    cout<<"closing file"<<endl;
    myfile.close();
    }else{ 
        cout << "File did not open";
    }
}


