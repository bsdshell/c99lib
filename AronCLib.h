#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define DoubleLinkedList

/**
 @file

 @brief The library only use C99 standard library

 KEY: gcc -I$b/cpplib -o /tmp/AronCLibTest  $b/clib/AronCLibTest.c

 Saturday, 23 October 2021 18:33 PDT
 NOTE: Use $b/clib/AronCLibNew.h instead
 
*/
 void ppp(const char * format, ... );
bool BinarySearch(int arr[], int lo, int hi, int k);
bool compareArrayF(float* arr1, int len1, float* arr2, int len2);
bool compareArray(char* arr1, int len1, char* arr2, int len2);
bool cmp(float *a, float* b);  
const int MAXDIGIT = 20;
const bool RUNTEST = false;


// Begin Double Linkedlist
// DDL_beg
#ifdef DoubleLinkedList
typedef struct CNode {
  struct CNode* prev;
  struct CNode* next;
  void* data;
} CNode;

CNode* createNode(void *data){
  CNode* pt = (CNode*)malloc(sizeof(CNode));
  pt -> prev = NULL;
  pt -> next = NULL;
  pt -> data = data;
  return pt;
}

// 24-05-2021
// There is error here
void freeNode(CNode* nodePt, void (*freeObject)(void *)){
  if(nodePt != NULL){
    
    nodePt -> prev = NULL;
    nodePt -> next = NULL;
    
    (*freeObject)(nodePt -> data);
    free(nodePt);
    nodePt = NULL;
  }
}


typedef struct List{
  int size;
  CNode* head;
  CNode* tail;
  int (*compareTo)(const void*, const void*);
  char* (*toString)(void*);
  void (*freeObject)(void*);
  void (*addFirst)(struct List* list, CNode* node);
  void (*deleteFirst)(struct List* list);

}List;


List* createList(int (*compareTo)(const void*, const void*),
		 char* (*toString)(void*),
		 void (*freeObject)(void*)){
  List* pt = (List*)malloc(sizeof(List));
  pt -> size = 0;
  pt -> head = NULL;
  pt -> tail = NULL;
  pt -> compareTo = compareTo;
  pt -> toString = toString;
  pt -> freeObject = freeObject;
  return pt;
}

int compareTo(const int* pt1, const int* pt2){
  return 0;
}

char* toString(char* pt){
  return pt;
}

/*
char* toString(int* pt){
  return "toString";
}
*/

void freeObject(int* pt){
  // free(pt);
  // pt = NULL;
}

void freeInt(int* pt){
  free(pt);
}

void freeStr(char* pt){
  free(pt);
}

void freeList(List* list){
  /*
  CNode* curr = list -> head;

  CNode* next = curr -> next;
  // free(curr->next -> data);
  // free(curr);

  // free the first node ONLY
  freeNode(curr, freeObject);
  list -> head = next;
  */

  CNode* curr = list -> head;
  while(curr){
    CNode* prev = curr;
    curr = curr -> next;
    freeNode(prev, freeObject);
  }
  // list -> head = NULL;
}

/**
TODO: fixme, there is error when freeNode is used
FIXME: DO NOT need to free memory if no memory is allocated
     int n1 = 10
     CNode* node = createNode(&n1);
free(nodePt->data) cause error because nodePt->data is not allocated

int n2 = 3;
CNode* nodePt = createNode(&n2);
*/
void deleteFirst(List* list){
  if(list != NULL){
    if(list -> head != NULL){
      CNode* head = list -> head;
      list -> head = head -> next;
      head -> next = NULL;
      if(list -> head){
	list -> head -> prev = NULL;
      }else{
	// only one node
	list -> head = list -> tail = NULL;
      }
      list -> freeObject(head -> data);
      free(head);
      list -> size--;
      //// freeNode(nodePt, freeObject);
    }
  }
}

/**
           
 */
