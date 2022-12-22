#include<iostream>
#include<fstream>
#include "RGBValue.h"
#include "PPMImage.h"
#include "PPMLine.h"
#include <vector>
#include <string>

int main() {



        // Test constructors
        PPMImage img0;
        PPMImage img1("pikachu.ppm");
        PPMImage img2 = img1;
        PPMImage img3 ("catcough.ppm");
	std::cout << "---Constructors Tested---" << std::endl;
        PPMImage img5 = img3;
        // Test first class operations

        // tests + of PPMImage
        PPMImage img4 = img1 + img1;

        // tests - of PPMImage
        PPMImage img6 = img4 - img1;

        // tests inversion of an image
        PPMImage img7 = -img3;
        PPMImage img9 = img1 + img3;


        // tests output to stdout
        //std::cout << img7 << std::endl;

        
        PPMImage img8;
        img8.LoadFile("blank.ppm");
      

        std::vector<PPMImage> imagesToOutput;
        imagesToOutput.push_back(img0);
        imagesToOutput.push_back(img1);
        imagesToOutput.push_back(img2);
        imagesToOutput.push_back(img3);
        imagesToOutput.push_back(img4);
        imagesToOutput.push_back(img5);
        imagesToOutput.push_back(img6);
        imagesToOutput.push_back(img7);
        imagesToOutput.push_back(img8);
        imagesToOutput.push_back(img9);


        for (unsigned short i = 0; i < imagesToOutput.size(); i++) {
                std::string filename = "img" + std::to_string(i) + ".ppm";   
                std::ofstream outFile(filename.c_str(), std::ios_base::out | std::ios_base::binary);
                outFile << imagesToOutput[i];
		outFile.close();
        }



	return 0;
}