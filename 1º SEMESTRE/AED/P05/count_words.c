//
// Tomás Oliveira e Silva, AED, November 2021
//
// to compare strings use the function strcmp()
// to copy a string use the function strcpy()
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// complete the define T !!!
//

#define T ...

#include "hash_table.h"

void register_word(char word[64])
{
  hash_table_node *p = find_hash_table_node(word);
  if (p != NULL){
    p -> value++;
  } else{
    p = allocate_hash_table_node();
    p -> value = 1;
    strcpy(p -> key,word);
    insert_hash_table_node(p);
  }
}


//
// main program
//

int main(int argc,char **argv)
{
  char line[10000],word[64];
  hash_table_node *n;
  FILE *fp;
  int i,j;

  for(i = 1;i < argc;i++)
  {
    //
    // open file for reading
    //
    fp = fopen(argv[i],"r");
    if(fp == NULL)
    {
      fprintf(stderr,"Unable to open file %s\n",argv[i]);
      exit(1);
    }
    //
    // place your counter initialization code here (creation of the hash table ...)
    //

    //
    // scan the entire file
    //
    while(fgets(line,sizeof(line),fp) != NULL)
    {
      // replace non-digits and non-letters by a space
      for(i = 0;line[i] != '\0';i++)
        if((line[i] < '0' || line[i] > '9') && (line[i] < 'A' || line[i] > 'Z') && (line[i] < 'a' || line[i] > 'z') && line[i] != '\'')
          line[i] = ' ';
      // go over the line and extract each word
      for(i = 0;line[i] != '\0';i += j)
        if(line[i] == ' ')
          j = 1;
        else
        {
          for(j = 0;line[i + j] != '\0' && line[i + j] != ' ';j++)
            if(j < 63)
              word[j] = line[i + j];
          word[(j < 63) ? j : 63] = '\0';
          register_word(word);
        }
    }
    //
    // close file
    //
    fclose(fp);
    
    for(i=0; i < hash_table_size;i++){
      p = hash_table[i];
      while(p != NULL){
        printf("%s : %d", p -> key, p -> value);
        p = p->next;
      }
    }

  }
  return 0;
}
