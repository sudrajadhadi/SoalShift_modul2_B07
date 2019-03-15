# Penjelasan Soal Shift Modul 2

### Nomer 1
Diminta untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.

###### Jawab
Source Code: [Soal1.c](https://github.com/sudrajadhadi/SoalShift_modul2_B07/blob/master/Soal%201/soal1.c)

* Menyimpan data file dalam struct dirent dengan
  ```
  struct dirent *variabel
  ```
* Membuka direktori serta membaca file-file yang berada didalamnya
  ```
  DIR *directory;
  directory = opendir("/home/[user]/Documents/");
  ```
* Menghitung jumlah karakter agar dapat menemukan .png berada dalam indeks ke berapa dengan
  ```
  strlen(dir->d_name);
  ```
  Dan mengambil nama file dengan
    ```
    dir->d_name;
    ```
* Jika file tersebut merupakan file berekstensi png, maka nama file tersebut akan diubah menjadi [namafile]_grey.png
  ```
  if(nama[cpy-4] == '.' && nama[cpy-3]=='p' && nama[cpy-2]=='n' && nama[cpy-1] == 'g'){
		strcpy(namafile, "/home/user/modul2/gambar/");
		strcat(namafile, nama);
		cpy = (int)strlen(namafile);
		namafile[cpy-4] = '\0';
		strcat(namafile, "_grey.png");
  }
  ```
* Setelah berhasil diubah namanya, file tersebut dipindahkan menuju direktori /home/Documents/modul2/gambar
  ```
  char *argv[] = {"mv", nama, namafile, NULL};
	execv("/bin/mv", argv);
  ```
  
### Nomer 2
Diminta untuk menghapus file "elen.ku" setiap 3 detik dengan syarat owner dan groupnya adalah "www-data"

###### Jawab
Source Code : [Soal2.c](https://github.com/sudrajadhadi/SoalShift_modul2_B07/blob/master/soal%202/soal2.c)

* Disini saya menggunakan struct stat yang ada dalam c, dalam stat tersebut terdapat owner dan group pada file yang diminta, kemudian saya masukkan kedalam variabel bernama info
  ```
  struct stat info;
  stat("/home/ah/hatiku/elen.ku",&info);
  ```

* Karena progam akan berjalan dengan syarat owner dan groupnya adalah "www-data", maka saya membuat kondisi dengan membandingkan isi info dengan string "www-data"
  ```
  if(!strcmp(getpwuid(info.st_uid)->pw_name,"www-data") && !strcmp(getgrgid(info.st_gid)->gr_name,"www-data"))
  ```
  
* Karena terdapat masalah pada permission, maka diminta untuk mengubah permissionnya menjadi 777
  ```
  chmod("/home/ah/hatiku/elen.ku", 0777);
  ```
  
* setelah semua kondisi terpenuhi, maka file tinggal dihapus dengan format
  ```
  remove("/home/ah/hatiku/elen.ku");
  ```
  
* Karena progam akan berjalan setiap 3 detik sekali, maka menggunakan fungsi sleep selama 3 detik
  ```
  sleep(3);
  ```
### Nomer 3
Diminta untuk extract file campur2.zip dan menyimpan daftar file berekstensi .txt kedalam file bernama daftar.txt

##### Jawab
Source Code : [Soal3.c](https://github.com/sudrajadhadi/SoalShift_modul2_B07/blob/master/soal%203/soal3.c)

* Pertama diminta untuk mengextract file campur2.zip
  ```
  execl("/usr/bin/unzip", "unzip", "campur2.zip", NULL);
  ```
  
* kemudian membuat file daftar.txt untuk menyimpan daftar file berformat .txt yang ada pada folder campur2
  ```
  execlp("touch", "touch", "daftar.txt", NULL);
  ```
  
* dengan menggunakan fungsi pipe() dan dup2() kita dapat menyimpan daftar isi file yang ada pada folder campur2
  ```
  pipe(to);
  close(to[0]);
  
  dup2(to[1], STDOUT_FILENO);
  execlp("ls", "ls", "campur2", NULL)
  ```
  
* karena yang diminta adalah file yang berformat .txt maka di buat kondisi agar yang tertulis dalam file daftar.txt hanya file berformat .txt
  ```
  if (strstr(&temp[strlen(temp)-5], ".txt") != NULL)
  ```
### Nomer 4
Membuat progam untuk membuat file makan_sehat1.txt hingga tak terhingga dengan syarat file makan_enak.txt telah dibuka dalam kurun waktu 30 detik

##### Jawab
Source Code : [Soal4.c](https://github.com/sudrajadhadi/SoalShift_modul2_B07/blob/master/soal%204/soal4.c)

* pertama membuat perbandingan waktu, antara waktu yang sekarang dengan waktu terakhir file di buka, sama seperti soal ke 2, kali ini juga menggunakan fungsi stat untuk mendapatkan waktu file terakhir dibuka
  ```
  int dif = difftime(now, info_file.st_atime); 
  ```
  
* karena yang diminta syaratnya dalam kurun waktu 30 detik, maka dibuatkan kondisi
  ```
  if(dif<=30)
  ```
  
* setelah syarat terpenuhi, maka membuat file dengan format "makan_sehat[counter].txt", dengan variabel counter adalah increment dimulai dengan angka 1
  ```
  strcpy(path, "/home/its_time_to/Documents/makan");
  sprintf(str,"_sehat%d.txt",counter );
  strcat(path,str);
  ```

### Nomer 5

###### Jawab
Source Code: [Soal5.c](https://github.com/sudrajadhadi/SoalShift_modul2_B07/blob/master/soal%205/soal5.c)

* Mengambil localtime untuk membuat folder dengan
    ```
    time_t t = time(NULL);
    struct tm current = *localtime(&t);
    ```
* Membuat format direktori menjadi dd:mm:yyyy-hh:mm dengan
    ```
    sprintf(folder,"%d:%d:%d-%d:%d", current.tm_mday, current.tm_mon+1, current.tm_year+1900, current.tm_hour, current.tm_min);
    strcat(dir, folder);
    ```
* Membuat direktori tersebut dan mengubah hak aksesnya
    ```
    mkdir(dir, 0777);
    ```
* Membuat file log#.log tiap menit yaitu sleep(60) dari syslog
    ```
    while(i < 30){
            syslog = fopen("/var/log/syslog", "r");
            char file[100];
            char c;
            FILE *logbaru;
	    i++;
            sprintf(file, "%s/log%d.log", dir, i);
            logbaru = fopen(file, "w");
            while(fscanf(syslog, "%c", &c) != EOF) fprintf(logbaru, "%c", c);
            fclose(logbaru);
            fclose(syslog);
            sleep(60);
    }
    ```
    Loop diatas: membuka syslog dan menyimpan isinya kedalam log#.log
