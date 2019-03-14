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
