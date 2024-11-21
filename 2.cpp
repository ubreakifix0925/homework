#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace cv;

int t;
VideoCapture video("../video/video.mp4");

void ChangeTime(int,void*){
    video.set(CAP_PROP_POS_FRAMES,t);//调整视频进度
}

int main(){
    //VideoCapture video("../video/video.mp4");
    namedWindow("time", cv::WINDOW_AUTOSIZE);//视频进度条
    createTrackbar("time","time",&t,video.get(CAP_PROP_FRAME_COUNT),ChangeTime);
    while(1){
        Mat frame,gray,binary,blur,sharp,canny;
        vector<Vec3f> circles;
        video>>frame;
        if(frame.empty()){
            break;
        }
        cvtColor(frame,gray,COLOR_BGR2GRAY);//转换为灰度图
        //threshold(gray,binary,110,255,THRESH_BINARY);
        GaussianBlur(gray,blur,Size(3,3),10,20);//高斯模糊
        //Laplacian(gray,sharp,CV_8U,1);
        Canny(blur,canny,110,0);//锐化
        HoughCircles(canny,circles,HOUGH_GRADIENT,2,10,100,100,20,30);//检测半径20-30的圆形
        for(size_t i=0;i<circles.size();i++){
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
            int r=cvRound(circles[i][2]);
            circle(frame,center,3,Scalar(0,0,255),-1,8,0);
            putText(frame,"aim",center,0,2,Scalar(255,255,255));
            circle(frame,center,r,Scalar(0,0,255),3,8,0);
        }//标记圆形
        //imshow("video",gray);
        //imshow("video2",binary);
        //imshow("sharp",sharp);
        //imshow("blur",blur);
        imshow("canny",canny);
        imshow("marker",frame);
        if(waitKey(1000/video.get(CAP_PROP_FPS))==27)break;//esc中断
    }
    waitKey();
    return 0;
}