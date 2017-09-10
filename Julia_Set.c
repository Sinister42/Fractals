#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void compute(int w, int h, int max_iteration, struct range_t range, double re_c, double im_c, int *out);
double abs(double real, double img);

typedef struct range_t{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
} range_t;

int main(int argc, int **argv){
	return 0;
}

double abs(double real, double img){
	return sqrt((real*real)+(img*img));
}

void compute(int w, int h, int max_iteration, struct range_t range, double re_c, double im_c, int *out){
	double horizontal_move = (2*range.xmax)/w;
	double vertical_move = (2*ymax)/h;
	int i,j,k;
	double real;
	double img;
	double tmp;
	double im_constant = 0.0001;
	for(i=0; i < h; i++){
		for(j=0; j < w; j++){
			real = (range.xmin + (i * horizontal_move));
			img = (range.ymin + (j * vertical_move));
			for(k=0; k < max_iteration; k++){
				if(abs(real,img) > 2.0){
					out[(i*w)+j] = k;
					break;
				}
				// square
				tmp = real;
				real = (real*real)-(img*img);
				img = 2*tmp*img;
				// add c = 0.3515 - 0.07467i
				// c += k * const 
				//im_c += k * im_constant;
				real += re_c;
				img += im_c;
			}
		}
	}
}