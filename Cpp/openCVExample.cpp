#include <opencv2/opencv.hpp>
#include <iostream>

// sudo apt install libopencv-dev
// g++ openCVExample.cpp `pkg-config --libs --cflags opencv4` -o example
// g++ openCVExample.cpp $(pkg-config --libs --cflags opencv4) -o example

using namespace cv;
using namespace std;

int main()
{
	std::cout<<"Example"<<std::endl;

	Mat image(500, 600);//, CV_8UC1, Scalar(220));
	//Mat image = imread("/usr/share/backgrounds/ryan-stone-skykomish-river.jpg");
	
	String windowName = "Example";
	namedWindow(windowName);
	imshow(windowName, image);
	waitKey(0);
	destroyWindow(windowName);

	return 0;
}
