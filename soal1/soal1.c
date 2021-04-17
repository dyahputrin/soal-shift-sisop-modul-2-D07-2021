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

int main() 
{ 
    // Mendeklarasikan Variable-Variable
    pid_t pid, sid;        // Variabel untuk menyimpan PID
    pid_t child_id;
    pid_t child_id1;
    int x, tanggal, bulan, jam, menit, detik;
    char *link[] = {"https://drive.google.com/u/0/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "https://drive.google.com/u/0/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "https://drive.google.com/u/0/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
    // Struct untuk membuat schedule pada waktu yg ditentukan
    char *folder = {"/home/zntfire/Documents/SOALSHIFT/Modul 2/Soal 1"};

    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);

    tanggal = tm.tm_mday;
    bulan = tm.tm_mon + 1;
    jam = tm.tm_hour;
    menit = tm.tm_min;
    detik = tm.tm_sec;

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

    if ((chdir(folder)) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while(1)
    {
        // Proses yang akan dijalankan pada tgl 9 April
        if((tanggal==9) && (bulan==4) && (menit==22) && (detik==0))
        {   
            // Karena soal a,b,c harus dijalankan 6 jam sebelum ultah stevany maka 22-6 = 16
            if(jam==16)
            { 
                // B. Mendownload file musik,foto,film yang terdapat pada link yang sudah ditentukan
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
                sleep(10);
                // C. Melakukan unzip atau mengextract setelah didownload
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
                sleep(10);
                // A. Membuat Directory atau folder sesuai dengan ketentuan nama
                for (x=0;x<3;x++)
                {
                    child_id = fork();
                    if (child_id == 0) 
                    {
                        if (x==0)
                        {       
                            // Membuat directory baru
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
                sleep(10);
            }
            // Saat waktu menunjukkan ulang tahun stevany yaitu jam == 22 maka lakukan proses d, e, f
            if(jam==22)
            {
                // D. Setelah di extract maka file yang ada di folder sebelumnya dipindahkan ke directory baru yang sudah kita buat
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
                // E,F. Semua Folder akan di zip dan folder2nya akan dihapus
                child_id = fork();
                if (child_id == 0) 
                {
                    // Memasukkan 3 folder kedalam zip dan langsung menghapus foldernya.
                    char *argv[] = {"zip", "-r", "-m", "Lopyu_Stevany.zip", "Fyoto", "Musyik", "Fylm", NULL};
                    execv("/bin/zip", argv);
                }
            }
        }
    }
}
