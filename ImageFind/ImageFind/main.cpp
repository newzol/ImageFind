//
//  main.cpp
//  ImageFind
//
//  Created by Dan Liu on 2017/3/22.
//  Copyright © 2017年 Dan Liu. All rights reserved.
//

#include <iostream>
#include "CHistGram.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    cv::Mat srcImage,destImage;
    cv::Mat osrcImage,odestImage;
    ////Users//danliu//Documents/dev//
    srcImage =cv::imread("//Users//danliu//Documents/dev//linxinru.jpeg");// 加载图片文件
    if(NULL==srcImage.data) //校验是否加载的图像为空
    {
        std::cout<<"加载图片失败"<<std::endl;
        return -1;
    }
    destImage= cv::imread("//Users//danliu//Documents/dev//linxinru.jpeg");// 加载图片文件
    CHistGram myhist;
   // myhist.showImage("dest", destImage, 5000);
    myhist.colorReduce_con(srcImage, osrcImage, 64);
    myhist.colorReduce_con(destImage,odestImage,64);
    cv::MatND srcHist,destHist;
    myhist.CalcHistImage(srcImage, srcHist, 1);
    myhist.CalcHistImage(destImage, destHist, 1);
    myhist.showImage("dest", destImage, 5000);
    cv::normalize(srcHist, srcHist);
    cv::normalize(destHist, destHist);
    double dist1;
    dist1=cv::compareHist(srcHist,destHist,CV_COMP_BHATTACHARYYA);
    if(dist1 >0.5)
    {
        std::cout<<"MATCH"<<std::endl;
    }
    else
    {
        std::cout<<"NO MATCH"<<std::endl;
    }
    std::cout<<"匹配率为："<<dist1<<std::endl;
    return 0;
}
