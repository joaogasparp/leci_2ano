//
// AED, August 2022 (TomÃ¡s Oliveira e Silva)
//
// First practical assignement (speed run)
//
// Compile using either
//   cc -Wall -O2 -D_use_zlib_=0 solution_speed_run.c -lm
// or
//   cc -Wall -O2 -D_use_zlib_=1 solution_speed_run.c -lm -lz
//
// Place your student numbers and names here
//   N.Mec. XXXXXX  Name: XXXXXXX
//

//
// static configuration
//

#define _max_road_size_  800  // the maximum problem size
#define _min_road_speed_   2  // must not be smaller than 1, shouldnot be smaller than 2
#define _max_road_speed_   9  // must not be larger than 9 (only because of the PDF figure)
//#define C_MAX 50

//
// include files --- as this is a small project, we include the PDF generation code directly from make_custom_pdf.c
//

#include <math.h>
#include <stdio.h>
#include "../P02/elapsed_time.h"
#include "make_custom_pdf.c"

//
// road stuff
//

static int max_road_speed[1 + _max_road_size_]; // positions 0.._max_road_size_

static void init_road_speeds(void)
{
  double speed;
  int i;

  for(i = 0;i <= _max_road_size_;i++)
  {
    speed = (double)_max_road_speed_ * (0.55 + 0.30 * sin(0.11 * (double)i) + 0.10 * sin(0.17 * (double)i + 1.0) + 0.15 * sin(0.19 * (double)i));
    max_road_speed[i] = (int)floor(0.5 + speed) + (int)((unsigned int)random() % 3u) - 1;
    if(max_road_speed[i] < _min_road_speed_)
      max_road_speed[i] = _min_road_speed_;
    if(max_road_speed[i] > _max_road_speed_)
      max_road_speed[i] = _max_road_speed_;
  }
}

//
// description of a solution
//

typedef struct
{
  int n_moves;                         // the number of moves (the number of positions is one more than the number of moves)
  int positions[1 + _max_road_size_];  // the positions (the first one must be zero)
}
solution_t;

static unsigned int hash(int move_number,int position,int speed,int final_position){
  // 0 - 10000000-1;
  return (move_number *61+ position*22353 - speed*1234 - final_position) % 100000u;
}

typedef struct hash_data
{
    struct hash_data *next;
    
    int move_number;
    int position;
    int speed;
    int final_position; 

    int value;
}
hash_data;

#define hash_size 100000u
static hash_data *hash_table[hash_size];

static void init_hash_table(void)
{
    for(unsigned int idx = 0u; idx < hash_size ; idx++)
        hash_table[idx] = NULL;
}

static hash_data *new_hash_data(int move_number,int position,int speed,int final_position){
  hash_data *hd = (hash_data *)malloc(sizeof(hash_data));
  hd->next = NULL;
  hd->move_number = move_number;
  hd->position = position;
  hd->speed = speed;
  hd->final_position = final_position;
  if(hd == NULL){
    fprintf(stderr,"Out of memory\n");
    exit(1);
  }
  return hd;
}

static void add_to_table(int move_number,int position,int speed,int final_position){
  unsigned int idx = hash(move_number, position, speed, final_position);
  hash_data *new_hd = new_hash_data(move_number, position, speed, final_position);
  hash_data *hd = hash_table[idx];
  new_hd->next = hd;
  hash_table[idx] = new_hd;
}

static hash_data *find_data(int move_number,int position,int speed,int final_position)
{
    unsigned int idx = hash(move_number, position, speed, final_position);
    hash_data *hd = hash_table[idx];
    while(hd != NULL && !(move_number==hd->move_number && position==hd->position && speed==hd->speed && final_position==hd->final_position))
        hd = hd -> next;
    return hd;
}

//
// the (very inefficient) recursive solution given to the students
//

static solution_t solution_1,solution_1_best;
static double solution_1_elapsed_time; // time it took to solve the problem
static unsigned long solution_1_count; // effort dispended solving the problem

