//
// Tomás Oliveira e Silva, AED, November 2021
//
// Generic deque implementation based on a circular buffer
//

#ifndef _AEDdeque
#define _AEDdeque

#include <cassert>

template <typename T>
class deque
{
  private:
    int max_size;
    int cur_size;
    int head;
    int tail;
    T *data;
  private:
    int increment_index(int i) { return (i + 1 < max_size) ? i + 1 : 0;}
    int decrement_index(int i) { return (i - 1 >= 0) ? i - 1 : max_size - 1;}

  public:
    deque(int n = 100)
    {
      max_size = n;
      cur_size = 0;
      head = 1;
      tail = 0;
      data = new T[n];
    }
    ~deque(void)
    {
      delete[] data;
    }
    void clear(void)
    {
      cur_size = 0;
      head = 1;
      tail = 0;
    }
    int size(void) const
    {
      return cur_size;
    }
    int is_full(void) const
    {
      return (cur_size == max_size) ? 1 : 0;
    }
    int is_empty(void) const
    {
      return (cur_size == 0) ? 1 : 0;
    }
    void insert_at_head(T v)
    {
      assert(is_full() == 0);
      head = decrement_index(head);
      data[head] = v;
      cur_size++; 
    }
    T remove_head(void)
    {
      assert(is_empty() == 0);
      int old_head = head;
      head = increment_index(head);
      cur_size--;
      return data[old_head];
    }
    T peek_head(void)
    {
      assert(cur_size > 0);
      return data[head];
    }
    void insert_at_tail(T v)
    { 
       assert(is_full() == 0);
       tail = increment_index(tail);
       data[tail] = v;
       cur_size++;
    }
    T remove_tail(void)
    {
      assert(is_empty() == 0);
      int old_tail = tail;
      tail = decrement_index(tail);
      cur_size--;
      return data[old_tail];
    }
    T peek_tail(void)
    {
      assert(cur_size > 0);
      return data[tail];
    }
};

#endif
