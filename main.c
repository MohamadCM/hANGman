//HangMan game
//2018 Mohamad Chaman-motlagh
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "drown.h"
#include "linklist.h"
#define max_n 50
#define max_number_of_topics 15
//This string keeps the chosen Topics name and address
char topic[100]="Topics\\";
//This function will read the available topics.txt inside Topics folder print them and ask user to choose a topic then completes the topic address
int topic_select()
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
    for(j=8;j<100;j++)
        if(topic[j]=='\n'||topic[j]=='\r')
            topic[j]='\0';
    return ((int)num)-97;
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
    printf("How many words do you want to add to this topics?\n");
    int num;
    scanf("%d",&num);
    int i;
    char str[num][50];
    for(i=0;i<num;i++)
        scanf("%s",str[i]);
    char tmp[50]="Topics\\";
    strcat(tmp,name);
    //strcat(tmp,".txt");//This line was wrong
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
    fflush(stdin);
    Sleep(1500);
    return 0;
}
struct person
{
    char name[max_n];
    float score[max_number_of_topics];
    float scoreSum;
};
int check_word(char word[],char alp)
{
    int i;
    for(i=0;i<strlen(word);i++)
        if(word[i]==alp)
            return 0;
    return -1;
}
int game_logic(char word[max_n])
{
    if(word==NULL)
        return -1;
    fflush(stdin);
    system("cls");
    int i;
    drown(0);
    printf("\nNow Guess the word!\n");
    //printf("\n%s\n",word);    //Active this for testing
    char guess_word[strlen(word)];
    for(i=0;i<strlen(word);i++)
            guess_word[i]='_';
    for(i=0;i<strlen(word);i++)
        printf("%c ",guess_word[i]);
    char alp[26]={'\0'};
    i=0;
    int cnt=0,j=0,k=0,flag=0;
    while(j<5)
    {
        fflush(stdin);
        flag=0;
        printf("\n");
        scanf("%c",&alp[cnt]);
        for(i=0;i<cnt;i++)
            if(alp[i]==alp[cnt])
                flag++;
        if(alp[cnt]=='Q')
            return -1;
        if(alp[cnt]<97||alp[cnt]>122||flag!=0)
        {
            printf("Unavailable Character,Try again\n");
            //Sleep(1500);
            continue;
        }
        for(i=0;i<strlen(word);i++)
            for(k=0;k<26;k++)
                if(word[i]==alp[k])
                    guess_word[i]=alp[k];
        system("cls");
        drown(j);
        printf("\n");
        if(j==4)
                printf("Be careful!This your last choice!\n");
        if(check_word(word,alp[cnt])==-1)
        {
            j++;
            system("cls");
            drown(j);
            printf("\nWrong choice;you have %d choices left\n",5-j);
            if(j==4)
                printf("Be carefull!This your last choice!\n");
        }
        for(i=0;i<strlen(word);i++){
            printf("%c ",guess_word[i]);
        }
        if(check_word(guess_word,'_')==-1)
            break;
        cnt++;
    }
    if(j==5)
    {
        printf("You lost this one,the word was ***%s***\n",word);
        //Sleep(2000);
        return 0;
    }
    else
    {
        printf("\nYou won this one\n");
        Sleep(2000);
        return 3*strlen(word)-j;
    }
}
float rand_select()
{
    FILE * input=fopen(topic,"r");
    struct node *list=NULL;
    int size=1;
    char word[max_n];
    fscanf(input,"%s",word);
    struct node* current=NULL;
    list=createNode(word);
    current=list;
    while(1)
    {
        fscanf(input,"%s",word);
        if(feof(input))
            break;
        current->next=createNode(word);
        current=current->next;
        size++;
    }
    int random;
    srand(time(NULL));
    current=list;
 //   printList(current); Test the linkedlist of words
    int i,tmp=0,score=0;
    fclose(input);
    //time_t t1=time(NULL);
    clock_t start, end;
    double cpu_time_used;

    start = clock();
   // printf("%s\n\n\n\n",word); Test last input words from file
    while(size!=0)
    {
        tmp=0;
        printf("\n\n");
        random=(rand()%size)+1;
        if(random==1){
            list=deleteFront(list);
            if((tmp=game_logic(list->data))==-1)
                break;//Exit function wont be over here
            score+=tmp;
        }
        else if(random==size){
            deletEnd(list);
            while(current->next!=NULL)
                current=current->next;
            if((tmp=game_logic(current->data))==-1)
                break;//Exit function wont over here
                score+=tmp;
            }
        else
        {
            for(i=1;i<random-1;i++)
                current=current->next;
            if((tmp=game_logic(current->next->data))==-1)
                break;//Exit function wont be over here
            score+=tmp;
            deleteNode(current);
        }
//        printList(list);
        size--;
        current=list;
        if(size)
            printf("\nnext word will be loaded soon\nRemaining word in this topic:%d\n",size);
        else
            printf("\nNo Word Left in this topics\n");
        Sleep(2500);
    }
    //time_t t2=time(NULL);
    //return ((float)score)/((int)((t2-t1)%60)+1);
    end = clock();
    return ((double) score)/((int)(((double) (end - start)) / CLOCKS_PER_SEC)%10);

}
void EXIT(struct person p)
{
    printf("You choose to exit the game\ndo you want save your stats?\na-yes:))\nb-no:((\n");
    char check;
    fflush(stdin);
    scanf("%c",&check);
    if(check=='b')
    {
        printf("Thank you for playing, We'll miss you!\n");
        exit(-1);
    }
    FILE *personHolder=fopen("Persons.bin","r+b");
    struct person tmp;
    while(1)
    {
        if(fread(&tmp,sizeof(struct person),1,personHolder)<1)
            break;
        if(strcmp(tmp.name,p.name)==0)
        {
            fseek(personHolder,1*sizeof(p),SEEK_CUR);
            fwrite(&p,sizeof(struct person),1,personHolder);
            printf("Saved....We wait for your return:))");
            exit(0);
        }
    }
    fwrite(&p,sizeof(struct person),1,personHolder);
    printf("Saved....We wait for your return:))");
    fclose(personHolder);
    exit(1);
}
void highScoreShow()
{
    FILE *personHolder=fopen("Persons.bin","rb");
    int i=1;
    struct person* p;
    p=(struct person*) malloc(sizeof(struct person));//used to create an array of users
    while(1)
    {
        if(fread(&p[i-1],sizeof(struct person),1,personHolder)<1)
            break;
        i++;
        p=(struct person*)realloc(p,sizeof(struct person)*i);
    }
    int size=i,j=0;//Sort
    for(i=0;i<size;i++)
        for(j=0;j<size-1;j++)
            if(p[j].scoreSum<p[j+1].scoreSum)
            {
                struct person tmp;
                tmp=p[j+1];
                p[j+1]=p[j];
                p[j]=tmp;
            }
    printf("List of high score gamers:\n");
    for(i=1;i<size&&i<10;i++)//print
        printf("%d-%8s\t%f\n",i,p[i].name,p[i].scoreSum);
    free(p);
    fclose(personHolder);
}
int main()
{

    printf("\t*****Welcome to hangman game*****\n");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\t  ***It's %d-%d-%d %d:%d:%d***\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);//Intro menu
    printf("Please enter your name:");
    char name[max_n];
    gets(name);
    int cnt;
    for(cnt=0;cnt<max_n;cnt++)
        if(name[cnt]=='\n'||name[cnt]=='\r')
            name[cnt]='\0';
    FILE *personHolder=fopen("Persons.bin","r+b");
    if(personHolder==NULL)
        return -1;
   int currentSocore=0,flag=0;//Check will be used to check availability of person in Persons.txt
//    char tempname[max_n];
    struct person tmp,checkPerson;
    while(1)
    {
        if(fread(&checkPerson,sizeof(struct person),1,personHolder)<1)
            break;
        for(cnt=0;cnt<max_n;cnt++)
            if(checkPerson.name[cnt]=='\n'||checkPerson.name[cnt]=='\r')
                checkPerson.name[cnt]=='\0';
        if(strcmpi(checkPerson.name,name)==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        int i=0;
        for(i=0;i<=strlen(name);i++)
            tmp.name[i]=name[i];
        for(i=0;i<max_number_of_topics;i++)
            tmp.score[i]=0;
        tmp.scoreSum=0;
       // fwrite(&tmp,sizeof(struct person),1,personHolder);//This line added to exit function
    }
    else
    {
        tmp=checkPerson;
    }
//    printf("%s\n\n%d\n",tmp.name,flag);   //Test struct and flag
    fflush(stdin);
    fclose(personHolder);
    while(1)
    {
    printf("What Do you want to do next?(remember you can exit any time by entering Q)\n");
    printf("a-Start a new game\nb-Show high score\n");
    if(flag)
        printf("c-resume game\n");
    char choose;
    scanf("%c",&choose);
    fflush(stdin);
    switch (choose)
        {
            int c,scoreindex;
            char endFlag;
            float s;
            case('a'):
                printf("Which one do you want?\n1-Choose one from available topics!\n2-Make a new topic!\n");
                scanf("%d",&c);
                fflush(stdin);
                if(c!=2){
                    if((scoreindex=topic_select())==-1)
                        EXIT(tmp);
                    if((s=rand_select())>=tmp.score[scoreindex])
                        tmp.score[scoreindex]=s;
                    tmp.scoreSum+=s;
                    printf("Topic ended\n");
                    printf("Your score in this topics is %f and you high score in this topic is %f\nDo you want to continue?!\na-Yes!!!\nb-no\n",s,tmp.score[scoreindex]);
                    Sleep(2000);
                    fflush(stdin);
                    scanf("%c",&endFlag);
                    if(endFlag=='b')
                        EXIT(tmp);
                    fflush(stdin);
                }
                else
                    if(topic_generator()==-1)
                        EXIT(tmp);

                //Game logic wont function will be added here
                break;
            case('b'):
                highScoreShow();
            //Show high score here
            break;
            case('c'):
                printf("Which one do you want?\n1-Choose one from available topics!\n2-Make a new topic\n");
                scanf("%d",&c);
                fflush(stdin);
                if(c==1){
                    if((scoreindex=topic_select())==-1)
                        EXIT(tmp);
                    if((s=rand_select())>=tmp.score[scoreindex])
                        tmp.score[scoreindex]=s;
                    tmp.scoreSum+=s;
                    printf("Your score in this topics is %f and you high score in this topic is %f\nDo you want to continue?!\na-Yes!!!\nb-no\n",s,tmp.score[scoreindex]);
                    scanf("%c",&endFlag);
                    if(endFlag=='b')
                        EXIT(tmp);
                    fflush(stdin);
                }
                else
                    topic_generator();
                //Game logic wont be here:)
                break;
            case('Q'):
                EXIT(tmp);
                break;
            default:
                printf("Wrong option, try again!\n");
                Sleep(1000);
                break;
        }
    }
    EXIT(tmp);//Exit function is here:))
    return 0;
}
