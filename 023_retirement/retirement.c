#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
} retire_info;

void print_info(int age, double balance) {
  int yr = age / 12;
  int mo = age % 12;
  printf("Age %3d month %2d you have $%.2lf\n", yr, mo, balance);
}

double calculate_current_month(double amt, retire_info info) {
  return amt * ( 1 + info.rate_of_return) + info.contribution;
}

void retirement(
  int startAge, double initial,
  retire_info working, retire_info retired
) {
  print_info(startAge, initial);
  int age = startAge;
  double bal = initial;
  for (int i = 0; i < working.months; ++i) {
    bal = calculate_current_month(bal, working);
    print_info(++age, bal);
  }
  // retired
  for (int i = 1; i < retired.months; ++i) {
    bal = calculate_current_month(bal, retired);
    print_info(++age, bal);
  }
}

int main() {
  retire_info working = {
    .months=489, .contribution=1000, .rate_of_return=0.045/12
  };
  retire_info retire = {
    .months=384, .contribution=-4000, .rate_of_return=0.01/12
  };
  retirement(327, 21345, working, retire);
  return EXIT_SUCCESS;
}
