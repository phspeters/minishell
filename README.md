<h1 align="center">
	🐚 minishell
</h1>

## 💡 About the project

This project is about creating a simple shell.
Yes, your own little bash.
You will learn a lot about processes and file descriptors.

## 📝 Requirements

**Mandatory part:**

• Display a prompt when waiting for a new command.

• Have a working history.

• Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).

• Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).

• Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.

• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).

• Implement redirections (< , > , << , >>)

• Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

• Handle environment variables ($ followed by a sequence of characters) which should expand to their values.

• Handle $? which should expand to the exit status of the most recently executed foreground pipeline.

• Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.

• Your shell must implement the following builtins:

◦ echo with option -n

◦ cd with only a relative or absolute path

◦ pwd with no options

◦ export with no options

◦ unset with no options

◦ env with no options or arguments

◦ exit with no options


**Bonus part:**

• && and || with parenthesis for priorities.

• Wildcards * should work for the current working directory.

## 📋 Testing

To compile, go to the project path and run:

```shell
$ make 
```

Then, execute the program.

```shell
$ ./minishell 
```
