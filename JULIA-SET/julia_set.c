/*******************************************************************
  Simple program to check LCD functionality on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  mzapo_lcdtest.c       - main and only file

  (C) Copyright 2004 - 2017 by Pavel Pisa
      e-mail:   pisa@cmp.felk.cvut.cz
      homepage: http://cmp.felk.cvut.cz/~pisa
      work:     http://www.pikron.com/
      license:  any combination of GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L
#define CHANGE 0.001
#define ZOOM 0.4
#define HEIGHT 320
#define WIDTH 480
#define MAX_ITERATION 150

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

unsigned char* image;

typedef struct range_t {
	double xmin;
	double xmax;
	double ymin;
	double ymax;
} range_t;

// thread structs
pthread_t pool[2];
// mutex struct
pthread_mutex_t lock;
range_t range;
double re_c;
double im_c;
int send = 1;
int do_computation = 1;
int end = 1;


unsigned color(uint16_t r, uint16_t g, uint16_t b){
	return ((r<<11) | (g<<5) | (b));
}

double absolute(double real, double img) {
    return (real*real) + (img*img);
}

void compute(struct range_t range, double re_c, double im_c, int *out, double focus) {
	//printf("%f %f %f %f \n", range.xmax, range.xmin, range.ymax, range.ymin);
    //for moving the center - can be computed from range
    double center_x = 0, center_y = 0;//, focus = 0.4;
    double re_tmp, im_tmp, re_new, im_new;
	//printf("%f %f \n", re_c, im_c);
    int i, j, k, pix = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
           // calculate real and img part of z from pixel 
           re_new = range.xmax * (j - WIDTH / 2) / (range.ymax * focus * WIDTH) + center_x;
           im_new = (i - HEIGHT / 2) / (range.ymax * focus * HEIGHT) + center_y;
           for (k = 0; k < MAX_ITERATION; k++) {
                re_tmp = re_new;
                im_tmp = im_new;
                // calculations
                re_new = (re_tmp*re_tmp) - (im_tmp*im_tmp) + re_c;
                im_new = (2 * re_tmp*im_tmp) + im_c;
                if (absolute(re_new, im_new) > 4.0) {
                    //printf("K: %d ", k);
                    break;
                }
            }
            out[pix++] = k;
        }
    }
}

void get_color_image(int *iter) {
    //unsigned char* colors = (unsigned char*)malloc(3 * WIDTH*HEIGHT * sizeof(unsigned char));
    int i;
    double tmp;
    for (i = 0; i < WIDTH*HEIGHT; i++) {
        tmp = (double)iter[i] / (double)MAX_ITERATION;
        image[3 * i] = 9 * (1 - tmp)*pow((double)tmp, 3) * 31;
        image[(3 * i) + 1] = 15 * pow((double)(1 - tmp), 2)*pow((double)tmp, 2) * 63;
        image[(3 * i) + 2] = 8.5*pow((double)(1 - tmp), 3)*tmp * 31;
    }
    return colors;
}

void send_to_board(){
	unsigned char *parlcd_mem_base;
	int i, j;
	uint16_t c;//unsigned

	parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);

	if (parlcd_mem_base == NULL){
		exit(1);
	}
	
	for (i = 0; i < HEIGHT; i++) {
	    for (j = 0; j < 3*WIDTH; j+=3) {
			c = color(image[i*3*WIDTH + j],image[i*3*WIDTH + j+1],image[i*3*WIDTH + j+2]); 
			parlcd_write_data(parlcd_mem_base, c);
		}
	}
}

//only one image
void julia_set_image(range_t range, double re_c, double im_c, double zoom){
	//printf("%f %f %f %f \n", range.xmax, range.xmin, range.ymax, range.ymin);
	int* out = (int*)malloc(HEIGHT * WIDTH * sizeof(int));
    compute(range, re_c, im_c, out, zoom);
	
    image = get_color_image(out);
	free(out);
	/*for(int i = 0; i < 3*WIDTH*HEIGHT; i+=3){
		printf("%u %u %u",image[i], image[i+1], image[i+2]);
		if(i%3*WIDTH == 0)printf("\n");
	}*/
	/*
	FILE *output = fopen("output.ppm" , "wa");
    fprintf(output, "%s\n", "P6");
	fprintf(output, "%d\n", WIDTH);
	fprintf(output, "%d\n", HEIGHT);
	fprintf(output, "%d\n", 255);
	fwrite(image, sizeof(unsigned char), 3 * WIDTH * HEIGHT, output);
    fclose(output);
	*/
	//send_to_board(image);
}

//draw 200 images
void julia_set_simulation(range_t range, double re_c, double im_c){
	for(int k = 0; k < 200; k++){
		do_computation = 1;
		//julia_set_image(range, re_c, im_c, ZOOM);
		im_c += CHANGE;
		send = 1;
	}
}

