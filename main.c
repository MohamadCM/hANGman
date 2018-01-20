//HangMan game
//2018 Mohamad Chaman-motlagh
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "drown.h"
#include "linklist.h"
#define max_n 50
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
    for(j=0;j<(num-97);j++)
        fgets(str[j],50,input);
    strcat(topic,str[j]);
    for(j=0;j<50;j++)
        if(topic[j]=='\n')
            topic[j]='\0';
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
struct person
{
    char name[max_n];
    int score;
};

int main()
{

    printf("\t*****Welcome to hangman game*****\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t  ***It's %d-%d-%d %d:%d:%d***\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);//Intro menu
    printf("Please enter your name:");
    char name[max_n];
    scanf("%s",name);
    FILE *personHolder=fopen("Persons.txt","r+");
    if(personHolder==NULL)
        return -1;
    int currentSocore=0,check=0;//Check will be used to check availability of person in Persons.txt
    char tempname[max_n];
    while(1)
    {
        fscanf(personHolder,"%s %d",tempname,&currentSocore);
        if(strcmp(tempname,name)==0)
        {
            check++;
        }
        if(feof(personHolder))
            break;
    }
    struct person p;
    if(check==0)
    {
        int i=0;
        fprintf(personHolder,"\n%s\t%d",name,0);//This doesn't work properly?!!
    }
    fflush(stdin);
    while(1)
    {
    printf("What Do you want to do next?(remember you can exit any time by entering Q)\n");
    printf("a-Start a new game\nb-Show high score\n");
    if(check)
        printf("c-resume game\n");
    char choose;
    scanf("%c",&choose);
    fflush(stdin);
    switch (choose)
        {
            int c;
            case('a'):
                printf("Which one do you want?\n1-Choose one from available topics!\n2-Make a new topic!\n");
                scanf("%d",&c);
                if(c==1)
                    if(topic_read()==-1)
                        //Exit function will be here
                else
                    if(topic_generator()==-1)
                        //Exit function will be here
                //Game logic function will be added here
                break;
            case('b'):
            //Show high score here
            break;
            case('c'):
                printf("Which one do you want?\n1-Choose one from available topics!\n2-Make a new topic\n");
                scanf("%d",&c);
                if(c==1)
                    topic_read();
                else
                    topic_generator();
                //Game logic will be added here
                break;
            case('Q'):
                //Exit function will be here
                break;
        }
    }
    //Exit function will be here
    return 0;
}
