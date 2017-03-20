#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
 
pid_t pa;
sigset_t ms;
int nr;
struct sigaction a;
int total=0;

char* tabela;

//the encoded signals header (it prints out the char coresponding to the signal) and sends back SIGUSR1 signal to confirm 
void h(int n){

		printf("%c",tabela[n]);
		kill(pa,SIGUSR1);

		fflush(stdout);

}

// an empty handler
void g(int n){
	return;
}


int main(){


	// we fill the ms mask
    sigfillset(&ms); 

	// activate it so a signal can't interrupt the process
    sigprocmask(SIG_SETMASK,&ms,NULL);

	// get the PID of the partener process
    printf("PID propriu: %d\n",getpid());
    printf("PID advers: "); scanf("%d",&pa);
 

    fflush(stdin);

 
    char *buff = (char*)malloc(200);

	// endolde every letter with a signal 
    tabela = "0abcdefgh0ijklmnop00qrstuvwxyz\n ";

	// set h as a handler for a 
    a.sa_handler=h;
	// fill a's mask so the handler can't be interrupted
    sigfillset(&a.sa_mask);
    a.sa_flags = 0;
	// activate a for every signal 
    for(int i = 0; i < strlen(tabela); i++){
    	if(i != 9 && i != 10 && i != 18 && i != 19){
    		sigaction(i,&a,NULL);
    	}
    }
	// set g as a handler and activate it for SIGUSR1 
    a.sa_handler = g;
    sigaction(SIGUSR1,&a,NULL);

	// empty the mask and activate it
    sigemptyset(&ms); 
    sigprocmask(SIG_SETMASK,&ms,NULL);


	//start the chat
    while(1){
  
    	buff[0] = '\0';
    	while(1){
    		fgets(buff,100,stdin);


    		if(strlen(buff) > 1)
    			break;

    	}
    	for(int i = 0; i < strlen(buff); i++){
			for(int j = 0; j < strlen(tabela); j++){
				if(tabela[j] == buff[i]){

					kill(pa,j);
					break;
				}
			}
    				a.sa_handler = g;
    				sigaction(SIGUSR1,&a,NULL);
			sigsuspend(&ms);
    				a.sa_handler = h;
    				sigaction(SIGUSR1,&a,NULL);   		
    	}
    }
    
    free(buff);

}
