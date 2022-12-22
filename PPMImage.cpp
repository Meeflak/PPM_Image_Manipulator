#include "PPMImage.h"


//-----------------------------------------------------------------------------
//Default constructor
PPMImage::PPMImage() {
    pixels_X = 0;
    pixels_Y = 0;
    maxColor = 255;
}

//-----------------------------------------------------------------------------
//Copy constructor - takes copy of another PPMImage and steals its identity
PPMImage::PPMImage(const PPMImage& tocopy) {
    this->maxColor = tocopy.maxColor;
    this->pixels_X = tocopy.pixels_X;
    this->pixels_Y = tocopy.pixels_Y;
    this->myPPM.resize(pixels_X, vector<RGBValue>(pixels_Y));

    for (int i = 0; i < pixels_Y; i++) {
        for (int j = 0; j < pixels_X; j++){
            this->myPPM[j][i] = tocopy.myPPM[j][i];     
        }
    }
}

//-----------------------------------------------------------------------------
//Loadfile constructor - This takes a string (file name) and opens it into an 
// all ready constructed PPMImage object
PPMImage::PPMImage(string myFile) {
    LoadFile(myFile);
}

//-----------------------------------------------------------------------------
//Loadfile - takes a file name in the form of a string and loads it into the 
// object. Intilizes all variables and creates PPMImage. 
void PPMImage::LoadFile(string myFile){
   // ifstream infile(myFile, ios::binary | ios::in);
    ifstream infile(myFile);
    string line;
    bool useFile = true;
    int temp;
    unsigned char tempChar;

    if (!infile) {
        cout << "Error loading file." << endl;
    }

    getline(infile, line);
    if (line == "P6") {
        cout << "Correct file loaded" << endl;

        infile >> temp;
        pixels_X = temp;

        infile >> temp;
        pixels_Y = temp;

        infile >> temp;
        maxColor = temp;

   
        myPPM.resize(pixels_X, vector<RGBValue>(pixels_Y));
        tempChar= infile.get();

    
    }

    else if (line != "P6") {
      //  cout << "Wrong file type loaded, please load a .PPM file\n";
        useFile = false;
    }

    if (infile) {
        //cout << "pixels x " << pixels_X << " pixels_y " << pixels_Y;
        for (int i = 0; i < pixels_Y; i++) {
            for (int j = 0; j < pixels_X; j++) {
             
                tempChar = infile.get();               
                myPPM[j][i].red = tempChar;

                tempChar = infile.get();
                myPPM[j][i].green = tempChar;

                tempChar = infile.get();
                myPPM[j][i].blue = tempChar;
            }
        }
    }
}      

//-----------------------------------------------------------------------------
//get_X - returns the value of x_pixels
int PPMImage::get_X(){
    return pixels_X;
}

//-----------------------------------------------------------------------------
//Get_y - returns the value of y_pixels
int PPMImage::get_Y(){
    return pixels_Y;
}

//-----------------------------------------------------------------------------
//Output overload- This takes a given PPMImage and outputs it to a file. Used
// to create PPM images that can be opened in code or picture application
ostream& operator << (ostream& output, PPMImage& image) {
    
    output << "P6"  << endl;
    output << image.pixels_X << " ";
    output <<image.pixels_Y << endl;
    output <<image.maxColor << endl;
 
     for (int i = 0; i < image.pixels_Y; i++) {
         for (int j = 0; j < image.pixels_X; j++) {
            output << image.myPPM[j][i].red;
            output << image.myPPM[j][i].green;
            output << image.myPPM[j][i].blue;
         }
     }
    return output;
}

//-----------------------------------------------------------------------------
//Addition operator - Adds two PPMImages together regardless of shape, size, or
// total pixel count (an absolute nightmare to write)
PPMImage PPMImage :: operator +(PPMImage& toAdd){
      
        PPMImage tempImage;
        
        int x;
        int y;
        x = max(get_X(), toAdd.get_X());
        y = max(get_Y(), toAdd.get_Y());

        tempImage.myPPM.resize(x,vector<RGBValue>(y));
        tempImage.pixels_X = x;
        tempImage.pixels_Y = y;
         
         for (int i = 0; i < y ; i++) {
        
            for (int j = 0; j < x ; j++) {
                 
                if(pixels_Y < i){
                    tempImage.myPPM[j][i].red = toAdd.myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = toAdd.myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = toAdd.myPPM[j][i].blue;
                }
             
                 if(toAdd.get_Y() < i){
                    tempImage.myPPM[j][i].red = myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = myPPM[j][i].blue;
                    
                }
           
                 if(pixels_X < j){
                    tempImage.myPPM[j][i].red = toAdd.myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = toAdd.myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = toAdd.myPPM[j][i].blue;
                  
                }
            
                 if(toAdd.get_X() < j){
                    tempImage.myPPM[j][i].red = myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = myPPM[j][i].blue;
                     
                } 
               
                   if(pixels_Y > i && toAdd.get_Y() > i && pixels_X > j && toAdd.get_X() > j){
                    
                    tempImage.myPPM[j][i].red = (myPPM[j][i].red + toAdd.myPPM[j][i].red) % 256;
                    tempImage.myPPM[j][i].green = (myPPM[j][i].green + toAdd.myPPM[j][i].green) % 256;
                    tempImage.myPPM[j][i].blue = (myPPM[j][i].blue + toAdd.myPPM[j][i].blue) % 256;
                }   
                
            }//seperate the two statements into seperate ifs
        }
    return tempImage;
}

