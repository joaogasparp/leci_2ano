//
// AED, August 2022 (Tomás Oliveira e Silva)
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


//
// include files --- as this is a small project, we include the PDF generation code directly from make_custom_pdf.c
//

#include <math.h>
#include <stdio.h>
#include "P02/elapsed_time.h"
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
  int speed[1 + _max_road_size_];
  char move_type[1 + _max_road_size_];
}
solution_t;


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
  // no, try all legal speeds
  for(new_speed = speed - 1;new_speed <= speed + 1;new_speed++)
    if(new_speed >= 1 && new_speed <= _max_road_speed_ && position + new_speed <= final_position)
    {
      for(i = 0;i <= new_speed && new_speed <= max_road_speed[position + i];i++)
        ;
      if(i > new_speed)
        solution_1_recursion(move_number + 1,position + new_speed,new_speed,final_position);
    }
}

static void solve_1(int final_position)
{
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


// solution 2 (speeds seperation)

static solution_t solution_2,solution_2_best;
static double solution_2_elapsed_time; // time it took to solve the problem
static unsigned long solution_2_count; // effort dispended solving the problem

static void solution_2_recursion(int move_number,int position,int speed,int final_position)
{ 
  
  for(move_number; solution_2_best.positions[move_number + 1] != 0; move_number++)
  {
    solution_2_count++;
    solution_2.positions[move_number] = position = solution_2_best.positions[move_number];
    solution_2.speed[move_number] = speed = solution_2_best.speed[move_number];
  }
  // record move
  solution_2_count++;
  solution_2.positions[move_number] = position;
  solution_2.speed[move_number] = speed;
  // is it a solution?
  if(position == final_position && speed == 1)
  {
    // is it a better solution?
    if(move_number < solution_2_best.n_moves)
    {
      solution_2_best = solution_2;
      solution_2_best.n_moves = move_number;
    }
    return;
  }

  if(move_number > solution_2_best.n_moves && move_number > final_position)
    return;

  // no, try all legal speeds
  if(speed == 0)
  {
    if(position == 0)
      solution_2_recursion(1,1,1,final_position); 
  } else {
    if(position + (speed + 1) <= final_position  && (speed + 1) <= max_road_speed[position + (speed + 1)]){
      solution_2_recursion(move_number + 1, position + speed + 1, speed + 1, final_position);
    }
    if(position + speed <= final_position && speed <= max_road_speed[position + speed]){
      solution_2_recursion(move_number + 1, position + speed, speed, final_position);
    }
    if(position + (speed - 1) <= final_position && (speed - 1) <= max_road_speed[position + (speed - 1)]){
      solution_2_recursion(move_number + 1, position + speed - 1, speed - 1, final_position);
    }
    else {
      return;
    }
  }
}

static void solve_2(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_2: bad final_position\n");
    exit(1);
  }
  solution_2_elapsed_time = cpu_time();
  solution_2_count = 0ul;
  solution_2_best.n_moves = final_position + 100;
  solution_2_recursion(0,0,0,final_position);
  solution_2_elapsed_time = cpu_time() - solution_2_elapsed_time;
}

// solution 3
//
static solution_t solution_3,solution_3_best;
static double solution_3_elapsed_time; // time it took to solve the problem
static unsigned long solution_3_count; // effort dispended solving the problem
static solution_t best_past_moves[1 + _max_road_size_];

static void solution_3_recursion(int move_number,int position,int speed,int final_position)
{ 
  if(move_number > final_position)
    return;
  
  // use previous moves
  if(best_past_moves[final_position - 1].move_type[move_number] == '+' || best_past_moves[final_position - 1].move_type[move_number] == '-' || best_past_moves[final_position - 1].move_type[move_number] == '=') 
  {
    if(best_past_moves[final_position - 1].move_type[move_number] == '=' && best_past_moves[final_position - 1].move_type[move_number + 1] == '=')
      {
        solution_3_count++;
        solution_3.positions[move_number] = position = best_past_moves[final_position - 1].positions[move_number];
        solution_3.speed[move_number] = speed = best_past_moves[final_position - 1].speed[move_number];
        solution_3.move_type[move_number] = '+';
        solution_3_recursion(move_number + 1, position + speed + 1, speed + 1, final_position);
      }
    else if(best_past_moves[final_position - 1].move_type[move_number] == '-' && best_past_moves[final_position - 1].move_type[move_number + 1] == '=')
      {
        solution_3_count++;
        solution_3.positions[move_number] = position = best_past_moves[final_position - 1].positions[move_number];
        solution_3.speed[move_number] = speed = best_past_moves[final_position - 1].speed[move_number];
        solution_3.move_type[move_number] = '=';
        solution_3_recursion(move_number + 1, position + speed, speed, final_position);
      }
    else
      {
        solution_3_count++;
        solution_3.positions[move_number] = position = best_past_moves[final_position - 1].positions[move_number];
        solution_3.speed[move_number] = speed = best_past_moves[final_position - 1].speed[move_number];
        solution_3.move_type[move_number] = best_past_moves[final_position - 1].move_type[move_number];
        solution_3_recursion(move_number + 1, position + speed, speed, final_position);
      }
  }  
  else
  {
    // is it a solution?
    if(position == final_position && speed == 1)
    {
      // is it a better solution?
      if(move_number < solution_3_best.n_moves)
      {
        solution_3_best = solution_3;
        solution_3_best.n_moves = move_number;
        best_past_moves[final_position] = solution_3_best;
      }
      return;
    }

    // does the number of moves exceeds the limit?
    if(move_number > solution_3_best.n_moves)
      return;
    // no, try all legal speeds
    if(position == 0)
    {
      solution_3_count++;
      solution_3.positions[move_number] = position;
      solution_3.speed[move_number] = speed;
      solution_3.move_type[move_number] = '+';
      solution_3_recursion(1,1,1,final_position); 
    } else if(position == final_position - 1)
    {  
      if(speed == 1)
      {
        solution_3_count++;
        solution_3.positions[move_number] = position;
        solution_3.speed[move_number] = speed;
        solution_3.move_type[move_number] = '=';
        solution_3_recursion(move_number + 1, position + speed, speed, final_position);
      }
      else if(speed == 2)
      {
        solution_3_count++;
        solution_3.positions[move_number] = position;
        solution_3.speed[move_number] = speed;
        solution_3.move_type[move_number] = '+';
        solution_3_recursion(move_number + 1, position + 1, 1, final_position);
      } 
    }   
    else
    {
      return;
    }  
  }
}


