# BasicUnixLinuxShell
Implemented a simple shell that handles internal commands like ‘cd’, ‘echo’, ‘history’, ‘pwd’ and ‘exit’ directly as well as some of their flags and external commands like ‘ls’, ‘cat’, ‘date’, ‘rm’ and ‘mkdir’ and some of their flags through individual programs by creating a new process, using the fork() and execl() family of system calls to run the individual program along with error handling through C code and Operating Systems concepts.

------------------------------------------------------------------------------------------------------
Brief Details of Files :
------------------------------------------------------------------------------------------------------
1. shell.c 			- Main file containing the code for each of the commands
2. mydate.c 		- File called by parent process for executing the date command
3. myrm.c 			- File called by parent process for executing the rm command
4. mycat.c 			- File called by parent process for executing the cat command
5. myls.c 			- File called by parent process for executing the ls command
6. mymkdir.c 		- File called by parent process for executing the mkdir command
7. Makefile 		- Makefile for compiling all separate c files above commands to binary or object files
8. pwdhelp.txt 		- File containing data for the the help command line option of the pwd command
9. cdhelp.tx 		- File containing data for the the help command line option of the cd command
10. myhistory.txt 	- File containing the history list across all sessions/runs of the shell
11. Documentation.txt - This file



------------------------------------------------------------------------------------------------------
Description of basic Linux/Unix shell implemented:
------------------------------------------------------------------------------------------------------
BRIEF CODE EXPLANATION
------------------------------------------------------------------------------------------------------
We have three global variables. 
The exstat variable refers to the exit status of the program and is printed before termination of program. 
The temppath variable is a character array used throughout the program for ease of implementation. 
The macro mypath contains the directory where all the above files are stored followed by a forward slash charecter. This must be changed before compiling/execution of the shell program so that all files in the same directory can be located by our shell. 
The program execution starts with the main block of the shell.c file. Here, we first take an input using the readline function in the reader function this is returned to the main block. We also store the input in our history file here itself.
Main then calls the parser function which splits the input string into tokens using space as a delimeter and returns these tokens in a string array form to the main fucntion.
The docommand function is called next which goes on to execute the commands for each of the valid 10 commands through their separate function.
In the end, the exit status is printed and the shell is terminated.
All the functions for separate commands have the name 'do<command name' and return an integer value to be given to the exit status.
For the internal commands, the functions have all the code which causes the command to execute properly. 
However, for the external commands, the functions contain a system call fork() in which the child process uses execvp/execlp to call the compiled binary files for execution of commands. 



------------------------------------------------------------------------------------------------------
RUNNING THE SHELL
------------------------------------------------------------------------------------------------------
For running the shell, one must do the following in this given order:
1. Save all files in the same directory
2. Change the mypath macro at the top of the program to this directory followed by '/'
3. Run the makefile on the terminal using the make command for compilation of all files
4. Run the shell using this command: ./shell.exe
5. Enter valid commands and see their execution
6. For exiting the shell, use the exit command which may be followed by an integer for specifying exit status which otherwise takes the last command's status



------------------------------------------------------------------------------------------------------
COMMANDS EXPLANATION
------------------------------------------------------------------------------------------------------
A total of 10 commands (5 internal and 5 external) have been implemented in the shell. Their detailed descriptions are below:



------------------------------------------------------------------------------------------------------
1. EXIT
------------------------------------------------------------------------------------------------------
The exit [n] command terminates the program. It is an internal command handled by the doexit() function in my shell program. The function returns the exit status as defined below.

DESCRIPTION AND OPTIONS
It has an optional parameter [n] which is an integer between 0 to 255 and can be specified for desired exit status for termination of a run of the shell. 
If the user chooses not to specify the argument then the exit status of the previous command is automatically assigned. 
In cases of successful termination, the exit status is 0 while for other cases it takes values from 1 to 255. The exit status is printed on the console before each termination of the shell.

