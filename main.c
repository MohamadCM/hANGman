#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//This string keeps the chosen Topics name and address
char topic[100]="Topics\\";
//This function will read the available topics.txt inside Topics folder print them and ask user to choose a topic then completes the topic address
int topic_read()
{
    *topic="Topics\\";
    topic[0]='T';
    printf("Here are the available topics:");
    char str[100][50],c,num;
    int i=0,j=0,number_of_topics;
    FILE *input=fopen("Topics\\AVAILABLE_TOPICS.txt","r");
    while(1)
    {
        if(fgets(str[i],50,input)==0)
        break;
        printf("\n%c-",97+i);
        for(j=0;str[i][j]!='.'&&j<50;j++)
            printf("%c",str[i][j]);
        i++;
    }
    number_of_topics=i;
    printf("\nSelect a topic from available topics ***please type the topic's character:)***:");
    scanf("%c",&num);
    if(num=='Q')
        return -1;
    while(num>number_of_topics+97||num<97)
    {

        printf("Incorrect character:)please choose another character:");
        scanf("%c",&num);
    }
    for(j=0;j<(num-97)-1;j++)
        fgets(str[j],50,input);
    strcat(topic,str[j]);
    fclose(input);
    return 0;
}
//This function creates a new topic and fill it with user's chosen names
int topic_generator()
{
    fflush(stdin);
    char name[50];
    printf("Please enter the new topics name(Please use _ instead of space):");
    scanf("%s",name);
    if(strcmp(name,"Q")==0)
        return -1;
    FILE *input;
    input=fopen("Topics\\AVAILABLE_TOPICS.txt","a");
    fprintf(input,"\n");
    strcat(name,".txt");
    fputs(name,input);
    fclose(input);
    printf("How many names do you want to add to this topics?\n");
    int num;
    scanf("%d",&num);
    int i;
    char str[num][50];
    for(i=0;i<num;i++)
        scanf("%s",str[i]);
    char tmp[50]="Topics\\";
    strcat(tmp,name);
    strcat(tmp,".txt");
    FILE *out;
    out=fopen(tmp,"w");
    if(out==NULL)
        exit(-1);
    for(i=0;i<num;i++){
        fprintf(out,"%s",str[i]);
        if(i+1<num)
            fprintf(out,"\n");
    }
    fclose(out);
    return 0;
}
int main()
{
//    topic_read();
//    printf("%s",topic);
    return 0;
}
