#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "DIctionary.h"
#include <fstream>
using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
	ofstream f("text.txt", ios_base::out);

	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	for (int r = 0; r < image.rows - 10; r=r + 10)
	{
		for (int c = 0; c < image.cols - 10; c = c + 10)
		{
			string s;
			for (int i = r; i < r + 10; i = i+2)
			{
				int rem = 0;
				for (int j = c; j < c + 10; j = j+2)
				{
					if (rem + int(image.at<uchar>(i, j)) > 127)
					{
						s = s + '1';
						rem = rem - (255 - int(image.at<uchar>(i, j)));
					 }
					else
					{
						s = s + '0';
						rem = rem + int(image.at<uchar>(i, j));
					}
				}
			}
			auto it = dict.find(s);
			if (it != dict.end())
				f << (*it).second;
			else
			{
				auto z = dict.lower_bound(s);
				f << (*z).second;
			}
		}
		f << endl;
	}
	/*
	for (int r = 0; r < image.rows; r++) {
		cout << int(image.at<uchar>(r, image.cols / 2)) << ' ';
	}
	*/

	f.close();
	//namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	//imshow("Display window", image);                   // Show our image inside it.

	//waitKey(0);                                         
	return 0;
}