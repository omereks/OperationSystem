// Omer Eckstein 312350192

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


struct CommandStruct {
    char Name[100];
    char jobFullName[100];
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
    int i =0;
    while (i <= sizeCommands)
    {
        if ((commands[i].DoneOrRunnig == 0) && ((commands[i].InBackground == 1)))
        {
            printf("%s\n", commands[i].Name);
        }
        i++;
    }
    commands[sizeCommands].DoneOrRunnig = 1;
}

void history(struct CommandStruct commands[100], int sizeCommands){
    int i = 0;
    while (i <= sizeCommands)
    {
        printf("%s ", commands[i].jobFullName);
        if (commands[i].DoneOrRunnig == 0)
        {
            printf("RUNNING\n");
        } else {
            printf("DONE\n");
        }
        i++;
    }
    
    commands[sizeCommands].DoneOrRunnig = 1;
}

void splitString(char * str, char  strRet[100][100]){
    int j=0; 
    int ctr=0;
    //char newString[100][100];
    int i =0;
    while (i<=(strlen(str)))
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str[i]==' '||str[i]=='\0')
        {
            strRet[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            strRet[ctr][j]=str[i];
            j++;
        }
        i++;
    }
}


void builtIn(struct CommandStruct commands, char * str){
    char words[100][100];
    splitString(str ,words);
    int i = 0;
    int j =0;
    char * exep[100]; 

    while (i<100)
    {
        if ((!(strcmp(words[i],"\0"))) || (words[i][0] == '&')){
            exep[i] = NULL;
            i=100;
        }
        else {
            exep[i] = words[j];
            j++;
        }
        i++;
    }
    
    if(execvp(exep[0], exep) == -1){
        printf("exec failed\n");
        exitWin();
    }
    i = 0;
    while (i<100)
    {
       exep[i] = NULL;
    }
}

void cd(struct CommandStruct commands){

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
        //Full Name
        strcpy(commands[curCommand].jobFullName,commandInput);
        if (commands[curCommand].InBackground)
        {
            commands[curCommand].jobFullName[strlen(commands[curCommand].jobFullName) - 2] = '\0';
        } 
        

        //jobs
        if (strcmp(commands[curCommand].Name, "jobs") == 0)
        {
            jobs(commands, curCommand);
        }
        //history
        else if (strcmp(commands[curCommand].Name, "history") == 0)
        {
            history(commands, curCommand);
        }
        //cd
        else if (strcmp(commands[curCommand].Name, "cd") == 0)
        {
            cd(commands[curCommand]);
        }
        else if (strcmp(commands[curCommand].Name, "exit") == 0)
        {
            exitWin();
        }
        else
        {
            pid_t pid = fork();
            commands[curCommand].PidOfChild = pid;
            if (pid == 0)
            {
                builtIn(commands[curCommand], commandInput);
            }
            if (!commands[curCommand].InBackground)
            {
                waitpid(pid, NULL , 0);
                commands[curCommand].DoneOrRunnig = 1;
            } else {
                pid_t pid2 = fork();
                if (pid2 == 0){
                    waitpid(commands[curCommand].PidOfChild, NULL , WNOHANG);
                    commands[curCommand].DoneOrRunnig = 1;
                    exitWin();
                }
            }
        }
        /**
        printf("%s\n", commands[curCommand].Name);
        printf("%d\n", commands[curCommand].DoneOrRunnig);
        printf("%d\n", commands[curCommand].InBackground);
        */

        curCommand++;

    }
    
}