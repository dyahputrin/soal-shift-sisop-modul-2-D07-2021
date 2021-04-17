#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void killer(int argc, char *argv[],int pid){
	if(strcmp(argv[1],"-z")==0){
		FILE *killerproses;
		killerproses=fopen("pkiller.sh","w");
		fprintf(killerproses, "#!/bin/bash\nkillall ./soal3\nrm \"$0\"" );
		fclose(killerproses);	
	}
	else if(strcmp(argv[1],"-x")==0){
		FILE *killerproses;
		killerproses=fopen("pkiller.sh","w");
		fprintf(killerproses, "#!/bin/bash\nkill -9 %d\nrm \"$0\"",pid);
		fclose(killerproses);
	}
	
	if(fork()==0){
		char *argm[] = {"chmod","+x","pkiller.sh",NULL};
		execv("/bin/chmod",argm);
	}
}

void chiper(char message[]){
	char ch,hasil;
	int i, key=5;
	
	for(i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			
			message[i] = ch;
		}
	}
}


void statustext(char *folder){
	char nama[100],isi[]= {"Download Succes"};

	FILE *text;
	chiper(isi);
	sprintf(nama,"%s/status.txt",folder);
	text = fopen(nama,"w");
	fprintf(text,"%s",isi);
	fclose(text);
}

void zipfolder(char *folder){
	char *argv[] = {"zip","-r","-m",folder,folder,NULL};
	execv("/bin/zip",argv);
}


int timer(int i){
	sleep(1);
	return i;
}

int main(int argc, char *argv[]){
	int status,i=1;
	pid_t child_pid,sid;
	
	time_t rawtime;
	struct tm *info;

	char mkfolder[80];
	char file[80];
	
	char folder[100][50];
	int f=0;
	int g=0;
	int h=1;
	int j=1;
	char fp[100];
	int size;
	char url[100];

	int cek = getpid();
	
	

	if (child_pid < 0) {
    		exit(EXIT_FAILURE);
  	}

  	if (child_pid > 0) {
   		exit(EXIT_SUCCESS);
  	}

  	umask(0);
	
	if ((chdir("/")) < 0) {
    		exit(EXIT_FAILURE);
  	}

	sid = setsid();
  	if (sid < 0) {
    		exit(EXIT_FAILURE);
	}
	close(STDIN_FILENO);
 	close(STDOUT_FILENO);
  	close(STDERR_FILENO);
	
	
	while(1){
		timer(i);
		printf("s : %d\n",i);
		
		if(i%40==0){
			f++;
			time (&rawtime);
			strftime(mkfolder,80,"%Y-%m-%d_%H:%M:%S",localtime(&rawtime));
			printf("createfolder : %d -> ",f);
			strcpy(folder[f], mkfolder);
			puts(folder[f]);


			if(fork()==0){
				char *argv[] = {"mkdir",mkfolder,NULL};
				execv("/bin/mkdir",argv);
			}
					
		}
		
		
		
		if(i>40 && i%5==0){
			g++;
			time (&rawtime);
			strftime(file,80,"/%Y-%m-%d_%H:%M:%S.jpg",localtime(&rawtime));
		
			size=(int)time(NULL);
			size=(size%1000)+50;
			sprintf(url,"https://picsum.photos/%d",size);
			
			printf("proses download ke %d\n",g);
			if(g>=10){
				if(g%10==1) h++;
				sprintf(fp,"%s%s",folder[h],file);	
				printf("%s%s\n",folder[h],file);
				if(g%10==0){ //create new file
					statustext(folder[h]);
					printf("zipping");
					zipfolder(folder[h]);				
				}
			}else if(g<10){
				sprintf(fp,"%s%s",folder[h],file);	
				printf("%s%s\n",folder[h],file);
			}
			

			if(fork()==0){
				
				printf("download ke %d\n",g);
				char *args[] = {"/usr/bin/wget", "-qO",fp, "https://picsum.photos/200", (char *) 0 };
				execv("/usr/bin/wget", args);
			}
		}
	i++;
		
	}
}



















