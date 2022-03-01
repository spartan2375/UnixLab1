/*Normal Shell Implementation
 * Xavier Swehla
 * CSCI3800 Unix Lab 1
 */
#include "apue.h"
#include <sys/wait.h>

static void sig_int(int); /* our signal-catching function */

int main(void)
{
	char buf[MAXLINE]; /* from apue.h */
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal error");

	printf("%% "); /* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0)
		{
			err_sys("fork error");
		}
		else if (pid == 0)
		{ /* child */
			/*printf("'%s'\n", buf);*/
			char *cmd = strtok(buf, " ");
			char firstCmd[15];
			memset(firstCmd, '\0', 15);
			memcpy(firstCmd, cmd, strlen(cmd));
			char *argList[25];
			int i;
			for (i = 0; i < 25; ++i)
			{
				argList[i] = cmd;
				if (cmd == NULL)
					break;
				cmd = strtok(NULL, " ");
			}

			execvp(firstCmd, argList); /*(cmd, buf);*/
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

void sig_int(int signo)
{
	printf("interrupt\n%% ");
}
