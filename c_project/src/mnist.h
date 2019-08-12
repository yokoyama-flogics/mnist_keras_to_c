#ifndef __MNIST_H__

#define WIDTH               28
#define HEIGHT              28
#define N_OUTPUTS           10

#define N_DENSE_1           128
#define N_DENSE_2           N_OUTPUTS

#define INPUT_DIV_SCALE     255.0

#include <stdint.h>

int mnist_run(float const input[HEIGHT][WIDTH], float output[N_OUTPUTS]);

#define __MNIST_H__
#endif
