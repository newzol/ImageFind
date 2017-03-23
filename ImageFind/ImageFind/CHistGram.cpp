//
//  CHistGram.cpp
//  ImageFind
//
//  Created by Dan Liu on 2017/3/23.
//  Copyright © 2017年 Dan Liu. All rights reserved.
//

#include "CHistGram.hpp"
CHistGram::CHistGram()
{
    graychannel[0]=0;
    colorchannel[0]=0;
    colorchannel[1]=1;
    colorchannel[2]=2;
    grayhistsize[0]=256;
    colorhistsize[0]=256;
    colorhistsize[1]=256;
    colorhistsize[2]=256;
    hranges[0]=0;
    hranges[1]=255;
    
};
CHistGram::~CHistGram()
{
}
//计算直方图
void CHistGram::CalcHistImage(cv::Mat &image, cv::MatND &hist, int channel)
{
    
    switch (channel)
    {
        case 1:
        {
            //先将图像转换成灰度图
            cv::cvtColor(image, image, CV_BGR2GRAY);
            const float *ranges[1]={hranges};
            //计算直方图
            cv::calcHist(&image,1,graychannel,cv::Mat(),hist,1,grayhistsize,ranges);
            break;
        }
        case 2:
        {
            const float *ranges[]={hranges,hranges,hranges};
            //计算多通道直方图
            cv::calcHist(&image,1,colorchannel,cv::Mat(),hist,3,colorhistsize,ranges);
            break;
        }
        default:
        {
            //std::cout<<"不支持的通道类型"<<std::endl;
            break;
        }
    }
    
}

void CHistGram::showImage(std::string szWinName,cv::Mat &image,int iSecon)
{
    cv::namedWindow(szWinName,CV_WINDOW_AUTOSIZE);
    cv::imshow(szWinName, image);
    cv::waitKey(iSecon);
}
//获取直方图
void CHistGram::getImageHist(cv::Mat &image, cv::MatND &hist)
{
    double dMax=0.0,dMin=0.0;
    cv::minMaxLoc(hist,&dMin, &dMax,0,0);
    int histsize = hist.rows;
    cv::Mat hisimage(histsize,histsize,CV_8U,cv::Scalar(255));
    int hpt = static_cast<int>(0.9*histsize);
    for(int i=0;i<histsize;i++)
    {
        float binVal=hist.at<float>(i);
        int intensity=static_cast<int>(binVal*hpt/dMax);
        line(hisimage,cv::Point(i,histsize),cv::Point(i,histsize-intensity),cv::Scalar::all(0));
    }
    image = hisimage.clone();
    return ;
}
//遍历图像的点使图像降低维度
void CHistGram::colorReduce(cv::Mat &image,int div)
{
    for(int i=0;i<image.rows;i++)
    {
        for(int j=0;i<image.cols;j++)
        {
            image.at<cv::Vec3b>(i,j)[0] = image.at<cv::Vec3b>(i,j)[0]/div*div + div/2;
            image.at<cv::Vec3b>(i,j)[1] = image.at<cv::Vec3b>(i,j)[1]/div*div + div/2;
            image.at<cv::Vec3b>(i,j)[2] = image.at<cv::Vec3b>(i,j)[2]/div*div + div/2;
        }
    }
    return ;
}
//使用指针
void CHistGram::colorReduce_ptr(const cv::Mat &image, cv::Mat &outimage, int div)
{
    //创建目的输出图像
    outimage.create(image.rows, image.cols, image.type());
    //获取行数并将三通道转换成一通道
    int nr = image.rows;
    int nl = image.cols*image.channels();
    for(int i=0;i<nr;i++)
    {
        //获取每一行的指针，并转换为行
        const uchar *pIndata = image.ptr<uchar>(i);
        uchar *pOutdata = outimage.ptr<uchar>(i);
        for(int l=0;l<nl;l++)
        {
            pOutdata[l]=pIndata[l]*div/div + div/2;
        }
        
    }
}
//根据图像是否连续进行判断
void CHistGram::colorReduce_con(const cv::Mat &image, cv::Mat &outimage, int div)
{
    //创建目的输出图像
    outimage.create(image.rows, image.cols, image.type());
    //获取行数并将三通道转换成一通道
    int nr = image.rows;
    int nc = image.cols;
    if(image.isContinuous()&&outimage.isContinuous())
    {
        nr = 1;
        nc = nc*image.rows*image.channels();
    }
    for(int k=0;k<nr;k++)
    {
        const uchar *pIndata = image.ptr<uchar>(k);
        uchar *pOutdata = outimage.ptr<uchar>(k);
        *(pOutdata++) = *(pIndata++) * div/div + div/2;
    }
    
}
//s使用迭代器进行访问
void CHistGram::colorReduce_itr(const cv::Mat &image, cv::Mat &outimage, int div)
{
    cv::MatConstIterator_<cv::Vec3b> itconbegin = image.begin<cv::Vec3b>();
    cv::MatConstIterator_<cv::Vec3b> itconend = image.end<cv::Vec3b>();
    cv::MatIterator_<cv::Vec3b> itbegin = outimage.begin<cv::Vec3b>();
    //cv::MatIterator_<cv::Vec3b> itend = outimage.end<cv::Vec3b>();
    while(itconbegin!=itconend)
    {
        (*itbegin)[0] = (*itconbegin)[0]/div*div + div/2;
        (*itbegin)[1] = (*itconbegin)[1]/div*div + div/2;
        (*itbegin)[2] = (*itconbegin)[2]/div*div + div/2;
        itconbegin++;
        itbegin++;
    }
    return ;
}
