### Laporan Resmi Soal Shift Modul 2 (D07)

----------------------

### Soal 1
### A. Dikarenakan Stevany sangat menyukai huruf Y, Steven ingin nama folder-foldernya adalah Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg
Jadi untuk menyelesaikan permasalahan atau soal a ini, yang pertama disoal disuruh memuat folder-folder bernama Musyik untuk file mp3, Fylm untuk mp4 dan Pyoto untuk jpg, namun disini saya hanya membuat direktori/folder biasa saja, karena pada soal terdapat peringatan tidak boleh menggunakan fungsi-fungsi yang ada dibahasa c, seperti system(), mkdir(), rename(), dll. Sehingga untuk mengerjakannya saya menggunakan  ```execv```, yang mana untuk menggunakan execv dibutuhkan path dan char argumen, char argumen ini digunakan agar terbaca saat menggunakan ```execv```, berikut adalah cara penyelesaianya <br/> <br/>
    1. Untuk membuat direktori pada linux, cara yang bisa kita gunakan yaitu ```mkdir -p foldername```, agar bisa dijalankan di program c di linux, kita perlu memasukkan code tersebut ke sebuah variable char, agar nanti kita tinggal memanggilnya saja, <br/>
    2. Selanjutnya cara memasukkan code tersebut ke dalam sebuah variable yaitu dengan memecah kata-kata yang ada pada code itu, jadi apabila dimasukkan ke dalam variable akan menjadi seperti ini ```char *argv[] = {"mkdir", "-p", "Fyoto", NULL}``` <br/>
    3. Setelah itu selanjutnya kita mencari path yang terdapat/letak mkdirnya, untuk mencari pathnya kita bisa mencarinya pada terminal, dengan mengetikkan ```whereis mkdir``` dan akan ditampilkan pathnya yaitu ```/bin/mkdir``` <br/>
    4. Selanjutnya karena kita sudah mendapatkan path dan variable nya, tinggal kita panggil menggunakan ```execv("/bin/mkdir", argv)```, argv merupaka variable yang menyimpan code untuk membuat direktorinya. <br/>
    5. Lalu pada soal A ini kita disuruh membuat 3 folder dengan ketentuan nama ```Fyoto, Musyik, Fylm``` kita bisa menggunakan langka 1 sampai 4, hanya mengubahnya saja pada bagian ```foldername```, namun agar bisa langsung membuat 3 folder, yaitu kita perlu membuat perulangan for dulu yang mana, membuat perulangan sebanyak 3x ```for(int x=0;x<3;x++)``` dan ketika ```x==0``` membuat folder Fyoto, begitu juga seterusnya, untuk kode lengkapnya bisa dilihat dibawah ini.
