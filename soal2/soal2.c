#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

void splitFileName(char *namaFileAsli, char *fileName);

pid_t child1, child2, child3, child4, child5, child6;
int status;

int main(){

    //unzip file pets.zip ke dalam petshop
    child1 = fork();

    if(child1 == 0) {
        char *argv[] = {"unzip", "-q", "/home/putri/modul2/pets.zip", "-d", "/home/putri/modul2/petshop", NULL};
        execv("/usr/bin/unzip", argv);
    }
    
    waitpid(child1, &status, 0);

    //delete folder yang tidak diperlukan
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


	//split file yang mengandung dua kategori hewan
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

                    if(animalType2 != NULL) splitFileName(fileOriginPath, animalType2); //animalType2 != NULL artinya, file tsb terdiri dari dua hewan

                    splitFileName(fileOriginPath, animalType1); //animalType1 masuk ke fungsi split untuk extract jenis, nama, dan umur nya

                    //remove file setelah semua di split
                    child3 = fork();
                    if(child3 == 0) {
                        char *argv[] = {"rm", "-rf", fileOriginPath, NULL};
                        execv("/usr/bin/rm", argv);
                    }

                    waitpid(child3, &status, 0);
                }
            }
        }
    }

}

//fungsi untuk split nama file, dan mengkategorikan nya
void splitFileName(char *namaFileAsli, char *fileName) {

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

    //membuat folder;
    child4 = fork();

    if(child4 == 0) {
        char *argv[] = {"mkdir", "-p", folderCategory, NULL};
        execv("/usr/bin/mkdir", argv);
    }
    waitpid(child4, &status, 0);

    //copy file ke folder
    child6 = fork();

    if(child6 == 0) {
        char *argv[] = {"cp", namaFileAsli, animalFileName, NULL};
        execv("/usr/bin/cp", argv);
    }
    waitpid(child6, &status, 0);
     
    sprintf(desc, "nama : %s \numur : %s\n\n", name, age);

    //membuat file keterangan.txt
    FILE *file;
    file = fopen(fileKet, "a");

    if(file) {
        fprintf(file, "%s", desc);
        fclose(file);
    }
}