static void solve_3(int final_position)
{
  if(final_position < 1 || final_position > _max_road_size_)
  {
    fprintf(stderr,"solve_2: bad final_position\n");
    exit(1);
  }
  solution_3_elapsed_time = cpu_time();
  solution_3_count = 0ul;
  solution_3_best.n_moves = final_position + 100;
  solution_3_recursion(0,0,0,final_position);
  solution_3_elapsed_time = cpu_time() - solution_3_elapsed_time;
}

/*static void solution_3(int move_number,int position,int speed,int final_position){
  int i;
  if(position == final_position){
    if(move_number < solution_1_best.n_moves){
      solution_1_best.n_moves = move_number;
      
      for(i = 0;i <= move_number;i++)
        solution_1_best.positions[i] = solution_1.positions[i];
    }
    
    return;
  }
  if(move_number >= solution_1_best.n_moves)
    
    return;
  if(speed > 0){
    solution_1.positions[move_number] = position + speed;
    solution_1_count++;
    solution_3(move_number + 1,position + speed,speed,final_position);
  }
  if(speed < max_road_speed[position]){
    solution_1.positions[move_number] = position + speed + 1;
    solution_1_count++;
    solution_3(move_number + 1,position + speed + 1,speed + 1,final_position);
  }
  if(speed > 1){
    solution_1.positions[move_number] = position + speed - 1;
    solution_1_count++;
    solution_3(move_number + 1,position + speed - 1,speed - 1,final_position);
  }
}

static void solution_4(int move_number,int position,int speed,int final_position){
  solution_1_count++;
  solution_1.positions[move_number] = position;

  if (position == final_position && speed == 1) {
    if (move_number <= solution_1_best.n_moves) {
      solution_1_best.n_moves = move_number;
      solution_1_best = solution_1;
    } else {
      return;
    }
  }
  if (position < final_position){
    return;
    }
  // we have to keep trying to find a solution
  if (position+speed+1 <= final_position && speed + 1 <= max_road_speed[position+speed+1]){
    solution_4(move_number + 1, position + speed + 1, speed + 1, final_position);
  }
  else if(position+speed <= final_position && speed <= max_road_speed[position+speed]){
    solution_4(move_number + 1, position + speed, speed, final_position);
  }
  else if (position+speed-1 <= final_position && speed - 1 <= max_road_speed[position+speed-1]){
    solution_4(move_number + 1, position + speed - 1, speed - 1, final_position);
  }
  else {
    return;
  }
}*/

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
  final_position = 1;
  solution_1_elapsed_time = 0.0;
  printf("    + --- ---------------- --------- +\n");
  printf("    |                plain recursion |\n");
  printf("--- + --- ---------------- --------- +\n");
  printf("  n | sol            count  cpu time |\n");
  printf("--- + --- ---------------- --------- +\n");
  while(final_position <= _max_road_size_/* && final_position <= 20*/)
  {
    print_this_one = (final_position == 10 || final_position == 20 || final_position == 50 || final_position == 100 || final_position == 200 || final_position == 400 || final_position == 800) ? 1 : 0;
    printf("%3d |",final_position);
    // first solution method (very bad)
    /*if(solution_1_elapsed_time < _time_limit_)
    {
      solve_1(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_1.pdf",final_position);
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
    if(solution_2_elapsed_time < _time_limit_)
    {
      solve_2(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_2.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_2_best.n_moves,&solution_2_best.positions[0],solution_2_elapsed_time,solution_2_count,"Plain recursion");
      }
      printf(" %3d %16lu %9.3e |",solution_2_best.n_moves,solution_2_count,solution_2_elapsed_time);
    }
    else
    {
      solution_2_best.n_moves = -1;
      printf("                                |");
    }*/
    if(solution_3_elapsed_time < _time_limit_)
    {
      solve_3(final_position);
      if(print_this_one != 0)
      {
        sprintf(file_name,"%03d_3.pdf",final_position);
        make_custom_pdf_file(file_name,final_position,&max_road_speed[0],solution_3_best.n_moves,&solution_3_best.positions[0],solution_3_elapsed_time,solution_3_count,"Plain recursion");
      }
      printf(" %3d %16lu %9.3e |",solution_3_best.n_moves,solution_3_count,solution_3_elapsed_time);
    }
    else
    {
      solution_3_best.n_moves = -1;
      printf("                                |");
    }
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




//we make a move regarding the speed of the car
//we check if we need to change the speed