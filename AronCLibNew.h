#ifndef ARONCLIBNEW
#define ARONCLIBNEW

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>

/**
@file

 @brief The library only use C99 standard library

 KEY: gcc -I$b/cpplib -o /tmp/AronCLibTest  $b/clib/AronCLibTest.c

 Move code from AronCLib.h to AronCLibNew.h
*/

const char* FALSE_RED = "\x1b[0;31m FALSE \x1b[0;0m";

// -------------------------------------------------------------------------------- 
// KEY: small test library
// compare c primitives
bool t_int(int n, int m, char* str);
bool t_intPtr(int m, int* ptr0, int n, int* ptr1, char* msg);
bool t_array_int(int m, int* ptr0, int n, int* ptr1, char* msg);
bool t_charPt(char* s1, char* s2, char* msg);
bool t_str(char* s1, char* s2, char* msg);
bool t_bool(bool a, bool b, char* msg);
bool t_voidPt(void* pt0, void* pt1, char* msg);
bool t_doublePt(int m, double* s1, int n, double* s2, char* msg);
// --------------------------------------------------------------------------------
void assert_c(bool b, char* str);


// -------------------------------------------------------------------------------- 

void pp(const char * format, ... );
void pl(const char * format, ... );
void fl();

int strToNumBase(const char* sp, int base);
void printArrayChar(const char* arr[], int size);
void printArraycharPt(char* arr, int len);
void printArrayfloat(float* arr, int len);
void printArrayint(int* arr, int len);
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

// -------------------------------------------------------------------------------- 
// KEY: print array
void print_array_int(int* pt, int len, int nCol);
void printArrayFixedint(int* pt, int len, int nCol);


void print_array_double(double* pt, int len, int nCol);
void printArrayFixedD(double* pt, int len, int nCol);


void print_array_float(float* pt, int len, int nCol);
void printArrayFixed(float* pt, int len, int nCol);
void print_matrix_int(int* arr, int len, int width);
void print_matrix_float(float* arr, int len, int width);

int maxLenStr_int(int* arr, int len);
int maxLenStr_float(float* arr, int len);
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// KEY: generate array
void gene_array_double(double* arr, int len);
void geneArrayDouble(double* arr, int len);

void gene_array_float(float* arr, int len);

// --------------------------------------------------------------------------------
int gcd_c(int m, int n);
int lcm(int m, int n);
int inx(int* arr, int i, int j, int w);
float inx_float(float* arr, int i, int j, int w);
// --------------------------------------------------------------------------------
void newline_c();



// BEG: Sat  4 May 12:52:20 2024 
typedef struct GroupFloat {
    float data;
    int count;
} GroupFloat;

// Compare GroupFloat according to count
int cmpGroupFloat(const GroupFloat* p1, const GroupFloat* p2) {
  return p1->count <= p2->count;
}

// Compare an GroupFloat
bool isEqualGroupFloat(GroupFloat *pt1, GroupFloat* pt2){
    return pt1->data == pt2->data && pt1->count == pt2->count;
}

bool cmpInt(const int* p1, const int* p2){
  return *p1 <= *p2;
}

void newline_c(){
  printf("\n");
}

void assert_c(bool b, char* str){
  if(!b){
	printf("ERROR: %s  arg => %s\n", __FUNCTION__, str);
	exit(1);
  }
}

// KEY: compare int array, array int
// NOTE: pt1[i] => pointer to int
//
// **pt1[i] == **(pt1 + i)
bool isEqualArrayInt(int** pt1, int** pt2, const int len){
  for(int i = 0; i < len; i++){
    // if(*pt1[i] != *pt2[i])
    if(**(pt1 + i) != **(pt2 + i))
      return false;
  }
  return true;
}

// Compare an array of GroupFloat
bool isEqualArrayGroupFloat(GroupFloat** pt1, GroupFloat** pt2, const int len){
    for(int i=0; i<len; i++){
        if(!isEqualGroupFloat(pt1[i], pt2[i]))
            return false;
    }
    return true;
}

bool compareArrayPt(float** arr1, float** arr2, int len) {
    if(arr1 != NULL && arr2 != NULL) {
        for(int i=0; i<len; i++) {
            if(arr1[i] != NULL && arr2[i] != NULL && *arr1[i] != *arr2[i])
                return false;
        }
    }
    return true;
}


