#include <iostream>
#include "ServerSocket.h"
#include <stdlib.h>
using namespace std;
int main (){

  ServerSocket agente(9000);
  while(true)
    {
      ServerSocket new_socket;
      agente.accept(new_socket);
      int pid = fork();
      if(pid<0)
        exit(-1);
      else if(pid == 0)
        {

          string load ="";
          new_socket >> load;
          if(load != "")
            {
              int error = 0;
              error = system("echo ----------Memory---------- > ServerLoad && free -m >> ServerLoad");
              error = system("echo ----------Disk Usage---------- >> ServerLoad && df -h >> ServerLoad");
              error = system("echo ----------Process---------- >> ServerLoad && top -b -n 1 >> ServerLoad");

            }
          else
            {
              exit(0);
            }
          FILE *input = fopen( "ServerLoad", "r" );
          load = "";
          char buffer[1024];
          while(fgets(buffer,1024,input))
            {
              load = buffer;
              load += "\n";
              new_socket << load;

            }
          new_socket.~ServerSocket();
          exit(0);
        }
      else
        new_socket.~ServerSocket();
    }

  return 0;
}