void deleteLast(List* list){
  if(list -> tail != NULL){
    CNode* tail = list -> tail;
    CNode* prev = tail -> prev;

    if(prev){
      prev -> next = NULL;
      tail -> prev = NULL;
      list -> tail = prev;
    }else{
      list -> head = list -> tail = NULL;
    }
    list -> freeObject(tail -> data);
    free(tail);
    list -> size--;
  }
}

/**
   
 */
void addFirst(List* list, CNode* nodePt){
  if(list -> head == NULL){
    list -> head = list -> tail = nodePt;
  }else{
    CNode* first = list -> head;
    nodePt -> next = first;
    first -> prev = nodePt;
    list -> head = nodePt;
    
    /*
    CNode* first = list -> head;
    list -> head = node;
    node -> next = first;
    first -> prev = node;
    */
  }
  list -> size++;
}


void addLast(List* list, CNode* nodePt){
  if(list -> tail == NULL){
    list -> head = list -> tail = nodePt;
  }else{
    CNode* tail = list -> tail;
    tail -> next = nodePt;
    nodePt -> prev = tail;
    list -> tail = nodePt;
  }
  list -> size++;
}

/**
   delete middle node
   M-x gx http://localhost/image/linkedlist34.jpg
 */
void deleteIndexNode(List* list, int index){
  if(0 <= index && index < list -> size){
    if(list -> size > 0){
      if(index == 0){ // first element
	deleteFirst(list);
      }else if(index == list -> size - 1){ // last element
	deleteLast(list);
      }else{
	// "middle" element
	CNode* curr = list -> head;
	int inx = 0;
	while(curr){
	  if(inx != index){
	    curr = curr -> next;
	    inx++;
	  }else{
	    // found element
	    CNode* prev = curr->prev;
	    CNode* next = curr->next;
	    curr -> prev = NULL;
	    curr -> next = NULL;
	    prev -> next = next;
	    next -> prev = prev;
	    freeNode(curr, list ->freeObject);
	    list -> size--;
	    break;
	  }
	}
      }
    }
  }
}

void printList(List* list){
  CNode* curr = list -> head;
  while(curr){
    printf("%s", list -> toString(curr -> data));
    curr = curr -> next;
  }
}

void printListNewLine(List* list){
  CNode* curr = list -> head;
  while(curr){
    printf("%s\n", list -> toString(curr -> data));
    curr = curr -> next;
  }
}
#endif
// DDL_end
// End Double Linked List


// Dynamic array
// BEG_DYNAMIC_ARRAY
// END_DYNAMIC_ARRAY

void ppp(const char * format, ... ){
    printf(format);
}


void t(bool predicate, char* str){
  printf("%s=>%s\n", str, predicate ? "true" : "false");
}

void assert(bool predicate, char* str){
  printf("%s=>%s\n", str, (predicate ? "true" : "false"));
}

void myassert(bool predicate, char arr[]){
   if(!predicate) {
       printf("%s", arr);
       exit(1);
   }
}

int max(int a, int b){
    return a < b ? b : a;
}

int minInt(int a, int b){
    return a < b ? a : b;
}

int minLong(long a, long b){
    return a < b ? a : b;
}

/**
* \brief check whether pt is NULL.
*/
bool isNull1(void* pt){
    if(pt == NULL){
        printf("Pointer is NULL.\n");
        return true; 
    }
    return false;
}

int factorial(int n){
    if(n == 0)
        return 1;
    else
        return n*factorial(n-1);
}

/*
  KEY: string to number, str to digit, convert string to number, string to int
 */
int strToNum(char* sp){
  int sum = 0;
  for(int i = strlen(sp) - 1; i >= 0; i--){
    int maxInx = strlen(sp) - 1;
    int c = sp[i] - '0';
    sum += c*pow(10, maxInx - i);
  }
  return sum;
}

bool notNull(void* pt){
    return !isNull1(pt);
}


