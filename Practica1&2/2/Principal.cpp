#include <iostream>
#include <cstdlib>
#include <cmath>
#include <opencv2/core/core.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace std;
using namespace cv;

cv::Mat erosion,dilatacion,top_hat,black_hat,operacion,part1,part2,part3,img;

void operaciones(Mat img, Mat elementoEstructurante){
    
    erode(img, erosion, elementoEstructurante);
    dilate(img, dilatacion, elementoEstructurante);
    morphologyEx(img, top_hat, MORPH_TOPHAT, elementoEstructurante);
    morphologyEx(img, black_hat, MORPH_BLACKHAT, elementoEstructurante);
    absdiff(top_hat, black_hat, operacion);
    add(img, operacion, operacion);
    
    namedWindow("Imagen", WINDOW_AUTOSIZE);
    imshow("Imagen", img);
    
    namedWindow("Erosion imagen", WINDOW_AUTOSIZE);
    imshow("Erosion imagen", erosion);
    
    namedWindow("Dilatacion imagen", WINDOW_AUTOSIZE);
    imshow("Dilatacion imagen", dilatacion);
    
    namedWindow("TopHat imagen", WINDOW_AUTOSIZE);
    imshow("TopHat imagen", top_hat);
    
    namedWindow("BlackHat imagen", WINDOW_AUTOSIZE);
    imshow("BlackHat imagen", black_hat);
    
    namedWindow("Operacion imagen", WINDOW_AUTOSIZE);
    imshow("Operacion imagen", operacion);
    
    
    waitKey(0);
}

int main(int argc, char *argv[]){
    //Kernel para la erosion y dilatacion
    part1=getStructuringElement(MORPH_CROSS, Size(5,5));
    part2=getStructuringElement(MORPH_CROSS, Size(15,15));
    part3=getStructuringElement(MORPH_CROSS, Size(37,37));
    
    
    img = imread("1.jpg", IMREAD_GRAYSCALE);
    resize(img, img, Size(), 0.3, 0.3);
    operaciones(img, part1);
    
    img = imread("2.jpg", IMREAD_GRAYSCALE);
    resize(img, img, Size(), 0.3, 0.3);
    operaciones(img, part2);
    
    img = imread("3.jpg", IMREAD_GRAYSCALE);
    resize(img, img, Size(), 0.3, 0.3);
    operaciones(img, part3);
    
    
    return 0;
}

