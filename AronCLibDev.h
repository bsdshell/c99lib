#ifndef ARONCLIBDEV
#define ARONCLIBDEV

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct pair{
  int x;
  int y;
} pair;

void print_pair(pair p){
  printf("x=%d y=%d", p.x, p.y);
}

pair fun3(int a, int b){
  pair p;
  p.x = a;
  p.y = b;
  return p;
}

void fun(int* arr, int len, int width){
  int nRow = len / width;
  for(int i = 0; i < nRow; i++){
	for(int j = 0; j < width; j++){
	  printf("%d ", arr[width*i + j]);
	}
	printf("\n");	
  }
}

void rowDiv(int n, int* arr, int r0, int w){
  for(int i = 0; i < w; i++){
	arr[r0*w + i] = arr[r0*w + i]/n;
  }
}


int gcd_array(int* arr, int len){
  if(len > 0){
	int a = arr[0];
	if(len > 1){
		for(int i = 1; i < len; i++){
		  int b = arr[i];
		  printf("i=%d a=%d b=%d\n", i, a, b);
		  a = gcd_c(a, b);
		}
	}
	return a;
  }else{
	printf("ERROR: len=%d", len);
  }
}

void remove_zero(int* arr, int len){
  int k = 0;
  int i = 0;
  int j = len - 1;
  while(i < j){
	while(arr[i] != 0){
	  i++;
	}
	while(arr[j] == 0){
	  j--;
	}
	if(i < j){
	  swap(arr, i, j);
	  i++;
	  j--;
	}
  }
}
int gcd_array_positive(int* arr, int len){
  int k = 0;
  int* buf = (int*)malloc(sizeof(int)*len);
  for(int i = 0; i < len; i++){
	if(arr[i] != 0){
	  buf[k] = arr[i];
	  k++;
	}
  }
  if(k > 0){
	int a = buf[0];
	if(k > 1){
	  for(int i = 1; i < k; i++){
		int b = arr[i];
		printf("i=%d a=%d b=%d k=%d\n", i, a, b, k);
		a = gcd_c(abs(a), abs(b));
	  }
	}
	free(buf);
	return a;
  }else{
	return -1;
  }
}

/*
  int array to char* or string
 */
void arrToStr_int(int* arr, int len, char** strArr){
  for(int i = 0; i < len; i++){
	sprintf(strArr[i], "%d", arr[i]);
  }
}

void** malloc2d(int hight, int width, char* type){
  if(strcmp(type, "int") == 0){
	int** pt = (int**)malloc(sizeof(int*)*hight);
	for(int i = 0; i < hight; i++){
	  pt[i] = (int*)malloc(sizeof(int) * width);
	}
	return pt;
  }else if(strcmp(type, "char") == 0){
	char** pt = (char**)malloc(sizeof(char*)*hight);
	for(int i = 0; i < hight; i++){
	  pt[i] = (char*)malloc(sizeof(char) * width);
	}
	return pt;
  }else{
	printf("Invalid type");
  }
}

/*
 NOTE: The determinant is different after matrix_reduce
 TODO: Fix the determinant of the matrix

 */
void matrix_reduce(int* arr, int len, int width){
  // const int len = 16;
  //const int width = 4;
	int nRow = len / width;
	// gene_array_int(arr, len, 1, 9);

	int factor = 1;
	for(int i = 0; i < nRow; i++){
	  for(int j = 0; j < width; j++){
		int r0 = i;
		int r1 = r0 + 1 + j;
		
		if(r1< width){
		  int i0 = inx(arr, r0, i, width);
		  int i1 = inx(arr, r1, i, width);
		  if(i0 != 0 && i1 != 0){
			int c = lcm(abs(i0), abs(i1));
			printf("lcm=%d\n", c);
			fw("print_array_int");
			print_matrix_int(arr, len, width);
		  
			printf("i0=%d\n", i0);
			printf("i1=%d\n", i1);
		  
			int fac1 = c/i0;
			mulRow(fac1, arr, r0, width);
			factor *= fac1;
			fw("mulRow 1");
			print_matrix_int(arr, len, width);

			int fac2 = c/i1;
			mulRow(fac2, arr, r1, width);
			factor *= fac2;
			fw("mulRow 2");
			print_matrix_int(arr, len, width);
		  
			subRow(arr, r0, r1, width);
			fw("subRow 1");
			print_matrix_int(arr, len, width);
		  }
		}
	  }
	}
	
	printf("factor=%d\n", factor);

	int gfact = 1;
	for(int i = 0; i < nRow; i++){
	  int rowBuf[width];
	  get_row(arr, len, rowBuf, i, width);
	  fw("rowBuf");
	  print_array_int(rowBuf, width, 1);
	  int g = gcd_array_positive(rowBuf, width);
	  printf("gcd()=%d\n", g);
	  rowDiv(g, arr, i, width);
	  gfact *= g;
	}
	print_matrix_int(arr, len, width);
	printf("gfact=%d\n", gfact);

	int gg = gcd_c(factor, gfact);
	printf("gg=%d\n", gg);
    float nn = (float)gfact / factor;
	printf("nn=%f\n", nn);
}

int add(int a, int b){ return a + b; };
int mul(int a, int b){ return a * b; };

void intToStr_c(char* buf, int n){
  sprintf(buf, "%d", n);
}

void floatToStr_c(char* buf, float n){
    sprintf(buf, "%0.2f", n);
}

void doubleToStr_c(char* buf, double n){
    sprintf(buf, "%0.2f", n);
}

#endif /* ARONCLIBDEV */
