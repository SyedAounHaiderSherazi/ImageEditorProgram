#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

#define MaxRows 400
#define MaxCols 400

class grayImage {

private:
    unsigned short Image[MaxRows][MaxCols]; //Use this 2D array to store pixels of Image
    int Rows, Cols;	//Total Rows, Columns of image
    char format[3];	//This is the magic number (The first row of pgm image)

public:
    unsigned short setPixel(unsigned short value, int r, int c) {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        Image[r][c] = value;
        return value;
    }

    /*Function for getting a single pixel at rth Row & cth Column*/
    int getPixel(int r, int c) {
        if (r >= Rows || c >= Cols || r < 0 || c < 0)
            return -1;
        return Image[r][c];
    }

    int setRows(int rows) {
        if (rows < 1 || rows > MaxRows)
            return -1;
        Rows = rows;
        return Rows;
    }

    int getRows() {
        return Rows;
    }

    int setCols(int cols) {
        if (cols < 1 || cols > MaxCols)
            return -1;
        Cols = cols;
        return Cols;
    }

    int getCols() {
        return Cols;
    }

    bool saveImage(string File_Name)
    {
        /*
        * Here write the code to save an image in .pgm format
        * The function will return true if the image is saved successfully
        */
        ofstream outFile(File_Name);
        outFile << format << endl;
        outFile << Cols << " " << Rows << endl << "255" << endl;
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                outFile << Image[i][j] << " ";
            }
            outFile << endl;
        }
        if (outFile) return true;
        return false;
    }

    bool loadImage(string File_Name)
    {
        /*
        * Here write the code to load an image which is in .pgm format
        * into the struct member "Image"
        * The function will return true if the image is loaded successfully
        */
        ifstream inFile(File_Name);
        int range = 255;
        inFile >> format;
        inFile >> Cols;
        inFile >> Rows;
        inFile >> range;

        if (!inFile.is_open()) {
            cout << "Error opening file: " << File_Name << endl;
            return false;
        }

        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < Cols; j++)
                inFile >> Image[i][j];

        if (inFile.fail()) {
            cout << "Error reading file: " << File_Name << endl;
            return false;
        }

        if (inFile.eof()) {
            cout << " End of file reached. " << endl;
        }

        inFile.close();
        return true;
    }

    void Negative()
    {
        /*
        * Here write the code to convert the grayscale image into negative form
        * Tip: You need to blacken the pixels at every index
        */

        for (int i = 0; i < Rows; i++)
            for (int j = 0;j < Cols; j++)
                Image[i][j] = 255 - Image[i][j];

    }


    void changeBrightness(double amount)
    {
        /*
        * Here write the code to brighten the grayscale image by the provided amount.
        * The range of amount is from -255 till +255
        * Tip: You need to brighten the pixels at every index
        */

        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                Image[i][j] += amount;
                if (Image[i][j] > 255) Image[i][j] = 255;
            }
        }

    }

    void medianFilter(int filterSize = 3)
    {
        /*
        * This function applies a median filter to an image.
        * It reduces noise in the image by replacing each pixel with the median value
        * of neighboring pixels within a specified filter window.
        */

        //new array 
        unsigned short newImage[MaxRows][MaxCols];          

        //itrating thro each pixel
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {

                // counter to track  number of pixels within the filter window
                int count = 0;

                // temporary array to store pixel values within the filter window
                unsigned short* temp = new unsigned short[filterSize * filterSize];

                unsigned short median = 0;

                // iterte over each pixel within  filter window
                for (int r = i; r < i + filterSize; r++) {
                    for (int c = j; c < j + filterSize; c++) {
                        // check if the pixel is within the bounds of the image
                        if (r < Rows && c < Cols) {
                            // copy pixel value to temporary array
                            temp[count++] = Image[r][c];
                        }
                    }
                }

                // sort the temporayy array to find median value
                for (int k = 0; k < count - 1; k++) {
                    for (int m = k + 1; m < count; m++) {
                        if (temp[m] < temp[k]) {
                            // Swap values to sort in ascending order
                            int temporary = temp[m];
                            temp[m] = temp[k];
                            temp[k] = temporary;
                        }
                    }
                }

                // calculating  median value based on sorted temporary array
                median = temp[count / 2];

                // assigng the median value to  corresponding pixel in the new image
                newImage[i][j] = median;

                delete[] temp;
            }
        }

        // Copy the filtered image back to  original image array
        for (int i = 0; i < Rows; i++) {
            for (int j = 0; j < Cols; j++) {
                Image[i][j] = newImage[i][j];
            }
        }
    }


    void combineSideBySide(grayImage& Two, int fillValue)
    {
        /*
        * This function combines the second image side-by-side to the current image.
        * It increases the resultant image size by adding the width of the second image to the width of the current image.
        */

        // determine  number of rows and columns for  combined image
        int r = Rows > Two.getRows() ? Rows : Two.getRows(); 
        int c = Cols + Two.getCols(); 

        // new arr
        unsigned short combinedImage[MaxRows][MaxCols];

        // cpy pixels from the cur imge -> copy impage
        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < Cols; j++)
                combinedImage[i][j] = Image[i][j];

        // cpy pixels from  second image to the combined image starting from  end of  first image
        for (int i = 0; i < Two.getRows(); i++)
            for (int j = 0; j < Two.getCols(); j++)
                combinedImage[i][j + Cols] = Two.getPixel(i, j);