USE
For terminating the shell, you can use this command with or without the integer argument. Kindly make sure the exit is in all lowercase letters. Specify argument like 'exit 2' (without quotes) for an exit status of 2.

ERROR HANDLING
1. If the optional argument entered is NULL, the exit status is that of the previous command or 0 and the shell terminates.
2. If the optional argument entered is not an integer, the shell does not terminate but prints an error message and the user can again choose to enter the exit command with a valid argument or no argument. 
3. If the optional argument entered is an integer but not in the range of 0 to 255, the shell does not terminate but prints an error message and the user can again choose to enter the exit command with a valid argument or no argument. 



------------------------------------------------------------------------------------------------------
2. PWD
------------------------------------------------------------------------------------------------------
The pwd command prints the name of the current working directory. It is an internal command handled by the dopwd() function in my shell program. The dopwd() function returns 1 on succesful execution and otherwise if an error occurs, it returns the error number errno is set to.

DESCRIPTION AND OPTIONS
The pwd command prints the name of the directory you are presently in to the console. On starting the shell, the pwd command will print the directory where the shell.c file is in since you will run the file from that directory itself. 
By default, the pwd command without any argument, prints the name of the directory you are in. This behaviour is more or less mimicked by the -L flag of pwd and pwd and pwd -L both behave the same way. 
Another option for pwd is the --help. It prints helpful data on the console for use of the pwd command. 

USE
You can use this command to get the name of the current working directory. Make sure the command pwd is in all lowercase while the flag -L is an uppercase L. The help for the other option should also be in all lowercase. You can write the command like 'pwd -L' (without the quotes). 

