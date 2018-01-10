#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

int frobcmp(char const * a, char const * b){
  while(1){
    if (*a == ' ' && *b == ' ')
      return 0;
    else if (*a == ' ' || ((*a^42) < (*b^42)))
      return -1;
    else if (*b == ' ' || ((*a^42) > (*b^42)))
      return 1;
    a++;
    b++;
  }
}

int cmp(const void* aa, const void* bb)
{
  const char* a = *(const char**)aa;
  const char* b = *(const char**)bb;
  return frobcmp(a,b);
}

int print(char**strlist, int wordNum){
  size_t x;
  for( x = 0; x < wordNum; x++){
    size_t y = 0;
    while(1){
      if(write(1,&strlist[x][y],1) <= 0){
      	fprintf(stderr, "Error: Can't write character");
      	exit(1);
      }
      if(strlist[x][y] == ' '){
  	  break;
      }
      y++;
    };
  }
}

int main(){
  struct stat file;
  if(fstat(0,&file)<0){
    fprintf(stderr, "Error: Can't get file information");
    exit(1);
  }

  

  char curcha[1];
  char ** strlist;
  int indstrlist = 0;
  if(S_ISREG(file.st_mode)){
    int indfilestr;
    char* filestr = (char*)malloc((file.st_size+1)*sizeof(char));
    if (!filestr){
      fprintf(stderr, "Error: Can't allocate space");
      exit(1);
    }

    int x;
    if(read(0, filestr, file.st_size)){
      int wordCount = 0;
      filestr[file.st_size] = ' ';
      for(x = 1; x <= file.st_size; x++){
        if (filestr[x] == ' ' && filestr[x - 1] != ' '){
          wordCount ++;
        }
      }
      printf("%d\n", wordCount);
      strlist = (char**)malloc(wordCount*sizeof(char*));
      if(strlist){
        if(filestr[0] != ' '){
          strlist[0] = &filestr[0];
          indstrlist++;
        }
        for(x = 1; x < file.st_size; x++){
          if (filestr[x] != ' ' && filestr[x - 1] == ' '){
            strlist[indstrlist] = &filestr[x];
            indstrlist++;
          }
        }
      }else{
        fprintf(stderr, "Error: Can't allocate space");
        exit(1);
      }
    }else{
      fprintf(stderr, "Error: Can't read from file");
      exit(1);
    }
  }else{
    strlist = (char**)malloc(sizeof(char*));
  }

  int dynamic = indstrlist;
  printf("%d\n", indstrlist);

  char* str = (char*)malloc(sizeof(char));
  if(str && strlist){
  }
  else{
    fprintf(stderr, "Error: Can't allocate space");
    exit(1);
  }
  
  int indstr = 0;

  char current[1], next[1];
  int indcur = read(0, current, 1);
  int indnex = read(0, next, 1);

  while (indcur > 0){
    if((current[0] == ' ' && next[0] == ' ')||(current[0] == ' ' && indnex == 0)){
      current[0] = next[0];
      indnex = read(0, next, 1);
    
    }else{
      
      str[indstr] = current[0];
      char* nextstr = realloc(str, (indstr+2)*sizeof(char));
      
      if(nextstr){
      	str = nextstr;
      	indstr++;
      }
      else{
      	free(str);
      	free(strlist);
      	fprintf(stderr, "Error: Can't allocate space");
      	exit(1);
      }


      if (current[0] == ' '){
      	strlist[indstrlist] = str;
      	char** nextlist = realloc(strlist, (indstrlist+2)*sizeof(char*));
      	if(nextlist){
      	  strlist = nextlist;
      	  indstrlist++;
      	  str = NULL;
      	  str = (char*)malloc(sizeof(char));
      	  indstr = 0;
      	}else{
      	  free(strlist);
      	  fprintf(stderr, "Error: Can't allocate space");
      	  exit(1);
      	}
      }else if (indnex == 0){
        	str[indstr] = ' ';
        	strlist[indstrlist] = str;
        	indstrlist++;
      }

      current[0] = next[0];
      indcur = indnex;
      indnex = read(0, next, 1);
    }
  }
  
  if(indstrlist != 0){
    qsort(strlist, indstrlist, sizeof(char*),cmp);
    print(strlist, indstrlist);
    int f;
    for(f = 0; f < indstrlist; f++){
      printf("%d\n", f)
      printf("%s\n", **strlist[f])
      free(strlist[f]);
    }
    free(strlist);
  }else{
    free(strlist);
    free(str);
  }
  exit(0);
}
