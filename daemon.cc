#include <iostream>
#include "ServerSocket.h"
#include <stdlib.h>
#include <string.h>
using namespace std;

long long TIME = 0;
char * MEMO, *DISK,*PROCESS;
void init()
{
  int len_file_str = 0;
  const char * memo1 = "echo ----------Memory---------- > ",
    * memo2 = " && free -m >> ",
    * disk1 = "echo ----------Disk Usage---------- >> ",
    * disk2 = " && df -h >> ",
    * process1 = "echo ----------Process---------- >> ",
    * process2 = " && top -b -n 1 >> ";
  char file_to_save[255];
  freopen("config.daemon","r",stdin);
  scanf("%s %Ld", file_to_save, &TIME);
  len_file_str = strlen(file_to_save);
  TIME *= 1000000; /*To microseconds*/

  MEMO = (char *)malloc( ( strlen(memo1) + 2*len_file_str + strlen(memo2) + 1)*sizeof(char));
  strcpy(MEMO,memo1);
  strcat(MEMO,file_to_save);
  strcat(MEMO,memo2);
  strcat(MEMO,file_to_save);
  /*puts(MEMO);*/

  DISK = (char *)malloc( ( strlen(disk1) + 2*len_file_str + strlen(disk2) + 1)*sizeof(char));
  strcpy(DISK,disk1);
  strcat(DISK,file_to_save);
  strcat(DISK,disk2);
  strcat(DISK,file_to_save);
  /*puts(DISK);*/

  PROCESS = (char *)malloc( ( strlen(process1) + 2*len_file_str + strlen(process2) + 1)*sizeof(char));
  strcpy(PROCESS, process1);
  strcat(PROCESS, file_to_save);
  strcat(PROCESS, process2);
  strcat(PROCESS, file_to_save);
  /*puts(PROCESS);*/

}
int main (int argc, const char * argv[]){
  init();
  int error = 1;
  int times = 0;
  while(true)
    {
      error = system(MEMO);
      error = system(DISK);
      error = system(PROCESS);
      printf("%d\n", times++);
      usleep(TIME);
    }

  return 0;
}

