#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// reading index = 0.0588 * L - 0.296 * S - 15.8

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    string text=get_string("Text : ");

    for( int i=0 , n = strlen(text) ; i < n ; i++ )
    {
        text[i]=tolower(text[i]);
    }

    int letters= count_letters(text);
    int words= count_words(text);
    int sentences= count_sentences(text);

    float L=letters*100/words;
    float S=sentences*100/words;

    float index=0.0588 * L - 0.296 * S - 15.8;

    printf("%d letters \n",letters);
    printf("%d words \n",words);
    printf("%d sentences \n",sentences);

    if (index >= 16)
    {
        printf("Grade 16+ \n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1 \n");
    }
    else
    {
        printf("Grade %d \n" , (int) round(index));
    }
}

int count_letters(string text)
{
    int letters=0;
    for(int i=0 , n=strlen(text) ; i < n ; i++ )
    {
        if ( islower(text[i]) )
        {
            letters+=1;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words=0;
    for(int i=0, n=strlen(text); i<n ; i++)
    {
        if (isspace(text[i]))
        {
            words+=1;
        }
    }
    words+=1;
    return words;
}
//(int) text[i]==33 || (int) text[i] == 46 || (int) text[i] == 63

int count_sentences(string text)
{
    int sentences=0;
    for(int i=0, n=strlen(text); i<n ; i++)
    {
        if ((int) text[i]==33 || (int) text[i] == 46 || (int) text[i] == 63)
        {
            sentences+=1;
        }
    }
    return sentences;
}