// filling  rem space with the specifed val
        for (int i = 0; i < r; i++)
            for (int j = Cols + Two.getCols(); j < c; j++)
                combinedImage[i][j] = fillValue;

        // update the dimensions of ns  dwklkm232 current image to match the combined image
        Rows = r, Cols = c;

        // cpy the combined image back to  current image array
        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < Cols; j++)
                Image[i][j] = combinedImage[i][j];
    }


    void FlipHorizontally()
    {
        /*
        * This function flips the image horizontally.
        * It achieves this by swapping the pixels of each row horizontally.
        */

        // Iterate over each row 
        for (int i = 0; i < Rows; i++) {
            int temp = Cols - 1; 
            for (int j = 0; j < Cols / 2; j++) {
                int temporary = Image[i][j]; 
                Image[i][j] = Image[i][temp]; 
                Image[i][temp] = temporary; 
                temp--; // decr temp move begging row
            }
        }
    }
    void FlipVertically()
    {
        /*
        * This function flips the image vertically.
        * It achieves this by swapping the pixels of each column vertically.
        */

        for (int i = 0; i < Cols; i++) {
            int temp = Rows - 1; 
            for (int j = 0; j < Rows / 2; j++) {
                // Swap the pixel at index (j, i) with the pixel at index (temp, i)
                int temporary = Image[j][i]; 
                Image[j][i] = Image[temp][i]; 
                Image[temp][i] = temporary; 
                temp--; // Decr temp to move top of the colmn
            }
        }
    }


    /* BONUS TASK */
    void Filter(double Mask[][3], int ro, int co)
    {
        /*
        * This function applies a filter of the user's choice to the image.
        * It enhances each pixel using a 3x3 mask array provided by the user.
        */

        int l = 0, r = 0, z = 0, s = 0, x = 0, summ = 0;
        int n = ro / 2; 
        cout << endl;
        cout << "Enter the Elements of Mask Filter Array " << endl;

        // input  elements of  filter mask array
        for (int q = 0; q < ro; q++)
        {
            for (int w = 0; w < co; w++)
                cin >> Mask[q][w];
        }

        unsigned short tempImg[MaxRows][MaxCols];

        // iterate over each pixel in  image
        for (l = 0; l < Rows; l++) {
            for (r = 0; r < Cols; r++) {
                summ = 0;
                s = 0;
                // iterate over  neighboring   s pixels within  filter mask
                for (z = l - n; z <= l + n; z++) {
                    for (x = r - n; x <= r + n; x++) {
                        // Check if  neighboring pixel is within  bounds of  image
                        if (l >= 0 && l < Rows && r >= 0 && r < Cols) {
                            // apply  filter mask to enhance  pixel
                            summ = summ + (Image[z][x] * Mask[z - (l - n)][x - (r - n)]);
                            s++;
                        }
                    }
                }
                // calculae  average value of  enhanced pixel
                if (s > 0) summ = summ / s;
                // assign the enhanced pixel value to  respe position in the temping array
                tempImg[l][r] = (summ);
            }
        }

        for (int i = 0; i < Rows; i++)
            for (int j = 0; j < Cols; j++)
                Image[i][j] = tempImg[i][j];
    }

};

