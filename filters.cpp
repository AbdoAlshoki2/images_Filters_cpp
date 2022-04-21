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

void rotate();
void rotateImage90();
void rotateImage180();
void rotateImage270();

void lighting();
void shrink();

int main()
{
    loadImage();
    invertImage();
    merge();
    rotate();
    lighting();
    shrink();
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
//_________________________________________
void rotate(){
    //check the input from the user
    string numRotate;

    while (true) {
        cout << "Please Enter valid Rotates (90, 180, 270):\n";
        cin >> numRotate;
        if (numRotate == "90" or numRotate == "180" or numRotate == "270")
            break;
    }
    if(numRotate == "90"){
        rotateImage90();
    }
    else if(numRotate == "180"){
        rotateImage180();
    }
    else if(numRotate == "270"){
        rotateImage270();
    }

}

void rotateImage90() {
    //make image rotate 90 degree
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            newImage[i][j] = image[255-j][i];
        }
    }
    equlaity();
}

void rotateImage180() {
    //make image rotate 180
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            newImage[i][j] = image[255 - i][255 - j];
        }
    }
    equlaity();
}

void rotateImage270() {
    //make image rotate 270
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            newImage[i][j] = image[j][255 - i];
        }
    }
    equlaity();
}
//_________________________________________
void lighting() {
    string choice;
    cout<<"Do you want to make it lighter or darker"<<endl;
    cin>>choice;
    for_each(choice.begin(), choice.end(), [](char & c){
        c = ::tolower(c);
    });
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            if (choice == "lighter") {
                image[i][j] = fmin(255,image[i][j]*1.5);
                // make each pixel by 1.5  and take the minimum of 255 and the multiplication
            }
            if (choice == "darker")
                image[i][j] *= 0.5;
            // divide each pixel by 2
        }
    }
}
//_________________________________________
void shrink(){
    int x;
    cout << "enter the the percentage \n"
         << "1- 25%\n"
         << "2- 33%\n"
         << "3- 50%\n";
    cin>>x;
    // depend on user .. make every 2 pixels in new image = 1 pixel in original
    // or 3 pixels in new image = 1 pixel in original image
    // or 4 pixels in new image = 1 pixel in original image

    for (int i = 1; i < SIZE -1 ; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            if(x == 1 or x ==25)
                newImage[i/4][j/4] = image[i][j];
            else if (x == 2 or x == 33)
                newImage[i/3][j/3] = image[i][j];
            else if (x == 3 or x == 50)
                newImage[i/2][j/2] = image[i][j];
        }
    }
    equlaity();
}


