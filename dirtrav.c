#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[1;31m"
#define KGRN  "\x1B[1;32m"
#define KYEL  "\x1B[1;33m"
#define KBLU  "\x1B[1;34m"
#define KMAG  "\x1B[1;35m"
#define KCYN  "\x1B[1;36m"
#define KWHT  "\x1B[1;37m"

int nrSpatii;
int *afis;
int nD,nF;

//Dfs on directories... or more like an inorder traversal in the directories tree 
void dfspedirectoare(char* cale);

//print details about the specified file
void afisare(char* nume,char* calen,int e_ultimul_dir){



			struct stat sb;
			char *culoare;

			int s = lstat(calen,&sb);
/*
			if(s < 0){
				if(errno != ENOENT){
				perror(calen);
				exit(2);
				}
			}
*/
			if(S_ISDIR(sb.st_mode))
				culoare = KBLU;
			else if(sb.st_mode & S_IXUSR)
				culoare = KGRN;
			else
				culoare = "";

			int oprire = -1;
			for(int i = 0;i < strlen(nume); i++){
				if(nume[i] == '.')
					oprire = i;
			}
			if(oprire > 0){
				if(!strcmp(nume+oprire+1,"jpg"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"jpeg"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"png"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"bmp"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"mp4"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"gif"))
					culoare = KMAG;
				else if(!strcmp(nume+oprire+1,"zip"))
					culoare = KRED;
				else if(!strcmp(nume+oprire+1,"gz"))
					culoare = KRED;
			}



			for(int i = 0; i < nrSpatii; i++)
				if(afis[i] == 1)
					printf("│  ");
				else
					printf("   ");
			
			if(e_ultimul_dir == 0)
				printf("├──%s%s%s\n",culoare,nume,KNRM);
			else
				printf("└──%s%s%s\n",culoare,nume,KNRM);

			if((sb.st_mode & S_IFMT) == S_IFDIR && !(strcmp(nume,".") == 0 || strcmp(nume,"..") == 0)){
				nD++;
				nrSpatii++;
				dfspedirectoare(calen);
				nrSpatii--;

			}else{
				nF++;
			}
}


// the implementation of the inorder traversal
void dfspedirectoare(char* cale){
	struct dirent *info;
	int count = 0;



	DIR *d;
	d = opendir(cale);


	if(!d){
		perror(cale);
		exit(1);
	}

	while((info = readdir(d)) != NULL){



		if(strcmp(info->d_name,".") == 0 || strcmp(info->d_name,"..") == 0){
			continue;
		}
		count++;
	}
	closedir(d);
	d = opendir(cale);

	while((info = readdir(d)) != NULL){
		
		if(strcmp(info->d_name,".") == 0 || strcmp(info->d_name,"..") == 0){
			continue;
		}

		char* calen = malloc(2560*sizeof(char));



		strcpy(calen,cale);
		strcat(calen,"/");
		strcat(calen,info->d_name);



		if(count > 1){
			afis[nrSpatii] = 1;
			afisare(info->d_name,calen,0);
		}else{
			afis[nrSpatii] = 0;
			afisare(info->d_name,calen,1);
		}
		count--;

		free(calen);
	}
	closedir(d);

}


int main(int argc, char **argv){
	//printf("dfs pe %s\n",argv[1]);


	afis = (int*)malloc(100*sizeof(int));

	char s[100];

	scanf("%s",s);

	dfspedirectoare(s);

	free(afis);

	printf("\n%d directories, %d files detected\n",nD,nF);

	return 0;
}
