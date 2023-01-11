#include "helpers.h"
#include <math.h>

void swap(BYTE *a, BYTE *b)
{
    BYTE temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
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
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blurRed,blurGreen,blurBlue;
    RGBTRIPLE blur[height][width];
    for (int i=1; i<height-1 ; i++)
    {
        for (int j=1 ; j<width-1 ; j++)
        {
            blurRed=(image[i-1][j-1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i][j-1].rgbtRed+image[i][j].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed);
            blurGreen=(image[i-1][j-1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j-1].rgbtGreen+image[i][j].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen);
            blurBlue=(image[i-1][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j-1].rgbtBlue+image[i][j].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue);
            blur[i][j].rgbtRed=(int) (blurRed/9);
            blur[i][j].rgbtGreen=(int) (blurGreen/9);
            blur[i][j].rgbtBlue=(int) (blurBlue/9);
        }
    }
    for (int i=1; i<height-1 ; i++)
    {
        for (int j=1 ; j<width-1 ; j++)
        {
            image[i][j].rgbtRed=blur[i][j].rgbtRed;
            image[i][j].rgbtBlue=blur[i][j].rgbtBlue;
            image[i][j].rgbtGreen=blur[i][j].rgbtGreen;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgeX[height][width],edgeY[height][width],value[height][width];
    for (int i=1; i<height-1 ; i++)
    {
        for (int j=1 ; j<width-1 ; j++)
        {
            edgeX[i][j].rgbtRed=(BYTE)(-1*image[i-1][j-1].rgbtRed+0*image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed-2*image[i][j-1].rgbtRed+0*image[i][j].rgbtRed+2*image[i][j+1].rgbtRed-1*image[i+1][j-1].rgbtRed+0*image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed);
            edgeX[i][j].rgbtGreen=(BYTE)(-1*image[i-1][j-1].rgbtGreen+0*image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen-2*image[i][j-1].rgbtGreen+0*image[i][j].rgbtGreen+2*image[i][j+1].rgbtGreen-1*image[i+1][j-1].rgbtGreen+0*image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen);
            edgeX[i][j].rgbtBlue=(BYTE)(-1*image[i-1][j-1].rgbtBlue+0*image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue-2*image[i][j-1].rgbtBlue+0*image[i][j].rgbtBlue+2*image[i][j+1].rgbtBlue-1*image[i+1][j-1].rgbtBlue+0*image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue);
            edgeY[i][j].rgbtRed=(BYTE)(-1*image[i-1][j-1].rgbtRed-2*image[i-1][j].rgbtRed-1*image[i-1][j+1].rgbtRed+image[i+1][j-1].rgbtRed+2*image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed);
            edgeY[i][j].rgbtGreen=(BYTE)(-1*image[i-1][j-1].rgbtGreen-2*image[i-1][j].rgbtGreen-1*image[i-1][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen+2*image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen);
            edgeY[i][j].rgbtBlue=(BYTE)(-1*image[i-1][j-1].rgbtBlue-2*image[i-1][j].rgbtBlue-1*image[i-1][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue+2*image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue);


            value[i][j].rgbtRed=(BYTE)(sqrt(edgeX[i][j].rgbtRed*edgeX[i][j].rgbtRed+edgeY[i][j].rgbtRed*edgeY[i][j].rgbtRed));

            if (value[i][j].rgbtRed>255)
            {
                value[i][j].rgbtRed=255;
            }
            if (value[i][j].rgbtRed<0)
            {
                value[i][j].rgbtRed=0;
            }
            value[i][j].rgbtGreen=(BYTE)(sqrt(edgeX[i][j].rgbtGreen*edgeX[i][j].rgbtGreen+edgeY[i][j].rgbtGreen*edgeY[i][j].rgbtGreen));
            if (value[i][j].rgbtGreen>255)
            {
                value[i][j].rgbtGreen=255;
            }
            if (value[i][j].rgbtGreen<0)
            {
                value[i][j].rgbtGreen=0;
            }
            value[i][j].rgbtBlue=(BYTE)(sqrt(edgeX[i][j].rgbtBlue*edgeX[i][j].rgbtBlue+edgeY[i][j].rgbtBlue*edgeY[i][j].rgbtBlue));
            if (value[i][j].rgbtBlue>255)
            {
                value[i][j].rgbtBlue=255;
            }
            if (value[i][j].rgbtBlue<0)
            {
                value[i][j].rgbtBlue=0;
            }

        }
    }
    for (int i=1; i<height/2 ; i++)
    {
        for (int j=1 ; j<width-1 ; j++)
        {
            image[i][j].rgbtRed=value[i][j].rgbtRed;
            image[i][j].rgbtBlue=value[i][j].rgbtBlue;
            image[i][j].rgbtGreen=value[i][j].rgbtGreen;
        }
    }
    return;
}
