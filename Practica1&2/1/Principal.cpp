// Librerías que contienen funciones estándar de C++
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
using namespace cv; // Espacio de nombres de OpenCV (Contiene funciones y definiciones de varios elementos de OpenCV)


int sal = 0;
int pimienta = -255;

cv::Mat ruidoMediana,ruidoGaussiana,ruidoBlur,videoframe,sobel,sobel2,sobel2Abs,bordes,bordesAbs,gris,gX,gY,gXAbs,gYAbs,a,b,saltImg,pimientaImg,noiseSalt,noisePimienta;

void trackBarEventHSV(int v, void *p){
}


int main(){

VideoCapture video("cuerdas.mp4");

if(video.isOpened()){
    
    namedWindow("Original", WINDOW_AUTOSIZE);
    moveWindow("Original", 695, 85);
    namedWindow("Ruido de sal", WINDOW_AUTOSIZE);
    moveWindow("Ruido de sal", 10, 30);
    namedWindow("Ruido de pimienta", WINDOW_AUTOSIZE);
    moveWindow("Ruido de pimienta",1320, 30);
    namedWindow("Filtro mediana", WINDOW_AUTOSIZE);
    moveWindow("Filtro mediana",10, 500);
    namedWindow("Filtro Gaussiano");
    moveWindow("Filtro Gaussiano", 695, 500);
    namedWindow("Filtro Blur");
    moveWindow("Filtro Blur", 1320, 500);
    namedWindow("Sobel Bordes 1", WINDOW_AUTOSIZE);
    namedWindow("Sobel Bordes 2", WINDOW_AUTOSIZE);
    
    while(3==3){
    
    video >> videoframe;
    resize(videoframe, videoframe, Size(), 0.12, 0.12);
    cvtColor(videoframe, gris, COLOR_BGR2GRAY);
    
    
    Sobel(gris, gX, CV_16S, 1, 0, 3);
    Sobel(gris, gY, CV_16S, 0, 1, 3); 
    Sobel(gris, sobel2, CV_16S, 1, 1, 3); 
        
    convertScaleAbs(gX, gXAbs); 
    convertScaleAbs(gY, gYAbs); 
    convertScaleAbs(sobel2, sobel2Abs);
    
    Laplacian(gris, bordes, CV_16S, 3);
    convertScaleAbs(bordes, bordesAbs);
    
    noiseSalt = Mat::zeros(gris.rows, gris.cols,CV_8U);
    randu(noiseSalt,sal,255);
    
    noisePimienta = Mat::zeros(gris.rows, gris.cols,CV_8U);
    randu(noisePimienta,pimienta,255);
    
    createTrackbar("RUIDO", "Ruido de sal",&sal, 255, trackBarEventHSV, NULL);
    createTrackbar("RUIDO", "Ruido de pimienta", &pimienta, 30, trackBarEventHSV, NULL); 

    a = noisePimienta <30;
    b = noiseSalt > 225;

    saltImg = gris.clone();
    pimientaImg = gris.clone();
    
    saltImg.setTo(255,b);
    pimientaImg.setTo(0,a);  
    
    medianBlur(saltImg, ruidoMediana, 3);
    GaussianBlur(pimientaImg, ruidoGaussiana, Size(3, 3), 2, 2);
    blur(saltImg, ruidoBlur, Size(5, 5));
    
    imshow("Original", gris);
    imshow("Ruido de sal",saltImg);
    imshow("Ruido de pimienta",pimientaImg);
    imshow("Filtro mediana",ruidoMediana);
    imshow("Filtro Gaussiano",ruidoGaussiana);
    imshow("Filtro Blur",ruidoBlur);
    imshow("Sobel Bordes 1",bordesAbs);
    imshow("Sobel Bordes 2",sobel2Abs);
    
    
    Mat laplace;
    Mat laplace_filtro_gaussiano;
    
    Laplacian(ruidoGaussiana, laplace_filtro_gaussiano, CV_16S, 3);
    convertScaleAbs(laplace_filtro_gaussiano, laplace_filtro_gaussiano);
    
    Laplacian(videoframe, laplace, CV_16S, 3);
    convertScaleAbs(laplace, laplace);
    
    namedWindow("Laplace", WINDOW_AUTOSIZE);
    moveWindow("Laplace",350, 550);
    imshow("Laplace", laplace);
    
    namedWindow("Laplace Gaussiano", WINDOW_AUTOSIZE);
    moveWindow("Laplace Gaussiano",1000, 550);
    imshow("Laplace Gaussiano", laplace_filtro_gaussiano);
        
     if(waitKey(23)==27)
                break;       
        }
    destroyAllWindows();  
    }
    return 0;
}
  