```
for (x=0;x<3;x++)
{
    child_id = fork();
    if (child_id == 0) 
    {
        if (x==0)
        {       
            char *argv[] = {"mkdir", "-p", "Fyoto", NULL};
            execv("/bin/mkdir", argv);
        }
        if (x==1)
        {
            char *argv[] = {"mkdir", "-p", "Musyik", NULL};
            execv("/bin/mkdir", argv);
        }
        if (x==2)
        {
        char *argv[] = {"mkdir", "-p", "Fylm", NULL};
        execv("/bin/mkdir", argv);
        }
    }
}
```
### B. Untuk musik Steven mendownloadnya dari link di bawah, film dari link di bawah lagi, dan foto dari link dibawah juga :).
Selanjutnya untuk mengerjakan soal b ini menggunakan cara yang mirip, yaitu dengan menggunakan ```execv``` dan untuk bisa menggunakan execv kita membutuhkan path dan sebuah argumen, untuk mendownload file dari link di terminal linux, itu menggunakan code sebagai berikut: <br/> ```wget --no-check-certificate "https://drive.google.com/uc?id=ID-FILE&export=download" -O Nama_untuk_filenya.ext``` <br/> karena menggunakan execv maka, code tersebut dimasukkan ke dalam variable argumen sehingga berbentuk seperti berikut 
```char *argv[] = {"wget", "-q", "--no-check-certificate", link, "-O", "nama.zip", NULL};```<br/>
Lalu pada soal B ini kita disuruh mendownload 3 buah file dari link yang berbeda-beda, kita bisa menggunakan cara seperti 1a langkah 1 sampai 4, hanya mengubahnya saja pada bagian ```link``` nya saja, dan juga link untuk mendownloadnya sudah saya masukkan ke dalam sebuah array. namun agar bisa langsung mendownload 3 file, yaitu kita perlu membuat perulangan for dulu yang mana, membuat perulangan sebanyak 3x ```for(int x=0;x<3;x++)``` dan ketika ```x==0``` mendownload file pertama, begitu juga seterusnya, untuk kode lengkapnya bisa dilihat dibawah ini.
```
for (x=0;x<3;x++)
{
    child_id = fork();
    if (child_id == 0) 
    {
	    if(x==0)
	    {
        	// Mengambil / mendownload file pada link[0], yang mana char link sudah berisi 3 link
            char *argv[] = {"wget", "-q", "--no-check-certificate", link[0], "-O", "Foto_for_Stevany.zip", NULL};
            execv("/bin/wget", argv);
	    }
		if(x==1)
	    {
            char *argv[] = {"wget", "-q", "--no-check-certificate", link[1], "-O", "Musik_for_Stevany.zip", NULL};
            execv("/bin/wget", argv);
	    }	
		if(x==2)
	    {   	 
            char *argv[] = {"wget", "-q", "--no-check-certificate", link[2], "-O", "Film_for_Stevany.zip", NULL};
            execv("/bin/wget", argv);
	    }  
    }
}
```
### C. Mengekstrak / unzip file yang sudah didownload pada Poin B
Mengekstrak file yang sudah didownload tadi bisa menggunakan cara seperti diatas namun hanya terletak pada argumennya saja yaitu apabila unzip menggunakan cara berikut:
```char *argv[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};```<br/>
```-q``` berfungsi agar saat proses tersebut dijalankan tidak akan mengeluarkan output diterminal, lalu agar langsung bisa mengekstrak 3 file sekaligus yaitu dengan cara:
```
for (x=0;x<3;x++)
{
    child_id1 = fork();
    if (child_id1 == 0) 
    {
        if (x==0)
        {
            // Melakukan unzip setelah mendownload file yang bernama .....
            char *argv[] = {"unzip", "-q", "Foto_for_Stevany.zip", NULL};
            execv("/bin/unzip", argv);
        }
        if (x==1)
        {
            char *argv[] = {"unzip", "-q", "Musik_for_Stevany.zip", NULL};
            execv("/bin/unzip", argv);
        }
        if (x==2)
        {
            char *argv[] = {"unzip", "-q", "Film_for_Stevany.zip", NULL};
            execv("/bin/unzip", argv);
        }
    }
}
```
Agar langsung bisa mengekstrak 3 file sekaligus maka dibutuhkan perulangan dan didalamnya terdapat if statement yang apabila memenuhi kondisi 1,2,3 maka akan menjalankan execv nya.


### Menjalankan Proses A, B, dan C Otomatis 6 Jam sebelum Ulang Tahun, dan D, E Saat Ulang tahun
untuk mengerjakannya karena tidak boleh menggunakan crontab, maka untuk membuat schedulenya saya membuat secara manual, yaitu menggunakan struct untuk mengeset waktunya,
```
        time_t T= time(NULL);
        struct  tm tm = *localtime(&T);

        tanggal = tm.tm_mday;
        bulan = tm.tm_mon + 1;
        jam = tm.tm_hour;
        menit = tm.tm_min;
        detik = tm.tm_sec;
```
```*localtime``` disini berguna untuk mengambil waktu sekarang/ waktu realnya, dan disimpan ke struct tm. selanjutnya tinggal membuat variable-variable seperti tanggal, bulan, jam, dll dengan menggunakan struct tm dan kode waktunya seperti tm_mday, tm_mon, tm_hour, dll. setelah variable-variable itu sudah menyimpan waktu real, maka tinggal kita lakukan if statement, jika waktu ulang tahun dikurangi 6 jam maka lakukan proses a,b, dan c. Seperti berikut :
```
time_t T= time(NULL);
        struct  tm tm = *localtime(&T);

        tanggal = tm.tm_mday;
        bulan = tm.tm_mon + 1;
        jam = tm.tm_hour;
        menit = tm.tm_min;
        detik = tm.tm_sec;

        // Proses yang akan dijalankan pada tgl 9 April
        // Karena soal a,b,c harus dijalankan 6 jam sebelum ultah stevany maka 22-6 = 16
        if(tanggal==9&&bulan==4&&jam==16&&menit==22&&detik == 0)
        {   
            //SC soal 1a
            //SC soal 1b
            //SC soal 1c
        }
        // Saat waktu menunjukkan ulang tahun stevany yaitu jam == 22 maka lakukan proses d, e
        if(tanggal==9&&bulan==4&&jam==22&&menit==22&&detik == 0)
        { 
            //SC Soal 1d
            //SC soal 1e
         }
```
### D. Memindahkan File yang diunzip tadi ke dalam folder baru yang sudah dibuat
Memindahkan file dari folder satu ke folder lainnya, bisa menggunakan cara seperti diatas namun hanya terletak pada argumennya saja yaitu apabila memindahkan file menggunakan cara berikut:
```char *argv[] = {"mv", "-T", "/path_folder1", "/path_folder2", NULL};```<br/>
Lalu agar langsung bisa memindahkan 3 file sekaligus yaitu dengan cara:
```
            for (x=0;x<3;x++)
            {
                child_id = fork();
                if (child_id == 0) 
                {
                    if (x==0)
                    {   
                        // Memindah isi file yang ada di folder FOTO ke Fyoto
                        char *argv[] = {"mv", "-T", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/FOTO", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/Fyoto", NULL};
                        execv("/bin/mv", argv);
                    }
                    if (x==1)
                    {
                        char *argv[] = {"mv","-T", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/MUSIK", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/Musyik", NULL};
                        execv("/bin/mv", argv);
                    }
                    if (x==2)
                    {
                        char *argv[] = {"mv","-T", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/FILM", "/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1/Fylm", NULL};
                        execv("/bin/mv", argv);
                    }
                }
            }
```
Agar langsung bisa memindahkan 3 file dari folder ke folder sekaligus maka dibutuhkan perulangan dan didalamnya terdapat if statement yang apabila memenuhi kondisi 1,2,3 maka akan menjalankan execv nya.

