/************************************************************************/
/* Получение информации о файле                                         */
/************************************************************************/
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
   struct stat file_stats;

   if (argc != 2)
   {
      fprintf(stderr, "Usage: file_info FILE...\n");
      exit(EXIT_FAILURE);
   }

   if (stat(argv[1], &file_stats) == -1)
   {
      perror("file_info");
      return EXIT_FAILURE;
   }

   printf("File name: %s\n", argv[1]);
   printf("Local drive: %lld\n", file_stats.st_dev);  /* Устройство */
   printf("Inod: %ld\n", file_stats.st_ino); /* Инод */
   printf("The number of hard links: %d\n", file_stats.st_nlink); /* Число жестких ссылок */
   printf("UID owner: %d\n", file_stats.st_uid);   /* UID владельца */
   printf("GID owner: %d\n", file_stats.st_gid);   /* GID владельца */
   printf("Device type: %lld\n", file_stats.st_rdev); /* Тип устройства */
   printf("Size in bytes: %ld\n", file_stats.st_size);   /* Общий размер в байтах */
   printf("Last access time: %ld : %s\n",
      file_stats.st_atime,
      ctime(&file_stats.st_atime));
   printf("Last change time: %ld : %s\n",
      file_stats.st_mtime,
      ctime(&file_stats.st_mtime));
   printf("Creation time: %ld : %s\n",
      file_stats.st_ctime, ctime(&file_stats.st_ctime));

   return EXIT_SUCCESS;
}