void window_case(int number_of_image){//0 is for ilustrate images, other options ilustrate simulations
	//range_t range;
	//double re_c, im_c;
	//while(1){
		//for(int i = 0; i < 5; i++){
			/*range.xmax = 1.6;
			range.xmin = -1.6;
			range.ymax = 1.1;
			range.ymin = -1.1;*/
			switch(number_of_image){
				case 0:
					re_c = -0.7269;
					im_c = 0.1889;
					break;
				case 1:
					re_c = -0.75;
					im_c = 0.11;
					break;
				case 2:
					re_c = 0.285;
					im_c = 0.01;
					break;
				case 3:
					re_c = 0.3;
					im_c = 0.6;
					break;
				case 4:
					re_c = -0.835;
					im_c = -0.2321;
					break;
			}
			do_computation = 1;
			//julia_set_image(range, re_c, im_c, ZOOM);
			
			//if(image_or_simulation == 0){
			//}else{
				//julia_set_simulation(range, re_c, im_c);
			//}
		/*	char o[35];
   			sprintf(o,"output%d.ppm",i);
   			FILE *output = fopen(o, "wa");
    		fprintf(output, "%s\n", "P6");
			fprintf(output, "%d\n", WIDTH);
			fprintf(output, "%d\n", HEIGHT);
			fprintf(output, "%d\n", 255);
			fwrite(image, sizeof(unsigned char), 3 * WIDTH * HEIGHT, output);
   			fclose(output);*/
		//}
	//}
}

void zoom_in(range_t range, double re_c, double im_c){
	double focus = 0.4;
	for(int i = 0; i < 50; i++){
		julia_set_image(range, re_c, im_c, focus);
		focus += 0.02;//?????
		char o[35];
   		sprintf(o,"output%d.ppm",i);
   		FILE *output = fopen(o, "wa");
    	fprintf(output, "%s\n", "P6");
		fprintf(output, "%d\n", WIDTH);
		fprintf(output, "%d\n", HEIGHT);
		fprintf(output, "%d\n", 255);
		fwrite(image, sizeof(unsigned char), 3 * WIDTH * HEIGHT, output);
		fclose(output);
	}
}

void *julia_set_image_thread(void *arg){
	while(end){
		if(do_computation){
			pthread_mutex_lock(&lock);
			julia_set_image(range,re_c,im_c, ZOOM);
			do_computation = 0;
			pthread_mutex_unlock(&lock);
		}
	}
}

void *send_to_board_thread(void *arg){
	// add boolean value to control sending;
	while(end){
		if(send){
			pthread_mutex_lock(&lock);
			send_to_board();
			send = 0;
			pthread_mutex_unlock(&lock);
			//sleep(5);
		}
	}
	
}

void receive_parameters_from_UDB(){

}

uint32_t receive_parameters_from_desk(){
	unsigned char *mem_base;
	mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

	if(mem_base == NULL){
		exit(1);
	}

	uint32_t knobs;
	knobs = *(volatile uint32_t*)(mem_base + SPILED_REG_KNOBS_8BIT_o);

	return knobs;
}

int main(int argc, char *argv[])
{	
	//basic declaration
	re_c = -0.4;
	im_c = 0.6;
	range_t range;
	range.xmin = -1.6;
    range.xmax = 1.6;
    range.ymin = -1.1;
    range.ymax = 1.1;
	//int s = 0;
	int images = -1;
	image = (unsigned char*)malloc(3*WIDTH*HEIGHT*sizeof(unsigned char));
	if(pthread_mutex_init(&lock, NULL) != 0){
		printf("Mutex init error!\n");
		return 1;
	}
	if((pthread_create(&(pool[0]),NULL, &julia_set_image_thread, NULL)) != 0){
		printf("Error creating computational thread!");
		return 1;
	}
	if((pthread_create(&(pool[1]), NULL, &send_to_board_thread, NULL)) != 0){
		printf("Error creating sending thread!");
		pthread_cancel(pool[0]);
		return 1;
	}
	
	//julia_set_image(range, re_c, im_c, ZOOM);
	while(1){
		
		uint32_t knobs = receive_parameters_from desk();
		int [] bits = new int[32];
		for(int i = 31; i >= 0; i--){
			bits[i] = (knobs & (1 << i)) != 0;
		}
		int r_knob = bits[26];
		int g_knob = bits[25];
		int b_knob = bits[24];
		
		if(r_knob){
			for(int j = 0; j < 3*WIDTH*HEIGHT; j++){
				image[j] = 0;
			}
			send = 1;
			break;
		}
		if(g_knob){//simulacia
			re_c = 0.3515;
			im_c = -0.07467;
			julia_set_simulation(range, re_c, im_c);
		}
		if(b_knob){//5 images
			images = (images+1) % 5;
			window_case(images);
			send = 1;
		}
		
	}
	end = 0;
	pthread_join(pool[0], NULL);
	pthread_join(pool[1], NULL);
	free(image);

	//first option... just julia set image
	//julia_set_image(range, re_c, im_c, ZOOM);
	
	//second option... simulation
	//julia_set_simulation(range, re_c, im_c);

	//third option... window case of images
	//window_case(0);

	//fourth option... window case of simulations
	//window_case(1);

	//fifth option... zoom
	//zoom_in(range, re_c, im_c);

	//sixth option... set parameters from desk
	/*while(0){
		uint32_t parameters = receive_parameters_from_desk();
		printf("%x \n", parameters);
		/*uint8_t x, y, c;
		x = parameters >> 8;
		y = parameters >> 16;
		c = parameters >> 24;
		//set range, re_c, im_c
		julia_set_image(range, re_c, im_c);*/
	//}

	return 0;
}

