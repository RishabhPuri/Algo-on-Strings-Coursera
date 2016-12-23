#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    unsigned char **child;
    unsigned int  N=0, i, j, k;

    unsigned int count = 0, maxCount = 0; 
    unsigned int *hd;

    child = calloc (3001, sizeof(char *));
    child[0] = calloc (3001, sizeof(char));
    scanf ("%s",child[0]);
    if (strlen(child[0])>3000)
    {   
        printf ("more length, exiting ... \n");
        return 0;
    }   
    scanf ("%u", &N);
    hd = calloc (N+1, sizeof(int)); 
    memset (hd,0,N+1);
    for (i=1; i<=N; i++)
    {   
        child[i] =  calloc (3001, sizeof(char));
        scanf ("%s", child[i]);
    }   

    for (j=0;j<=N;j++)
    {
        for (i=0;i<strlen(child[0]);i++)
        {
            if (child[0][i] != '*')
                hd[j]+=(child[j][i]-'a');
        }
    }
   
    unsigned int tempSumM = 0, tempSumC = 0; 
    for (i=0;i<strlen(child[0]);i++)
    {   
        if (child[0][i] == '*') continue;
        
        count = 0;

        for (j=0;j<=N;j++)    
        {
            //hd[j]-=(child[j][i]-'a');
            tempSumC = hd[j] - (child[j][i]-'a');

            if (j==0)
            {
                tempSumM = tempSumC;
                continue;
            }
                    
            if (tempSumC == tempSumM) count++;
            
            tempSumC = 0;
        }
          
        if (count > maxCount)
            maxCount = count;
    }

    printf ("%u", maxCount);
    return 0;
}

