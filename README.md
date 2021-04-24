# soal-shift-sisop-modul-2-D07-2021


# soal 3 
Ranora adalah mahasiswa Teknik Informatika yang saat ini sedang menjalani magang di perusahan ternama yang bernama “FakeKos Corp.”, perusahaan yang bergerak dibidang keamanan data. Karena Ranora masih magang, maka beban tugasnya tidak sebesar beban tugas pekerja tetap perusahaan. Di hari pertama Ranora bekerja, pembimbing magang Ranora memberi tugas pertamanya untuk membuat sebuah program.

## soal 3a
diminta membuat folder dengan program c dengan format nama sesuai timestamp[YYYY-mm-dd_HH:ii:ss] dengan waktu pembuatan 40 detik sekali.

### Langkah pengerjaan 
program dijalankan dengan penerapan daemon agar program tidak terganggu dengan proses proses yang lain. setelah penerapan daemon maka masuk kedalam fungsi untuk membuat folder yaitu fungsi ``` crtdir ```.
```
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
```
pada fungsi diatas hal yang dilakukan pertama kali adalah mendeclare variabel-variabel dan menambahkan ```sleep(39)``` yang mana perintah tersebut memerintahkan untuk menunggu selama 39 detik agar tepat menjadi 40 detik pada program utama ditambahkan ```sleep(1)``` , lalu memanggil fungsi fork untuk membuat proses baru yang memiliki fungsi untuk menciptakan file baru dengan command ```execv``` sedangkan strftime digunakan untuk memberi nama pada folder atau directory yang telah dibuat.

### Kendala
pada pembuatan fungsi tersebut harus dibuat proses dengan perintah ```fork()``` proses tidak keluar sebelum perulangan.


## soal 3b
Setiap direktori yang telah dibuat, diminta untuk mengunduh 10 gambar yang dari "https://picsum.photos/", dimana setiap gambar diunduh setiap 5 detik. Lalu setiap gambar diberi nama dengan format format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

### cara pengerjaan 
pada fungsi ```crtdir()``` , fungsi tersebut memanggil fungsi baru yaitu fungsi ```download()``` yang berisi perintah untuk mendownload gambar dengan format nama  timestamp setiap 5 detik sekali yang dilakukan dengan perintah ```sleep(5)``` sebanyak 10 gambar dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix, kemudian hasil dari dowload gambar dimasukan kedalam folder-folder yang telah dibuat.
```
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
```
fungsi download dengan ```char *path``` yang menjadi directory tujuan, perintah-perintah diatas dilakukan perulangan sebanyak 10 kali dimana untuk mencapai 10 kali download. didalam perintah-perintah tersebut terdapat perintah ```strftime``` yang digunakan sebagai penamaan file yang telah diunduh,variabel ```size```digunakan sebagai tempat untuk menyimpan ukuran gambar seperti yang telah ditentukan soal dan  ```fork()``` digunakan untuk membuat proses baru yang berfungsi untuk mendowload gambar dengan perintah ```wget```, setelah iterasi while selesai dijalankan maka akan memanggil fungsi baru yaitu ```statustext()```.

### Kendala 
pada awal pengerjaan soal saya membuat program agar program tersebut dapat  menyimpan nama directory yang dibuat dengan array, namun hal tersebut menyebabkan error apabila array penuh.


## Soal 3c
Setelah direktori telah terisi dengan 10 gambar, buat sebuah file “status.txt”, dimana didalamnya berisi pesan “Download Success” yang terenkripsi dengan teknik Caesar Cipher dan dengan shift 5. Setelah file dibuat, zip direktori dan hapus direktori tersebut sehingga menyisakan file zip saja.

### Langkah pengerjaan
pada soal diatas kita disuruh untuk membuat sebuah text yang berisikan pesan ```"Download Succses"``` yang mana pesan tersebut kan dienkripsi dengan fungsi Chaesan Chiper ```chiper()``` dengan shift 5 dan disimpan dengan nama```status.txt```, apabila directory sudah penuh 10 gmabar dan sudah berisi text yang terenkripsi, maka akan folder tersbut akan dibuat zip dan menghapus folder yang dijadikan zip. perintah - perintah tersbut terdapat pada fungsi ```statustext(), chiper(), zipfolder()```.
```
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


int zipfolder(char *folder){
	char zipbaru[200];
	char zip[100]={".zip"};
	strcpy(folder, zipbaru);
	strcat(zipbaru,zip);

	char *argv[] = {"zip","-r","-m",zipbaru,folder,NULL};
	execv("/usr/bin/zip", argv);
}

```
pada kode diatas saya melakukan bypass pada fungsi ```statustext()``` dengan langsung menuliskan kode yang ada pada ```zipfolder()```.

### Kendala
```-```

## Soal 3d dan e
Pada saat program C dijalankan, program tersebut akan men-generate sebuah program killer dalam bentuk program bash yang executable, dan setelah program killer dijalankan, maka program killer tersebut akan menghapus dirinya sendiri. Apabila program C dijalankan dengan menggunakan argument -z, maka apabila program killer dijalankan, semua proses yang sedang dilakukan oleh program C akan berhenti saat itu juga. Namun apabila program C dijalankan dengan menggunakan argument -x, maka program akan berhenti namun akan menyelesaikan proses pada direktori yang telah dibuat.

### Langkah Pengerjaan 
dengan memanggil fungsi ```killer()``` yang mana fungsi tesebut mempassing argument ketika menjalankan program yang mana argument tersebut berasal dari ```main()```. soal tersebut memerintahkan kita untuk membuat sebuah ekstensi ketika program dijalankan dengan argumen tambahan. ```-z``` untuk mengkill seluruh proses yang berlangsung sendangkan ```-x``` untuk mengkill proses untuk mencreate folder baru hingga proses- proses setelahnya.
```
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
```
program tersebut membuat file bash yang merupakan file untuk eksekusi final dari ekstensi argumen yang telah diinputkan diawal. pada fungsi diatas berisi ``` if(strcmp(argv[1],"-z")==0)``` yang digunakan untuk menyeleksi apakah argumen yang masuk adalah argumen ```-z``` apabial iya maka akan dibuat file bash baru dengan nama ```pkiller.sh``` yagn berisis perintah bash untuk mengkill semua proses yang berlangsung dengan menggunakan perintah ```killall``` dan pada filebash baru tersebut berisi perintah ```rm``` yang berfugnsi untuk meremove file baru tersebut yang telah dijalankan.
sedangkan pada ```else if(strcmp(argv[1],"-x")==0)``` adalah perintah untuk menjalankan program yang mirip dengan argumen ```-z``` namun pada program ini hanya akan mengeliminasi proses dari pembuatan folder baru dan melanjutkan proses hingga pembuatan zip baru.

### Kendala 
kendala pada soal diatas adalah kebingungan mengeliminasi proses pada argumen ```-x```.


## Hasil 





