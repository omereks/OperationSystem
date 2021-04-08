// Omer Eckstein 312350192

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//struct of command
struct CommandStruct {
    char Name[100];
    char jobFullName[100];
    int DoneOrRunnig;
    int InBackground;
    pid_t PidOfChild;
};

//exit built in
void exitWin(){
    exit(0);
}

// gets the first word in the input
char * firstWord(char* str){
    char delimiter[] = " ";
    char * context;
    int inputLength = strlen(str);
    char *cpInput = (char*) calloc(inputLength + 1, sizeof(char));
    strncpy(cpInput, str, inputLength);
    char * firstWord = strtok_r (cpInput, delimiter, &context);
    return firstWord;
}

// gets the last word in the input
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

// job build in
void jobs(struct CommandStruct commands[100], int sizeCommands){
    int i =0;
    while (i <= sizeCommands)
    {
        if ((commands[i].DoneOrRunnig == 0) && ((commands[i].InBackground == 1)))
        {
            printf("%s\n", commands[i].jobFullName);
        }
        i++;
    }
    commands[sizeCommands].DoneOrRunnig = 1;
}

// history build in
void history(struct CommandStruct commands[100], int sizeCommands){
    int i = 0;
    while (i <= sizeCommands)
    {
        printf("%s ", commands[i].jobFullName);
        // or done or last one (currnt job)
        if ((commands[i].DoneOrRunnig == 0) && ((waitpid(commands[i].PidOfChild, NULL, WNOHANG) == 0) || (i == sizeCommands)))
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
        if(str[i] == '\"'){
            i++;
            continue;
        }
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

// other jobs in execv
void builtIn(struct CommandStruct commands, char * str){
    char words[100][100];
    splitString(str ,words);
    int i = 0;
    int j =0;
    char * exep[100]; 

    // build the char[] for the execvp
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
    //run the execvp
    if(execvp(exep[0], exep) == -1){
        printf("exec failed\n");
        exitWin();
    }
}

//split to tokens for cd
int getTokens(char **currentJob, char *input) {
    char *token;
    char cpInput[100];
    strcpy(cpInput, input);
    int size, i = 0;
    token = strtok(cpInput, " ");
    currentJob[0] = token;

    token = strtok(input, " ");
    
    while (token != NULL)
    {
        currentJob[i] = token;
        token = strtok(NULL, " ");
        size = i;
        i++;
    }
   
    
    return size;
}


// check dor cases in cd - help for cd
void cdHelp(char *path, char prevPath[100]) {
    char curPath[100];
    if (strcmp(path, "-") == 0) { // only -
        strcpy(path, prevPath);
        return;
    }
    if (strstr(path, "~")) { // contain ~
        if (strlen(path) == 1) { // only ~
            strcpy(path, getenv("HOME"));
            return;
        } 
        if (getcwd(curPath, sizeof(curPath)) == NULL) {
            printf("An error occurred\n");
            return;
        }
        strcpy(curPath, getenv("HOME"));
        strcat(curPath, ++path);
        strcpy(--path, curPath);
        return;
    }
}

//build in cd
void cd(char *path, int size, char prevPath[100]) {
    char curPath[100];
    if (getcwd(curPath, sizeof(curPath)) == NULL) {
        printf("An error occurred\n");
        return;
    } 
    if(size == 0) { //only cd
        if (chdir(getenv("HOME")) < 0) {
            printf("chdir failed\n");
        } else {
            strcpy(prevPath, curPath);
        }
        return;
    }
    if (size > 1) {// more then alowed args
        printf("Too many arguments\n");
        return;
    } 

    // ok
    cdHelp(path, prevPath);
    if ((chdir(path)) < 0) {
        printf("chdir failed\n");
    } else {
        strcpy(prevPath, curPath);
    }
    
}



int main(){

    struct CommandStruct  commands[100];
    int curCommand = 0;
    char commandInput[100];
    char prevPath[100];

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
            //cd(char *path, int size, char prevPath[100])
            char *currentJob[100];
            int size = getTokens(currentJob, commandInput);
            cd(currentJob[1], size, prevPath);

            //strcpy(prevPath, cd(commands[curCommand], prevPath));
        }
        else if (strcmp(commands[curCommand].Name, "exit") == 0)
        {
            exitWin();
        }
        else // execv 
        {
            pid_t pid;
            if ((pid = fork()) < 0)
            {
                printf("fork failed\n");
            }
             
            commands[curCommand].PidOfChild = pid;
            if (pid == 0)
            {
                builtIn(commands[curCommand], commandInput);
            }
            if (!commands[curCommand].InBackground)
            {
                waitpid(pid, NULL , 0);
                commands[curCommand].DoneOrRunnig = 1;
            } 
        }

        curCommand++;
    }
}