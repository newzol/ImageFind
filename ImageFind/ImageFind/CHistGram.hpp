//
//  CHistGram.hpp
//  ImageFind
//
//  Created by Dan Liu on 2017/3/23.
//  Copyright © 2017年 Dan Liu. All rights reserved.
//

#ifndef CHistGram_hpp
#define CHistGram_hpp

#include <stdio.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
class CHistGram
{
public:
    CHistGram();
    ~CHistGram();
private:
    int graychannel[1];
    int colorchannel[3];
    int grayhistsize[1];
    int colorhistsize[3];
    float hranges[2]={0,255};
public:
    //点遍历
    void colorReduce(cv::Mat &image,int div);
    //指针遍历
    void colorReduce_ptr(const cv::Mat &image,cv::Mat &outimage,int div);
    //通过遍历图像是否连续进行处理
    void colorReduce_con(const cv::Mat &image,cv::Mat &outimage,int div);
    //通过迭代器进行遍历
    void colorReduce_itr(const cv::Mat &image,cv::Mat &outimage,int div);
    //channel 1:灰度 单通道 2 彩色，三通到
    void CalcHistImage(cv::Mat &image,cv::MatND &hist,int channel);
    cv::Mat getHistImage(cv::MatND &hist);
    void getImageHist(cv::Mat &image,cv::MatND &hist);
    void showImage(std::string strWinName,cv::Mat &image,int iSecon);
};

#endif /* CHistGram_hpp */
