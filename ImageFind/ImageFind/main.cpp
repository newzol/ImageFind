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
    char szHome[128]={0};
    snprintf(szHome, 128, "%s//%s",getenv("HOME"),"//Documents//dev");
    std::string strPath(szHome);
    strPath.append("//linxinru.jpg");
    srcImage =cv::imread(strPath.c_str());// 加载图片文件
    if(NULL==srcImage.data) //校验是否加载的图像为空
    {
        std::cout<<"加载图片失败"<<__LINE__<<std::endl;
        return -1;
    }
     std::string desPath(szHome);
    desPath.append("//pengyuyan.jpeg");
    destImage= cv::imread(desPath.c_str());// 加载图片文件
    if(NULL==destImage.data) //校验是否加载的图像为空
    {
        std::cout<<"加载图片失败"<<__LINE__<<std::endl;
        std::cout<<getenv("HOME")<<std::endl;
        return -1;
    }
    CHistGram myhist;
   // myhist.showImage("dest", destImage, 5000);
    myhist.colorReduce_con(srcImage, osrcImage, 64);
    myhist.colorReduce_con(destImage,odestImage,64);
    cv::MatND srcHist,destHist;
    myhist.CalcHistImage(srcImage, srcHist, 1);
    myhist.CalcHistImage(destImage, destHist, 1);
    //myhist.showImage("dest", destImage, 5000);
    cv::normalize(srcHist, srcHist);
    cv::normalize(destHist, destHist);
    double dist1;
    dist1=cv::compareHist(srcHist,destHist,CV_COMP_CORREL);//CV_COMP_BHATTACHARYYA);
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
