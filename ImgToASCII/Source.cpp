#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "DIctionary.h"
#include <fstream>
using namespace cv;
using namespace std;


int main()
{
	
	ofstream f("text.txt", ios_base::out);
	
	string s;
	int scale;
	cout << "Enter image title: ";
	cin >> s;
	cout << "Enter how many times to reduce the image: ";
	cin >> scale;
	Mat image;
	image = imread(s, CV_LOAD_IMAGE_GRAYSCALE);  

	if (!image.data)                           
		cout << "Could not open or find the image" << endl;
	else 
		cout << "Open text.txt" << endl;

	for (int r = 0; r < image.rows - 5*scale; r = r + 5*scale)
	{
		for (int c = 0; c < image.cols - 5*scale; c = c + 5*scale)
		{
			int s = 0;
			int k = 0;
			for (int i = r; i < r + 5*scale; i = i + scale)
			{
				int rem = 0;
				for (int j = c; j < c + 5*scale; j = j + scale)
				{
					k++;
					if (rem + int(image.at<uchar>(i, j)) > 127)
					{
						s = s + pow(2, k - 1);
						rem = rem - (255 - int(image.at<uchar>(i, j)));
					}
					else
					{
						rem = rem + int(image.at<uchar>(i, j));
					}
				}
			}
			auto it = dict.find(s);
			if (it != dict.end())
				f << (*it).second << (*it).second;
			else
			{
				auto z1 = dict.lower_bound(s);
				auto z2 = dict.upper_bound(s);
				if ((*z2).first - s < s - (*z1).first)
					f << (*z2).second << (*z2).second;
				else f << (*z1).second << (*z1).second;
			}
		}
		f << endl;
	}

	f.close();
	system("pause");
	return 0;
}