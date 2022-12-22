#include<iostream>
#include<fstream>
#include<string>

#include <vector>
#include"RGBValue.h"
#include"PPMLine.h"
#pragma once
using namespace std;

class PPMImage
{
public:
//-----------------------------------------------------------------------------
//Constructors 
// Default, String, copy
    PPMImage();
    PPMImage(string myFile);
    PPMImage(const  PPMImage& tocopy);
    
//-----------------------------------------------------------------------------
//Standard funtions for accessors and loading file
//drawline does not work    
    int get_X();
    int get_Y();
    void LoadFile(string myFile);
    void DrawLine(int one, int two, int three, int four, RGBValue& value);

//-----------------------------------------------------------------------------
//Operator overloads. These overloaded operators function for the standard
// operators. operators taking ppmlines do not work
    bool operator ==(PPMImage& tocheck);
    bool operator !=(PPMImage& tocheck);
    PPMImage operator +(PPMImage& toAdd);
    PPMImage operator +(PPMLine line);
    PPMImage operator - (PPMImage& toMin);
    PPMImage operator -();
    PPMImage operator +=(PPMLine line);
//-----------------------------------------------------------------------------
//output overload. This is used to print to an img file
    friend ostream& operator << (ostream& output, PPMImage& image);

private:
//-----------------------------------------------------------------------------
//private data types initalized to start, modified by constructors
    int pixels_X = 0;
    int pixels_Y = 0;
    int maxColor = 0;
    vector <vector<RGBValue>> myPPM;
};

