#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>
#include <signal.h>


void killer(int argc, char *argv[],int pid){
	pid_t child_pid;
	child_pid=fork();
	int status;
	
	if(child_pid < 0) exit(EXIT_FAILURE);
	if(child_pid == 0 ){
		if(strcmp(argv[1],"-z")==0){
			FILE *killerproses;
			killerproses=fopen("pkiller.sh","w");

			fprintf(killerproses, "#!/bin/bash\nkillall ./soal3\nrm \"$0\"" );
			fclose(killerproses);	
		}
		else if(strcmp(argv[1],"-x")==0){
			FILE *killerproses;
			killerproses=fopen("pkiller.sh","w");

			fprintf(killerproses, "#!/bin/bash\nkill %d\nrm \"$0\"", pid);
			fclose(killerproses);
		}
	}
	
	else if(child_pid > 0 && wait(&status) > 0 ){
		char *argm[] = {"chmod","+x","pkiller.sh",NULL};
		execv("/usr/bin/chmod",argm);
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
	
	if(fork()==0){
		char zipbaru[200];
		sprintf(zipbaru,"%s.zip",folder);

		char *argv[] = {"zip","-rmq",zipbaru,folder,NULL};
		execv("/usr/bin/zip", argv);
	}
}

int zipfolder(char *folder){
	char zipbaru[200];
	char zip[100]={".zip"};
	strcpy(folder, zipbaru);
	strcat(zipbaru,zip);

	char *argv[] = {"zip","-r","-m",zipbaru,folder,NULL};
	execv("/usr/bin/zip", argv);
}


int timer(int i){
	sleep(1);
	return i;
}

int download(char *path){
	int t=1;
	int status;
	while(t<=10){
		t++;
		sleep(5);
		time_t rawtime;

		char file[80];
		char url[100];
		char fp[100];
		int size;

		time (&rawtime);
		strftime(file,80,"/%Y-%m-%d_%H:%M:%S.jpg",localtime(&rawtime));
	
		size=(int)time(NULL);
		size=(size%1000)+50;
		sprintf(url,"https://picsum.photos/%d",size);
		
		sprintf(fp,"%s%s",path,file);

		if(fork()==0){
			char *args[] = {"/usr/bin/wget", "-qO",fp,url, (char *) 0 };
			execv("/usr/bin/wget", args);
		}
		
	}
	while(wait(&status) > 0 );
	statustext(path);

}

int crtdir(){
	char mkfolder[80];
	time_t rawtime;
	int t=10;

	sleep(39);

	if(fork()==0){
		

		time (&rawtime);
		strftime(mkfolder,80,"%Y-%m-%d_%H:%M:%S",localtime(&rawtime));
		
		if(fork()==0) download(mkfolder);

		char *argv[] = {"mkdir",mkfolder,NULL};
		execv("/bin/mkdir",argv);
	}
	
}


int main(int argc, char **argv){
	

	pid_t pid, sid;

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

  	if (pid > 0) {
    		exit(EXIT_SUCCESS);
  	}

	umask(0);

	sid = setsid();
	if (sid < 0) {
		exit(EXIT_FAILURE);
	}


	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	int t=3;
	killer(argc ,argv, (int) getpid()+1);

	while(1){

		crtdir();
		
	sleep(1);

	}
}
