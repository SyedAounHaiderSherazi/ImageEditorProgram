![image](https://github.com/SyedAounHaiderSherazi/ImageEditorProgram/assets/168753404/de52b104-dbbd-41b2-8498-82c2fb8edde9)
# ImageEditorProgram
AN Image Editor Program in C++ implementing all the necessary functions of filters.
A .PGM image format can be represented using a 2D Integer Matrix, each index representing a colour pixel which ranges from (0 - 255), where 0 is the darkest and 255 is the brightest. Below is a sample pgm image file, and another can be found by clicking here Sample-2: 
P2
4 4
255
0 33 0 170
0 143 0 0
0 0 63 0
170 0 0 255
Here the first row represents a magic number “P2” which provides encoded information about the image. This row can be hard coded. The next row contains information about the total number of columns and rows of the image respectively. The third row contains information about the maximum grey scale value of the image. You can read more about Portable Grey Map Images on the following page: PGM Images Info
Your task is to implement an image editor program in C++ containing a class “Image” that will have the following functions:
1. Read a PGM image file into a 2D Integer Matrix
2. Save the edited PGM image into a file
3. Change the image's brightness by a value which ranges from -255 to 255
4. Flip the image horizontally or vertically
5. Combine Two Images Side to Side
6. Find the negative of an Image
7. Apply the median filter on an image to reduce noise
8. Implement the additional feature of applying filter which will count towards bonus marks in the assignment
Use the following skeleton code as a starting point in order to understand the question more briefly. Code URL: Github
