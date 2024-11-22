#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
//#include <cmath>
using namespace std;
using namespace cv;

int t,b=1;
VideoCapture video("../video/video.mp4");

void ChangeTime(int,void*){
    video.set(CAP_PROP_POS_FRAMES,t);//调整视频进度
}

void ChangeBlurSize(int,void*){

}

int main(){
    int start;
    float time;
    //VideoCapture video("../video/video.mp4");
    namedWindow("time", cv::WINDOW_AUTOSIZE);//视频进度条
    createTrackbar("time","time",&t,video.get(CAP_PROP_FRAME_COUNT),ChangeTime);
    namedWindow("size", cv::WINDOW_AUTOSIZE);//
    createTrackbar("size","size",&b,5,ChangeBlurSize);
    while(1){
        Mat frame,gray,binary,Blur,sharp,canny,mor;
        vector<Vec3f> circles;
        video>>frame;
        if(frame.empty()){
            break;
        }
        start=clock();
        cvtColor(frame,gray,COLOR_BGR2GRAY);//转换为灰度图
        //threshold(gray,binary,110,255,THRESH_BINARY);
        //blur(gray,Blur,Size(5,5));//滤波
        GaussianBlur(gray,Blur,Size(2*b+1,2*b+1),0,0);//高斯滤波
        //morphologyEx(Blur,mor,MORPH_OPEN,getStructuringElement(0,Size(3,3)));
        //Laplacian(gray,sharp,CV_8U,1);
        Canny(Blur,canny,110,0);//锐化
        HoughCircles(Blur,circles,HOUGH_GRADIENT,2,10,100,100,20,30);//检测半径20-30的圆形
        time=(float)(clock()-start)/CLOCKS_PER_SEC;
        for(size_t i=0;i<circles.size();i++){
            Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));
            Point Pt1,Pt2,text;
            int r=cvRound(circles[i][2]);
            Pt1=Point(cvRound(circles[i][0])-25,cvRound(circles[i][1])-25);
            Pt2=Point(cvRound(circles[i][0])+25,cvRound(circles[i][1])+25);
            text=Point(cvRound(circles[i][0])-50,cvRound(circles[i][1])-30);
            rectangle(frame,Pt1,Pt2,Scalar(0,0,255),15);
            //circle(frame,center,3,Scalar(0,0,255),-1,8,0);
            putText(frame,to_string(time),text,2,1,Scalar(255,255,255),2);
            //circle(frame,center,r,Scalar(0,0,255),3,8,0);
        }//标记圆形
        //imshow("video",gray);
        //imshow("video2",binary);
        //imshow("sharp",sharp);
        //imshow("blur",Blur);
        //imshow("canny",canny);
        imshow("marker",frame);
        if(waitKey(1000/video.get(CAP_PROP_FPS))==27)break;//esc中断
    }
    waitKey();
    return 0;
}