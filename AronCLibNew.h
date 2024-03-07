#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/**
 @file

 @brief The library only use C99 standard library

 KEY: gcc -I$b/cpplib -o /tmp/AronCLibTest  $b/clib/AronCLibTest.c

 Move code from AronCLib.h to AronCLibNew.h
*/

const char* FALSE_RED = "\x1b[0;31m FALSE \x1b[0;0m";

// -------------------------------------------------------------------------------- 
// compare c primitives
bool t_int(int n, int m, char* str);
bool t_charPt(char* s1, char* s2, char* msg);
bool t_bool(bool a, bool b, char* msg);
bool t_voidPt(void* pt0, void* pt1, char* msg);
// -------------------------------------------------------------------------------- 

void pp(const char * format, ... );
void pl(const char * format, ... );
void fl();

int strToNumBase(const char* sp, int base);
void printArrayChar(const char* arr[], int size);
void printArraycharPt(char* arr, int arrSize);
void printArrayfloat(float* arr, int arrSize);
void printArrayint(int* arr, int arrSize);
void printArray2dint(int height, int width, int** arr);
void printArray2df(int height, int width, float **arr);



char** splitPath(char* buf, int bufLen, int *retRow, char c);

char** splitStrChar(char* buf, int bufLen, int *retRow, char c);
void free_splitStrChar(char ** retppt, int retRow);
char** allocateCharPt(int nCol, int nRow);
void free_allocateCharPt(char** ppt, int nCol);
bool all_digit(char * str);
int strToInt(char* str);
int toLower(int c);
int toUpper(int c);
char* toUpperStr(char* s);
char* toLowerStr(char* s);
long LCG(long m, long a, long c, long seed);
long randomNum(long seed);
// char** readFileToBuffer(char* fname, int *len);
void free2d(void** pt, int len);
void printCharPt2d(char** pt, int nCol);
void printArrayFixed(float* pt, int len, int nCol);

// Linear Congruential Generator
long LCG(long m, long a, long c, long seed){
    long x0 = seed;
    long x1 = (a * x0 + c) % m;    
    return x1;
}

// KEY: random number
long randomNum(long seed){
    long m = (long)pow(2, 32);
    long a = 1664525;
    long c = 1013904223;
    long r = LCG(m, a, c, seed);
    return r;
}

void printCharPt2d(char** pt, int nCol){
  for(int i = 0; i < nCol; i++){
	printf("[%s]\n", pt[i]);
  }
}

/*
 *  char* s = "123"
 *  strToInt(s) => 123
 *
 *  ERROR: return -1
 */
int strToInt(char* str){
    int len = strlen(str);
    int sum = -1;
    if(all_digit(str)){
        sum = 0;
        for(int i = len - 1; i >= 0; i--){
            int p = pow(10, len - 1 - i);
            int n = str[i] - '0';
            sum += n*p;
            // printf("n=%d, p=%d\n", n, p);
        }
    }
    return sum;
}

/*
 *  char* str = "0123";
 *  all_digit(str) => true
 *
 *  char* str = "12abc";
 *  all_digit(str) => false 
 *
 */
bool all_digit(char * str){
    bool ret = false; 
    int len = strlen(str);

    if(len > 0){
        ret = true;
        for(int i = 0; i < len && ret; i++){
            if('0' <= str[i] && str[i] <= '9'){
            }else{
                ret = false;
            }
        }
    }
    return ret;
}

/**
 * 
 * int n = 3;
 * char c = 'a';
 * repeatChar(3, c) => "aaa"
 *
 * repeatChar(0, c) => ""
 *
 */
char* repeatChar(int n, char c){
    char* pt = (char*)malloc(sizeof(char)*(n + 1));
    int i = 0;
    for(i = 0; i < n; i++){
        pt[i] = c; 
    }
    pt[i] = '\0';
    return pt;
}


char** allocateCharPt(int nCol, int nRow){
  char** ppt = (char**)malloc(sizeof(char*)*nCol);
  for(int c = 0; c < nRow; c++){
	ppt[c] = (char*)malloc(sizeof(char)*nRow);
  }
  return ppt;
}

