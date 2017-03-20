# SO

Here are some of the projects that helped me understand linux pipes, IPCs and files structure.

<h3>Directory traversal</h3>

<img src = "dir.png"/>

<p>Dirtrav is a copy of the <a href = "https://linux.die.net/man/1/tree">tree</a> call. It prints out the contents of the directory given as argument and (recursively) subdirectories as shown in the iamge above.</p>


<h3>Pipe Graph</h3>

<p>
Pipegraph is used as `./pipegraph com1 arg1 ... argn ... comn arg1 ... argn` 
  As shown in the scheme below, pipegraph has a main process that take input from the stdin, create some pipes
</p>


               /---> tubi1 ---> com1 ---\
             /                            \
     input    ........................    ---> tubo ---> output         
             \                            /
	             \---> tubin ---> comn ---/            




