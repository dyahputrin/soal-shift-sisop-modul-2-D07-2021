# soal-shift-sisop-modul-2-D07-2021

# soal 2
Loba bekerja di sebuah petshop terkenal, suatu saat dia mendapatkan zip yang berisi banyak sekali foto peliharaan dan Ia diperintahkan untuk mengkategorikan foto-foto peliharaan tersebut. Loba merasa kesusahan melakukan pekerjaanya secara manual, apalagi ada kemungkinan ia akan diperintahkan untuk melakukan hal yang sama. Kamu adalah teman baik Loba dan Ia meminta bantuanmu untuk membantu pekerjaannya.

## soal 2a
Mengextract zip yang diberikan ke dalam folder "home/[user]/modul2/petshop" dan menghapus folder-folder yang tidak dibutuhkan
```
child1 = fork();

    if(child1 == 0) {
        char *argv[] = {"unzip", "-q", "/home/putri/modul2/pets.zip", "-d", "/home/putri/modul2/petshop", NULL};
        execv("/usr/bin/unzip", argv);
    }
    
    waitpid(child1, &status, 0);
```

Potongan kode diatas, menunjukkan langkah-langkah untuk mengextract pets.zip menggunakan command ```unzip```. Setelah itu, kita harus menghapus folder-folder yang tidak dibutuhkan dengan menggunakan kode dibawah ini.
```
char folderName[1000];
    sprintf(folderName, "%s/","/home/putri/modul2/petshop");

    DIR *folder;
    struct dirent *entry;
    
    if((folder = opendir(folderName)) != NULL) {
        while((entry = readdir(folder)) != NULL) {
            if(strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".")) {
                if(entry->d_type == DT_DIR) { //DT_DIR itu data type buat folder

                    char folderDelete[1256];
                    sprintf(folderDelete, "%s%s", folderName, entry->d_name);

                   	child2 = fork();

                    if(child2 == 0) {
                        char *argv[] = {"rm", "-rf", folderDelete, NULL};
                        execv("/bin/rm", argv);
                    }

                    waitpid(child2, &status, 0);
                }
            } 
        }
	}
```
Untuk menghapus folder-folder yang tidak dibutuhkan pada folder pets, kita harus menulusuri ke semua file yang ada di folder pets. Apabila ditemukan type ```DT_DIR``` maka itu merupakan sebuah directory. Sehingga, directory tersebut harus dihapus. Penghapusan directory dapat menggunakan command ```rm -rf```

## soal 2b
Membuat folder sesuai dengan jenis hewan peliharaan
```
child4 = fork();

    if(child4 == 0) {
        char *argv[] = {"mkdir", "-p", folderCategory, NULL};
        execv("/usr/bin/mkdir", argv);
    }
    waitpid(child4, &status, 0);
```
Potongan kode diatas, menunjukkan tahapan untuk membuat folder sesaui dengan jenis hewan peliharaan. Namun, sebelum itu, kita perlu melakukan split nama file untuk mendapatkan jenis-jenis hewan peliharaan apa saja yang tersedia. Untuk melakukan split nama file, kita menggunakan fungsi ```strtok``` dengan delimiter tertentu. Stelah itu menggunakan ```sprintf``` untuk menggabungkan beberapa string menjadi sebuah path, agar memudahkan dalam pembuatan folder nantinya. Potongan kode dibawah ini menunjukan tahapan tersebut.
```
char *deli = ";";	//sebagai delimiter
    char *category = strtok(fileName, deli);
    char *name = strtok(NULL, deli); 
    char *age = strtok(NULL, deli);

    char folderCategory[1000]; //variable dengan isi path folder berdasar jenis
    char fileKet[1000]; //variabel dengan isi path folder file keterangan
    char animalFileName[1000]; //variable dengan isi path untuk me-rename file dengan nama hewannya saja
    char desc[1000];//variable dengan isi nama dan umur hewan, untuk dimasukkan ke file keterangan

    sprintf(folderCategory, "%s%s", "/home/putri/modul2/petshop/", category);
    sprintf(fileKet, "%s%s/keterangan.txt", "/home/putri/modul2/petshop/", category);
    sprintf(animalFileName, "%s%s/%s.jpg", "/home/putri/modul2/petshop/", category, name);
```
Dikarenakan terdapat file yang terdiri dari dua jenis hewan peliharaan, file-file seperti itu harus di split terlebih dahulu menggunakan potongan kode dibawah ini.
```
if((folder = opendir(folderName)) != NULL) {
        while((entry = readdir(folder)) != NULL) {
            if(strcmp(entry->d_name, "..") && strcmp(entry->d_name, ".")) {
                if(entry->d_type == DT_REG) { //DT_REG itu data type buat file

                    char fileOrigin[1000];
                    char fileOriginPath[1000];

                    sprintf(fileOriginPath, "%s%s", "/home/putri/modul2/petshop/", entry->d_name);

                    sprintf(fileOrigin, "%s", entry->d_name); //fileOrigin adalah file dengan nama asli (sebelum di split2)
                    fileOrigin[strlen(fileOrigin)-4] = '\0'; //strlen nya - 4 dikarenakan untuk menghilangkan .jpg

                    char *deli2 = "_";
                    char *animalType1 = strtok(fileOrigin, deli2); //nama file yang hanya terdiri dari satu hewan
                    char *animalType2 = strtok(NULL, deli2); //nama file yang terdidiri dari dua hewan
```
##soal 2c
Setelah folder kategori berhasil dibuat, programmu akan memindahkan foto ke folder dengan kategori yang sesuai dan di rename dengan nama peliharaan.

