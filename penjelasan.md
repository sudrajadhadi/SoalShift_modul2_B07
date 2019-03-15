# Penjelasan Soal Shift Modul 2

### Nomer 2
Di minta untuk menghapus file "elen.ku" setiap 3 detik dengan syarat owner dan groupnya adalah "www-data"

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
diminta untuk extract file campur2.zip dan menyimpan daftar file berekstensi .txt kedalam file bernama daftar.txt

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
