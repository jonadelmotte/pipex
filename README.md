*This project has been created as part of the 42 curriculum by jdelmott*

# PIPEX
<br />

## Description

creat a program that behave exactly like the following shell command : <br />
&emsp; `< file1 cmd1 | cmd2 > file2`

### " < " symbol:

&emsp; The `<` symbol is an "input redirection" symbol. <br />
&emsp; In the `< file1 cmd1` shell command, `file1` becomes the new STDIN.  
&emsp; `cmd1` is not applied on the standart input anymore but on the content of `file1`.

### " > " symbol:

&emsp; The `>` symbol is an "output redirection" symbole. <br />
&emsp; In the `cmd2 > file2` shell command, `fil2` becomes the new STDOUT. <br />
&emsp; The result of `cmd2` is not stocked in the standart output anymore but in  the content of `file2`

### " | " symbol:

&emsp; the `|` (pipe) symbol redirects the output of the command on the left to the input of the command on the right. <br />
&emsp; In the `< file1 cmd1 | cmd2 > file2` shell command, the output of `< file1 cmd1` <br />
&emsp; will be the new input of `cmd2 > file2`.  
<br />

## Instruction

first use the command `make` to creat the `pipex` executable.  
then use:  
&emsp; `./pipex file1 cmd1 cmd2 file2`  
replacing `file1` and `file2` with files.  
and replacing `cmd1` and `cmd2` with shell commands.
<br />

## Bonus

### Description

there are tow part to the bonus of pipex.  
- First the programe must be able to handle multiple pipes : <br />
&emsp; `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2` <br />
in my program :<br />
&emsp; `./pipex_bonus file1 cmd1 cmd2 cmd3 ... cmdn file2`  
<br />
- the second part is a little more tricky.  <br />
we must recreate the behaviour of this shell command : <br />
&emsp; `cmd << LIMITER | cmd1 >> file <br />

### " << " symbol:

&emsp; The `<<` symbol is known as a `here-document` structure. <br />
&emsp; In the `<< LIM cmd` shell command, the terminal will open. <br />
&emsp; What you write will be registered until you write `LIM` <br />
&emsp; This information will be the new input of the `cmd` shell command <br />

### " >> " symbole:

&emsp; the `>>` symbole work the same way as the `>` symbole. <br />
&emsp; the sole difference is that the `>>` symbole will append the outpute <br />
&emsp; at the end of the document <br />

### Instruction

first use the command `make bonus` to creat the `pipex_bonus` executable <br />
then to replicate this shell command : <br />
&emsp; `cmd << LIMITER | cmd1 >> file` <br />
use this command : <br />
`./pipex_bonus here_doc LIMITER cmd cmd1 file` <br />

## Resources

##### doc :

- https://gitlab.com/madebypixel02/pipex <br />
- https://www.youtube.com/watch?v=Vax97MIL_uI&list=PLKUb7MEve0TjHQSKUWChAWyJPCpYMRovO&index=59 <br />
- https://stackoverflow.com/questions/24538470/what-does-dup2-do-in-c <br />
- https://www.ibm.com/docs/fr/aix/7.3.0?topic=w-wait-waitpid-wait3-wait364-wait4-subroutine <br />


##### tool :

- https://github.com/bastienkody/pipex_tester :
- https://github.com/michmos/42_pipex_tester :
