#include "../../include/include.h"


int ft_exec(t_list *str)
{
    char *command;
    char *sub_command;
    char *saveptr;
    char *path;
    char *option;
    pid_t pid;
    int pipefd[2];
    int last_pipefd[2];

    path = split_cmd_file(); // ici je recup bien le bon path
    printf("path == %s\n", path);
    // faire attention, si je vire le path de l env pdt l'exec, prochaine exec cest ici que le path vaut null et return rien mais a ameliorer
	// if (path == NULL)
    //     return (0);
    // ft_unset();
	ft_env(NULL);
	ft_pwd();
    if (str != NULL) {
        command = str->content;
		if (strcmp(command, "exit") == 0)
		{
			ft_exit(ft_atoi(sub_command));
		}
		if (strcmp(command, "unset") == 0)
			ft_unset(str->next->content);
        // //printf("Commande : %s\n", command);
        // if (strcmp(command, "exit") == 0) {
        //     printf("Bye\n");
        //     exit(0);
        // }
        if (str->next != NULL)
            option = str->next->content;
        else
            option = NULL;
        sub_command = strtok_r(command, " ", &saveptr);
        //printf("sub_command == %s\n", sub_command);
        while (sub_command != NULL) {
            if (pipe(pipefd) == -1) {
                perror("Erreur pipe");
                exit(1);
            }
            pid = fork();
            if (pid == -1) {
                perror("Erreur fork");
                exit(1);
            }
            if (pid == 0) {
                // Nous sommes dans le processus enfant
                if (last_pipefd[0] != 0) {
                    dup2(last_pipefd[0], 0);
                    close(last_pipefd[0]);
                }
                close(pipefd[0]);
                close(pipefd[1]);
                char *args[] = {path, option, NULL};
                printf("path == %s\n", path);
                printf("option == %s\n", option);
                printf("la sub_command == %s\n", sub_command);
                execve(args[0], args, NULL);
               
                perror("Erreur execvp");
                 } else {
                // Nous sommes dans le processus parent
                if (last_pipefd[0] != 0) {
                    close(last_pipefd[0]);
                }
                last_pipefd[0] = pipefd[0];
                close(pipefd[1]);
            }
            sub_command = strtok_r(NULL, "|", &saveptr);
        }
        if (last_pipefd[0] != 0) {
            close(last_pipefd[0]);
        }
        //printf("La commande a été exécutée avec succès\n");
        //free(command);
        //pourattendre le procesessus fils
        while(wait(NULL) != -1);
    }
    return 0;
}
