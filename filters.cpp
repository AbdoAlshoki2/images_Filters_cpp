#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE] , newImage[SIZE][SIZE], image2[SIZE][SIZE];


void loadImage ();
void saveImage ();
void loadImage2 ();
void equlaity();

void invertImage();

void merge ();

int main()
{
    loadImage();
    invertImage();
    merge();
    saveImage();
}

//_________________________________________
void loadImage () {
    while(true){
        char imageFileName[100];
        // Get gray scale image file name
        cout << "Enter the source image file name:";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat (imageFileName, ".bmp");
        if(readGSBMP(imageFileName, image) != 1)
            break;
    }
    cin.clear();
    cin.sync();
}

//_________________________________________
void saveImage () {
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, image);
}

//_________________________________________
void loadImage2 () {
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the second source image file name:";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);
}
//_________________________________________
void equlaity(){
    for(int i = 0; i < SIZE; ++i){
        for(int j = 0; j < SIZE; j++){
            image[i][j] = newImage[i][j];
            newImage[i][j] = 0;
        }
    }
}

//_________________________________________
void invertImage() {
    //invert image (invert black to white and white to black and grey to the opposite level of brightness)
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            newImage[i][j] = 255 - image[i][j];
        }
    }
    equlaity();
}
//_________________________________________
void merge() {
    long avg = 0;
    // get avg values of 2 pixels in 2 image
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            avg = (image[i][j] + image2[i][j]) / 2;
            image[i][j] = avg;
        }
    }
}


