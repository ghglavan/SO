# SO

Here are some of the projects that helped me understand linux pipes, IPCs and files structure.

### Directory traversal

![dir img](dir.png)

Dirtrav is a copy of the [tree]("https://linux.die.net/man/1/tree") call. It prints out the contents of the directory given as argument and (recursively) subdirectories as shown in the iamge above.


### Pipe Graph


Pipegraph is used as ``` ./pipegraph com1 arg1 ... argn ... comn arg1 ... argn ``` 
  As shown in the scheme below, pipegraph has a main process that take input from the stdin, create some pipes
  


               /---> tubi1 ---> com1 ---\
             /                            \
     input    ........................    ---> tubo ---> output         
             \                            /
	             \---> tubin ---> comn ---/            




