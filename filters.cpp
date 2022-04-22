#include <bits/stdc++.h>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE] , newImage[SIZE][SIZE], image2[SIZE][SIZE];
unsigned char quarter1[128][128],quarter2[128][128] , quarter3[128][128],quarter4[128][128];


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
void enlarge();
void shrink();
void shuffle();
void bluring();

int main()
{
    loadImage();
    invertImage();
    merge();
    rotate();
    lighting();
    enlarge();
    shrink();
    shuffle();
    bluring();

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
void enlarge() {
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i < 128 and j < 128) {
                quarter1[i][j] = image[i][j];
            } else if (i < 128 and j > 128) {
                quarter2[i][j - 128] = image[i][j];
            } else if (i > 128 and j < 128) {
                quarter3[i - 128][j] = image[i][j];
            } else if (i > 128 and j > 128) {
                quarter4[i - 128][j - 128] = image[i][j];
            }
        }
    }
    int choice;
    cout << "Please enter the quarter you want:";
    cin>> choice;
    if(choice == 1){
        for (int i = 0; i < SIZE ; i++) {
            for (int j = 0; j < SIZE ; j++) {
                newImage[i][j] = quarter1[i/2][j/2];
            }
        }

    }

    if(choice == 2){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                newImage[i][j] = quarter2[i/2][j/2];
            }
        }
    }
    if(choice == 3) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = quarter3[i / 2][j / 2];
            }
        }
    }
    if(choice == 4){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = quarter4[i / 2][j / 2];
            }
        }
    }
    equlaity();
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
//_________________________________________
void shuffle(){
    string choice;
    cout<<"enter the order you like:";
    cin>> choice;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i < 128 and j < 128) {
                quarter1[i][j] = image[i][j];
            } else if (i < 128 and j > 128) {
                quarter2[i][j - 128] = image[i][j];
            } else if (i > 128 and j < 128) {
                quarter3[i - 128][j] = image[i][j];
            } else if (i > 128 and j > 128) {
                quarter4[i - 128][j - 128] = image[i][j];
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i < 128 and j < 128) {
                    if(choice[0] == '1')
                        newImage[i][j] = quarter1[i][j];
                    else if(choice[0] == '2')
                        newImage[i][j] = quarter2[i][j];
                    else if(choice[0] == '3')
                        newImage[i][j] = quarter3[i][j];
                    else if(choice[0] == '4')
                        newImage[i][j] = quarter4[i][j];

                }

                else if (i < 128 and j > 128) {
                    if(choice[1] == '1')
                        newImage[i][j] = quarter1[i][j-128];
                    else if(choice[1] == '2')
                        newImage[i][j] = quarter2[i][j-128];
                    else if(choice[1] == '3')
                        newImage[i][j] = quarter3[i][j-128];
                    else if(choice[1] == '4')
                        newImage[i][j] = quarter4[i][j-128];
                }

                else if (i > 128 and j < 128) {
                    if(choice[2] == '1')
                        newImage[i][j] = quarter1[i-128][j];
                    else if(choice[2] == '2')
                        newImage[i][j] = quarter2[i-128][j];
                    else if(choice[2] == '3')
                        newImage[i][j] = quarter3[i-128][j];
                    else if(choice[2] == '4')
                        newImage[i][j] = quarter4[i-128][j];

                }

                else if (i > 128 and j > 128) {
                    if(choice[3] == '1')
                        newImage[i][j] = quarter1[i-128][j-128];
                    else if(choice[3] == '2')
                        newImage[i][j] = quarter2[i-128][j-128];
                    else if(choice[3] == '3')
                        newImage[i][j] = quarter3[i-128][j-128];
                    else if(choice[3] == '4')
                        newImage[i][j] = quarter4[i-128][j-128];

                }
            }

        }

    }
    equlaity();
}
//_________________________________________
void bluring(){
    long avg = 0;
    // get average of around pixels and put it in the value of pixel
    for (int i = 0; i < SIZE  ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            long long avg = 0;
            for (int k = i-3; k <= i+3; ++k) {
                for (int l = j - 3; l <= j + 3; ++l) {
                    avg += image[k][l];
                }
            }
            image [i][j] = avg/49 ;
        }
    }
}


