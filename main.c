#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  clear_screen(s);
  struct matrix *edge1;
  struct matrix *edge2;
  struct matrix *edge3;
  struct matrix *m1;
  struct matrix *m2;
  // struct matrix *test;


  m2 = new_matrix(4, 2);
  printf("Testing add_edge. Adding (1, 2, 3), (4, 5, 6) m2 = ");
  // add_edge( m2,
  // 	       1.0, 2.0, 3.0,
  // 	       4.0, 5.0, 6.0);

  // same as this
  add_point(m2, 1.0, 2.0, 3.0);
  add_point(m2, 4.0, 5.0, 6.0);

  // printing matrix with added values
  print_matrix(m2);

  // matrix indent
  m1 = new_matrix(4,4);
  m1->lastcol = 4;
  ident(m1);
  printf("\nTesting ident. m1=\n");
  print_matrix(m1);

  // matrix mult
  printf("\nTesting matrix mult. m1 * m2=\n");
  matrix_mult(m1, m2);
  print_matrix(m2);

  m1->lastcol = 0;
  add_point(m1, 1.0, 2.0, 3.0);
  add_point(m1, 4.0, 5.0, 6.0);
  add_point(m1, 7.0, 8.0, 9.0);
  add_point(m1, 10.0, 11.0, 12.0);

  printf("\ntesting matrix mult. m1=\n");
  print_matrix(m1);

  printf("\ntesting matrix mult. m1 * m2 =\n");
  matrix_mult(m1,m2);
  print_matrix(m2);

  // image codee
  edge1 = new_matrix(4, 2000);
  edge2 = new_matrix(4, 2000);
  edge3 = new_matrix(4, 2000);

  int i;
  for (i = 0 ; i < 1000; i++) {
      add_edge(edge1,
	       250 + 100 * sin(M_PI * i/ 100), 250 + 100 * sin(M_PI * i* 100), 0,
	       250 + 100 * cos(2 * i * M_PI/ 10), 250 + 100 * cos(2 * i * M_PI* 10), 0);
      if (i > 900){
      add_edge(edge3,
         250 + 104 * cos(M_PI * i/ 100), 250 + 104 * sin(M_PI * i/ 100), 0,
         250 , 250 , 0);
       }
    }
    add_edge(edge2,
       250 + 200 * cos(M_PI * 100/ 100), 250 + 200 * sin(M_PI * 100/ 100), 0,
       250 + 200 * cos(2 * 100 * M_PI/ 10), 250 + 200 * sin(2 * 100 * M_PI/ 10), 0);

  color c;
  c.red = 35;
  c.green = 200;
  c.blue = 175;
  draw_lines(edge1, s, c);
  c.red = 235;
  c.green = 20;
  c.blue = 75;
  draw_lines(edge2, s, c);
  c.red = 210;
  c.green = 180;
  c.blue = 140;
  draw_lines(edge3, s, c);
  
  save_ppm(s, "matrix.ppm");
  save_extension(s, "matrix.png");
  printf("matrix.ppm and matrix.png");
  // display(s);
  free_matrix( m1 );
  free_matrix( m2 );
  free_matrix( edge1 );

  // edge1 = new_matrix(4, 4);
  // test = new_matrix(4, 4);
  // ident(edge1);
  // oneTest(test);
  // print_matrix(edge1);
  // print_matrix(test);
  // matrix_mult(edge1, test);

}
