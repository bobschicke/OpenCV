
#include "ImageOperator.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"

int main() {

    //This is for testing with a cam
    cv::VideoCapture cam(0);
    if (!cam.isOpened()) {
        throw std::runtime_error("Error");
    }

    //This is for testing with an image
    //std::string img = "lenna.jpg";
    //cv::Mat srcImage = cv::imread(img);
    //cv::imshow("srcImage", srcImage);
    //if (!srcImage.data) {
    //    return 1;
    //}
    //cv::waitKey(10000);

    cv::namedWindow("Window");
    cv::Mat output(350,350,CV_8UC1);
    cv::Mat rgb_output(350,350,CV_8UC3);
    
    while(true){
        cv::Mat frame;
        
        //This is for testing with a cam
        cam>>frame;

        //This is for testing with an image
        //frame = srcImage;
        //cv::imshow("frame", frame);
    //cv::waitKey(10000);

        cv::resize(frame, frame,cv::Size(350,350));

        cv::imshow("bgr_frame", frame);
    //cv::waitKey(10000);

        cv::cvtColor(frame, output, cv::COLOR_BGR2GRAY);
        cv::imshow("opencv_func", output);
    //cv::waitKey(10000);

        ImageOperator::to_gray_m1(frame,output);
        cv::imshow("to_gray_m1",output);
    //cv::waitKey(10000);

        ImageOperator::to_gray_m2(frame,output);
        cv::imshow("to_gray_m2",output);
    //cv::waitKey(10000);

        ImageOperator::to_gray_m3(frame,output);
        cv::imshow("to_gray_m3",output);
    //cv::waitKey(10000);

        ///No OpenCV
        const unsigned char* bgr_input = (unsigned char*)frame.data;
        unsigned char* gray_output = new unsigned char[frame.rows*frame.cols];
        ImageOperator::to_gray(bgr_input,frame.cols,frame.rows,frame.channels(),gray_output);
        cv::Mat output_gray(frame.rows, frame.cols, CV_8UC1, gray_output);
        cv::imshow("to_gray_no_opencv", output_gray);
        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}
