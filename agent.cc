#include <iostream>
#include "ServerSocket.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;
int main (){

  ServerSocket agente(9000);
  int pid = -1, error;
  char * buffer;
  string load;
  FILE * input;
  while(true)
    {
      ServerSocket new_socket;
      agente.accept(new_socket);
      pid = fork();
      if(pid<0)
        exit(-1);
      else if(pid == 0)
        {

          load ="";
          new_socket >> load;
          if(load != "")
            {
	      error = system("echo ----------Memory---------- > ServerLoad && free -m >> ServerLoad");
              error = system("echo ----------Disk Usage---------- >> ServerLoad && df -h >> ServerLoad");
              error = system("echo ----------Process---------- >> ServerLoad && top -b -n 1 >> ServerLoad");
	      
            }
          else
            {
              exit(0);
            }
          input = fopen( "ServerLoad", "r" );
	  buffer = (char *) malloc(1024 * sizeof(char));
          while(fgets(buffer,1024,input))
            {
	      new_socket << buffer;
            }
          fclose(input);
          new_socket.~ServerSocket();
	  free(buffer);
          exit(0);

        }
      else
	{
	  wait(NULL);
	  new_socket.~ServerSocket();
	}
    }

  return 0;
}