int main()
{
    grayImage GM;
    string outputFile;
    string image1;

    cout << "Enter name of image 1: " << endl;
    getline(cin, image1);
    GM.loadImage(image1);

    //system("CLS");

    int option = 0;

    while (option != -1)
    {
        cout << "Choose an option:\n" << endl;
        cout << " 1. Combine Two images side by side " << endl;
        cout << " 2. Change Brightness of Image" << endl;
        cout << " 3. Find Negative of an Image " << endl;
        cout << " 4. Flip an image Vertically" << endl;
        cout << " 5. Flip an image Horizontally" << endl;
        cout << " 6. Apply Median Filter (Remove Noise)" << endl;
        cout << " 7. Apply your own Filter (Bonus)" << endl;
        cout << "ENTER -1 TO EXIT" << endl;
        cin >> option;
        cout << endl;

        if (option == 1) //sidebyside
        {
            grayImage GM2;
            string image2;

            cout << "Enter name of image 2: " << endl;
            cin.ignore(999, '\n');
            getline(cin, image2);
            GM2.loadImage(image2);

            int fillVal;
            cout << "Enter the gray fill Value: " << endl;
            cin >> fillVal;
            GM.combineSideBySide(GM2, fillVal);
            cout << "Enter the output file name: ";
            cin >> outputFile;
            GM.saveImage(outputFile);
        }

        else if (option == 2) { //brightness
            int amount;
            cout << "Enter the amount for brightness: " << endl;
            cin >> amount;
            cout << endl;
            GM.changeBrightness(amount);
            cout << "Enter the output file name: ";
            cin >> outputFile;
            cout << endl;
            GM.saveImage(outputFile);
            cout << endl;
            cout << "Files Saved successfully in the output folder" << endl;
        }

        else if (option == 3) { //negative
            GM.Negative();
            cout << "Enter the output file name: ";
            cin >> outputFile;
            GM.saveImage(outputFile);
            cout << endl;
            cout << "Files Saved successfully in the output folder" << endl;
        }

        else if (option == 4) { //flip v
            GM.FlipVertically();
            cout << "Enter the output file name: ";
            cin >> outputFile;
            GM.saveImage(outputFile);
            cout << endl;
            cout << "Files Saved successfully in the output folder" << endl;
        }

        else if (option == 5) { //flip h
            GM.FlipHorizontally();
            cout << "Enter the output file name: ";
            cin >> outputFile;
            GM.saveImage(outputFile);
            cout << endl;
            cout << "Files Saved successfully in the output folder" << endl;
        }

        else if (option == 6) { //median

            int filtersize;
            cout << "Enter filter size: " << endl;
            cin >> filtersize;
            GM.medianFilter(filtersize);
            cout << "Enter the output file name: ";
            cin >> outputFile;
            cout << endl;
            GM.saveImage(outputFile);
            cout << endl;
            cout << "Files Saved successfully in the output folder" << endl;
        }

        else if (option == 7) { //Filter
            double b[3][3];
            int r = 3, c = 3;
            GM.Filter(b, r, c);
            cout << "Enter the output file name: ";
            cin >> outputFile;
            cout << endl;
            GM.saveImage(outputFile);
        }

        else if (option == -1)
            break;
    }

    return 0;
}