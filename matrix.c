/*==========================================
  A matrix will be a 4xN array of doubles
  Each row will represent an [x, y, z, 1] point.
  For multiplication purposes, consider the rows like so:
  x0  x1      xn
  y0  y1      yn
  z0  z1  ... zn
  1  1        1
  ==========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m

print the matrix such that it looks like
the template in the top comment
*/
void print_matrix(struct matrix *m) {
  printf("\n~printing results~");
  int i, j;
  // for (i=0;i<m->rows;i++) {
  //   printf("\nRow %d: ", i);
  //   for (j=0;j<m->cols;j++) {
  //     printf("Col %d: %f", j, m->m[i][j]);
  //   }
  // }
  for (i=0; i < m->rows; i++) {
    printf("\nRow %d: ", i);
    for (j=0; j < m->cols; j++) {
      printf(" %f ", m->m[i][j]);
    }
  }
  printf("\n");
}

void oneTest(struct matrix *m) {
  printf("\n~making all into 1~");
  int i, j;
  for (i=0; i < m->rows; i++) {
    printf("\nRow %d: ", i);
    for (j=0; j < m->cols; j++) {
      m->m[i][j] = 1;
      printf(" %f ", m->m[i][j]);
    }
  }
  printf("Done with oneTest\n");
}

void randTest(struct matrix *m) {
  printf("\n~making all into 1~");
  int i, j;
  for (i=0; i < m->rows; i++) {
    printf("\nRow %d: ", i);
    for (j=0; j < m->cols; j++) {
      m->m[i][j] = j;
      printf(" %f ", m->m[i][j]);
    }
  }
  printf("Done with oneTest\n");
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  printf("\n~running through ident~");
  int i, j;
  int cur = 0;
  for (i=0; i < m->rows; i++) {
    printf("\nRow %d: ", i);
    for (j=0; j < m->cols; j++) {
      if (j == cur && i == cur){
        m->m[i][j] = 1;
        cur++;
      } else{
        m->m[i][j] = 0;
      }
      printf("  %f", m->m[i][j]);
    }
  }
  printf("\n");
}



/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b

multiply a by b, modifying b to be the product
a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int currArow,currBrow,currBcol,counter,bool; // iteration for loop variables
  counter = 1;
  currArow = 0;
  currBrow = 0;
  currBcol = 0;
  bool = 0;
  double a_fact, b_fact; // temp factor variables for the multiplation
  struct matrix *third;
  third = new_matrix(a->rows, b->cols); // creating third matrix
  printf("third matrix created with size: %d, %d\n", a->rows, b->cols);

  // first matrix
  int thirdRow = 0;
  int thirdCol = 0;
  int acol = 0;
  while (acol < a->cols) {
    // printf("\nCol for A %d:", acol);
    // printf("          row x col\n");
    // printf("Matrix A: %d x %d\n", currArow, acol);
    // printf(" %f         \n", a_fact = a->m[currArow][acol]);
    a_fact = a->m[currArow][acol];

    // second matrix
    // printf("  Row for B %d: ", currBrow);
    // printf("Matrix B: %d x %d", currBrow, currBcol);
    // printf(" %f \n", b_fact = b->m[currBrow][currBcol]);
    b_fact = b->m[currBrow][currBcol];

    currBrow++; //going down the columns
    // printf("THIRD BEFORE: %f", third->m[thirdRow][thirdCol]);
    // printf("THIRD: %f\n", third->m[thirdRow][thirdCol] += a_fact * b_fact );
    third->m[thirdRow][thirdCol] += a_fact * b_fact;
    acol++;

    // restarts while loop and goes to the next column in the second matrix
    // printf("Counter %d\n", counter);
    if (acol == a->cols && counter != a->rows * b->cols){
    // if (acol == a->cols && currArow + 1 != a->rows && currBrow != b->rows){
      // goes to the next row in the first matrix
      // printf("=================================b->cols : %d\n", b->cols);
      counter++;
      if (currBcol + 1 == b->cols && currBrow == b->rows){
        // printf("RESETING MATRIX B COLS" );
        currBcol = 0;
        currArow++;
      } else {
        currBcol++;
      }

        // printf("LOOP RESET\n");
        acol = 0;
        currBrow = 0;
        // printf("Same number go to next row %d\n", acol);
        // move the third matrix accordingly
        if ( thirdCol + 1 == third->cols && currBrow == b->rows){ // if at the end of the row restart and move to next row
          thirdCol = 0;
          thirdRow++;
          third->m[thirdRow][thirdCol] = 0;
          // printf("\nNeXT ROW %d\n", thirdRow);
        } else { // if not at the end of the row go to the next empty space
          thirdCol++;
          third->m[thirdRow][thirdCol] = 0;
          // printf("NeXT COL %d\n", thirdCol);
        }
    }
    // // goes to the next row in the first matrix
    // if (currBcol + 1 == b->cols && bool && currBrow + 1 == b->rows){
    //   printf("RESETING MATRIX B COLS" );
    //   currBcol = 0;
    //   currArow++;
    //   bool = 0; // turns off (becomes false) since it was already changed
    // } else if (currBcol + 1 == b->cols){
    //   printf("BOOL TURNEED ON==========");
    //   bool = 1; // turns on (becomes true) needs to be changed next time
    // }
    if (counter/4 == a->rows * b->cols) {
      printf("~Finishing matrix multi\n");
    }

  } // end of while loop

  // copy over third matrix into the second one
  copy_matrix(third, b);
  // printf("\n~running through copy~");
  // int i, j;
  // for (i=0; i < b->rows; i++) {
  //   printf("\nRow %d: ", i);
  //   for (j=0; j < b->cols; j++) {
  //     b->m[i][j] = third->m[i][j] ;
  //     printf(" %f ", b->m[i][j]);
  //   }
  // }
}



/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)calloc(rows , sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)calloc(cols , sizeof(double));
    }

  m=(struct matrix *)calloc(1, sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {
  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }

  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }

  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {
  int r, c;
  for (r=0; r < a->rows; r++){
    for (c=0; c < a->cols; c++){
      b->m[r][c] = a->m[r][c];
    }
  }
}
