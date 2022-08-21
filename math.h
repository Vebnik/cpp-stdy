inline int factorial(int num) {

  int tmp = 1;

  for (int i = 1; i <= num; i++)
    tmp = i * tmp;
  
  return tmp;
}

int sum(int a, int b) {
  return a + b;
}