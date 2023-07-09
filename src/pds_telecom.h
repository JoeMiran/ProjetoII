#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

int* tx_data_read(const char* filename, long* file_size);
void rx_data_write(const char* filename, const int* decimal_sequence, int sequence_length);