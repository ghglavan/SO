#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char** argv){

	//count is the number of executables given as arguments
	int count = 0;

	//with this vector I store the positions which holds the path to executables
	int pozitii[argc];
	pozitii[count++] = 0;

	//parse the command line arguments
	for(int i = 1; i < argc; i ++){
		if(strcmp(argv[i],",") == 0){
			argv[i] = (char*)0;
			pozitii[count++] = i;
		}
	}

	//the matrix of pipes
	int pipes[count][2];

	//the first pipe
	int tubo[2];

	//create the first pipe
	pipe(tubo);

	//create the other pipes
	for(int i = 0 ; i < count; i++){
		pipe(pipes[i]);
	}

	int tata;

	//tata is the main execution thred
	tata = fork();

	//in the child tread  we dup the stdout to every pipe and close the other end of the pipe
	//then we print out a string from stdin	
	if( tata == 0){
		char s[100];

		scanf("%s",s);
		
		for(int i = 0; i < count; i++){

			dup2(pipes[i][1],1);
			close(pipes[i][0]);
			printf("%s",s);
			fflush(stdout);

		}

	

		exit(1);
	}

	//we close the stdout pipes as we don't need them anymore
	for(int i = 0; i < count; i ++){
		close(pipes[i][1]);
	}

	wait(0);

	//for every executable given as argument, we make another execution thread and we replace the proccess image of every thread with the image of the executable
	// we first dub the stdin to every pipe, so the new process will take input from the coresponding pipe and we close the other end of the pipe
	// we dub stdout to tubo for every process to print the result in the tubo pipe
	for(int i = 0; i < count; i ++){
		tata = fork();

		if(tata == 0){
			dup2(pipes[i][0],0);
			close(pipes[i][1]);
			dup2(tubo[1],1);
			close(tubo[0]);

		char c[100];

		strcpy(c,argv[pozitii[i]+1]);

		char **s = argv + pozitii[i] +1;

		if(execvp(c,s) == -1){
			printf("eroare");
		}


			exit(1);
		}

	}
	
	//we close the first end of every pipe
	for(int i = 0; i < count; i ++){
		close(pipes[i][0]);
	}

	//wait for every child to finish

	for(int i = 0; i < count; i++){
		wait(0);
	}

	//fork for the last time to output the result
	//dub the stdin and print to stdout.
	tata = fork();

	if(tata == 0){
		dup2(tubo[0],0);
		close(tubo[1]);

		char s[100];

		while(fgets(s,100,stdin) != 0)
			printf("%s",s);

		exit(1);

	}

	close(tubo[1]);

	wait(0);


}
