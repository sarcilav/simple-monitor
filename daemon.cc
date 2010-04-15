#include <iostream>
#include "ServerSocket.h"
#include <stdlib.h>
using namespace std;

long long TIME = 0;
char * MEMO, * DISK,* PROCESS;
void init()
{
  string file_to_save,memo,disk,process;
  freopen("config.daemon","r",stdin);
  cin >> file_to_save >> TIME;

  memo = "echo ----------Memory---------- > "+file_to_save+" && free -m >> "+file_to_save;
  disk = "echo ----------Disk Usage---------- >> "+file_to_save+" && df -h >> "+file_to_save;
  process = "echo ----------Process---------- >> "+file_to_save+" && top -b -n 1 >> "+file_to_save;

  MEMO = (char *) memo.c_str();
  DISK = (char *) disk.c_str();
  PROCESS = (char *) process.c_str();

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
      usleep(TIME*1000000);
    }

  return 0;
}

