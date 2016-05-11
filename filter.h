
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp> 
#include <boost/filesystem.hpp>
//#include <iostream>
#include <string>
#include <vector>


using namespace boost::filesystem;
using namespace cv;
using namespace std;

class Filter {

public:
	void computeFilter(const Mat& image, const Mat& realMask, Mat& filterImage, bool passFilter, int lowPassMaskSum, int highPassMaskSum) {
		int a = (realMask.rows - 1) / 2;
		int b = (realMask.cols - 1) / 2;
		//Mat test = imread("./test.bmp", IMREAD_GRAYSCALE);
		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				double eachPixelValue = 0.0;
				for (int s = -a; s <= a; s++) {
					for (int t = -b; t <= b; t++) {
						if (i - s >= 0 && j - t >= 0 && i - s < image.rows && j - t < image.cols) {
							eachPixelValue += realMask.at<float>(s + a, t + b) * image.at<uchar>(i - s, j - t);
						}
						else {
							eachPixelValue += realMask.at<float>(s + a, t + b) * 128.0;
						}
					}
				}
				float computedPixelValue = 0;
				if (passFilter == true) {
					computedPixelValue = ((float)eachPixelValue / lowPassMaskSum);
				}
				else {
					computedPixelValue = (float)eachPixelValue;
					computedPixelValue += highPassMaskSum * 255.0;
					computedPixelValue = computedPixelValue / (highPassMaskSum * 2.0);
				}

				filterImage.at<float>(i, j) = computedPixelValue;

				/*///////////////////////////////////////////////TESTING //////////////////////////////////////////////////





				double testPixelValue = test.at<uchar>(i, j);
				double errorValue = 0.0;
				double fraction = computedPixelValue;

				fraction = fraction - (long)fraction;

				if (fraction >= 0.5) {
				computedPixelValue += (1 - fraction);
				}
				else {
				computedPixelValue -= (fraction);
				}

				errorValue = computedPixelValue;
				errorValue = errorValue - testPixelValue;
				if (fabs(errorValue) >= 1.0) {
				cout << ": " << (float)(test.at<uchar>(i, j)) << "  ,  " << filterImage.at<float>(i, j) << "-----------  " << errorValue << endl;
				}*/
			}
		}
	};

};