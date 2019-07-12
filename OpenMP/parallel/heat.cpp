#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <iomanip>
using namespace std;

typedef std::chrono::high_resolution_clock Clock;

int main () {

	int n, niters;	
	n = 1000, niters = 10000;

	double ** input_temp = new double*[n+2];
	double ** output_temp = new double*[n+2];

	for (int i = 0; i < n+2; ++i){
		input_temp[i] = new double[n+2];
		output_temp[i] = new double[n+2];
	}
	
	for (int i = 0; i < n+2; ++i){
		for (int j = 0; j < n+2; ++j){
			if (i == 0 || j == 0 || i == n+1 || j == n+1){
				input_temp[i][j] = 100.0;
				output_temp[i][j] = 100.0;
			} else {
				input_temp[i][j] = -100.0;
			}
		}
	}

	double c, delta_t, delta_s;
	c = 0.1;
	delta_s = 1.0 / (n+1.0);
	delta_t = (delta_s*delta_s) / (4.0*c);

	omp_set_num_threads(16);	
	auto t1 = Clock::now();	
	for (int iter = 0; iter < niters; ++iter){
		int i, j;
		//#pragma omp parallel for schedule(auto) shared(input_temp, output_temp, n) private(i, j)
		#pragma omp parallel for schedule(auto) shared(input_temp, output_temp) private(i, j)
		for (i = 1; i < n+1; ++i){
			for (j = 1; j < n+1; ++j){	
				output_temp[i][j] = input_temp[i][j] + (c * (delta_t/(delta_s*delta_s)) * (input_temp[i+1][j] + input_temp[i-1][j] - (4 * input_temp[i][j]) + input_temp[i][j+1] + input_temp[i][j-1])); 
			}
		}
		swap(input_temp, output_temp);
	}
	auto t2 = Clock::now();
	cout << "Parallel Runtime: " << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count() << " nanoseconds" << endl;

	double final_temp = 0.0;	
	for (int i = 1; i < n+1; ++i){
		for (int j = 1; j < n+1; ++j){
			final_temp += input_temp[i][j];
		}
	}
	delete input_temp;
	delete output_temp;
	cerr << std::setprecision(10) << "Final Temp: " << final_temp << endl;	
}
