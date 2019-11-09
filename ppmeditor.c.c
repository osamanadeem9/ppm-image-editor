
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

struct pix {            // structure for image pixels
    int red;
    int blue;
    int green;
} pixel[1000000];

// forward declaration of functions

void grayscale(struct pix pixel[], int number_of_pixels);
void horizontal_flip(struct pix pixel[], int horizontal, int vertical);
void negate_red(struct pix pixel[], int number_of_pixels);
void negate_green(struct pix pixel[], int number_of_pixels);
void negate_blue(struct pix pixel[], int number_of_pixels);
void flatten_red(struct pix pixel[], int number_of_pixels);
void flatten_green(struct pix pixel[], int number_of_pixels);
void flatten_blue(struct pix pixel[], int number_of_pixels);
void extreme_contrast(struct pix pixel[],int number_of_pixels);


int main()
{
    int number_of_pixels;
    char  buffer[3000];     //buffer for storing a row of file
    FILE  *fptr1, *fptr2;
    char filename[50];

    printf("+------------------------------------+\n");
    printf("| Portable Pixmap (PPM) Image Editor |\n");
    printf("+------------------------------------+\n\n");

    printf("Enter name of image file: ");
    scanf("%s", filename);

    fptr1 = fopen( filename , "r" );    //read file using file handling

    if ( fptr1 == NULL ) {              // returns if file is missing
        printf("Can't open file.\n");
        return;
    }

    int count=0;
    int i=0, j[200], k=0;
    int horizontal, vertical;

    while (fgets(buffer, 3000, fptr1)!=NULL) {
        count++;    // stores the line number whenever line is read from file

        if (count==2) {
            sscanf(buffer,"%d %d", &horizontal, &vertical);     // stores the number of rows and columns in variables using sscanf
            if (horizontal>1000 || vertical>1000) {
                printf("\nBUFFER SIZE EXCEEDS!!! PROGRAM TERMINATES!\n");     // program terminates if buffer exceeds 3000 i.e. number
                return;                                                     // of pixels in a row or column exceeds 1000
            }
            break;
        }
    }
    while (fgets(buffer, 3000, fptr1)!=NULL) {
        count++;
        if (count>3) {

            char *pch=strtok(buffer, " ");  //breaks buffer string to tokens using the space delimiter
            while (pch!=NULL) {

                j[i]=atoi(pch);     // converts string argument to integers
                if (i%3==0) {
                    pixel[k].red=j[i];

                }
                if (i%3==1) {
                    pixel[k].green=j[i];
                }
                if (i%3==2) {
                    pixel[k].blue=j[i];
                    k++;
                }

        // stores the extracted integers in red, blue, green element of pixel

                i++;
                pch = strtok (NULL, " ");
            }
        }
        i=0;
    }
    number_of_pixels=k;     // stores number of pixels in another variable

    printf("Enter name of output file: ");
    scanf("%s", &filename);

    menu(pixel, number_of_pixels, horizontal, vertical);    // displays menu, asks for choice and applies the functions
                                                            // to the image
    fptr2=fopen(filename, "w");         // open the output file for writing

    fprintf(fptr2, "P3\n%d %d\n255\n", horizontal, vertical);   //writes the header to output ppm file

    for (i=0; i<number_of_pixels; i++) {
        fprintf(fptr2, "%d %d %d ", pixel[i].red, pixel[i].green, pixel[i].blue);   // writes the edited pixels to output file
    }

    fclose(fptr1);      // closes the file
    fclose(fptr2);
}

void greyscale(struct pix pixel[], int number_of_pixels) {      //takes the pixel structure and number of pixels as parameter
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].red=(pixel[i].red+pixel[i].green+pixel[i].blue)/3;     // calculates the average of pixel elements
        pixel[i].blue=pixel[i].green=pixel[i].red;
    }
}

void negate_red(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].red=255-pixel[i].red;      // subtracts the red element from 255 for negate red function
    }
}

void negate_green(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].green=255-pixel[i].green;
    }
}

void negate_blue(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].blue=255-pixel[i].blue;
    }
}

void flatten_red(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].red=0;     // assigns 0 to all red elements to apply flatten red function
    }
}

void flatten_green(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].green=0;
    }
}

void flatten_blue(struct pix pixel[], int number_of_pixels) {
    int i;
    for (i=0; i<number_of_pixels; i++) {
        pixel[i].blue=0;
    }
}

void horizontal_flip(struct pix pixel[], int horizontal, int vertical) {
    /*
        flips the image horizontally by swapping each pixel element of an image row
    */
    int i,j,k,m=0;
    for (i=0; i<vertical*2; i++) {
        for (j=m, k=m+horizontal-1; j<((i+1)*horizontal)/2; j++, k--) {
            int temp1=pixel[j].red;
            pixel[j].red=pixel[k].red;
            pixel[k].red=temp1;

            int temp2=pixel[j].green;
            pixel[j].green=pixel[k].green;
            pixel[k].green=temp2;

            int temp3=pixel[j].blue;
            pixel[j].blue=pixel[k].blue;
            pixel[k].blue=temp3;
        }
        m=j;
    }
}

void extreme_contrast (struct pix pixel[],int number_of_pixels) {
    /*
        sets the RGB values to either higher or lower extreme
    */
    int i;
    for (i=0; i<number_of_pixels; i++) {
        if (pixel[i].red>(255/2)) {
            pixel[i].red=255;
        } else {
            pixel[i].red=0;
        }

        if (pixel[i].green>(255/2)) {
            pixel[i].green=255;
        } else {
            pixel[i].green=0;
        }

        if (pixel[i].blue>(255/2)) {
            pixel[i].blue=255;
        } else {
            pixel[i].blue=0;
        }
    }
}

int menu(struct pix pixel[], int number_of_pixels, int horizontal,int vertical)
{
    /*
        The function displays the menu to the user.
        Then asks the user to choose the effect user wants to be applied to the
        image. Multiple effects can also be applied to the same image.
    */
    char choice;
    printf("\n\nHere are your choices: \n");
    printf("\t[1] convert to greyscale [2] flip horizontally \n");
    printf("\t[3] negative of red \t [4] negative of green \t [5] negative of blue \n");
    printf("\t[6] just the reds \t [7] just the greens \t [8] just the blues\n");
    printf("\t[9] extreme contrast\n\n");

    printf("\tDo you want [1]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        greyscale(pixel, number_of_pixels);
    }

    printf("\tDo you want [2]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        horizontal_flip(pixel, horizontal, vertical);
    }

    printf("\tDo you want [3]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        negate_red(pixel, number_of_pixels);
    }

    printf("\tDo you want [4]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        negate_green(pixel, number_of_pixels);
    }

    printf("\tDo you want [5]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        negate_blue(pixel, number_of_pixels);
    }

    printf("\tDo you want [6]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        flatten_red(pixel, number_of_pixels);
    }

    printf("\tDo you want [7]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        flatten_green(pixel, number_of_pixels);
    }

    printf("\tDo you want [8]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        flatten_blue(pixel, number_of_pixels);
    }

    printf("\tDo you want [9]? (y/n)  ");
    scanf(" %c", &choice);
    if (choice=='y' || choice=='Y') {
        extreme_contrast(pixel, number_of_pixels);
    }
}
