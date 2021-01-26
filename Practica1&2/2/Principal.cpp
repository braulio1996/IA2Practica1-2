#include <iostream>
#include <cstdlib>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    
    cv::Mat nueva;
    Mat imagen1 = imread("I.png");
    resize(imagen1, imagen1, Size(), 0.5, 0.5);
    Mat imagen2 = imread("II.png");
    resize(imagen2, imagen2, Size(), 0.5, 0.5);
    Mat respuesta = imagen1.clone();


    namedWindow("foto1", WINDOW_AUTOSIZE);
    namedWindow("foto2", WINDOW_AUTOSIZE);
    namedWindow("respuesta", WINDOW_AUTOSIZE);

    Mat resta;
    resta = abs(imagen1 - imagen2);
    //pasamos a escala de gris
    cvtColor(resta, resta, COLOR_BGR2GRAY);

    int pixel;
    vector<Point> imagePoints2;
    for (int i = 0; i < resta.rows; i++) {
        for (int j = 0; j < resta.cols; j++) {
            pixel = resta.at<uchar>(i, j);
            if (pixel > 0) {
                imagePoints2.push_back(Point(j, i));
            }
        }
    }
    const Point* pts = (const cv::Point*) Mat(imagePoints2).data;
    int npts = Mat(imagePoints2).rows;
    fillPoly(respuesta, &pts, &npts, 1, Scalar(255, 255, 255));

    imshow("foto1", imagen1);
    imshow("foto2", imagen2);
    imshow("respuesta", respuesta);
    imwrite("resultado.png", respuesta);
    waitKey(0);
   // destroyAllWindows();
    return 0;
}