//-----------------------------------------------------------------------------
//Subtraction operator - Uses the same logic as the addition to subtract 
// instead of add. 
PPMImage PPMImage :: operator -(PPMImage& toMin){
    
        PPMImage tempImage;
        
        int x;
        int y;
        x = max(get_X(), toMin.get_X());
        y = max(get_Y(), toMin.get_Y());

        tempImage.myPPM.resize(x,vector<RGBValue>(y));
        tempImage.pixels_X = x;
        tempImage.pixels_Y = y;
         
         for (int i = 0; i < y ; i++) {
        
            for (int j = 0; j < x ; j++) {
                
                if(pixels_Y < i){
                    tempImage.myPPM[j][i].red = toMin.myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = toMin.myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = toMin.myPPM[j][i].blue;
                }
             
                 if(toMin.get_Y() < i){
                    tempImage.myPPM[j][i].red = myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = myPPM[j][i].blue;
                    
                }
           
                 if(pixels_X < j){
                    tempImage.myPPM[j][i].red = toMin.myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = toMin.myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = toMin.myPPM[j][i].blue;
                  
                }
            
                 if(toMin.get_X() < j){
                    tempImage.myPPM[j][i].red = myPPM[j][i].red;
                    tempImage.myPPM[j][i].green = myPPM[j][i].green;
                    tempImage.myPPM[j][i].blue = myPPM[j][i].blue;
                     
                } 
               
                   if(pixels_Y > i && toMin.get_Y() > i && pixels_X > j && toMin.get_X() > j){
                    
                    tempImage.myPPM[j][i].red = (myPPM[j][i].red - toMin.myPPM[j][i].red) % 256;
                    tempImage.myPPM[j][i].green = (myPPM[j][i].green - toMin.myPPM[j][i].green) % 256;
                    tempImage.myPPM[j][i].blue = (myPPM[j][i].blue - toMin.myPPM[j][i].blue) % 256;
                }   
                
            }
        }
    return tempImage;
}

//-----------------------------------------------------------------------------
//Negation operator - inverts the image by making the values for each pixel be
// the max color value minus the pixel value. 
PPMImage PPMImage :: operator -(){
    PPMImage temp;
    temp.pixels_X = get_X();
    temp.pixels_Y = get_Y();
    maxColor = 255;
    temp.myPPM.resize(pixels_X, vector<RGBValue>(pixels_Y));
    
    for (int i = 0; i < pixels_Y ; i++) {
            for (int j = 0; j < pixels_X ; j++) {
                temp.myPPM[j][i].red = (256 - myPPM[j][i].red);
                temp.myPPM[j][i].green =( 256 - myPPM[j][i].green);
                temp.myPPM[j][i].blue = (256 - myPPM[j][i].blue);      
        }
    }     
    return temp;
}

//-----------------------------------------------------------------------------
//Equals operator - Checks to see if two PPMImages are equal. Checks against 
// all elements of the file. x, y, max color, and pixel vectors. returns false
// if images do not match
bool PPMImage::operator ==(PPMImage& tocheck){
    if(get_X() == tocheck.get_X() && get_Y() == tocheck.get_Y()){
        for (int i = 0; i < get_Y(); i++) {
            for (int j = 0; j < get_X(); j++) {
                if (myPPM[j][i].red != tocheck.myPPM[j][i].red){
                    return false;
                    if(myPPM[j][i].green != tocheck.myPPM[j][i].green){
                        return false;
                        if(myPPM[j][i].blue != tocheck.myPPM[j][i].blue){
                            return false;
                        }
                    }
                }
            }     
        }
        return true;
    }

    else{
        return false;
    }

}

//-----------------------------------------------------------------------------
//Not equals operator - Checks to see if two PPMImages are not equal. checks
// against all elements of the file. x, y, max color, and pixel vectors. Returns
// true if the files do not match. 
bool PPMImage::operator !=(PPMImage& tocheck){
    if(get_X() == tocheck.get_X() && get_Y() == tocheck.get_Y()){
        for (int i = 0; i < get_Y(); i++) {
            for (int j = 0; j < get_X(); j++) {
                if (myPPM[j][i].red != tocheck.myPPM[j][i].red){
                    return true;
                    if(myPPM[j][i].green != tocheck.myPPM[j][i].green){
                        return true;
                        if(myPPM[j][i].blue != tocheck.myPPM[j][i].blue){
                            return true;
                        }
                    }
                }
            }     
        }
        return false;
    }

    else{
        return true;
    }
}

