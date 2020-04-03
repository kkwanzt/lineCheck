// lineCheck.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int thresholdvaluemin = 100;
int thresholdvaluemax = 255;

void capCanny();//调用摄像头并进行canny操作
void xuanzhuan(Mat src);
void imagePers(Mat src);

int main()
{
    Mat src=imread("D:\\opencv\\myproject\\1picture\\lena.jpg");
    if (src.empty())
    {
        printf("can't get the picture");
        return -1;
    }
    void capCanny();
    xuanzhuan(src);
    imagePers(src);
    return 0;
}

void capCanny()//调用摄像头并进行canny操作
{
    VideoCapture cap(0);
    Mat edge,edgs;
    while (1) {
        Mat frame;
        cap >> frame;
        cvtColor(frame, edge, CV_BGR2GRAY);
        Canny(edge,edge, thresholdvaluemin, thresholdvaluemax, 3, false);
    }
    
    imshow("cannydst", edge);
    waitKey(30);
}

void xuanzhuan(Mat src)
{
    Mat dstroll;
    float angle = -10.0, scale = 1;
    cv::Point2f center(src.cols * 0.5, src.rows * 0.5);
    const cv::Mat affine_matrix = getRotationMatrix2D(center, angle, scale);

    cv::warpAffine(src, dstroll, affine_matrix, src.size());
    imshow("dstroll", dstroll);
    waitKey(0);
}

void imagePers(Mat src)//仿射投影
{
    cv::Mat dstpers;
    cv::Mat dstwap;
    cv::Point2f ptrs[] = {//映射前四点
        Point2f(150,150),
        Point2f(150, 300),
        Point2f(350, 300),
        Point2f(350, 150)
    };
    cv::Point2f ptrs1[] = {//映射后坐标
        Point2f(200,150),
        Point2f(200,300),
        Point2f(340,270),
        Point2f(340,180)
    };

    cv::Point2f ptrs2[] = {//仿射前三点
        Point2f(200,200),
        Point2f(250,200),
        Point2f(200,100)
    };
    cv::Point2f ptrs3[] = {//仿射后坐标
        Point2f(300,100),
        Point2f(300,50),
        Point2f(250,100)
    };
    cv::Mat perspective_matrix = getPerspectiveTransform(ptrs,ptrs1);
    cv::Mat affine_matrix = getPerspectiveTransform(ptrs2, ptrs3);

    cv::warpAffine(src, dstpers, perspective_matrix, src.size());//映射
    cv::warpAffine(src, dstwap, affine_matrix, src.size());//仿射
    
    imshow("dstpers", dstpers);
    imshow("dstwap", dstwap);
    waitKey(0);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
