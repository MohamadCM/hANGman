#include <stdio.h>
#include <stdlib.h>
void drown(int num)
{
        char str[100];
        FILE *input;
        if(num==0)
            input=fopen("drown S0.txt","r");
        if(num==1)
            input=fopen("drown S1.txt","r");
        if(num==2)
            input=fopen("drown S2.txt","r");
        if(num==3)
            input=fopen("drown S3.txt","r");
        if(num==4)
            input=fopen("drown S4.txt","r");
        if(num==5)
            input=fopen("drown S5.txt","r");
        while(1)
        {
            if(fgets(str,100,input)==0)
                break;
            printf("%s",str);
        }
        fclose(input);
}
