
#include <cstdio>
#include <iostream>
#include <chrono>

//#define cimg_use_jpeg
#include "CImg.h"

using namespace cimg_library;
using namespace std;
using namespace std::chrono;
int main() {
  cimg_library::CImg<unsigned char> input_img("bombus.jpg");

  int width, height;
  width = input_img.width();
  height = input_img.height();
  
  cimg_library::CImg<unsigned char> output_img(
      width, height, 1, 3);
  int * arrayR;
  int * arrayG;
  int * arrayB;
 
  arrayR = new int [752*1002];
  arrayG = new int [752*1002];
  arrayB = new int [752*1002];

  int * arrayR_mod;
  int * arrayG_mod;
  int * arrayB_mod;
  
  arrayR_mod = new int [752*1002];
  arrayG_mod = new int [752*1002];
  arrayB_mod = new int [752*1002];

for (int c = 0; c < width+2; ++c) {
    for (int r = 0; r < height+2; ++r) {
        if (c == 0 || r == 0 || c == width + 1 || r == height + 1){
		arrayR[(c * (height+2)) + r] = 0;
		arrayG[(c * (height+2)) + r] = 0;
		arrayB[(c * (height+2)) + r] = 0;
        } else {
        	arrayR[(c * (height+2)) + r] = input_img(c-1, r-1, 0);
        	arrayG[(c * (height+2)) + r] = input_img(c-1, r-1, 1);
        	arrayB[(c * (height+2)) + r] = input_img(c-1, r-1, 2);
        }
    }
  }
  
  typedef std::chrono::high_resolution_clock Clock; 
  using std::chrono::nanoseconds;
  using std::chrono::duration_cast;
  high_resolution_clock::time_point t1 = Clock::now();

 
  for (int c = 1; c < width -1; c++){
    for (int r=1; r < height - 1; r++){
        arrayR_mod[(c * height) + r] = (arrayR[((c-1) * height) + (r-1)] / 8) +  (arrayR[((c-1) * height) + r] / 8) + (arrayR[((c-1) * height) + (r+1)] / 8) + (arrayR[(c * height) + (r-1)] / 8) + (arrayR[(c * height) + (r+1)] / 8) + (arrayR[((c+1) * height) + (r-1)] / 8) + (arrayR[((c+1) * height) + r] / 8) + (arrayR[((c+1) * height) + (r+1)] / 8);
        arrayG_mod[(c * height) + r] = (arrayG[((c-1) * height) + (r-1)] / 8) +  (arrayG[((c-1) * height) + r] / 8) + (arrayG[((c-1) * height) + (r+1)] / 8) + (arrayG[(c * height) + (r-1)] / 8) + (arrayG[(c * height) + (r+1)] / 8) + (arrayG[((c+1) * height) + (r-1)] / 8) + (arrayG[((c+1) * height) + r] / 8) + (arrayG[((c+1) * height) + (r+1)] / 8);
        arrayB_mod[(c * height) + r] = (arrayB[((c-1) * height) + (r-1)] / 8) +  (arrayB[((c-1) * height) + r] / 8) + (arrayB[((c-1) * height) + (r+1)] / 8) + (arrayB[(c * height) + (r-1)] / 8) + (arrayB[(c * height) + (r+1)] / 8) + (arrayB[((c+1) * height) + (r-1)] / 8) + (arrayB[((c+1) * height) + r] / 8) + (arrayB[((c+1) * height) + (r+1)] / 8);
    }
  }


  high_resolution_clock::time_point t2 = Clock::now();
  auto duration = duration_cast<nanoseconds>(t2-t1).count();
  std::cout << "Blur applied in " << duration << " nanoseconds\n";
  
  for (int c = 1; c < width+1; ++c) {
    for (int r = 1; r < height+1; ++r) {
	output_img(c-1, r-1, 0) = arrayR_mod[(c * (height+2)) + r];
	output_img(c-1, r-1, 1) = arrayG_mod[(c * (height+2)) + r];
	output_img(c-1, r-1, 2) = arrayB_mod[(c * (height+2)) + r];
        }
    }
  
  
  delete arrayR;
  delete arrayG;
  delete arrayB;

  delete arrayR_mod;
  delete arrayG_mod;
  delete arrayB_mod;
  output_img.save_jpeg("output.jpg");
}