void free_allocateCharPt(char** ppt, int nCol){
  for(int c = 0; c < nCol; c++){
	if(ppt[c]){
	  free(ppt[c]);
	  ppt[c] = NULL;
	}
  }
  if(ppt){
	free(ppt);
  }
}

/**
 * KEY: file size, check file size
 * https://stackoverflow.com/questions/238603/how-can-i-get-a-files-size-in-c
 */
int fileSize(char* fname){
  FILE * fp = fopen(fname, "r");
  int sz = -1;
  if(fp == NULL){
	printf("Can not open file %s", fname);
	exit(EXIT_FAILURE);
  }else{
	int prev = ftell(fp);
	// SEEK from the beginning
	fseek(fp, 0L, SEEK_END);
	sz = ftell(fp);
	// Go back to previous position
	fseek(fp, prev, SEEK_SET);
  }
  return sz;
}

/**
   NOTE: There is bug on the function
   SEE: https://stackoverflow.com/questions/1735236/how-to-write-my-own-printf-in-c

   ERROR:
   pl("%g", atof("3.114"));
   printf("%g\n", atof("3.14159"));
 */
void pp(const char * format, ... ){
    printf(format);
}

/**
   NOTE: There is bug on the function
   SEE: https://stackoverflow.com/questions/1735236/how-to-write-my-own-printf-in-c
   
   ERROR:
   pl("%g", atof("3.114"));
   printf("%g\n", atof("3.14159"));
 */
void pl(const char * format, ... ){
  printf(format);
	printf("\n");
}

void fl(){
  char* pt = repeatChar(80, '-');
  printf("%s\n", pt);
  free(pt);
  pt = NULL;
}
void fw(char* s){
  int len = strlen(s);
  char* pt = repeatChar(80, '-');
  int start = (80 - len)/2;
  strncpy(pt + start, s, len);
  printf("%s\n", pt);
  free(pt);
  pt = NULL;
}

/*
  NOTE: Deprecated:
  USE: free_splitStrChar()
*/
void free_splitPath(char ** retppt, int retRow){
    for(int i = 0; i < retRow; i++){
        if(retppt[i]){
            free(retppt[i]);
            retppt[i] = NULL;
        }
    }
    if(retppt){
        free(retppt);
        retppt = NULL;
    }
}
/*
  NOTE: Deprecated:
  USE: splitStrChar()
 */
char** splitPath(char* buf, int bufLen, int *retRow, char c){
   int n = 1024;
   int k = 0;
   int count = 0;
   
   bool loop = true;
   bool endLoop = false;
   int maxRow = 2;
   int countRow = 0;
   int inxRow = 0;
   char** retppt = NULL;

   while(loop){
       retppt = (char**)malloc(sizeof(char*)*maxRow);
       for(int i = 0; i < maxRow; i++){
           retppt[i] = (char*)malloc(sizeof(char)*bufLen);
       }

       int inx = 0;
       for(inx = 0; inx < bufLen; inx++){
		 if(inxRow < maxRow){
		   if(buf[inx] != c){
			 retppt[inxRow][k] = buf[inx];
			 k++;
		   }else{
			 retppt[inxRow][k] = '\0';
			 inxRow++; 
			 k = 0;
		   }
		 }else{
		   free_splitPath(retppt, maxRow);
		   maxRow += 10;
		   inxRow = 0;
		   k = 0;
		   break;
		 }
	   }
	   
	   if(inx == bufLen){
		 if(k > 0){
		   retppt[inxRow][k] = '\0';
		   inxRow++;
		   k = 0;
		 }
		 
		 loop = false;
	   }
   }
   *retRow = inxRow;
   return retppt;
}

void free_splitStrChar(char ** retppt, int retRow){
    for(int i = 0; i < retRow; i++){
        if(retppt[i]){
            free(retppt[i]);
            retppt[i] = NULL;
        }
    }
    if(retppt){
        free(retppt);
        retppt = NULL;
    }
}

