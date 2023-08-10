#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

char *path_exists_pwd2(char *abs_path, char *path_value, char *command);
char *_getenviron(char *name_value, char *env_var, char **envp);
char *absolute_path(char **argv, char **envp);
char *path_exists(char *abs_path, char *path_value, char *command);
char **split_string(char **argv, char *getline_string);
int set_env(char **argv, char **envp);
int unset_env(char **argv, char **envp);
#endif
