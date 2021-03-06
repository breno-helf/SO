#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <grp.h>

/*
  Maximum size for prompt
*/
const int MAX = 1123;

/* 
   Make prompt based on current directory
*/
void make_prompt(char * prompt_str) {
    prompt_str[0] = '[';
    getcwd(prompt_str + 1, MAX - 4);
    strcat(prompt_str, "]$ ");
}

/*
  Count the number of arguments in a command
*/
int args_num(char * str) {
    int number = 0, i;

    for (i = 0; str[i] != '\0'; i++) {
	if (str[i] != ' ' && (i == 0 || str[i - 1] == ' '))
	    number++;
    }
    return number;
}

/*
  Make the command based on the string. A command
  is a vector of strings (command + arguments).
*/
void make_command(char * str, char ** command) {
    int number = 0, i;

    for (i = 0; str[i] != '\0'; i++) {
	if (str[i] == ' ')
	    str[i] = '\0';
	else if (i == 0 || str[i - 1] == '\0')
	    command[number++] = str + i;

    }
    command[number] = NULL;
}

/*
  Change the owner group based on
  chown system command
*/
void change_owner_group(char *gr, char *file) {
    char * dir;

    dir = (char *) malloc(sizeof(char) * MAX);
   	    
    getcwd(dir, MAX - (strlen(file) + 2));
    strcat(dir, "/");
    strcat(dir, file);
    
    struct group * g = getgrnam(gr + 1);
    
    gid_t GroupID = g->gr_gid;
    
    if (chown(file, -1, GroupID) == -1)
	fprintf(stderr, "chown failed: %s\n", strerror(errno));
    free(dir);
}

/*
  Creates a child process that execute a
  command with execv.
*/
void execute_command(char * dir, char * args[]) { 
    pid_t pid;
    int status;
    if ((pid = fork()) == 0) {
	if (execv(dir, args) == -1)
	    fprintf(stderr, "%s failed: %s\n", dir, strerror(errno));
	
	status = 0;
	exit(0);
    } else {
	waitpid(pid, &status, 0);
    }
}

int main(int argc, char * argv[]) {
    char ** command;
    char * prompt;
    char * str;
    char loop = 1;
    
    prompt = (char *) malloc(sizeof(char) * MAX);

    while (loop) {
	make_prompt(prompt);
	str = readline(prompt);
	if (str == NULL || str[0] == '\n') {
	    str = (char *) malloc(sizeof(char) * 5);
	    strcpy(str, "exit");	    
	} else if (args_num(str) != 0) add_history(str);
	else continue;
	
	command = (char **) malloc(sizeof(char *) * (args_num(str) + 1));
	make_command(str, command);
	
	if (strcmp(command[0], "exit") == 0) {
	    loop = 0;
	} else if (strcmp(command[0], "chown") == 0) {
	    change_owner_group(command[1], command[2]);
	} else if (strcmp(command[0], "date") == 0) {
	    time_t * now = (time_t *) malloc(sizeof(time_t));
	    time(now);
	    printf("%s", ctime(now));
	} else if (strcmp(command[0], "/bin/ping") == 0) {
	    execute_command(command[0], command);	    
	} else if (strcmp(command[0], "/usr/bin/cal") == 0) {
	    execute_command(command[0], command);	    
	} else if (strcmp(command[0], "./ep1") == 0) {
	    execute_command(command[0], command);	    
	} else {
	    fprintf(stderr, "Command %s not supported\n", str);
	}
	
	free(str);
	free(command);
    }

    clear_history();
    free(prompt);
    
    return 0;
}
