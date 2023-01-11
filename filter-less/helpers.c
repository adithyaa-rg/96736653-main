#include "helpers.h"
#include <math.h>
#include <stdio.h>

void swap(BYTE *a, BYTE *b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for (int i=0; i<height ; i++)
    {
        for (int j=0; j<width ; j++)
        {
            average=(image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3;
            average=round(average);
            image[i][j].rgbtBlue=(BYTE)average;
            image[i][j].rgbtRed=(BYTE)average;
            image[i][j].rgbtGreen=(BYTE)average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float Blue,Green,Red;
    for (int i=0;i<height;i++)
    {
        for (int j=0; j<width ; j++)
        {
            Blue=.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            Green=.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            Red=.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if (Blue>255)
            {
                Blue=255;
            }
            if (Green>255)
            {
                Green=255;
            }
            if (Red>255)
            {
                Red=255;
            }
            image[i][j].rgbtBlue=(BYTE)Blue;
            image[i][j].rgbtRed=(BYTE)Red;
            image[i][j].rgbtGreen=(BYTE)Green;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tempRed;
    BYTE tempGreen;
    BYTE tempBlue;

    for (int i=0; i<height ; i++)
    {
        for (int j=0 ; j<width/2 ; j++)
        {
            swap(&image[i][j].rgbtRed,&image[i][width-j].rgbtRed);

            swap(&image[i][j].rgbtGreen,&image[i][width-j].rgbtGreen);

            swap(&image[i][j].rgbtBlue,&image[i][width-j].rgbtBlue);

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blurRed,blurGreen,blurBlue;
    for (int i=1; i<height-1 ; i++)
    {
        for (int j=1 ; j<width-1 ; j++)
        {
            blurRed=(image[i-1][j-1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed);
            blurGreen=(image[i-1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen);
            blurBlue=(image[i-1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue);
            image[i][j].rgbtRed=(int) (blurRed/9);
            image[i][j].rgbtGreen=(int) (blurGreen/9);
            image[i][j].rgbtBlue=(int) (blurBlue/9);

        }
    }
/*
        for (int i=0,j=0;j<width;j++)
        {
            blurRed=(image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed;
            blurGreen=(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen;
            blurBlue=(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue;
            image[i][j].rgbtRed=(int) (blurRed/6);
            image[i][j].rgbtGreen=(int) (blurGreen/6);
            image[i][j].rgbtBlue=(int) (blurBlue/6);
        }
        for (int i=height-1,j=0;j<width;j++)
        {
            blurRed=(image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+image[i-1][j-1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed;
            blurGreen=(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+image[i-1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen;
            blurBlue=(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+image[i-1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue;
            image[i][j].rgbtRed=(int) (blurRed/6);
            image[i][j].rgbtGreen=(int) (blurGreen/6);
            image[i][j].rgbtBlue=(int) (blurBlue/6);
        }
        for (int i=0,j=0;i<height;i++)
        {
            blurRed=(image[i][j+1].rgbtRed+image[i][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed;
            blurGreen=(image[i][j+1].rgbtGreen+image[i][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen;
            blurBlue=(image[i][j+1].rgbtBlue+image[i][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue;
            image[i][j].rgbtRed=(int) (blurRed/6);
            image[i][j].rgbtGreen=(int) (blurGreen/6);
            image[i][j].rgbtBlue=(int) (blurBlue/6);
        }
        for (int i=0,j=0;j<width;j++)
        {
            blurRed=(image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed;
            blurGreen=(image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen;
            blurBlue=(image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue;
            image[i][j].rgbtRed=(int) (blurRed/6);
            image[i][j].rgbtGreen=(int) (blurGreen/6);
            image[i][j].rgbtBlue=(int) (blurBlue/6);
        }
*/
    return;
}

void swap(BYTE *a, BYTE *b)
{
    BYTE temp;
    temp=*a;
    *a=*b;
    *b=temp;
}