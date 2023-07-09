#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_linalg.h>

int * tx_data_read(FILE *file, long int sequencia_bytes);
void rx_data_write(int *s, long int sequencia_bytes, char *filename);
complexo *tx_qam_mapper(int *s, long int qam);