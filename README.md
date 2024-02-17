In order to make it work you need to create infile.txt, compile program with make and after that execute a program
./pipex infile "shell command" "shell command" outfile
It will create outfile with result of you commands
Behavior of this like
infile "shellcommand | shellcommand" outfile
