#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct range_t{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
} range_t;

void compute(int w, int h, int max_iteration, struct range_t range, double re_c, double im_c, int *out);
unsigned char* color_that_shit(int w, int h, int threshold, int *iter);
unsigned char* colors_of_ostrava(int w, int h, int threshold, int *iter);
unsigned char* get_color_image(int w, int h, int threshold, int *iter);
double absolute(double re, double im);



int main(int argc, char** argv){
	// bla bla bla
	int i,j;
	for(i=0; i < 1; i++){
		int w = 600;
		int h = 600;
		int max_iter = 150;
		// range_t* range = (range_t*)malloc(sizeof(range_t));
		// range->xmax = 1.6;
		// range->ymax = 1.0;
		// range->xmin = -1.6;
		// range->ymin = -1.0;
		range_t range = {-1.6,1.6,-1.0,1.0};
		int* out = (int*)malloc(w*h*sizeof(int));
		compute(w, h, max_iter, range, -0.4, 0.6, out);
		/*for(j=0; j < (w*h);j++){
			printf("%d ", out[j]);
			if(j % w == 0){
				printf("\n");
			}
		}*/
		//unsigned char* colorful = color_that_shit(w,h,max_iter,out);
		unsigned char* colorful2 = get_color_image(w,h,max_iter,out);
		//unsigned char* colorful3 = colors_of_ostrava(w,h,max_iter,out);
		// send_to_board(colorful);
		/*for(j=0; j < (w*h); j++){
			printf("R: %u G: %u B: %u ", colorful2[3*j],colorful2[(3*j)+1],colorful2[(3*j)+2]);
			if(j%w == 0){printf("\n");}
		}*/
		//free(colorful);
		free(colorful2);
		//free(colorful3);
		free(out);
	}
	return 0;
}

double absolute(double re, double im){
	return sqrt(re*re)+(im*im);
}

void compute(int w, int h, int max_iteration, struct range_t range, double re_c, double im_c, int *out){
	//for moving the center - can be computed from range
	double center_x = 0, center_y = 0;
	double re_tmp,im_tmp,re_new,im_new;
	int i,j,k, pix = 0;
	for(i=0; i < h; i++){
		for(j=0; j < w; j++){
			// calculate real and img part of z from pixel 
			/*
			re_new = range.xmax * (j - w / 2)/(range.ymax * w) + center_x;
			im_new = (i - h / 2)/(range.ymax * h) + center_y;
			*/
			// alternatively
			re_new = 1.6 * (j - w / 2)/(1.0*w) + center_x;
			im_new = (i - h / 2)/(1.0*h) + center_y;
			
			for(k=0; k < max_iteration; k++){
				re_tmp = re_new;
				im_tmp = im_new;
				// calculations
				re_new = (re_tmp*re_tmp) - (im_tmp*im_tmp) + re_c;
				im_new = (2*re_tmp*im_tmp) + im_c;
				// is closer than 2.0???
				if(absolute(re_new,im_new) > 2.0){
					//printf("K: %d ", k);
					break;
				}
			}
			out[pix++] = k;
		}
	}
}
// new approach - promising
unsigned char* color_that_shit(int w, int h, int threshold, int *iter){
	unsigned char* colors = (unsigned char*)malloc(3*w*h*sizeof(unsigned char));
	// value == brightness
	double hue,saturation,value,remainder,red,green,blue,x,y,z;
	int tmp,flr;
	int iterator = 0;
	while(iterator < (w*h)){
		tmp = iter[iterator];
		hue = ((tmp % 256) / 256.0) * 6.0;
		saturation = 255 / 256.0;
		value = (255 * (tmp < threshold)) / 256.0;
		flr = (int)(floor(hue));
		remainder = hue - flr;
		x = value * (1.0 - saturation);
		y = value * (1.0 - (saturation * remainder));
		z = value * (1.0 - (saturation * (1.0 - remainder)));
		if(flr == 0){
			red = value;
			green = z;
			blue = x;
		} else if(flr == 1){
			red = y;
			green = value;
			blue = x;
		} else if(flr == 2){
			red = x;
			green = value;
			blue = z;
		} else if(flr == 3){
			red = x;
			green = y;
			blue = value;
		} else if(flr == 4){
			red = z;
			green = x;
			blue = value;
		} else if(flr == 5){
			red = value;
			green = x;
			blue = y;
		} else {
			red = green = blue = 0;
		}
		colors[3*iterator] = red;
		colors[(3*iterator)+1] = green;
		colors[(3*iterator)+2] = blue;
	}
	return colors;
	
}
// classic
unsigned char* get_color_image(int w, int h, int threshold, int *iter){
	unsigned char* colors = (unsigned char*)malloc(3*w*h*sizeof(unsigned char));
	int i;
	double tmp;
	for(i = 0; i < w*h; i++){
		tmp = (double)iter[i]/(double)threshold;
		colors[3*i] = 9*(1-tmp)*pow((double)tmp,3)*255;
		colors[(3*i)+1] = 15*pow((double)(1-tmp),2)*pow((double)tmp, 2)*255;
		colors[(3*i)+2] = 8.5*pow((double)(1-tmp),3)*tmp*255;
	}
	return colors;
}
// probably bullshit
unsigned char* colors_of_ostrava(int w, int h, int threshold, int *iter){
	unsigned char* colors = (unsigned char*)malloc(3*w*h*sizeof(unsigned char));
	int i, tmp;
	for(i=0; i < (w*h);i++){
		tmp = iter[i];
		colors[3*i] = (tmp / 65536) % 256;
		colors[(3*i)+1] = (tmp / 256) % 256;
		colors[(3*i)+2] = tmp % 256;
	}
	return colors;
}