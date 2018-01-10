File Edit Options Buffers Tools C Help
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int num, char* arg[]){
  if(num != 3)
    {
      fprintf(stderr, "Error: Can only handle 2 arguments");
      exit(1);
    }


  if(strlen(arg[1]) != strlen(arg[2]))
    {
      fprintf(stderr, "Error: Input string must be same length");
      exit(1);
    }

  int x, y;
  for (x = 0; x < strlen(arg[1]); x++){
    for(y = x + 1; y < strlen(arg[2]); y++){
      if(arg[1][x] == arg[1][y]){
        fprintf(stderr, "Error: First argument cannot contain duplicate words");
        exit(1);
      }
    }
  }
  int t;
  char b[1];
  while(read(0, b, 1) > 0){
    t = 0;
    for(x = 0; x < strlen(arg[1]); x++){
      if(arg[1][x] == b[0]){
        b[0] = arg[2][x]
        write(1, b, 1);
        t = 1;
        break;
      }
    }

    if(!t){
      write(1,b,1);
    }
  }
  return 0;
}
