// Filters code
// Team members :
// 1- Mennt Allah Ahmed Saeed Shiha
// 2- Alaa Azazi Abdelhamid
// 3- Abdelrahman Mohamed Ali Hassan
// TA: Eng Yousra Ayman
// TA: Nesma Mohamed
// Course Instructors: Dr. Mohammed El-Ramly

#include <bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE] , newImage[SIZE][SIZE], image2[SIZE][SIZE];
unsigned char quarter1[128][128],quarter2[128][128] , quarter3[128][128],quarter4[128][128];


void loadImage ();
void saveImage ();
void loadImage2 ();
void equlaity();

void BlacknWhite();
void invertImage();
void merge ();

void flipping();
void flipLeftRight();
void flipUpDown();

void rotate();
void rotateImage90();
void rotateImage180();
void rotateImage270();

void lighting();
void detectimage();
void enlarge();
void shrink();
void mirrorimage();
void shuffle();
void bluring();

int main()
{
    string choice;
    cout<<"Ahlan ya user ya habibi\nPlease enter file name of the image to process\n";

    loadImage();
    cout <<"Please select a filter to apply or 0 to exit:\n";
    while(true){
        cout << "1- Black & White Filter\n"
             <<"2- Invert Filter\n"
             <<"3- Merge Filter\n"
             <<"4- Flipping image\n"
             <<"5- Rotate image\n"
             <<"6- Darken and Lighten Image\n"
             <<"7- Detect Image Edges \n"
             <<"8- Enlarge Image \n"
             <<"9- Shrink Image \n"
             <<"a- Mirror 1/2 Image \n"
             <<"b- Shuffle Image \n"
             <<"c- Blur Image \n"
             <<"s- Save the image to a file\n"
             <<"0- Exit" << endl;

        getline(cin,choice);
        for_each(choice.begin(), choice.end(), [](char & c){
            c = ::tolower(c);
        });
        if ( choice == "black & white" or choice == "1"){
            BlacknWhite();
        }
        else if(choice == "invert image" or choice =="2") {
            invertImage();
        }
        else if(choice == "merge image" or choice =="3") {
            loadImage2();
            merge();
        }
        else if (choice == "flipping image" or choice == "4") {
            flipping();
        }
        else if(choice == "rotate image" or choice =="5") {
            rotate();
        }
        else if (choice == "darken and lighten" or choice == "6"){
            lighting();

        }
        else if(choice == "detect image" or choice =="7") {
            detectimage();
        }
        else if(choice == "enlarge image" or choice =="8") {
            enlarge();
        }
        else if(choice == "shrink image" or choice =="9") {
            shrink();
        }
        else if(choice == "mirror 1/2 image" or choice =="a") {
            mirrorimage();
        }
        else if(choice == "shuffle image" or choice =="b") {
            shuffle();
        }
        else if(choice == "blur image" or choice =="c") {
            bluring();
        }

        else if (choice == "s" or choice == "save"){
            saveImage();
            break;
        }
        else if (choice == "0" or choice == "exit"){
            saveImage();
            break;
        }
        else {
            cout<<"invalid input, please try again" <<endl;
        }
        cin.clear();
        cin.sync();
        cout<<"make your choice"<<endl;
    }
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
    while(true) {
        char imageFileName[100];

        // Get gray scale image file name
        cout << "Enter the second source image file name:";
        cin >> imageFileName;

        // Add to it .bmp extension and load image
        strcat(imageFileName, ".bmp");
        if(readGSBMP(imageFileName, image2) != 1)
            break;
    }
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
void BlacknWhite(){
    for (int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(image[i][j]>127)    // invert black .. make pixel white if it is > the medium
                image[i][j]=255;
            else
                image[i][j]=0;  // make pixel black if it is < the medium
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
void flipping(){
    cout<<"how do you want to flip: (enter the number of choice)\n"<<"1- left and right\n2- up and down"<<endl;
    string x;
    cin>>x;
    while(true) {
        if (x == "1"){
            flipLeftRight();   // invert to flip to left
            break;
        }
        else if (x == "2") {
            flipUpDown();      // invert to flip to down
            break;
        }
        else {
            cout << "wrong input, enter the right choice" << endl;
            cin>>x;
        }
    }
}

void flipLeftRight()
{
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE/2; y++) {
            int temp = image[x][y];
            image[x][y]=image[x][SIZE-y];
            image[x][SIZE-y]=temp;
        }
    }
}

void flipUpDown()
{
    for (int x = 0; x < SIZE/2; x++) {
        for (int y = 0; y < SIZE; y++) {
            int temp = image[x][y];
            image[x][y]=image[SIZE-x][y];
            image[SIZE-x][y]=temp;
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
    while(true){
        if(choice == "lighter" || choice == "darker")
            break;
        else {
            cout << "wrong input, try again" << endl;
            cin>> choice;
        }
    }
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
void detectimage(){
    // algorithm sobel for detected edges
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            int x,y;
            if ( (i-1)>0 && (i+1)<255 && (j-1>0) && (j+1)<255 ) {
                x = image[i+1][j]+ image[i-1][j] -2 * image[i][j];
                y =  image[i][j+1] + image[i][j-1] -2 *image[i][j];
                newImage[i][j] =abs(255-(abs(x)+abs(y)));
            }
            else
                newImage[i][j]=255 ;
        }
    }
    equlaity();
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
    string choice;
    while(true) {
        cout << "Please enter the quarter you want (1, 2, 3 or 4):";
        cin >> choice;
        if(choice == "1" or choice == "2" or choice == "3" or choice == "4")
            break;
    }

    if(choice == "1"){
        for (int i = 0; i < SIZE ; i++) {
            for (int j = 0; j < SIZE ; j++) {
                newImage[i][j] = quarter1[i/2][j/2];
            }
        }
    }

    if(choice == "2"){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                newImage[i][j] = quarter2[i/2][j/2];
            }
        }
    }
    if(choice == "3") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                newImage[i][j] = quarter3[i / 2][j / 2];
            }
        }
    }
    if(choice == "4"){
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
    string x;
    cout << "enter the the percentage \n"
         << "1- 25%\n"
         << "2- 33%\n"
         << "3- 50%\n";
    cin>>x;
    // depend on user .. make every 2 pixels in new image = 1 pixel in original
    // or 3 pixels in new image = 1 pixel in original image
    // or 4 pixels in new image = 1 pixel in original image
    while(true){
        if(x == "1" || x == "25" || x == "3" || x == "50" || x == "2" || x == "33" )
            break;
        else {
            cout << "wrong input, try again" << endl;
            cin>> x;
        }
    }
    for (int i = 1; i < SIZE -1 ; i++) {
        for (int j = 1; j < SIZE - 1; j++) {
            if(x == "1" || x =="25")
                newImage[i/4][j/4] = image[i][j];
            else if (x == "2" || x == "33")
                newImage[i/3][j/3] = image[i][j];
            else if (x == "3" || x == "50")
                newImage[i/2][j/2] = image[i][j];
        }
    }
    equlaity();
}
//_________________________________________
void mirrorimage(){
    string n;
    cout<<" press 1 for right mirror, 2 for left, 3 for upper , 4 for lower:   ";
    cin>>n;
    while(true){
        if(n == "1" || n == "2" || n == "3" || n == "4" )
            break;
        else {
            cout << "wrong input, try again" << endl;
            cin>> n;
        }
    }
    if(n=="1") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {        // divide each pixel by 2
                image[i][j] = image[i][255 - j];
            }
        }
    }

    if(n=="2") {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE / 2; j++) {
                image[i][255 - j] = image[i][j];
            }
        }
    }
    if(n=="3") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[255 - i][j] = image[i][j];
            }
        }
    }
    if(n=="4") {
        for (int i = 0; i < SIZE / 2; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = image[255 - i][j];
            }
        }
    }

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


