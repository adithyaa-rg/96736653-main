#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc!=2)
    {
        return 1;
    }
    FILE *file = fopen(argv[1], "r");

    if (file==NULL)
    {
        printf("No file has been opened");
        return 1;
    }
    int BLOCK_SIZE=512;
    BYTE *buffer=malloc(512*sizeof(BYTE));
    BYTE *final=malloc(512*sizeof(BYTE));
    BYTE *final_temp;
    int size=0;
    int state=0;
    int i=0;
    char *write_file=malloc(sizeof("###.jpg"));
    FILE *file_write;
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        printf("%d %d %d %d\n",(int)*(buffer+0),(int)*(buffer+1),(int)*(buffer+2),(int)*(buffer+3));
        if (*(buffer+0)==255 && *(buffer+1)==216 && *(buffer+2)==255 && buffer[3]<240 && buffer[3]>=224)
        {
            state=1;
            size=1;
            sprintf(write_file, "%03i.jpg", i);
            if (file_write!=NULL)
            {
                fclose(file_write);
            }
            i+=1;
        }
        if(state==1)
        {

          //if (size!=1)
            //{
            if (final_temp!=NULL)
            {
                free(final);
                final_temp=malloc(512*sizeof(BYTE)*size);
            }
            //}
            /*else
            {
                free(final);
                final_temp=malloc(512*sizeof(BYTE));
            }*/

            for (int j=0; j<512*(size-1);j++)
            {

                if (final!=NULL)
                {
                    printf("%d",j);
                    final_temp[i]=final[i];
                }
            }
            int j=512*(size-1),k=0;
            while(k<512)
            {
                final_temp[j]=buffer[k];
                j++;
                k++;
            }

            size+=1;
            final=final_temp;
            //free(final_temp);*/
            file_write = fopen(write_file, "w");
            fwrite(final_temp, 1, BLOCK_SIZE, file_write);
            fclose(file_write);

            //printf("%d-size\n",size);
            //printf("%li-size of final\n",sizeof(final));

        }

    }
    fclose(file);

}