/*
    char * str = "/";
	int len = strlen(str);
    splitStrChar(str, len, retRow, '/')
	=> ["", "/", ""]
	
	char * str = "/f.x";
	int len = strlen(str);
	splitStrChar("/f.x", len, retRow, '/')
	=> ["", "/", "f.x"]
	
	char * str = "tmp/f.x";
	int len = strlen(str);
	splitStrChar("tmp/f.x", len, retRow, '/')
	=> ["tmp", "/", "f.x"]
	
	char * str = "/tmp/f.x";
	int len = strlen(str);
	splitStrChar("/tmp/f.x", len, retRow, '/')
	=> ["", "/", "tmp", "/", "f.x"]

	TODO: refactor the code,
 */
char** splitStrChar(char* buf, int bufLen, int *retRow, char c){
   int k = 0;
   bool loop = true;
   int maxRow = 2;
   int inxRow = 0;
   char** retppt = NULL;
   while(loop){
       retppt = (char**)malloc(sizeof(char*)*maxRow);
       for(int i = 0; i < maxRow; i++){
           retppt[i] = (char*)malloc(sizeof(char)*bufLen);
       }
       int inx = 0;
       for(inx = 0; inx < bufLen; inx++){
		 if(inxRow < maxRow){
		   if(buf[inx] != c){
			 retppt[inxRow][k] = buf[inx];
			 k++;
		   }else{
			 if(k >= 0){
			   // NOT '/'
			   retppt[inxRow][k] = '\0';
			   inxRow++;
			   if(inxRow < maxRow){
				 // '/'
				 retppt[inxRow][0] = c;
				 retppt[inxRow][1] = '\0';
			   }else{
				 free_splitStrChar(retppt, maxRow);
				 maxRow += 10;
				 inxRow = 0;
				 k = 0;
				 break;
			   }
			 }
			 inxRow++; 
			 k = 0;
		   }
		 }else{
		   free_splitStrChar(retppt, maxRow);
		   maxRow += 10;
		   inxRow = 0;
		   k = 0;
		   break;
		 }
	   }
	   
	   if(inx == bufLen){
		 if(inxRow < maxRow){
		   retppt[inxRow][k] = '\0';
		   inxRow++;
		   loop = false;
		 }else{
		   free_splitStrChar(retppt, maxRow);
		   maxRow += 10;
		   inxRow = 0;
		 }
		 k = 0;
	   }
   }
   *retRow = inxRow;
   return retppt;
}

int toLower(int c){
  return tolower(c);
}

int toUpper(int c){
  return toupper(c);
}

/*
  NOTE: free(pt)
 */
char* toUpperStr(char* s){
  int len = strlen(s);
  char* pt = (char*)malloc(sizeof(char)*(len + 1));
  int i = 0;
  for(i = 0; i < len; i++){
	pt[i] = toupper(s[i]);
  }
  pt[i] = '\0';
  return pt;
}

/*
  NOTE: free(pt)
 */
char* toLowerStr(char* s){
  int len = strlen(s);
  char* pt = (char*)malloc(sizeof(char)*(len + 1));
  int i = 0;
  for(i = 0; i < len; i++){
	pt[i] = tolower(s[i]);
  }
  pt[i] = '\0';
  return pt;
}


