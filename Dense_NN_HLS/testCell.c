

#include "util/mnist-utils.h"
#include "1lnn.h"

void testCell(Cell *c, MNIST_Image *img, int target){
	c->output=0;

	loop:for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
	        //c->input[i] = img->pixel[i] ? 1 : 0;
			c->input[i] = img->pixel[i] / 255.0;

	        c->output += c->input[i] * c->weight[i];
	}

	c->output += c->bias;				// add bias
	c->output /= NUMBER_OF_INPUT_CELLS; // normalize output (0-1)
}
