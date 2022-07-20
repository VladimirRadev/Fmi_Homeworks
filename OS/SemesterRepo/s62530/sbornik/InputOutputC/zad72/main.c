// find ~ -printf '%T@ %p\n' | sort -n | head -n 1 | cut -d ' ' -f 2
#include <stdlib.h>
#include <err.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>

void safe_dup(int oldfd, int newfd) {
	if (dup2(oldfd, newfd) == -1) {
		err(1, "could not dup %d into %d", newfd, oldfd);
	}
}

pid_t pipe_child(char* const args[], int pipe_in[2], int pipe_out[2]) {
	pid_t child_pid = fork();
	if (child_pid == -1) {
		err(1, "could not fork");
	}

	if (child_pid == 0) {
		if (pipe_in != NULL) {
			close(pipe_in[1]);
			safe_dup(pipe_in[0], 0);
		}
		if (pipe_out != NULL) {
			close(pipe_out[0]);
			safe_dup(pipe_out[1], 1);
		}

		if (execvp(args[0], args) == -1) {
			err(1, "could not exec %s", args[0]);
		};
	}

	if (pipe_in != NULL) {
		close(pipe_in[0]);
	}
	if (pipe_out != NULL) {
		close(pipe_out[1]);
	}

	return child_pid;
}

int main (int arg, char* args[])
{
	if (arg != 2) {
		err(1, "expected 1 argument but got %d", arg - 2);
	}

	int pops[3][2];
	for (int i = 0; i < 3; i++) {
		if (pipe(pops[i]) == -1) {
			err(1, "could not create pipe %d", i);
		}
	}

	pid_t pids[4];

	char* const find_args[] = { "find", args[1], "-printf", "%T@ %p\\n", NULL };
	pids[0] = pipe_child(find_args, NULL, pops[0]);
	
	char* const sort_args[] = { "sort", "-n", NULL };
	pids[1] = pipe_child(sort_args, pops[0], pops[1]);

	char* const head_args[] = { "head", "-n", "1", NULL };
	pids[2] = pipe_child(head_args, pops[1], pops[2]);

	char* const cut_args[] = { "cut", "-d", " ", "-f", "2-", NULL };
	pids[3] = pipe_child(cut_args, pops[2], NULL);

	for (int i = 0; i < 4; i++) {
		int status;
		if (waitpid(pids[i], &status, 0) == -1) {
			err(1, "could not wait for process %d with pid %d", i, pids[i]);
		}
		if (WEXITSTATUS(status) != 0) {
			errx(1, "process %d failed", i);
		}
	}
	
	exit(0);
}