bool t_int(int n, int m, char* msg){
  bool ret = false;
    if(n == m){
	  ret = true;
    }
	printf("t_int [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
	return ret;
}

bool t_charPt(char* s1, char* s2, char* msg){
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    bool ret = true;
    if(n1 == n2){
        for(int i = 0; i < n1 && ret; i++){
            if(s1[i] != s2[i]){
                ret = false;
            }
        }
    }
	printf("t_charPt [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
	return ret;
}

bool t_bool(bool n, bool m, char* msg){
  bool ret = false;
    if(n == m){
	  ret = true;
    }
	printf("t_bool [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
	return ret;
}

bool t_voidPt(void* pt0, void* pt1, char* msg){
  bool ret = false;
  if(pt0 == pt1){
	ret = true;
  }
  printf("t_voidPt [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
  return ret;
}



/*

  KEY: concat ALL strings to ONE string
  
  pt[0] = "abc"
  pt[1] = "def"
  pt[2] = "hij"
  int len = 3
  char* str = concatStr(pt, len);
  str = "abcdefhij"

 */
char* concatStr(char** pt, int len){
  char* strPt = NULL;
  int k = 0;
  int nByte = 0;
  for(int i = 0; i < len; i++){
	nByte += strlen(pt[i]);
  }
  strPt = (char*)malloc(sizeof(char)*nByte);
  
  for(int i = 0; i < len; i++){
	int n = strlen(pt[i]);
	memcpy(strPt + k, pt[i], n);
	pt[i][n] = '\0';
	k += n;
  }

  return strPt;
}

void free_concatStr(char* strPt){
  if(strPt){
	free(strPt);
	strPt = NULL;
  }
}

// KEY: print array
void printArrayChar(const char* arr[], int size){
  for(int i = 0; i < size; i++){
    printf("[%s]", arr[i]);
  }
}

int strToNumBase(const char* sp, int base){
  int sum = 0;
  for(int i = strlen(sp) - 1; i >= 0; i--){
    int maxInx = strlen(sp) - 1;
    int c = sp[i] - '0';
    sum += c*pow(base, maxInx - i);
  }
  return sum;
}

// KEY: print array
void printArraycharPt(char* arr, int arrSize){
  const int nRow= 10 + 1;
  for(int i=0; i<arrSize; i++){
    if((i+1) % nRow != 0){
      printf("[ %c ]", arr[i]);
    }else{
      printf("\n[ %c ]", arr[i]);
    }
  }
}

void printArrayfloat(float* arr, int arrSize){
  const int nRow= 10 + 1;
  for(int i=0; i<arrSize; i++){
    if((i+1) % nRow != 0){
      printf("[ %f ]", arr[i]);
    }else{
      printf("\n[ %f ]", arr[i]);
    }
  }
}

void printArrayint(int* arr, int arrSize){
  const int nRow= 10 + 1;
  for(int i=0; i<arrSize; i++){
    if((i+1) % nRow != 0){
      printf("[%d]", arr[i]);
    }else{
      printf("\n[ %d ]", arr[i]);
    }
  }
  printf("\n");
}


/**
   	{
	  float arr[4][4] = {
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	  };
	  pl("");
	  printArray2df(4, 4, arr[0]);
	}
 */
void printArray2df(int height, int width, float** arr){
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
		  printf("%f ", arr[h][w]);
        }
        printf("\n");
    }
}

void printArray2dint(int height, int width, int** arr){
    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
		  // printf("%d ", *(arr + h*width + w));
		  printf("%-2d ", arr[h][w]);
        }
        printf("\n");
    }
}

void* mc(int n, char arr[10]){
  void *pt;
  if (strcmp(arr, "int") == 0){
	pt = (int*)malloc(sizeof(int) * n);
  }else if (strcmp(arr, "float") == 0){
	pt = (float*)malloc(sizeof(float) * n);
  }else if (strcmp(arr, "char") == 0){
	pt = (char*)malloc(sizeof(char) * n);
  }else if (strcmp(arr, "long") == 0){
	pt = (long*)malloc(sizeof(long) * n);
  }
  
  return pt;
}

void free2d(void** pt, int len){
  for(int i = 0; i < len; i++)
    if(pt[i])
      free(pt[i]);
}


/**
    NOTE: need to free pt from outside the function
    USE: free2d(pt, len)
    @
    int len = 10;
                                           + -> address of len 
    char* fname = "/tmp/x.x";              ↓ 
    char** pt = readFileToBufferX(fname, &len);
                                           ↑ 
                                           + -> len will be modifed inside the function
                                         
    printf("len=%d\n",len);
    for(int k = 0; k < len; k++){
        printf("%s\n", pt[k]);
    }

    free2d(pt, len);
    @
    
*/
/**
char** readFileToBuffer(char* fname, int *len){
  FILE* fp;
  char* line = NULL;
  ssize_t read;
  fp = fopen(fname, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  
  char** pt = (char**)malloc(sizeof(char*)*(*len));

  int inx = 0;
  size_t maxLen = 0;
  while((read = getline(&line, &maxLen, fp)) != -1){
    printf("read=%d line=%s", read, line);
    pt[inx] = (char*)malloc(sizeof(char)*(strlen(line) + 1));
    strcpy(pt[inx], line); // strcpy(source, destination), including null '\0'
    inx++;
  }
  *len = inx;
  
  if(fp)
    fclose(fp);
  if(line)
    free(line);
  return pt;
}
*/