// KEY: print array
// Move to AronCLibNew.h
// void printArray(char* arr, int arrSize){
  // const int nRow= 10 + 1;
  // for(int i=0; i<arrSize; i++){
    // if((i+1) % nRow != 0){
      // printf("[ %c ]", arr[i]);
    // }else{
      // printf("\n[ %c ]", arr[i]);
    // }
  // }
// }

/*
void printArray(float* arr, int arrSize){
  const int nRow= 10 + 1;
  for(int i=0; i<arrSize; i++){
    if((i+1) % nRow != 0){
      printf("[ %f ]", arr[i]);
    }else{
      printf("\n[ %f ]", arr[i]);
    }
  }
}
*/

int len(const char* s){
    return (int)strlen(s);
}

void plen(const char* msg, const char* s){
    printf("%s=%d\n", msg, len(s));
}


/**
 * \brief zero an array
 */
void zeroArrayInt(int* arr, const int n){
    for(int i=0; i<n; i++)
        arr[i] = 0;
}
void zeroArrayChar(char* arr, const int n){
    for(int i=0; i<n; i++)
        arr[i] = 0;
}

/**
 * \brief remove duplicate elements from char array, arr is modified
 * 
 */
void uniqueOrder(char* arr, int* n, const int NUM){
    int boolArr[NUM];
    int k = 0;
    int c = *n;
    zeroArrayInt(boolArr, NUM);
    for(int i=0; i<c; i++){
        int r = arr[i] % NUM;
        if(boolArr[r] == 0){
            boolArr[r] = 1;
            arr[k] = arr[i];
            k++;
        }
    }
    *n = k;
    arr[k] = '\0';
}

/**
 * \brief remove duplicate elements, oldPtr is not modified.
 * 
 * char* oldPtr = "abab"
 * char* newPtr = (char*) malloc((strlen(oldPtr)+1)*sizeof(char))
 * removeDuplicate(oldPtr, newPtr) => newPtr => "ab"
 * 
 */
void removeDuplicate(char* oldPtr, char* newPtr){
  char ascii[256];
  // initialize array to zero
  for(int i=0; i<256; i++)
    ascii[i] = -1;

  int k = 0;
  for(int i=0; i<strlen(oldPtr); i++){
    int inx = oldPtr[i];
    if(ascii[inx] == -1){
      newPtr[k] = inx;
       ascii[inx] = 1;
       k++;
    }
  }
  newPtr[k] = '\0';
}


/**
 * \brief remove index element from char*
    char arr[] = "abc";
    removeIndexChar(arr, 1) // => ac

    "ab" len = 2
    "b"
    "b\0"
    oldPtr = "b\0"
    --------------------------------------------------------------------------------
    NOTE: wrong way to use it. 
    char* arr = "abc";
    removeIndexChar(arr, 1) 
 */
void removeIndexChar(char arr[], int inx){
    int len = strlen(arr);
    if(inx < len){
        for(int i = 0; inx + i + 1 < len; i++){
            arr[inx + i] = arr[inx + i + 1];
        }
        arr[len - 1] = '\0';
    }
}

/**
   
 Drop n chars from the front
 
 dropChar(1, arr)
 a b c d '\n'
   b c d '\n'

 Drop n chars from the back
 
 dropChar(-1, arr)
 abcd'\n'
 abc'\n'
 
*/
void dropChar(int n, char arr[]){
    int len = strlen(arr);
    int absn = abs(n);
    if(absn <= len){
      int diff = len - absn;
      int i = 0;
      if(n > 0){
	for(i=0; i< diff + 1; i++)
	  arr[i] = arr[n + i];
      }else{
	arr[diff] = '\0';
      }
    }
}