static void solution_1_recursion(int move_number,int position,int speed,int final_position)
{
  int i,new_speed;

  // record move
  solution_1_count++;
  solution_1.positions[move_number] = position;
  // is it a solution?
  // terminal condition
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_1_best.n_moves)
    {
      solution_1_best = solution_1;
      solution_1_best.n_moves = move_number;
    }
    return;
  }
  // depth first search
  // breath first search

  // no, try all legal speeds
  for(new_speed = speed - 1;new_speed <= speed + 1;new_speed++)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++);
      //
      //fprintf(stderr,"speed %d, i %d\n",new_speed, i);
      if(i > new_speed){
        
        //index = hash(move_number + 1, position + new_speed,new_speed,final_position);
        //fprintf(stderr,"hash %d - (%d,%d,%d,%d))\n",index,move_number + 1,position + new_speed,new_speed,final_position);
        if (find_data(move_number + 1, position + new_speed,new_speed,final_position)==NULL){
          //fprintf(stderr,"solution_1_recursion(%d,%d,%d,%d)\n",move_number + 1,position + new_speed,new_speed,final_position);
          add_to_table(move_number + 1, position + new_speed,new_speed,final_position);
          solution_1_recursion(move_number + 1, position + new_speed,new_speed,final_position);

        }
        
      }
    }
}

static void solve_1(int final_position)
{
  init_hash_table();
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_1: bad final_position\n");
    exit(1);
  }
  solution_1_elapsed_time = cpu_time();
  solution_1_count = 0ul;
  solution_1_best.n_moves = final_position + 100;
  solution_1_recursion(0,0,0,final_position);
  solution_1_elapsed_time = cpu_time() - solution_1_elapsed_time;
}

//
// example of the slides
//

static void example(void)
{
  int i,final_position;

  srandom(0xAED2022);
  init_road_speeds();
  final_position = 30;
  solve_1(final_position);
  make_custom_pdf_file("example.pdf",final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
  printf("mad road speeds:");
  for(i = 0;i <= final_position;i++)
    printf(" %d",max_road_speed[i]);
  printf("\n");
  printf("positions:");
  for(i = 0;i <= solution_1_best.n_moves;i++)
    printf(" %d",solution_1_best.positions[i]);
  printf("\n");
}

//
// main program
//

int main(int argc,char *argv[argc + 1])
{
# define _time_limit_  3600.0
  int n_mec,final_position,print_this_one;
  char file_name[64];

  // generate the example data
  if(argc == 2 && argv[1][0] == '-' && argv[1][1] == 'e' && argv[1][2] == 'x')
  {
    example();
    return 0;
  }
  // initialization
  n_mec = (argc < 2) ? 0xAED2022 : atoi(argv[1]);
  srandom((unsigned int)n_mec);
  init_road_speeds();
  // run all solution methods for all interesting sizes of the problem
  final_position = 1;//C_MAX;
  solution_1_elapsed_time = 0.0;
  printf("    + --- ---------------- --------- +\n");
  printf("    |                plain recursion |\n");
  printf("--- + --- ---------------- --------- +\n");
  printf("  n | sol            count  cpu time |\n");
  printf("--- + --- ---------------- --------- +\n");
  while(final_position <= _max_road_size_ /*&& final_position <= C_MAX*/)
  {
    print_this_one = (final_position == 10 || final_position == 20 || final_position == 50 || final_position == 100 || final_position == 200 || final_position == 400 || final_position == 800) ? 1 : 0;
    printf("%3d |",final_position);
    // first solution method (very bad)
    if(solution_1_elapsed_time < _time_limit_)
    {
      solve_1(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_2.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_1_best.n_moves,&solution_1_best.positions[0],solution_1_elapsed_time,solution_1_count,"Plain recursion");
      }
      printf(" %3d %16lu %9.3e |",solution_1_best.n_moves,solution_1_count,solution_1_elapsed_time);
    }
    else
    {
      solution_1_best.n_moves = -1;
      printf("                                |");
    }
    // second solution method (less bad)
    // ...

    // done
    printf("\n");
    fflush(stdout);
    // new final_position
    if(final_position < 50)
      final_position += 1;
    else if(final_position < 100)
      final_position += 5;
    else if(final_position < 200)
      final_position += 10;
    else
      final_position += 20;
  }
  printf("--- + --- ---------------- --------- +\n");
  return 0;
# undef _time_limit_
}
