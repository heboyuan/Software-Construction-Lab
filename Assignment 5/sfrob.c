#include <stdio.h>
#include <stdlib.h>

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
      if(putchar(strlist[x][y]) == EOF)
	{
	  fprintf(stderr, "Error: Can't write character");
	  exit(1);
	}
      if(strlist[x][y] == ' ')
	{
	  break;
	}
      y++;
    };
  }
}

int main(){
  char* str = (char*)malloc(sizeof(char));
  char ** strlist = (char**)malloc(sizeof(char*));
  
  if(str && strlist){
  }
  else{
    fprintf(stderr, "Error: Can't allocate space");
    exit(1);
  }
  
  int indstr = 0;
  int indstrlist = 0;
  char current = getchar();
  char next = getchar();
  while (current != EOF){
    if((current == ' ' && next == ' ')||(current == ' ' && next == EOF)){
      current = next;
      next = getchar();
    }
    else{
      str[indstr] = current;
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


      if (current == ' '){
	strlist[indstrlist] = str;
	char** nextlist = realloc(strlist, (indstrlist+2)*sizeof(char*));
	if(nextlist){
	  strlist = nextlist;
	  indstrlist++;
	  str = NULL;
	  str = (char*)malloc(sizeof(char));
	  indstr = 0;
	}
	else{
	  free(strlist);
	  fprintf(stderr, "Error: Can't allocate space");
	  exit(1);
	}
      }
      else if (next == EOF){
      	str[indstr] = ' ';
      	strlist[indstrlist] = str;
      	indstrlist++;
      }
      
      current = next;
      next = getchar();
    }
  }
  
  if(indstrlist != 0){
    qsort(strlist, indstrlist, sizeof(char*),cmp);
    print(strlist, indstrlist);
    int f;
    for(f = 0; f < indstrlist; f++){
      free(strlist[f]);
    }
    free(strlist);

    exit(0);
  }else{
    free(strlist);
    free(str);
  }
  
}