/**

 NOTE: need to free(newArr)
 Drop n chars from the front, origin array is NOT modifed
 
 char* newArr = dropCharImmutable(1, arr)
 a b c d '\n'
   b c d '\n'
   

 Drop n chars from the back
 
 char* newArr = dropCharImmutable(-1, arr)
 abcd'\n'
 abc'\n'
 
*/
char* dropCharImmutable(int n, char arr[]){
  int len = strlen(arr);
  int absn = abs(n);
  char* newArr = NULL;
  if(absn <= len){
    int diff = len - absn;
    newArr = (char*)malloc(sizeof(char)*diff);
    if(n > 0){
      for(int i=0; i < diff + 1; i++)
	newArr[i] = arr[n + i];
    }else{
      for(int i=0; i < diff; i++){
	newArr[i] = arr[i];
      }
      newArr[diff] = '\0';
    }
  }
  return newArr;
}

/**
   \* zero or more occurrence previous character
   .  match single character
   

    regex => ""
    text  => ""
    
    start =  ""
    regex + 1 => '\0'

    regex => "."
    text  => "a"


    "a*"   => "", a, aa, aaa
    "a.*b" => ab, aab, acb
    ".*b"  => b, ab, ccb
    "*b", "b"

    ".*"
    "."
    "a*"
    regex = "."
    text  = "a"
    
    regex = ".*"
    text  = ""
    
    regex = "a*"
    text  = ""
    
    regex = "a*b"
    text  = "b"
    
    regex = ".*a"
    text  = "a"
    
    regex = ".*ab"
    text  = "ab"

    regex = ".*a."
    regex = "ab"
    
    start = regex[0];
    match(start, regex + 1, text)
 */
int match(char start, char* regex, char* text){
  if(regex[0] == '.'){
    return match(regex[0], regex + 1, text);
  }else if(regex[0] == '*'){
    if(start == '.'){
      
    }else{
      
    }
  }
  return 0;
}

void matchStart(char c, char* regex, char* text){
}


void takeChar(char arr[], const int n, char narr[]){
    int len = strlen(arr);
    int i = 0;
    for(i=0; i<minInt(n, len); i++)
        narr[i] = arr[i];
    narr[i] = '\0';
}

/**
   KEY: split string
   
   keymap for insert-image
   https://www.gnu.org/software/emacs/manual/html_node/elisp/Showing-Images.html
   + => increasing size
   - => decreasing size
   
   ht=__ tp://localhost/pdf/split_string.jpg
 */
List* splitStr(char* str){
  List* list = createList(compareTo, toString, freeStr);
  int k = 0;
  int ii = 0;
  for(int i = 0; i < strlen(str); i++){
    if(str[i] != ' '){
      if(k == 0)
	ii = i;
      k++;
    }else{
      if(k > 0){
	char* pt = (char*)malloc(sizeof(char*)*(k + 1));
	strncpy(pt, str + ii, k);
	pt[k] = '\0';
	CNode* nodePt = createNode(pt);
	addLast(list, nodePt);
	printf("[%s]\n", pt);
	k = 0;
      }
    }
  }
  if(k > 0){
    char* pt = (char*)malloc(sizeof(char*)*(k + 1));
    strncpy(pt, str + ii, k);
    pt[k] = '\0';
    CNode* nodePt = createNode(pt);
    addLast(list, nodePt);
    printf("[%s]\n", pt);
    k = 0;
  }
  return list;
}


void testit(char* pt){
  pt = (char*)malloc(sizeof(char)*10);
  strncpy(pt, "abc", 3);
  pt[3] = '\0';
  
}

