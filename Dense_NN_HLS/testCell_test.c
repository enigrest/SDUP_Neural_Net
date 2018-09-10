/**
 * @file main.c
 *
 * @mainpage MNIST 1-Layer Neural Network
 *
 * @brief Main characteristics: Only 1 layer (= input layer), no hidden layer.  Feed-forward only.
 * No Sigmoid activation function. No back propagation.\n
 *
 * @details Learning is achieved simply by incrementally updating the connection weights based on the comparison
 * with the desired target output (supervised learning).\n
 *
 * Its performance (success rate) of 85% is far off the state-of-the-art techniques (surprise, surprise)
 * but close the Yann Lecun's 88% when using only a linear classifier.
 *
 * @see [Simple 1-Layer Neural Network for MNIST Handwriting Recognition](http://mmlind.github.io/Simple_1-Layer_Neural_Network_for_MNIST_Handwriting_Recognition/)
 * @see http://yann.lecun.com/exdb/mnist/
 * @version [Github Project Page](http://github.com/mmlind/mnist-1lnn/)
 * @author [Matt Lind](http://mmlind.github.io)
 * @date July 2015
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "util/screen.h"
#include "util/mnist-utils.h"
#include "util/mnist-stats.h"
#include "1lnn.h"




/**
 * @details Performs the testing of the trained network
 */

void sw_testCell(Cell *c, MNIST_Image *img, int target){

    	c->output=0;

    	Neurons_loop:for (int i=0; i<NUMBER_OF_INPUT_CELLS; i++){
    	        //c->input[i] = img->pixel[i] ? 1 : 0;
    			c->input[i] = img->pixel[i]/255.0;

    	        c->output += c->input[i] * c->weight[i];
    	}

    	c->output += c->bias;							// add bias
    	c->output /= NUMBER_OF_INPUT_CELLS;             // normalize output (0-1)

    }



/**
 * @details Tests a layer by looping through and testing its cells
 * Exactly the same as TrainLayer() but WITHOUT LEARNING.
 * @param l A pointer to the layer that is to be training
 */

double testLayer(Layer *l){

	double result_successRate;

    // open MNIST files
    FILE *imageFile, *labelFile;
    imageFile = openMNISTImageFile(MNIST_TESTING_SET_IMAGE_FILE_NAME);
    labelFile = openMNISTLabelFile(MNIST_TESTING_SET_LABEL_FILE_NAME);


    // screen output for monitoring progress
    //displayImageFrame(7,5);

    int errCount = 0;

    // Loop through all images in the file
    for (int imgCount=0; imgCount<MNIST_MAX_TESTING_IMAGES; imgCount++){

        // display progress
        displayLoadingProgressTesting(imgCount,5,5);

        // Reading next image and corresponding label
        MNIST_Image img = getImage(imageFile);
        MNIST_Label lbl = getLabel(labelFile);

        // set target ouput of the number displayed in the current image (=label) to 1, all others to 0
        Vector targetOutput;
        targetOutput = getTargetOutput(lbl);

        //displayImage(&img, 8, 6);

        // loop through all output cells for the given image
        for (int i=0; i < NUMBER_OF_OUTPUT_CELLS; i++){
            testCell(&l->cell[i], &img, targetOutput.val[i]);
        }

        int predictedNum = getLayerPrediction(l);
        if (predictedNum!=lbl) errCount++;

        //printf("\n      Prediction: %d   Actual: %d ",predictedNum, lbl);

        result_successRate = displayProgress(imgCount, errCount, 5, 66);

    }

    // Close files
    fclose(imageFile);
    fclose(labelFile);

    return result_successRate;

}




/**
 * @details Tests a layer by looping through and testing its cells
 * Exactly the same as TrainLayer() but WITHOUT LEARNING.
 * @param l A pointer to the layer that is to be training
 */

double sw_testLayer(Layer *l){

	double result_successRate;

    // open MNIST files
    FILE *imageFile, *labelFile;
    imageFile = openMNISTImageFile(MNIST_TESTING_SET_IMAGE_FILE_NAME);
    labelFile = openMNISTLabelFile(MNIST_TESTING_SET_LABEL_FILE_NAME);


    // screen output for monitoring progress
    //displayImageFrame(7,5);

    int errCount = 0;

    // Loop through all images in the file
    for (int imgCount=0; imgCount<MNIST_MAX_TESTING_IMAGES; imgCount++){

        // display progress
        displayLoadingProgressTesting(imgCount,5,5);

        // Reading next image and corresponding label
        MNIST_Image img = getImage(imageFile);
        MNIST_Label lbl = getLabel(labelFile);

        // set target ouput of the number displayed in the current image (=label) to 1, all others to 0
        Vector targetOutput;
        targetOutput = getTargetOutput(lbl);

        //displayImage(&img, 8, 6);

        // loop through all output cells for the given image
        for (int i=0; i < NUMBER_OF_OUTPUT_CELLS; i++){
            sw_testCell(&l->cell[i], &img, targetOutput.val[i]);
        }

        int predictedNum = getLayerPrediction(l);
        if (predictedNum!=lbl) errCount++;

        //printf("\n      Prediction: %d   Actual: %d ",predictedNum, lbl);

        result_successRate = displayProgress(imgCount, errCount, 5, 66);

    }

    // Close files
    fclose(imageFile);
    fclose(labelFile);

    return result_successRate;

}





/**
 * @details Main function to run MNIST-1LNN
 */

int main(int argc, const char * argv[]) {

    printf("    MNIST-1LNN: a simple 1-layer neural network processing the MNIST handwriting images\n\n");

    double hw_testLayer_successRate;
    double sw_testLayer_successRate;

    Layer hw_outputLayer;
    Layer sw_outputLayer;

    initLayer(&hw_outputLayer);
    loadWeights(&hw_outputLayer);
    hw_testLayer_successRate = testLayer(&hw_outputLayer);

    initLayer(&sw_outputLayer);
    loadWeights(&sw_outputLayer);
    sw_testLayer_successRate = sw_testLayer(&sw_outputLayer);

    printf("sw_: %f\nhw_: %f\n\n", sw_testLayer_successRate, hw_testLayer_successRate);

    if (sw_testLayer_successRate == hw_testLayer_successRate)
    	printf("test PASSED\n\n");
    else
    	printf("test FAILED\n\n");

    return 0;
}