### E. MenZIP semua folder yang ada, dan menghapus foldernya, sehingga hanya menampilkan file bertipe zip saja.
Agar bisa menzip folder-folder yang kita pilih, bisa menggunakan cara seperti diatas namun kuncinya hanya terletak pada argumennya saja yaitu apabila menzip folder menggunakan cara berikut:
```char *argv[] = {"zip", "-r", "-m", "namaoutput.zip", "Folder1", "Folder2", "Folder3", NULL}```<br/>
Namun cara ini tidak perlu menggunakan perulangan, karena untuk code zip ini bisa langsung menzip lebih dari 1 folder, dan juga saya tidak perlu membuat fungsi baru untuk menghapus sisa-sisa foldernya, karena pada code diatas, sudah saya tambahkan ```-m``` yang mana dengan memakai fungsi tersebut langsung menghapus folder-foldernya sehingga apabila diliat full codenya sebagai berikut: <br/>
```
            child_id = fork();
            if (child_id == 0) 
            {
                // Memasukkan 3 folder kedalam zip dan langsung menghapus foldernya.
                char *argv[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Fyoto", "Musyik", "Fylm", NULL};
                execv("/bin/zip", argv);
            }
```
### Fungsi-Fungsi Tambahan
Untuk mengerjakan soal ini, karena disoal terdapat petunjuk yaitu programnya berjalan di background secara terus menerus tanpa adanya interaksi secara langsung dengan user yang sedang aktif. Oleh karena itu saya menggunakan daemon, yang mana source code daemonnya tidak saya jelaskan karena sudah terdapat pada modul seslab 2, apabila menggunakan daemon saya hanya memasukkan source code pengerjaan soal 1a-e ini pada bagian ```while(1)``` nya. berikut contoh program daemonnya : <br/>
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini

    sleep(30);
  }
}
```
Dan juga setiap proses dari A-E setiap selesai melakukan perulangan saya tambahkan ```sleep(10)``` untuk memperlancar program tersebut

### Kendala
Kendala yang saya kerjakan awalnya terdapat pada schedule nya, yaitu bagaimana cara menjalankan program hanya pada jam yang ditentukan, dan akhirnya saya menemukan solusinya dengan menggunakan struct time.

### Output Apabila Dijalankan 6 Jam Sebelum Ulang Tahun
![alt text](https://github.com/migellamp/ss_soal1/blob/main/Screenshot%20from%202021-04-09%2016-23-34.png) <br />
### Output Apabila Dijalankan Saat Ulang Tahun
![alt text](https://github.com/migellamp/ss_soal1/blob/main/Screenshot%20from%202021-04-25%2018-57-39.png) <br />

----------------------

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
 
 ----------------------

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



