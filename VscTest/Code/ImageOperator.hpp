#include <iostream>
#include "opencv2/opencv.hpp"


class ImageOperator{
public:
    ImageOperator() = default;
    ~ImageOperator() = default;
    
    static void to_gray_m1(const cv::Mat& input, cv::Mat& output);
    static void to_gray_m2(const cv::Mat& input, cv::Mat& output);
    static void to_gray_m3(const cv::Mat& input, cv::Mat& output);
    static void to_gray(const unsigned char* input,
                        const int width,
                        const int height,
                        const int channel,
                        unsigned char* output);
    static void rotate(const unsigned char* input,
                           const int width,
                           const int height,
                           const int channel,
                           unsigned char*& output);
    static void rotateRGB(const unsigned char* input,
                   const int width,
                   const int height,
                   const int channel,
                   unsigned char*& output);


};


void ImageOperator::to_gray_m1(const cv::Mat &input, cv::Mat &output) {
  
    unsigned char *data_out = (unsigned char*)(output.data);
    int ind = 0;
    auto end = input.end<cv::Vec3b>();
    cv::MatConstIterator_<cv::Vec3b> it = input.begin<cv::Vec3b>();
    for (; it != end; ++it) {
        const unsigned char &r = (*it)[2];
        const unsigned char &g = (*it)[1];
        const unsigned char &b = (*it)[0];
        data_out[ind] = 0.3*r+0.59*g+0.11*b;
        ind++;
    }

}

void ImageOperator::to_gray_m2(const cv::Mat &input, cv::Mat &output) {
    unsigned char *data_in = (unsigned char*)(input.data);
    unsigned char *data_out = (unsigned char*)(output.data);

    int index = 0;
    int byte_size = input.channels()*input.rows*input.cols;
    while(index!=byte_size){
        data_out[index/input.channels()] = unsigned(0.11*data_in[index]+0.59*data_in[index+1]+0.3*data_in[index+2]);

        index+=3;
    }
}

void ImageOperator::to_gray_m3(const cv::Mat &input, cv::Mat &output) {

    unsigned char *data_in = (unsigned char*)(input.data);
    unsigned char *data_out = (unsigned char*)(output.data);

    int index = 0;
    for (int row = 0; row < input.rows; ++row) {
        for (int col = 0; col < input.cols*input.channels(); col+=input.channels()) {
            data_out[index]= 0.11*data_in[row*input.step+col]+
                             0.59*data_in[row*input.step+col+1]+
                             0.3*data_in[row*input.step+col+2];
            index++;
        }
    }
}

void ImageOperator::to_gray(const unsigned char* bgr_input,
                            const int width,
                            const int height,
                            const int channel,
                            unsigned char* gray_output){
    int index = 0;
    int step = channel*width;
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width*channel; col+=channel) {
            gray_output[index] = 0.11*bgr_input[row*step+col]+
                             0.59*bgr_input[row*step+col+1]+
                             0.3*bgr_input[row*step+col+2];
            index++;
        }
    }
}

void ImageOperator::rotate(const unsigned char* input,
                           const int width,
                           const int height,
                           const int channel,
                           unsigned char*& output){

    unsigned char* tmp = new unsigned char[width*height*channel];
    for (int row = 0; row < height; ++row) {
        for (int col = 0; col < width; col+=1) {
            tmp[col*width+width-1-row] = input[row*width+col];
        }
    }
    output = tmp;
}

void ImageOperator::rotateRGB(const unsigned char* input,
                   const int width,
                   const int height,
                   const int channel,
                   unsigned char*& output){

    int temp = 0;
    unsigned char* tmp = new unsigned char[width*height*channel];
    int step = channel*width;
    for (int row = 0; row < height; ++row) {

        for (int col = 0; col < width*channel; col+=channel) {
            for (int chan = 0; chan < channel; ++chan) {
                if(row == 349 && col == 340) 
                    ++temp;
               tmp[(col/channel)*step+(step-row*channel-1)+chan-(channel-1)] = input[row*step+col+chan];

            }
        }
    }
    output = tmp;

}