/**
   KEY: trim leading and tailing whitespace

   char* str = "   a bc ";
   char* newStr = trim(str);
   t(cmpStr(newStr, "a bc"), "204 newStr => abc");
   free(newStr);
*/
char* trim(char* str){
  char* newStr = NULL;
  int slen = strlen(str); // NOT including '\0'
  if(slen == 0){
    newStr = (char*)malloc(sizeof(char));
    newStr[0] = '\0';
  }else{
    int lx = 0;
    int rx = slen - 1;
    while(lx <= rx && (str[lx] == ' ' || str[rx] == ' ')){
      if(str[lx] == ' '){
	lx++;
      }
      if(str[rx] == ' '){
	rx--;

      }
    }
    if(lx > rx){
      newStr = (char*)malloc(sizeof(char));
      newStr[0] = '\0';
    }else{
      newStr = (char*)malloc(sizeof(char)*(slen - lx - (slen - 1 - rx) + 1));
      strncpy(newStr, str + lx, slen - lx - (slen - 1 - rx));
      newStr[slen - lx - (slen - 1 - rx)] = '\0'; // null string
    }
  }
  return newStr;
}

/**
 * \brief shift n pos to the left 
 *
 *  a % b = c 
 *  a = mb + c 
 *  if a < 0
 *  -a = -mb - c
 *  -a = (-m)b - c
 *
 *  3 % 4 = 3
 *  -3 % 4 = -3 + 4 % 4 = 1 => (4 - 1) = 3 
 * <file:///Users/cat/myfile/bitbucket/math/negative_modulo.pdf negative_modulo.pdf>
 */
void shiftLeftChar(char arr[], const int n){
    int len = strlen(arr);
    char* charPtr = (char*)malloc(sizeof(char)*(len + 1));
    if(charPtr){
        strncpy(charPtr, arr, len);
        charPtr[len] = '\0';
        for(int i=0; i<len; i++){
            // negative modulo
            arr[i - n < 0 ? len + ((i - n) % len) : (i - n) % len] = charPtr[i];  // right shift n pos
        }
        arr[len] = '\0';
        if(charPtr)
            free(charPtr);
    }
}

/**
 * \brief shift n pos to the right
 *
 */
void shiftRightChar(char arr[], const int n){
    int len = strlen(arr);
    char* charPtr = (char*)malloc(sizeof(char)*(len + 1));
    if(charPtr){
        strncpy(charPtr, arr, len);
        charPtr[len] = '\0';
        for(int i=0; i<len; i++)
            arr[(i + n) % len] = charPtr[i];  // right shift n pos
        arr[len] = '\0';
        if(charPtr)
            free(charPtr);
    }
}

// 5 - 1 - 3 =
// abc[3]
// de
// void concat(char arr1[], char arr2[], char arr3[]){
    // int len1 = strlen(arr1);
    // int len2 = strlen(arr2);
    // int sum = len1 + len2; 
    // for(int i=0; i<sum; i++){
        // if(i < len1)
            // arr3[i] = arr1[i];
        // else
            // arr3[i] = arr2[i - len1];
        
    // }
    // arr3[sum] = '\0';
    
// }


// char* allocateNChar(int n){
    // char* pt = (char*)malloc(sizeof(char)*n);
    // return pt;
// }
// void deallocateNChar(char*& pt){
    // if(pt)
        // free(pt);
// }


/**
* \brief check whether pt1 or pt2 is NULL.
*
*/
bool isNull2(void* pt1, void* pt2){
    if(pt1 == NULL || pt2 == NULL){
        printf("char* is NULL.\n");
        return true; 
    }
    return false;
}


/**
 * \brief return true if both strings are equals, otherwise return false.
 */
bool isEqualStr(const char* ptr1, const char* ptr2){
    return strcmp(ptr1, ptr2) == 0;
}

/*
* \brief Compare two char*, compare string
*
*  strcmp(const char* ptr1, const char* ptr2)
*  ret < 0, ret == 0, ret > 0 
*
* 
* return : true or false 
*/
bool cmpStr(char* pt1, char* pt2){
    bool ret = true;
    if(isNull2(pt1, pt2) == false){
        int len = strlen(pt1);
        if(strlen(pt1) == strlen(pt2)){
            for(int i=0; i<len && ret; i++){
                if(pt1[i] != pt2[i]){
                    ret = false;
                }
            }
        }else{
            ret = false;
        }
    }else{
        exit(1);
    }
    return ret;
}
bool cmpStrN(char* pt1, char* pt2, int len){
    bool ret = true;
    for(int i=0; i < len && ret; i++){
        if (pt1[i] != pt2[i]){
            ret = false;
        }
    }
    return ret;
}




