// Omer Eckstein 312350192

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct CommandStruct {
    char Name[100];
    //char jobFullName[100];
    int DoneOrRunnig;
    int InBackground;
    pid_t PidOfChild;
};

void exitWin(){
    exit(0);
}


char * firstWord(char* str){
    char delimiter[] = " ";
    char * context;
    int inputLength = strlen(str);
    char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
    strncpy(inputCopy, str, inputLength);
    char * firstWord = strtok_r (inputCopy, delimiter, &context);
    return firstWord;

}

char * lastWord(char* str){
    char *word = strrchr(str, ' ');    
    //check if it no null  - have only one word
    if (!word)
    {
        return str;
    }
    word++;
    return word;
}

void jobs(struct CommandStruct commands[100], int sizeCommands){
    for (int i = 0; i < sizeCommands ; i++)
    {
        if ((commands[i].DoneOrRunnig == 0) && ((commands[i].InBackground == 1)))
        {
            printf("%s\n", commands[i].Name);
            fflush(stdout);
        }
    }
}

int main(){

    struct CommandStruct  commands[100];
    int curCommand = 0;
    char commandInput[100];

    while (1)
    {
        
        printf("$ ");
        fflush(stdout);
        
        //input command from user
        scanf(" %[^\n]s", commandInput);

        //build the current Command 
        //name
        strcpy(commands[curCommand].Name , firstWord(commandInput));
        //status
        commands[curCommand].DoneOrRunnig = 0;
        //Background
        commands[curCommand].DoneOrRunnig = 0;
        if(strcmp("&", lastWord(commandInput)) == 0){
            commands[curCommand].InBackground = 1;
        } else {
            commands[curCommand].InBackground = 0;
        }


        if (strcmp(commands[curCommand].Name, "jobs") == 0)
        {
            jobs(commands, curCommand);
        }
        


        printf("%s\n", commands[curCommand].Name);
        printf("%d\n", commands[curCommand].DoneOrRunnig);
        printf("%d\n", commands[curCommand].InBackground);
        

        curCommand++;

    }
    
}