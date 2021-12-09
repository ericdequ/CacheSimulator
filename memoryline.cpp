#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#pragma once
using namespace std;

struct Datafilee{
    
    string index = "";
    bool valid = false;
    string tag = "";
    string data = "";
    string offset = "";
    string memBlock = "";
    string set = "";

    int count = 0;
    int timepassed = 0;
    int setform = 0;
    int linenum = 0;

    void printall(){

            cout<<"Binary form: "<<data<<endl;
            cout<<"The index value was: "<<set<<endl;         
            cout<<"The tag portion is: "<<tag<<endl;
            cout<<"Offset:  "<<offset<<endl;
            cout<<"line num = "<<linenum<<endl;
            cout<<"set num = "<<setform<<endl;
        
        }
    
};