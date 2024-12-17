#include "minishell.h"

void test_exec() {
    t_execcmd cmd;

    cmd.type = EXEC;
    cmd.argv[0] = "/bin/ls";
    cmd.argv[1] = "-l";
    cmd.argv[2] = NULL;

    printf("Testing EXEC command:\n");
    execute((t_cmd *)&cmd);
}

void test_redir() {
    t_redircmd cmd;
    t_execcmd exec;

    // Comando da eseguire: "ls -l"
    exec.type = EXEC;
    exec.argv[0] = "/bin/ls";
    exec.argv[1] = "-l";
    exec.argv[2] = NULL;

    // Redirezione dell'output su "output.txt"
	cmd.type = REDIR;
	cmd.cmd = (t_cmd *)&exec;
	cmd.file = "output.txt";
	cmd.mode = O_WRONLY | O_CREAT;
	cmd.fd = 1;

    printf("Testing REDIR command (output to output.txt):\n");
    execute((t_cmd *)&cmd);

    printf("Check output.txt for the results.\n");
}

void test_pipe() {
    t_pipecmd pipe_cmd;
    t_execcmd left_cmd;
    t_execcmd right_cmd;

    // Comando sinistro: "echo Hello World"
    left_cmd.type = EXEC;
    left_cmd.argv[0] = "/bin/echo";
    left_cmd.argv[1] = "Hello World";
    left_cmd.argv[2] = NULL;

    // Comando destro: "wc -w"
    right_cmd.type = EXEC;
    right_cmd.argv[0] = "/usr/bin/wc";
    right_cmd.argv[1] = "-w";
    right_cmd.argv[2] = NULL;

    // Configura il comando PIPE
    pipe_cmd.type = PIPE;
    pipe_cmd.left = (t_cmd *)&left_cmd;
    pipe_cmd.right = (t_cmd *)&right_cmd;

    printf("Testing PIPE command:\n");
    execute((t_cmd *)&pipe_cmd);
}

void test_list() {
    t_listcmd list_cmd;
    t_execcmd left_cmd;
    t_execcmd right_cmd;

    // Primo comando: "echo First Command"
    left_cmd.type = EXEC;
    left_cmd.argv[0] = "/bin/echo";
    left_cmd.argv[1] = "First Command";
    left_cmd.argv[2] = NULL;

    // Secondo comando: "echo Second Command"
    right_cmd.type = EXEC;
    right_cmd.argv[0] = "/bin/echo";
    right_cmd.argv[1] = "Second Command";
    right_cmd.argv[2] = NULL;

    // Configura il comando LIST
    list_cmd.type = LIST;
    list_cmd.left = (t_cmd *)&left_cmd;
    list_cmd.right = (t_cmd *)&right_cmd;

    printf("Testing LIST command:\n");
    execute((t_cmd *)&list_cmd);
}

void test_back() {
    t_back_cmd back_cmd;
    t_execcmd exec;

    // Comando: "sleep 5"
    exec.type = EXEC;
    exec.argv[0] = "/bin/sleep";
    exec.argv[1] = "5";
    exec.argv[2] = NULL;

    // Configura il comando BACK
    back_cmd.type = BACK;
    back_cmd.cmd = (t_cmd *)&exec;

    printf("Testing BACK command:\n");
    execute((t_cmd *)&back_cmd);
    printf("Command running in background...\n");
}

void run_test(void (*test_func)(), char *test_name)
{
	pid_t pid;

	pid = fork();
	if (pid == 0) // Processo figlio
	{
		printf("\n--- Running %s ---\n", test_name);
		test_func();
		printf("--- Finished %s ---\n\n", test_name);
		exit(0);
	}
	else if (pid < 0) // Errore nel fork
	{
		perror("fork");
	}
	else // Processo padre
	{
		waitpid(pid, NULL, 0); // Aspetta che il figlio termini
	}
}

void run_tests(void)
{
	printf("\n### Starting All Tests ###\n");
	run_test(test_exec, "EXEC Test");
	run_test(test_redir, "REDIR Test");
	run_test(test_pipe, "PIPE Test");
	run_test(test_list, "LIST Test");
	run_test(test_back, "BACK Test");
	printf("### All Tests Completed ###\n");
}