// concat two char* 
void concat(const char *s1, const char *s2, char* result) {
    const size_t len1 = strlen(s1);
    const size_t len2 = strlen(s2);
    if(result != NULL){
        memcpy(result, s1, len1);
        memcpy(result + len1, s2, len2 + 1); // +1 to copy the null-terminator
    }
}

// Assume the result is large enough
void copyStrAt(char* result, const char* source, int startIndex){
    if(strlen(result) >= strlen(source) + startIndex){
        memcpy(result + startIndex, source, strlen(source)); // NOT copy null from source
    }else{
        ppp("strlen(result)=%lu\n", strlen(result));
        ppp("strlen(source)=%lu\n", strlen(source)); 
        ppp("startIndex=%d\n", startIndex); 
        exit(EXIT_FAILURE);
    }
}


// Extract temp value from each row
int extract_temperature(char* line, char c, char tmp[MAXDIGIT]) {
    int delCount = 0;
    int k = 0;
    for(int i=0; i<strlen(line); i++) {
        if(line[i] != c) {
            if(delCount == 1) {
                if(line[i] == '.' || ('0' <= line[i] && line[i] <= '9')) {
                    tmp[k] = line[i];
                    k++;
                }
            }
        } else {
            delCount++;
            if(delCount > 1) {
                tmp[k] = '\0';
                break;
            }
        }
    }
    return 0;
}

// Compare two float pt
bool cmp(float *a, float* b) {
    return *a <= *b ? true : false;
}


// Partition an array of "any type", with comparator
/*
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
*/


