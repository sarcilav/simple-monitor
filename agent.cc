#include <iostream>
#include "ServerSocket.h"
#include <stdlib.h>
using namespace std;
int main (){

  ServerSocket agente(9000);
  FILE *input;
  int pid,error;
  char buffer[1024];
  string load;
  while(true)
    {
      ServerSocket new_socket;
      agente.accept(new_socket);
      pid = fork();
      if(pid<0)
        exit(-1);
      else if(pid == 0)
        {

          load = "";
          new_socket >> load;
          if(load != "")
            {
              error = 0;
              error = system("echo ----------Memory---------- > ServerLoad && free -m >> ServerLoad");
              error = system("echo ----------Disk Usage---------- >> ServerLoad && df -h >> ServerLoad");
              error = system("echo ----------Process---------- >> ServerLoad && top -b -n 1 >> ServerLoad");

            }
          else
            {
              exit(0);
            }
          input = fopen( "ServerLoad", "r" );
          while(fgets(buffer,1024,input))
            {
              new_socket << buffer;
            }
          fclose(input);
          new_socket.~ServerSocket();
          exit(0);

        }
      else
        new_socket.~ServerSocket();
    }

  return 0;
}

