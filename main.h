#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <signal.h>
void sighandler(int signal);
extern char **environ;
int non_interactive_mode(char **argv);
int interactive_mode(void);
size_t my_strlen(const char *str);
int s_shell(void);
char *getPathFromEnvironment(void);
char *shek_file(char *line);
void env(void);
void free_all(char **arg);
char **command_list(char *line, char *command);
char *S_f_S(char *line, char cH);
#endif
