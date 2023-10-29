#include <iostream>
#include "D:\Projects\STL_GNUPLOT\header\Read_File.h"
#include <fstream>
#include <string>
using namespace std;


fileReader :: fileReader()
{

}

fileReader :: ~fileReader()
{

}

void fileReader :: readFromFile(string filename)
{
    string line;
    ifstream read{filename};
    ofstream write{"D:\\Projects\\STL_GNUPLOT\\output\\final.txt"};
    int count=0;
    string firstline = "";
    while (getline(read,line))
    {
        int index=-1;
        index=line.find("vertex");
        
        if(index!=-1)
        {
            if(count==0)
            {
                firstline = line.substr(index+7);
            }
            count+=1;
            write << line.substr(index+7)<<endl;
        }
        if (count==3)
        {
            write <<firstline<<endl;
            firstline="";
            count =0;
        }
            
    }
    read.close();
    write.close();
    
}

