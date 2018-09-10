/**
 * @file 1lnn.c
 * @brief Machine learning functionality for a 1-layer neural network
 * @author Matt Lind
 * @date July 2015
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util/mnist-utils.h"
#include "1lnn.h"
#include "weights.h"

extern const float weights[];
extern const float bias[];


/**
 * @details Returns an output vector with targetIndex set to 1, all others to 0
 */

Vector getTargetOutput(int targetIndex){
    Vector v;
    for (int i=0; i<NUMBER_OF_OUTPUT_CELLS; i++){
        v.val[i] = (i==targetIndex) ? 1 : 0;
    }
    return v;
}




/**
 * @details Initialize layer by setting all weights to random values [0-1]
 * @attention It actually makes no difference whether the weights are
 * initialized to a constant (e.g. 0.5) or to a random number.
 * The result (85% success rate) will not change significantly.
 */

void initLayer(Layer *l){

    for (int o=0; o<NUMBER_OF_OUTPUT_CELLS; o++){

        for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
            l->cell[o].input[i]=0;
            l->cell[o].weight[i]=rand()/(double)(RAND_MAX);
        }

        l->cell[o].output = 0;
        l->cell[o].bias = 0;
    }
}




/**
 * @details The output prediction is derived by simply sorting all output values
 * and using the index (=0-9 number) of the highest value as the prediction.
 */

int getLayerPrediction(Layer *l){

    double maxOut = 0;
    int maxInd = 0;

    for (int i=0; i<NUMBER_OF_OUTPUT_CELLS; i++){

        if (l->cell[i].output > maxOut){
            maxOut = l->cell[i].output;
            maxInd = i;
        }
    }

    return maxInd;

}




/**
 * @details Returns the difference between a target value and the cell's ouput
 */

double getCellError(Cell *c, int target){

    double err = target - c->output;

    return err;
}




/**
 * @details Updates a cell's weights based on given error and LEARNING_RATE
 */

void updateCellWeights(Cell *c, double err){

    for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
        c->weight[i] += LEARNING_RATE * c->input[i] * err;
    }
}




/**
 * @brief Load weights from file and fill cells
 */

void loadWeights(Layer *l){

	for (int i = 0; i < NUMBER_OF_INPUT_CELLS*10; i++){

		l->cell[i%10].weight[i/10] = weights[i];
	}

	for (int j = 0; j < NUMBER_OF_OUTPUT_CELLS; j++){

		l->cell[j].bias = bias[j];
	}
}
