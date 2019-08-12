/*
BSD 2-Clause License

Copyright (c) 2019, Atsushi Yokoyama, Firmlogics (yokoyama@flogics.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <math.h>
#include "mnist.h"
#include "params.h"

static float dense_1_input[HEIGHT * WIDTH];
static float relu_1_input[N_DENSE_1];
static float dense_2_input[N_DENSE_1];
static float relu_2_input[N_DENSE_2];


static int flatten_1(
        float const input[HEIGHT][WIDTH],
        float output[N_OUTPUTS])
{
    int x;
    int y;
    int i_out;

    i_out = 0;

    for (y = 0; y < HEIGHT; y ++)
        for (x = 0; x < WIDTH; x ++)
            output[i_out ++] = input[y][x];

    return 0;
}


static int dense(
        float const input[],
        float output[],
        int n_input,
        int n_output,
        float const *weight,
        float const *bias)
{
    int i_node;
    int i_in;
    float out;

    for (i_node = 0; i_node < n_output; i_node ++) {
        out = 0.0;

        for (i_in = 0; i_in < n_input; i_in ++) {
            // out += weight[i_node * n_output + i_in] + bias[i_node];
            out += weight[i_in * n_output + i_node] * input[i_in];
        }

        output[i_node] = out + bias[i_node];
        // printf("bias %f\n", bias[i_node]);
    }

    return 0;
}


static int dense_1(
        float const input[HEIGHT * WIDTH],
        float output[N_DENSE_1])
{
    return dense(
            input,
            output,
            HEIGHT * WIDTH,
            N_DENSE_1,
            DENSE_1_WEIGHT,
            DENSE_1_BIAS);
}


static int dense_2(
        float const input[N_DENSE_1],
        float output[N_DENSE_2])
{
    return dense(
            input,
            output,
            N_DENSE_1,
            N_DENSE_2,
            DENSE_2_WEIGHT,
            DENSE_2_BIAS);
}


static int relu(
        float const input[],
        float output[],
        int n_size)
{
    int i_n;

    for (i_n = 0; i_n < n_size; i_n ++)
        output[i_n] = input[i_n] > 0.0 ? input[i_n] : 0.0;

    return 0;
}


static int softmax(
        float const input[],
        float output[],
        int n_size)
{
    int i_n;
    float sum;

    sum = 0.0;

    for (i_n = 0; i_n < n_size; i_n ++) {
        output[i_n] = expf(input[i_n]);
        sum += output[i_n];
    }

    for (i_n = 0; i_n < n_size; i_n ++)
        output[i_n] /= sum;

    return 0;
}


int mnist_run(float const input[HEIGHT][WIDTH], float output[N_OUTPUTS])
{
    flatten_1(input, dense_1_input);
    dense_1(dense_1_input, relu_1_input);
    relu(relu_1_input, dense_2_input, N_DENSE_1);

#if 0
    for (int i = 0; i < N_DENSE_1; i ++)
        printf("%f\n", dense_2_input[i]);
    exit(0);
#endif

    dense_2(dense_2_input, relu_2_input);

#if 0
    for (int i = 0; i < N_DENSE_2; i ++)
        printf("%f\n", relu_2_input[i]);
    exit(0);
#endif

    softmax(relu_2_input, output, N_DENSE_2);

    return 0;
}
