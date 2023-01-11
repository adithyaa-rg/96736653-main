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
            sprintf(write_file, "%d.jpg", i);
            printf("Hi\n");
            if (file_write!=NULL)
            {
                fclose(file_write);
            }
            file_write = fopen(write_file, "w");
            i+=1;
        }
        if(state==1)
        {
            *(final+size)=*buffer;
            size+=1;
            file_write = fopen(write_file, "w");

            final=realloc(final,512*sizeof(BYTE)*size);
            fwrite(final, 1 , BLOCK_SIZE, file_write);
            fclose(file_write);

            //printf("%d-size\n",size);
            printf("%li-size of final\n",sizeof(final));

        }

    }
    fclose(file);

}