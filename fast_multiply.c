#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int get_input_length(char** x, char** y)
{
  int length_x = strlen(*x);
  int length_y = strlen(*y);

  if(length_x < length_y) {
    char* str_a  = (char *) malloc((length_y+1) * sizeof(char));

    for(int i = 0; i < length_y-length_x; i++)
    {
        str_a[i] = '0';
    } 
    for(int i = length_y-length_x; i < length_y; i++)
    {
        str_a[i] = (*x)[i-(length_y-length_x)];
    }
    str_a[length_y] = '\0';
    *x = str_a;
  }
  else if(length_y < length_x) {
    char* str_b  = (char *) malloc((length_x+1) * sizeof(char));

    for(int i = 0; i < length_x-length_y; i++)
    {
        str_b[i] = '0';
    } 
    for(int i = length_x-length_y; i < length_x; i++)
    {
        str_b[i] = (*y)[i-(length_x-length_y)];
    }
    str_b[length_x] = '\0';
    *y = str_b;
  }

  return strlen(*x);
}

char* get_sub_string(char* x, int start, int end)
{
    char* sub_string = (char *) malloc(sizeof(char) * (end-start+2));

    for(int i=start; i<=end; i++)
    {
        sub_string[i-start] = x[i];
    }
    sub_string[end-start+1] = '\0';

    return sub_string;
}

char* add_bit_strings(char* x, char* y)
{
  int length = get_input_length(&x, &y);
  char* result = (char*) malloc(sizeof(char)*(length+2));
  int carry = 0;
  int bit_x, bit_y, temp;
  int n = length;
  
  while(n > 0)
  {
      bit_x = x[n-1]-'0';
      bit_y = y[n-1]-'0';
      temp = bit_x+bit_y+carry;
      if(temp >= 2) {
        carry = 1;
        temp = temp%2;
      }
      else {
        carry = 0;
      }
      result[n] = temp+'0';
      n--;
  }
  if(carry) result[0] = '1';
  else {
    for(int i=0; i < strlen(result)-1; i++) {
        result[i] = result[i+1];
    }
    result[strlen(result)-1] = '\0';
  }
  return result;
}

long int fast_multiply(char* x, char* y)
{
  int number_of_bits = get_input_length(&x, &y);
  
  if(number_of_bits == 0) return 0;
  if(number_of_bits == 1) return (x[0]-'0') * (y[0]-'0');
  
  int n_left_bits = number_of_bits / 2;
  int n_right_bits = number_of_bits - n_left_bits;

  char* x_left = get_sub_string(x, 0, n_left_bits-1);
  char* x_right = get_sub_string(x, n_left_bits, number_of_bits-1);
  char* y_left = get_sub_string(y, 0, n_left_bits-1);
  char* y_right = get_sub_string(y, n_left_bits, number_of_bits-1);

  long int A = fast_multiply(x_left, y_left);
  long int B = fast_multiply(x_right, y_right);
  long int C = fast_multiply(
      add_bit_strings(x_left, x_right),
      add_bit_strings(y_left, y_right));

  return A*(1<<(2*n_right_bits))+(C-A-B)*(1<<n_right_bits)+B;
  


  return 0;
}


int main()
{
  char* s1 = "010";
  char* s2 = "110";
  assert(get_input_length(&s1, &s2) == 3);

  s1 = "10";
  s2 = "110";
  assert(get_input_length(&s1, &s2) == 3);
  assert(strcmp(s1, "010") == 0);
  assert(strcmp(s2, "110") == 0);

  s1 = "101";
  s2 = "11";
  assert(get_input_length(&s1, &s2) == 3);
  assert(strcmp(s1, "101") == 0);
  assert(strcmp(s2, "011") == 0);

  s1 = "";
  s2 = "";
  assert(get_input_length(&s1, &s2) == 0);

  s1 = "1100111";
  assert(strcmp(get_sub_string(s1, 0, 3), "1100") == 0);
  assert(strcmp(get_sub_string(s1, 4, 6), "111") == 0);

  s1 = "11";
  s2 = "11";
  assert(strcmp(add_bit_strings(s1, s2), "110") == 0);

  s1 = "01";
  s2 = "10";
  assert(strcmp(add_bit_strings(s1, s2), "11") == 0);

  s1 = "10";
  s2 = "111";
  assert(strcmp(add_bit_strings(s1, s2), "1001") == 0);

  assert(fast_multiply("1100", "1010")==120); 
  assert(fast_multiply("110", "1010")==60); 
  assert(fast_multiply("11", "1010")==30); 
  assert(fast_multiply("1", "1010")==10); 
  assert(fast_multiply("0", "1010")==00); 
  assert(fast_multiply("111", "111")==49); 
  assert(fast_multiply("11", "11")==9);
  assert(fast_multiply("11", "101")==15); 

  return 0;
}
