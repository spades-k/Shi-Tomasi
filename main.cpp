#include <QCoreApplication>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "Shi-Tomasi"

Mat g_srcImage,g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);

void on_GoodFeaturesToTrack(int,void*)
{
    if(g_maxCornerNumber <= 1)
    {
        g_maxCornerNumber = 1;
    }

    vector<Point2f> corners;
    double qualityLevel = 0.01;
    double minDistance =10;
    int blockSize = 3;
    double k =0.04;
    Mat copy = g_srcImage.clone();

    goodFeaturesToTrack(g_grayImage,corners,g_maxCornerNumber,qualityLevel,minDistance,Mat(),blockSize,false,k);
    cout << "> the number of corners is " << corners.size()<<endl;

    int r=4;
    for (unsigned int i =0;i<corners.size();i++)
    {
        circle(copy,corners[i],r,Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255)),-1,8,0);

    }
    imshow(WINDOW_NAME,copy);


    Size winSize =Size(5,5);
    Size zeroZone= Size(-1,-1);

    TermCriteria criteria =TermCriteria(TermCriteria::EPS+TermCriteria::MAX_ITER,40,0.01);

    cornerSubPix(g_grayImage,corners,winSize,zeroZone,criteria);


    for (int i =0 ; i < corners.size() ; i++)
    {
        cout << " \t>>zuobiao[" << i << "](" << corners[i].x <<"," <<corners[i].y << ")" << endl;
    }

}

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    g_srcImage = imread("/home/spadesk/workspace/lena.jpg",1);
    if (!g_srcImage.data)
    {
        printf("something wrong!");
    }
    cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);

    namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
    createTrackbar("maxCornerNumber",WINDOW_NAME,&g_maxCornerNumber,g_maxTrackbarNumber,on_GoodFeaturesToTrack);
    imshow(WINDOW_NAME,g_srcImage);
    on_GoodFeaturesToTrack(0,0);

    waitKey(0);
    return 0;
//    return a.exec();
}

