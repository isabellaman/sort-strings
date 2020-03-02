/* Isabella Man
 * CSE 15
 * lab5
 * 12/4/19
 * Takes an array of strings of type char** and sorts each string alphabetically
 */

//-----------------------------------------------------------------------------
// Sort.c
//
// compile: gcc -std=c99 -o Sort Sort.c
//
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

#define MAX_STRING_LENGTH 100
// function prototype 
void extract_chars(char* a, char* s);

void printArray(char** A, int n){
   int i;
   for(i=0; i<=n; i++){
      printf("%s ", A[i]);
   }
   printf("\n");
}

void swap(char** A, int i, int j){
   char* temp;
   temp = A[i];
   A[i] = A[j];
   A[j] = temp;
}

int Partition(char** A, int p, int r){
   int i, j;
   char* x;
   x = A[r];
   i = p-1;
   for(j=p; j<r; j++){
      if (strcmp(A[j], x) < 0 || strcmp(A[j], x) == 0) {
         i++;
         swap(A, i, j);
      }
   }
   swap(A, i+1, r);
   return(i+1);
}

void QuickSort(char** A, int p, int r){
   int q;
   if( p<r ){
      q = Partition(A, p, r);
      QuickSort(A, p, q-1);
      QuickSort(A, q+1, r);
   }
}

int main(int argc, char** argv){
   FILE *in;
   FILE *out;

   char** listOfWords;		//an array of strings
   char* a;	
   char* line;			//string holding input
   int numWords;

   if ((in = fopen(argv[1], "r")) == NULL) {
      printf("Unable to read from file %s\n", argv[1]);
      exit(1);
   }

   line = calloc(MAX_STRING_LENGTH+1, sizeof(char));
   a = calloc(MAX_STRING_LENGTH+1, sizeof(char));

   fscanf(in, "%d", &numWords);
   listOfWords = calloc(numWords, sizeof(char*));

   int outer = 0;
   while (fgets(line, MAX_STRING_LENGTH, in) != NULL) {
      int count = 0;
      int i = 0; 
      while(line[i] != '\0' && i < MAX_STRING_LENGTH) {
         if (isalpha(line[i])) {
            a[count] = line[i];
            count++;
         }
         i++;
      }
      if(a[count] > 2) {
         a[count] = '\0';
      }
      char* temp = calloc(count+1, sizeof(char));
      strcpy(temp, a);
      listOfWords[outer] = temp;
      outer = outer + 1;
   }

   //printArray(listOfWords, numWords);
   QuickSort(listOfWords, 0, numWords-1);
   //printArray(listOfWords, numWords);

   if ((out = fopen(argv[2], "w")) == NULL) {
      printf("Unable to write to file %s\n", argv[1]);
      exit(1);
   }
   for (int i = 1; i <= numWords; i++) {
         fprintf(out, "%s\n", listOfWords[i]);
   }


   //free heap memory   
   for (int i = 0; i <= numWords; i++) {
      free(listOfWords[i]);
      listOfWords[i] = NULL;
   }

   free(a);
   free(line);
   
   a = NULL;
   line = NULL;
   
   fclose(in); 
   fclose(out);

   return(EXIT_SUCCESS);
}