bool cmpFloat(const float* p1, const float* p2) {
  return *p1 <= *p2;
}

// Compare two float array
bool compareArrayF(float* arr1, int len1, float* arr2, int len2) {
    if(arr1 != NULL && arr2 != NULL && len1 == len2) {
        for(int i=0; i<len1; i++) {
            if(arr1[i] != arr2[i])
                return false;
        }
    }
    return true;
}


// END: Sat  4 May 12:52:20 2024 

void swap(int* arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

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

bool t_intPtr(int len1, int* arr1, int len2, int* arr2, char* msg) {
  bool ret = true;
    if(arr1 != NULL && arr2 != NULL && len1 == len2) {
        for(int i=0; i<len1 && ret; i++) {
          ret = arr1[i] == arr2[i];
        }
    }
	  printf("t_intPtr [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
    if(!ret){
      for(int i = 0; i < len1; i++){
        printf("arr1[%d]=%d ", i, arr1[i]);
      }
      printf("\n");
      for(int i = 0; i < len2; i++){
        printf("arr2[%d]=%d ", i, arr2[i]);
      }
    }
    return ret;
}

bool t_array_int(int len1, int* arr1, int len2, int* arr2, char* msg) {
  t_intPtr(len1, arr1, len2, arr2, msg);
}


bool t_int(int m, int n, char* msg){
  bool ret = false;
  if(m == n){
    ret = true;
  }
	printf("t_int [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
  if(!ret){
    printf("m=%d n=%d\n", m, n);
  }
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

bool t_str(char* s1, char* s2, char* msg){
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
  printf("t_str [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
  return ret;
}



bool t_doublePt(int m, double* s1, int n, double* s2, char* msg){
    bool ret = true;
    if(m == n){
        for(int i = 0; i < n && ret; i++){
            if(s1[i] != s2[i]){
                ret = false;
            }
        }
    }
    printf("t_doublePt [%s] => %s\n", msg, ret ? "TRUE" : FALSE_RED);
    if(!ret){
      for(int i = 0; i < m; i++){
        printf("%f ", s1[i]);
      }
      printf("\n");
    }
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
void printArraycharPt(char* arr, int len){
  const int nRow= 10 + 1;
  for(int i=0; i<len; i++){
    if((i+1) % nRow != 0){
      printf("[ %c ]", arr[i]);
    }else{
      printf("\n[ %c ]", arr[i]);
    }
  }
}

void printArrayfloat(float* arr, int len){
  const int nRow= 10 + 1;
  for(int i=0; i<len; i++){
    if((i+1) % nRow != 0){
      printf("[ %f ]", arr[i]);
    }else{
      printf("\n[ %f ]", arr[i]);
    }
  }
}

void printArrayint(int* arr, int len){
  const int nRow= 10 + 1;
  for(int i=0; i<len; i++){
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


// BEG: print array float
void print_array_float(float* pt, int len, int nCol){
    for(int i = 0; i < len; i++){
        if((i + 1) % nCol != 0){
            printf("%.2f ", pt[i]);
        }else{
            printf("%.2f\n", pt[i]);
        }
    }
}

void printArrayFixed(float* pt, int len, int nCol){
  print_array_float(pt, len, nCol);
}
// END: print array float

// BEG: print array double
void print_array_double(double* pt, int len, int nCol){
    for(int i = 0; i < len; i++){
        if((i + 1) % nCol != 0){
            printf("%.2f ", pt[i]);
        }else{
            printf("%.2f\n", pt[i]);
        }
    }
}

void printArrayFixedD(double* pt, int len, int nCol){
  print_array_double(pt, len, nCol);
}
// END: print array double

// BEG: print array int
void print_array_int(int* pt, int len, int nCol){
    for(int i = 0; i < len; i++){
        if((i + 1) % nCol != 0){
            printf("%d ", pt[i]);
        }else{
            printf("%d\n", pt[i]);
        }
    }
}
void printArrayFixedint(int* pt, int len, int nCol){
  print_array_int(pt, len, nCol);
}
// END: print array int

/**
   Partition an array with pivot, return index of the pivot
   1, 2, 4, 3
   1 < 3
            1
   2 < 3
   1  2
   4 > 3
   1   2    4
   3 == 3
         3
   1 2	 3  4

   x
   2 3
   .
     x
   2 3
     .


   1 3 2
   x
     x
	   .
   1 2 3
       x
 */
int partition_array(int* arr, int lo, int hi) {
    int bigInx = lo;
    int pivotInx = lo;
    int pivot = arr[hi];
    for(int i = lo; i <= hi; i++) {
        if(arr[i] <= pivot) {
            swap(arr, bigInx, i);
            pivotInx = bigInx;
            bigInx++;
        }
    }
    return pivotInx;
}


void quick_sort(int* arr, int lo, int hi) {
    if(lo < hi) {
        int pivotInx = partition_array(arr, lo, hi);
        quick_sort(arr, lo, pivotInx - 1);
        quick_sort(arr, pivotInx + 1, hi);
    }
}

/*
  KEY: get current time, get time, nano second, time now
 
  struct timeval {
      time_t      tv_sec;     // seconds
      suseconds_t tv_usec;    // microseconds
  }

  FILE: /Users/aaa/myfile/github/c99/current_time_nano_second.c

  printf("Current time in seconds: %llu\n", time_second());
  printf("Current time in microseconds: %llu\n", time_micro());
  printf("Current time in nanoseconds: %llu\n", time_nano());

 */
uint64_t time_second(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec;
}

uint64_t time_micro() {
    struct timeval tv;
    uint64_t micro = 1E6;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * micro) + ((uint64_t)tv.tv_usec);
}

uint64_t time_nano() {
    struct timeval tv;
    uint64_t nano = 1E9;
    gettimeofday(&tv, NULL);
    return ((uint64_t)tv.tv_sec * nano) + ((uint64_t)tv.tv_usec * 1000);
}

/*
 * KEY: quick sort, partition
 *
 * */
long partition(long lo, long hi, int* arr){
  int piv = arr[hi];
  long bigInx = lo;
  for(long i = lo; i <= hi; i++){
    if(arr[i] <= piv){
      int tmp = arr[i]; 
      arr[i] = arr[bigInx];
      arr[bigInx] = tmp;
      if(i < hi)
        bigInx++;
    }
  }
  return bigInx;
}

/*
 * lo => begin index
 * hi => end   index
 * arr => input array
 */
void quickSortInt(long lo, long hi, int* arr){
  if(lo < hi){
    long pInx = partition(lo, hi, arr);
    quickSortInt(lo, pInx-1, arr);
    quickSortInt(pInx+1, hi, arr);
  }
}

// Partition an array of "any type", with comparator
int partitionAny(void** ls, int (*cmp)(const void *, const void *), int lo, int hi) {
    const int len = hi - lo + 1;
    int i=0;
    int j=len - 1;
    int k=lo;
    void* arr[len];
    
    if(len > 1) {
        // Use last element as pivot
        void* pivot = ls[hi];
        // if i == j then, the i or j is pivot position
        while(i != j) {
            if(cmp(ls[k], pivot)) {
                arr[i] = ls[k];
                i++;
            } else {
                arr[j] = ls[k];
                j--;
            }
            k++;
        }
        arr[i] = pivot;

        for(int i=0; i<len; i++) {
            ls[lo+i] = arr[i];
        }
    }
    return (lo + i);
}


// Quicksort any array type with comparator
void quickSortAny(void** ls, int (*cmp)(const void*, const void*), int lo, int hi) {
    if ( lo < hi) {
        int p = partitionAny(ls, cmp, lo, hi);
        quickSortAny(ls, cmp, lo, p-1);
        quickSortAny(ls, cmp, p+1, hi);
    }
}

void gene_array_int(int* arr, int len, int low, int high){
  long seed = 101;
  for(int i = 0; i < len; i++){
  	long r = randomNum(seed) % (high - low + 1) + low;
	seed = r;
	arr[i] = r;
  }
}

void fillArray(int* arr, int len, int low, int high){
  long seed = 101;
  for(int i = 0; i < len; i++){
  	long r = randomNum(seed) % (high - low + 1) + low;
	seed = r;
	arr[i] = r;
  }
}

void fillArrayStart(int* arr, int len, int init){
  for(int i = 0; i < len; i++){
	arr[i] = init + i;
  }
}

void fillArrayZero(int* arr, int len){
  for(int i = 0; i < len; i++){
	arr[i] = 0;
  }
}

void fillArraySame(int* arr, int len, int n){
  for(int i = 0; i < len; i++){
	arr[i] = n;
  }
}

//  0 < random value < 1
void gene_array_double(double* arr, int len){
    long range = 10000;
    long seed = time(NULL);
    int i = 0;
    while(i < len){
      long r = randomNum(seed);
      long m = r % range;
      double fn = m/(double)range;
      if(m != 0){
        arr[i] = fn;
        // printf("r=%d m=%d fn=%0.2f\n", r, m, fn);
        i++;
      }
      seed = r;
    }
}


/*
 *  Generate a random double array with 0 < value < 1
 *
 */
void geneArrayDouble(double* arr, int len){
  gene_array_double(arr, len);
}

void gene_array_float(float* arr, int len){
    long range = 10000;
    long seed = time(NULL);
    int i = 0;
    while(i < len){
      long r = randomNum(seed);
      long m = r % range;
      float fn = m/(float)range;
      if(m != 0){
        arr[i] = fn;
        // printf("r=%d m=%d fn=%0.2f\n", r, m, fn);
        i++;
      }
      seed = r;
    }
}

int gcd_c(int m, int n){
  assert_c(m >= 0 && n >= 0, "m >= 0 n >= 0");
  
  if(m == 0 && n == 0){
	printf("ERROR: m and n can be both zero.");
  }else{
	if(m == 0){
	  return n;
	}else if(n == 0){
	  return m;
	}else{
	  if(m < n){
		return gcd_c(n - m, m);
	  }else{
		return gcd_c(m - n, n);
	  }
	}
  }
}
int lcm(int m, int n){
  return (m * n) / gcd_c(m, n);
}

/*
 * one dim array to two dim array
 */
int inx(int* arr, int i, int j, int w){
  return arr[i*w + j];
}

float inx_float(float* arr, int i, int j, int w){
  return arr[i*w + j];
}

/*
 *  row r1 = row r0 - row r1,

     r0  2 3 4
	 r1  1 2 3 -
	 -----------
	 r1  1 1 1
 *
 */
void subRow(int* arr, int r0, int r1, int w){
  for(int i = 0; i < w; i++){
	arr[r1*w + i] = inx(arr, r0, i, w) - inx(arr, r1, i, w);
  }
}

/*
      n
      |
 *    2 x 1 2 3  <- r0
          2 4 6
 *
 *
 *
 */
void mulRow(int n, int* arr, int r0, int w){
  for(int i = 0; i < w; i++){
	arr[r0*w + i] = n* arr[r0*w + i];
  }
}

void concat_str(char* s1, char* s2, char* retBuf){
  strcpy(retBuf, s1);
  strcpy(retBuf + strlen(s1), s2);
}

void pad_left(char* arr, int n, int c, char* retBuf){
  char buf[50];
  for(int i = 0; i < n; i++){
	buf[i] = c;
  }
  buf[n] = '\0';
  concat_str(buf, arr, retBuf);
}

void pad_right(char* arr, int n, int c, char* retBuf){
  char buf[50];
  for(int i = 0; i < n; i++){
	buf[i] = c;
  }
  buf[n] = '\0';
  concat_str(arr, buf, retBuf);
}


/*
     const int len = 6;
	 const int width = 3;
     int arr[len] = {
					 1, 2, 3,
					 2, 4, 5,
					};
     int rowArr[width];
	 int r0 = 0;
	 get_row(arr, len, rowArr, r0, width);
  
 */
void get_row(int* arr, int len, int* rowArr, int rowInx, int width){
  for(int i = 0; i < width; i++){
	rowArr[i] = arr[rowInx * width + i];
  }
}

void get_col(int* arr, int len, int* colArr, int colInx, int width){
  int nRow = len / width;
  for(int i = 0; i < nRow; i++){
	colArr[i] = arr[width * i + colInx];
  }
}

void get_col_float(float* arr, int len, float* colArr, int colInx, int width){
  int nRow = len / width;
  for(int i = 0; i < nRow; i++){
	colArr[i] = arr[width * i + colInx];
  }
}


int maxLenStr_int(int* arr, int len){
  int max = 0;
  char buf[50];
  for(int i = 0; i < len; i++){
	sprintf(buf, "%d", arr[i]);
	int n = strlen(buf);
	if(n > max){
	  max = n;
	}
  }
  return max;
}

int maxLenStr_float(float* arr, int len){
  int max = 0;
  char buf[50];
  for(int i = 0; i < len; i++){
	sprintf(buf, "%0.2f", arr[i]);
	int n = strlen(buf);
	if(n > max){
	  max = n;
	}
  }
  return max;
}


int foldl_int(int(*pt)(int, int), int id, int* arr, int len){
  int acc = id;
  for(int i = 0; i < len; i++){
	 acc = (*pt)(acc, arr[i]);
	 printf("acc=%d\n", acc);
  }
  return acc;
}

float foldl_float(float(*pt)(float, float), float id, float* arr, int len){
  float acc = id;
  for(int i = 0; i < len; i++){
	 acc = (*pt)(acc, arr[i]);
  }
  return acc;
}

double foldl_double(double(*pt)(double, double), double id, double* arr, int len){
  double acc = id;
  for(int i = 0; i < len; i++){
	 acc = (*pt)(acc, arr[i]);
  }
  return acc;
}


/*
 KEY: print 2d array, print matrix

 */
void print_matrix_int(int* arr, int len, int width){
  int nRow = len / width;
  int nCol = width;
  char buf[50];
  
  int* maxArr = (int*)malloc(sizeof(int) * width);

  // type here
  int* colArr = (int*)malloc(sizeof(int) * nRow);
  
  for(int i = 0; i < width; i++){
	get_col(arr, len, colArr, i, nRow);
	int max = maxLenStr_int(colArr, nRow);
	maxArr[i] = max;
  }
  
  char pbuf[50];
  char rbuf[50];
  
  for(int i = 0; i < nRow; i++){
	for(int j = 0; j < width; j++){
	  char bufx[50];
	  int mx = maxArr[j];
	  int num = inx(arr, i, j, width);
	  sprintf(bufx, "%d", num);
	  int k = strlen(bufx);
	  int diff = mx - k;
	  pad_right(bufx, diff + 1, ' ', rbuf);
	  printf("%s", rbuf);
	  rbuf[0] = '\0';
	}
	newline_c();
  }
  free(maxArr);
  free(colArr);
}

void print_matrix_float(float* arr, int len, int width){
  int nRow = len / width;
  int nCol = width;
  char buf[50];
  
  int* maxArr = (int*)malloc(sizeof(int) * width);
  float* colArr = (float*)malloc(sizeof(float) * nRow);
  
  for(int i = 0; i < width; i++){
	get_col_float(arr, len, colArr, i, nRow);
	int max = maxLenStr_float(colArr, nRow);
	maxArr[i] = max;
  }
  
  char pbuf[50];
  char rbuf[50];
  
  for(int i = 0; i < nRow; i++){
	for(int j = 0; j < width; j++){
	  char bufx[50];
	  int mx = maxArr[j];
	  float num = inx_float(arr, i, j, width);
	  sprintf(bufx, "%0.2f", num);
	  int k = strlen(bufx);
	  int diff = mx - k;
	  pad_right(bufx, diff + 1, ' ', rbuf);
	  printf("%s", rbuf);
	  rbuf[0] = '\0';
	}
	newline_c();
  }
  free(maxArr);
  free(colArr);
}



void merge_int(int* a, int lo, int mid, int hi){
  int len = hi - lo + 1;
  int* arr = (int*)malloc(sizeof(int) * len);
  int x0 = lo;
  int x1 = mid + 1;
  int k = 0;
  
  while( x0 <= mid || x1 <= hi){
	if(x0 > mid){
      arr[k] = a[x1];
	  x1++;
	}else if(x1 > hi){
	  arr[k] = a[x0];
	  x0++;
	}else{
	  if(a[x0] < a[x1]){
		arr[k] = a[x0];
		x0++;
	  }else{
		arr[k] = a[x1];
		x1++;
	  }
	}
	k++;
  }
  for(int i = 0; i < k; i++){
	a[lo + i] = arr[i];
  }
  free(arr);
}

void mergeSort(int* a1, int lo, int hi){
  if(lo < hi){
  int mid = (lo + hi)/2;
  mergeSort(a1, lo, mid);
  mergeSort(a1, mid + 1, hi);
  merge_int(a1, lo, mid, hi);
  }
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
    strcpy(pt[inx], line); // strcpy(destination, source), including null '\0'
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


#endif /* ARONCLIBNEW */
