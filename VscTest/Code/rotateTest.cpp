#include "ImageOperator.hpp"
#include <iostream>
#include "opencv2/opencv.hpp"



int main() {
    cv::VideoCapture cam(0);

    if (!cam.isOpened()) {
        throw std::runtime_error("Error");
    }

    cv::namedWindow("Window");
    cv::Mat input(350,350,CV_8UC3);
    
    while(true){
        cv::Mat frame;
        cam>>frame;
        cv::resize(frame, frame,cv::Size(350,350));
        cv::cvtColor(frame, input, cv::COLOR_BGR2GRAY);

        input = frame;

        cv::imshow("bgr_frame", frame);
        cv::imshow("gray_frame", input);
cv::waitKey(30);

        cv::Mat output_rotate(input.rows, input.cols, input.type());
        
        ImageOperator::rotateRGB(input.data,input.cols,input.rows,input.channels(),output_rotate.data);
        cv::imshow("rotate 90deg", output_rotate);

        ImageOperator::rotateRGB(output_rotate.data,output_rotate.cols,output_rotate.rows,output_rotate.channels(),output_rotate.data);
        cv::imshow("rotate 180deg", output_rotate);

        if(cv::waitKey(30) >= 0) break;
    }
    return 0;
}