ERROR HANDLING
1. If the current directory is unreadable, an error message is printed and the function returns the error number errno is set to but then the shell continues normal execution.
2. If the data for help stored in file pwdhelp.txt can not be read or the file can not be opened in read mode (it doesn't exist etc.) an error message is printed and the function returns the error number errno is set to but then the shell continues normal execution.
3. If an invalid option is entered for the pwd command, an error message is printed followed by returning 1 from the function and the shell continues execution.




------------------------------------------------------------------------------------------------------
3. CD
------------------------------------------------------------------------------------------------------
The cd command changes the current working directory to the directory specified as an argument. I no directory is specifies, it goes back to the root directory represented by '/'. It is an internal command handled by the docd() function in my shell program. It returns 1 on successful execution and otherwise if an error occurs, it returns the error number errno is set to.

DESCRIPTION AND OPTIONS
The cd command can be used with or without specifying a directory. If no directory is specified, it assumes the root directory. If a valid directory (one below the current one in the directory tree) is given it changes current working directory to that otherwise it throws an error. 
It has the '-L' option which behaves same as the default cd command. It also has the --help option which prints helpful data on the console for use of the cd command. 

USE
You can use this command to change the current working directory. Make sure the command cd is in all lowercase while the flag -L is an uppercase L. The help for the other option should also be in all lowercase. You can write the command like 'cd -L' or 'cd -L mydirectory' or 'cd -L dir1/dir2' (without the quotes). You can also change the directory to one with a space in the name, it can be done by using the backward slash '\' instead of the space in the name. For example a valid input is, 'cd my\dir' (without quotes) which will change the directory to 'my dir' if it exists.

ERROR HANDLING
1. If the directory specified is unreadable or does not exist, an error message is printed and the function returns the error number errno is set to but then the shell continues normal execution.
2. If the data for help stored in file cdhelp.txt can not be read or the file can not be opened in read mode (it doesn't exist etc.) an error message is printed and the function returns the error number errno is set to but then the shell continues normal execution.
3. If an invalid option is entered for the cd command, an error message is printed followed by returning 1 from the function and the shell continues execution.



------------------------------------------------------------------------------------------------------
4. HISTORY
------------------------------------------------------------------------------------------------------
The history command prints the numbered previous commands entered in the shell across all sessions. This data is stored in the history file and printed from there. It is an internal command handled by the dohistory() function in my shell program. The dohistory() function returns 1 on succesful execution and otherwise if an error occurs, it returns the error number errno is set to. The history is written to the file the moment any command is given on the shell whether valid or not.

DESCRIPTION AND OPTIONS
The history command prints the previous commands entered in the shell using a history file to the console. It shows a numbered list of all these commands on the console.
An option for the history command is -c which clears all the contents of the history file. The next time you show the history using the history command only the commands entered after the 'history -c' are printed. 
Another option is the -d offset. It deletes the specific history entry with the given offset from the file and renumbers the rest of the entries in the file to get a continuous numbering. Once deleted, there is no way to retrieve this history entry. 
Another option is the '!!' which prints the last command entered on the shell. One can then copy paste this command to use in the next command.

USE
If only 'history' is written in all lowercase it is a valid command which prints all the numbered history entries of previous shell commands. If 'history -c' is given as a command, all the contents in the history file are cleared. If one gives 'history -d offset' where offset if a valid number which has a corresponding entry in the history file, that line is deleted from the history file and can not be retrieved. If 'history !!' is the given command, the last command preceded by history is printed on the console.

ERROR HANDLING
1. The user should always enter a valid offset in the -d option. If not so, it is not recognised as a valid command and an error message followed by returning 1 from the function occurs. The shell execution continues as normal after this.
2. If the data for history stored in file myhistory.txt can not be read/write or the file can not be opened in read/write mode (it doesn't exist etc.) an error message is printed and the function returns the error number errno is set to but then the shell continues normal execution.



------------------------------------------------------------------------------------------------------
5. ECHO
------------------------------------------------------------------------------------------------------
The echo command displays a line of text entered on the shell after the echo command in the same line. It is an internal command handled by the doecho() function in my shell program. The doecho() function returns 1 on succesful execution.

DESCRIPTION AND OPTIONS
The echo command displays a line of text entered on the shell after the echo command in the same line. If the text specified does not contain any double quotes it is displayed as it is. However if it does contain double quotes, they are omitted. 
It has the -n option which omits the newline after displaying the line of text.
If using the '-E' command line option, the backslash character '\' is ommitted if the text does not contain any quotes but if it does, the text is displayed as it is without any change but only removing the quotes.

USE
The echo command must be written in all lowercase. You can use this command to display a line of text written after the echo command on the shell. If the command given is 'echo -n text' (without the quotes) the text will be printed but the cursor will not move to the next line. 
If the user inputs a text containing a word starting and/or ending with double quotes the double quotes are omitted. However, if you want to have double quotes in your text you can write double quotes twice like 'echo ""hi""' will print "hi". 
If the user does not give any text after the echo command, simply a newline is entered. 

ERROR HANDLING
Some errors are handled in echo command as specified above. No error messages are printed.



------------------------------------------------------------------------------------------------------
6. LS
------------------------------------------------------------------------------------------------------
The ls command lists directory contents on the console. It is an exernal command handled by the myls.c file called by the dols() function in my shell program. It returns either 1 on successful execution or the error number errno is set to in case of an error.

DESCRIPTION AND OPTIONS
The ls command lists information about the FILEs in specified directory (the current directory by default if no directory is specified).It does not sort them in any specific order and lists them in the order they are arranged in in the system. This can also be done for multiple directories with a single command if the directories are separated by spaces.
It has -a option which unhides the directories or files starting with . and lists them too. If no directory is specified it does so for current directory otherwise for the one which is specified. Similarly, the -m option lists these directories separated by a comma. 
This command ends with printing the exit status of the child process.

USE
The ls command must be written in all lowercase. You can use this command to list directory contents. If the command given is 'ls -a' (without the quotes) the names of all files and directories in current directory are printed. Otherwise for 'ls -m mydirectory1 mydirectory2 ', all contents of mydirectory1 and mydirectory2 are printed separately separated by commas.

ERROR HANDLING
1. If the fork system call used for handling this external command fails, an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
2. If the execvp system call used for executing the external command file in the child process fails then an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
3. If the directory specified or current directory is unreadable or cannot be opened, then an error message is printed followed by returning the error number set to by errno which is received from the child process which exits with exit status as errno. The shell then continues normal execution.



------------------------------------------------------------------------------------------------------
7. MKDIR
------------------------------------------------------------------------------------------------------
The mkdir command creates a directory of specified name in specified directory (the current directory by default if no directory is specified) if it does not already exists. It is an exernal command handled by the mymkdir.c file called by the domkdir() function in my shell program. It returns either 1 on successful execution or the error number errno is set to in case of an error.

DESCRIPTION AND OPTIONS
The mkdir command creates a directory of specified name in specified directory (the current directory by default if no directory is specified) if it does not already exists. 
It has -v option which prints a message for each created directory. 
The -p option creates parent directories if they do not already exist. 
This command ends with printing the exit status of the child process.

USE
The mkdir command must be written in all lowercase. You can use this command to create a directory with given name. Multiple directories can also be created with a single command if their names are specified separated by space. For creating a directory with a space in its name, the space must be replaced by backward slash '\' when giving the name as parameter to mkdir command. The spaced names do not work for -p however.
If the command given is 'mkdir -v' (without the quotes) a message for the created directory is printed. For 'mkdir -p d1/d2/d3', all directories are made d1 in current directory, d2 in d1 and d3 in d2.

ERROR HANDLING
1. If the fork system call used for handling this external command fails, an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
2. If the execvp system call used for executing the external command file in the child process fails then an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
3. If the directory specified or current directory is unreadable or cannot be opened or created, then an error message is printed followed by returning the error number set to by errno which is received from the child process which exits with exit status as errno. The shell then continues normal execution.



------------------------------------------------------------------------------------------------------
8. CAT
------------------------------------------------------------------------------------------------------
The cat command prints the contents of given file on the console and can also create a file while allowing user to write one line in it. It is an exernal command handled by the mycat.c file called by the docat() function in my shell program. It returns either 1 on successful execution or the error number errno is set to in case of an error.

DESCRIPTION AND OPTIONS
The cat command prints the contents of given file on the console and can also create a file while allowing user to write one line in it in current directory. This can also be done for multiple directories with a single command if the directories are separated by spaces.
It has -n option which prints the contents of the file specified after reading them line by line and numbering all these lines while printing. 
The -b command makes is similar to the -n command in that it numbers the lines but it also ensures that empty lines are not numbered.
For creating a file use the > character before the name of a file.
This command ends with printing the exit status of the child process.

USE
The cat command must be written in all lowercase. You can use this command to read contents of a file or create a new file.
You can create a new file using the > character before the name of the file.
If the command given is 'cat -n myfile1.txt myfile2.txt'(without the quotes) the numbered lines of all files in these files are printed. Similarly for -b. 
For 'cat >myfile.txt', a new file is created followed by a prompt to get content to write in the file, in one line. These contents must be written without a newline character since only the text before a newline character will be written to the file.

ERROR HANDLING
1. If the fork system call used for handling this external command fails, an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
2. If the execvp system call used for executing the external command file in the child process fails then an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
3. If the directory specified or current directory is unreadable or cannot be opened, then an error message is printed followed by returning the error number set to by errno which is received from the child process which exits with exit status as errno. The shell then continues normal execution.
4. If the file specified can not be read/written to or the file can not be opened in read/write mode an error message is printed and the child process exits by returns the error number errno is set to as exit status but then the shell continues normal execution.



------------------------------------------------------------------------------------------------------
9. RM
------------------------------------------------------------------------------------------------------
The rm command removes each specified directory. It is an exernal command handled by the myrm.c file called by the dorm() function in my shell program. It returns either 1 on successful execution or the error number errno is set to in case of an error.

DESCRIPTION AND OPTIONS
The rm command removes each specified file and also empty directories if given. This can also be done for multiple directories with a single command if the directories are separated by spaces. The rm command can take arguments as names of empty directories which have spaces in the name but the spaces must be replaced by backslash character '\'.
It has -v option which pritnts a message about each removed file. 
Another option is the -i option which prompts the user for a response to the question whether they want the given file to be deleted. If the user enter y or Y the file is removed otherwise it is not deleted.
This command ends with printing the exit status of the child process.

USE
The rm command must be written in all lowercase. You can use this command to remove files or even empty directories. If the command given is 'rm myfile1.txt' (without the quotes) the text file named myfile1 will be deleted if it exists. 

ERROR HANDLING
1. If the fork system call used for handling this external command fails, an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
2. If the execvp system call used for executing the external command file in the child process fails then an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
3. If the directory specified or current directory is unreadable or cannot be opened, then an error message is printed followed by returning the error number set to by errno which is received from the child process which exits with exit status as errno. The shell then continues normal execution.
4. If the file specified can not be read/written to or the file can not be opened in read/write mode an error message is printed and the child process exits by returns the error number errno is set to as exit status but then the shell continues normal execution.
5. If the file to be removed cannot be opened/found, error messages are printed followed by returning the error number set to by errno. The shell then continues normal execution.



------------------------------------------------------------------------------------------------------
10. DATE
------------------------------------------------------------------------------------------------------
The date command prints the system date or time. It can also print the last modification time of the file specified. It is an exernal command handled by the mydate.c file called by the dodate() function in my shell program. It returns either 1 on successful execution or the error number errno is set to in case of an error.

DESCRIPTION AND OPTIONS
The date command prints the system date or time.
It has -r option which prints the last modified time for a file specified in the current directory by deafult. 
The -u option prints the Coordinated Universal Time (UTC). 
This command ends with printing the exit status of the child process.

USE
The date command must be written in all lowercase. You can write a command like 'date'(without quotes) to get the system time and date. You can do 'date -u' for getting the Coordinated Universal Time (UTC). FOr getting the latest modification time of a file you can use the 'date -r filename.txt' command. 

ERROR HANDLING
1. If the fork system call used for handling this external command fails, an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
2. If the execvp system call used for executing the external command file in the child process fails then an error message is printed followed by returning the error number set to by errno. The shell then continues normal execution.
3. If the directory specified or current directory is unreadable or cannot be opened, then an error message is printed followed by returning the error number set to by errno which is received from the child process which exits with exit status as errno. The shell then continues normal execution.
4. If the strftime function used for getting the dates fails then appropriate error messages are printed and the child process exits with the errno as exit status. The shell then continues execution.



------------------------------------------------------------------------------------------------------
GENERAL ASSUMPTIONS
------------------------------------------------------------------------------------------------------
1. Only 1 space in the name of a directory is allowed. Other special characters like parentheses, underscore, hyphen are allowed as it is. For using the name of directory with a space you must alsways use a backward slash '\' instead of the space in the name. This can be used with the mkdir, rm and cd commands.
2. The rm command can also remove empty directories along with files which is the normal function of rm.
3. File names to be created using cat command can not haves spaces but other special characters like underscore are allowed.
4. All commands should be written in all lowercase characters. 
5. For names of files and directories, the shell is case-sensitive.
6. Only one command line option is given at a time for all commands.
7. It is assumed that the user will give valid inputs for all external commands as often as posiible in other cases appropriate error messages will be printed.
8. Multiple arguments separated by space can also be entered for the rm, mkdir, cat and ls commands.



------------------------------------------------------------------------------------------------------
TEST CASES
------------------------------------------------------------------------------------------------------
Refer Documentation.txt for sample test case and instructions to run the test case.