Untuk memindahkan foto ke folder kategori yang sesuai, dapat menggunakan command ```cp``` seperti potongan kode dibawah ini untuk meng-copy foto.
```
child6 = fork();

    if(child6 == 0) {
        char *argv[] = {"cp", namaFileAsli, animalFileName, NULL};
        execv("/usr/bin/cp", argv);
    }
    waitpid(child6, &status, 0);
 ```
 Setelah foto berhasil di copy ke folder yang sesuai, foto-foto yang terdapat pada path sebelumnya dapat di hapus, seperti pada potongan kode dibawah ini.
 ```
 child3 = fork();
                    if(child3 == 0) {
                        char *argv[] = {"rm", "-rf", fileOriginPath, NULL};
                        execv("/usr/bin/rm", argv);
                    }

                    waitpid(child3, &status, 0);
 ```
 
 ##soal 2d
 Karena dalam satu foto bisa terdapat lebih dari satu peliharaan maka foto harus di pindah ke masing-masing kategori yang sesuai
 
 Penyelesaian soal ini, sudah ada pada poin 2b.
 
 ##soal 2e
 Membuat file keterangan,txt yang berisi nama dan umur semua hewan peliharaan di setiap folder
 ```
  sprintf(desc, "nama : %s \numur : %s\n\n", name, age);

    //membuat file keterangan.txt
    FILE *file;
    file = fopen(fileKet, "a");

    if(file) {
        fprintf(file, "%s", desc);
        fclose(file);
    }
 ```
 Untuk membuat file keterangan, dapat menggunakan fungsi ```fopen```. Setelah itu, gunakan ```fprintf``` untuk mengeluarkan output nama dan umur dari setiap hewan ke dalam file keterangan.txt
 
 ### Hasil
  ![kendala](https://github.com/dyahputrin/image/blob/eb3fba6802348ddbd1bf1b4069f669a85eb6a09c/ss2.png)
  ![kendala](https://github.com/dyahputrin/image/blob/eb3fba6802348ddbd1bf1b4069f669a85eb6a09c/ss3.png)
  ![kendala](https://github.com/dyahputrin/image/blob/eb3fba6802348ddbd1bf1b4069f669a85eb6a09c/ss4.png)
 
 ### Kendala
 Pada saat sedang membuat keterangan.txt sempat ada kendala saat memunculkan nama hewan peliharaan
 ![kendala](https://github.com/dyahputrin/image/blob/eb3fba6802348ddbd1bf1b4069f669a85eb6a09c/ss1.png)

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

![Screenshot from 2021-04-24 21-01-46](https://user-images.githubusercontent.com/73246861/115961494-cfef7980-a540-11eb-816f-c8bca767ad5d.png)
membuat bash setelah run program.

![Screenshot from 2021-04-24 21-03-41](https://user-images.githubusercontent.com/73246861/115961514-eb5a8480-a540-11eb-8299-298b115de6d3.png)
mencreate folder setiap 40 detik sekali,dan zip ketika file download dan status.txt telah telah terisi.

![Screenshot from 2021-04-24 21-08-23](https://user-images.githubusercontent.com/73246861/115961588-442a1d00-a541-11eb-93f1-35289daf575c.png)
isi zip.

![Screenshot from 2021-04-24 21-08-28](https://user-images.githubusercontent.com/73246861/115961613-56a45680-a541-11eb-8846-6150b2a2098c.png)
isi status.txt

![Screenshot from 2021-04-24 21-04-05](https://user-images.githubusercontent.com/73246861/115961548-147b1500-a541-11eb-9bc9-c4e3b4257705.png)
semua proses berhenti ketika program bash dijankan.



