#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char **argv) {

	int n, niters;	
	n = 1000, niters = 10000;

	double c, delta_t, delta_s;
	c = 0.1;
	delta_s = 1.0 / (n+1.0);
	delta_t = (delta_s*delta_s) / (4.0*c);

	int rank, num_procs;
	
	int size;
	double** local_input;
	double** local_output;
	int save;
	
	MPI_Init(&argc, &argv);	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

	double total = 0.0;

	if (rank == 0){
		size = floor((n/num_procs)+2);
		save = (n/num_procs) * rank;
		printf("My proc number is %d, my start is %d end is %d, size is %d\n", rank, save, save+size, size);
		local_input = (double**) malloc(size * sizeof(double*));
		local_output = (double**) malloc(size * sizeof(double*));
		for (int i = 0; i < size; ++i){
			local_input[i] = (double*)malloc((n+2) * sizeof(double));
			local_output[i] = (double*)malloc((n+2) * sizeof(double));
		}
		
		for (int i = 0; i < size; i++){
			for (int j = 0; j < n+2; j ++){
				if (i == 0 || j == 0 || j == n+1){
					local_input[i][j] = 100.0;
				} else {
					local_input[i][j] = -100.0;
					local_output[i][j] = -100.0;
				}
			}
		}

	} else if (rank != num_procs-1 && rank != 0){
		size = floor((n/num_procs))+2;
		save = (n/num_procs) * rank;
		printf("My proc number is %d, my start is %d end is %d, size is %d\n", rank, save, save+size, size);
		local_input = (double**)malloc(size*sizeof(double*));
		if (local_input == NULL){
			printf("failed malloc on 82\n");
		}
		local_output = (double**)malloc(size*sizeof(double*));
		if (local_output == NULL){
			printf("failed malloc on 82\n");
		}
		for (int i = 0; i < size; i++){
			local_input[i] = (double*)malloc((n+2) * sizeof(double));
			if (local_input[i] == NULL){
				printf("failed malloc on 82\n");
			}
			local_output[i] = (double*)malloc((n+2) * sizeof(double));
			if (local_output[i] == NULL){
				printf("failed malloc on 82\n");
			}
			for (int j = 0; j < n+2; j++){
				if (j == 0 || j == n+1){
					local_input[i][j] = 100.0;
				} else {
					local_input[i][j] = -100.0;
					local_output[i][j] = -100.0;
				}
			}	
		}
	} else if (rank == (num_procs-1)){
		int r = rank;
		size = floor(((n+2)) - ((n/num_procs) * r));
		save = (n/num_procs) * rank;
		printf("My proc number is %d, my start is %d end is %d, size is %d\n", rank, save, save+size, size);
		
		local_input = (double**) malloc(size * sizeof(double*));
		local_output = (double**) malloc(size * sizeof(double*));
		for (int i = 0; i < size; ++i){
			local_input[i] = (double*)malloc((n+2) * sizeof(double));
			local_output[i] = (double*)malloc((n+2) * sizeof(double));
			for (int j = 0; j < n+2; ++j){
				if (i == size-1 || j == 0 || j == n+1){
					local_input[i][j] = 100.0;
				} else {
					local_input[i][j] = -100.0;
					local_output[i][j] = -100.0;
				}		
			}
		}
	}
	for (int iter = 0; iter < niters; ++iter){
		for (int i = 1; i < size-1; ++i){
			for (int j = 1; j < n+1; ++j){
				local_output[i][j] = local_input[i][j] + (c * (delta_t/(delta_s*delta_s)) * (local_input[i+1][j] + local_input[i-1][j] - (4 * local_input[i][j]) + local_input[i][j+1] + local_input[i][j-1])); 
			}
		}
		for (int i = 1; i < size-1; i++){
			for (int j = 1; j < n+1; j++){
				local_input[i][j] = local_output[i][j];
			}
		}
		
		if (rank != num_procs-1){
			MPI_Send(local_input[size-2], n+2, MPI_DOUBLE, rank+1, 0, MPI_COMM_WORLD);
		}
		if (rank != 0){
			MPI_Recv(local_input[0], n+2, MPI_DOUBLE, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		if (rank != 0){
			MPI_Send(local_input[1], n+2, MPI_DOUBLE, rank-1, 0, MPI_COMM_WORLD);
		}
		if (rank != num_procs-1){
			MPI_Recv(local_input[size-1], n+2, MPI_DOUBLE, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
	}

	for (int i = 1; i < size-1; i++){
		for (int j = 1; j < n+1; j++){
			total += local_input[i][j];
		}
	}

	if (rank != 0){
		MPI_Send(&total, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	} 
	if (rank == 0) {
		double temp;
		double finaltotal = 0.0;

		finaltotal += total;	
	
		for (int i = 1; i < num_procs; i++){
			MPI_Recv(&temp, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			finaltotal += temp;;
		}
		fprintf(stderr, "final temp = %f\n", finaltotal);
	}

	MPI_Finalize();
	return 0;
}
