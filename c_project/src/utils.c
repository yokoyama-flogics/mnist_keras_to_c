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
#include <float.h>
#include "mnist.h"
#include "utils.h"
#include "test_images.h"
#include "test_labels.h"

int ct_load = 0;

int load_input(float vect[HEIGHT][WIDTH], int *label, float div_scale)
{
    int x, y;

    int n_inputs = sizeof(TEST_IMAGES) / sizeof(TEST_IMAGES[0]);

    if (ct_load >= n_inputs)
        return -1;

    else {
        for (y = 0; y < HEIGHT; y ++)
            for (x = 0; x < WIDTH; x ++)
                vect[y][x] = TEST_IMAGES[ct_load][y][x] / div_scale;
    }

    *label = TEST_LABELS[ct_load];

    ct_load ++;

    return 0;
}


int print_input(float const vect[HEIGHT][WIDTH], float div_scale)
{
    int x;
    int y;

    for (y = 0; y < HEIGHT; y ++) {
        for (x = 0; x < WIDTH; x ++)
            printf("%3d ", (int) (vect[y][x] * div_scale));
        printf("\n");
    }

    return 0;
}


int test_output(float const vect[N_OUTPUTS], int label)
{
    int i;
    int n_max = -1;
    float val_max = - FLT_MAX;

    for (i = 0; i < N_OUTPUTS; i ++) {
        if (vect[i] > val_max) {
            n_max = i;
            val_max = vect[i];
        }
    }

    if (n_max == label)
        return 0;
    else
        return -1;
}


int print_output(float const vect[N_OUTPUTS])
{
    int i;

    for (i = 0; i < N_OUTPUTS; i ++)
        printf("%d: %.2f\n", i, vect[i]);

    return 0;
}
