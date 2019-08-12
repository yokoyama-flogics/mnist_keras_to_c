#ifndef __UTILS_H__

#include "mnist.h"

int load_input(float vect[HEIGHT][WIDTH], int *label, float div_scale);
int print_input(float const vect[HEIGHT][WIDTH], float div_scale);
int test_output(float const vect[N_OUTPUTS], int label);
int print_output(float const vect[N_OUTPUTS]);

#define __UTILS_H__
#endif