// partition an array of float, return a pivot index
int partition(float* ls, int lo, int hi) {
    const int len = hi - lo + 1;
    int i=0;
    int k=lo;
    int j=len - 1;
    float arr[len];
    if(len > 1) {
        // Use last element as pivot
        float pivot = ls[hi];
        // if i == j then, the spot is pivot position
        while(i != j) {
            if(ls[k] <= pivot) {
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
    return k;
}

void quickSort(float *ls, int lo, int hi) {
    if ( lo < hi) {
        int p = partition(ls, lo, hi);
        quickSort(ls, lo, p-1);
        quickSort(ls, p+1, hi);
    }
}

float maxList(float* arr, int len){
    int lo = 0;
    int hi = len - 1;
    quickSort(arr, lo, hi);
    return arr[lo];
}



int compare(const void *p1, const void *p2){
    GroupFloat*  gp1 = (GroupFloat*)p1;  // cast void* => GroupFloat*
    GroupFloat*  gp2 = (GroupFloat*)p2;  // cast void* => GroupFloat*
    return gp1 -> count <= gp2 -> count;
}


bool compareArray(char* arr1, int len1, char* arr2, int len2) {
    if(notNull(arr1) && notNull(arr2) && len1 == len2) {
        for(int i=0; i<len1; i++) {
            if(arr1[i] != arr2[i])
                return false;
        }
    }
    return true;
}

bool cmpArrayStr(char* arr1, int len1, char* arr2, int len2){
  return compareArray(arr1, len1, arr2, len2);
}

float mean(float* arr, const unsigned int len) {
    if(len > 0) {
        float sum = 0.0;
        for(int i=0; i<len; i++)
            sum += arr[i];
        return sum/len;
    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}


float median(float* arr, const unsigned int len) {
    int lo = 0;
    int hi = len - 1;
    if(len > 0) {
        quickSort(arr, lo, hi);
        if(len % 2 == 1)
            return arr[(lo + hi)/2];
        else {
            int m = (lo + hi)/2;
            return (arr[m] + arr[m + 1])/2;
        }
    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}

// Group all continuous elements with counter
void group(float* arr, const unsigned int len, GroupFloat* tempInfo[], int* groupInx) {
    if(len > 0) {
        int max = 1;
        int count = 1;
        int tx = 0;
        tempInfo[tx]->data = arr[0];
        tempInfo[tx]->count = 1;

        for(int i=1; i<len; i++) {
            if(arr[i-1] == arr[i]) {
                count++;
            } else {
                // repeating count
                count = 1;
                // group
                tx++;
            }
            tempInfo[tx]->data = arr[i];
            tempInfo[tx]->count = count;
        }
        *groupInx = tx;
    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}

// Compute the most frequency of temprature.
/*
void modeInfo(float* arr, const unsigned int len, GroupFloat** tempGroup, int* nGroup) {
    int lo = 0;
    int hi = len - 1;
    if(len > 0) {
        int groupInx = -1;
        quickSort(arr, lo, hi);
        group(arr, len, tempGroup, &groupInx);
        if(groupInx >= 0) {
            quickSortAny((void**)tempGroup, compare, lo, groupInx);
            *nGroup = groupInx + 1;
        }
    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}
*/

/**
* Compute the most frequently occuring value
*
* tempGroup : Any array of GroupFloat
*
* nGroup : size of the array
*
* repeating : number of groups 
*
* result : console message 
* 
* msgLen : max length of "most frequently occuring value"
*
*/
void mode(GroupFloat** tempGroup, int nGroup, int* repeating, char* result, const int msgLen) {
    if(nGroup > 0){
        int repeatCount = 0;
        if(tempGroup[nGroup - 1]->count > 1){
            int last = nGroup - 1; 
            char strPt[msgLen];
            sprintf(strPt, "%2.3f K repeats %d times,", tempGroup[last]->data, tempGroup[last]->count);
            // concat(result, result, strPt);
            concat(strPt, result, result);
            int ix = last;
            repeatCount = 1;
            while(ix - 1 >= 0){
                if(ix - 1 >= 0 && tempGroup[last]->count == tempGroup[ix - 1]->count){
                    sprintf(strPt, "%2.3f K repeats %d times,", tempGroup[ix-1]->data, tempGroup[ix-1]->count);
                    // concat(result, result, strPt);
                    concat(strPt, result, result);
                    repeatCount++;
                }else{   
                    result[strlen(result) - 1] = '.';
                    break;
                }
                ix--;
            }
        }else{
            // concat(result, "", "There is no repeating temperature.");
            concat("", "There is no repeating temperature.", result);
        }
        *repeating = repeatCount;

    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}

void min_max(float* arr, int len, float* min, float* max){
    int lo = 0;
    int hi = len - 1;
    quickSort(arr, lo, hi);
    *min = arr[lo];
    *max = arr[hi];
}

float standarddeviation(float* arr, int len, float mean) {
    if(len > 0) {
        float sum = 0.0;
        for(int i=0; i<len; i++) {
            sum += fabsf(arr[i] - mean)*fabsf(arr[i] - mean);
        }
        return sqrt(sum/len);
    } else {
        fprintf(stderr, "len can not be zero.\n");
        exit(EXIT_FAILURE);
    }
}


bool compareGroupFloat(GroupFloat g1, GroupFloat g2) {
    return g1.data == g2.data && g1.count == g2.count;
}

bool compareGroupFloatList(GroupFloat** g1, GroupFloat** g2, int len) {
    for(int i=0; i<len; i++) {
        if((g1[i] != NULL && g2[i] != NULL && g1[i]->data != g2[i]->data) || g1[i]->count != g2[i]->count)
            return false;
    }
    return true;
}

/*
* Count the number of rows in CSV file
*
* fname : input file name
*
* return : number of rows
*/
int line_count(char fname[40]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fname, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    float sum = 0.0;
    int nrow = 0;
    float* arr = (float*)malloc(sizeof(float)*nrow);
    int inx = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char tmp[MAXDIGIT];
        extract_temperature(line, ',', tmp);
        if(strlen(tmp) > 0) {
            nrow++;
        }
    }


    if(fp != NULL)
        fclose(fp);
    if(line != NULL)
        free(line);
    if(arr != NULL)
        free(arr);

    return nrow;
}

/*
* Read file
*
* fname : file name
*
* arr : allocation memeory for temperature.
*
* nrow : size of arr
*
*/

void read_file(char fname[40], float* arr, int nrow) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(fname, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    float sum = 0.0;
    int k = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        char tmp[MAXDIGIT];
        extract_temperature(line, ',', tmp);
        if(strlen(tmp) > 0) {
            arr[k] = strtod(tmp, NULL);
            k++;
        }
    }
    if(fp != NULL)
        fclose(fp);
    if(line != NULL)
        free(line);
}

void repeat_c(int n, char c, char* result){
    for(int i=0; i < n; i++){
        result[i] = c;
    }
}

// KEY: count the number of lines in a file
int fileLineCount(char* fname){
  int count = 0;
  FILE* fp;
  fp = fopen(fname, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  
  while(!feof(fp)){
    char ch = fgetc(fp);
    if(ch == '\n')
      count++;
  }
  if(fp)
    fclose(fp);

  return count;
}


void free2d(void** pt, int len){
  for(int i = 0; i < len; i++)
    if(pt[i])
      free(pt[i]);
}

#if 0

/*
 Thu 23 Jun 20:32:02 2022 
 Moved to AronCLibNew.h

 NOTE: need to free pt from outside the function
 USE: free2d(pt, len)
**/
char** readFileToBuffer(char* fname, int *len){
  FILE* fp;
  char* line = NULL;
  ssize_t read;
  fp = fopen(fname, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  
  /* 
   char** -> pt[0] -> char* -> "abc"
   char** -> pt[1] -> char* -> "def"

      [0]    [1]
    ["abc", "efg"]
  */
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
#endif

/**
   KEY: getline
   https://man7.org/linux/man-pages/man3/getline.3.html
 */
void readFileToList(char* fname, List* list){
  FILE* fp;
  char* line = NULL;
  ssize_t read;
  fp = fopen(fname, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  if(list == NULL){
    ppp("Error list == NULL\n");
    exit(EXIT_FAILURE);
  }
  size_t maxLen = 0;
  while((read = getline(&line, &maxLen, fp)) != -1){
    // ppp("strlen(line)=[%d] maxLen=[%d]\n", strlen(line), maxLen);
    char* buffer = (char*)malloc(sizeof(char)*strlen(line));
    strcpy(buffer, line);

    CNode* nodePt = createNode(buffer);
    addLast(list, nodePt);
  }
  free(line);
  fclose(fp);
}

void readFileLine(char fname[40]){
  FILE* fp;
  char* line = NULL;
  size_t len = 0;
  ssize_t read;
  fp = fopen(fname, "r");
  if(fp == NULL){
    exit(EXIT_FAILURE);
  }
  
  while((read = getline(&line, &len, fp)) != -1){
    printf("%s", read, line);
  }
  if(fp)
    fclose(fp);
  if(line)
    free(line);
}

bool BinarySearch(int arr[], int lo, int hi, int k){
  if(lo <= hi){
    int m = (lo + hi)/2;
    if (k < arr[m]){
      return BinarySearch(arr, lo, m-1, k);
    }else if(k > arr[m]){
      return BinarySearch(arr, m+1, hi, k);
    }else{
      return k == arr[m];
    }
  }
  return false;
}

void summary(float mean, float median, char* mode, float max, float min, float stdev){
    printf("============================================================\n");
    printf("============================================================\n");
}
