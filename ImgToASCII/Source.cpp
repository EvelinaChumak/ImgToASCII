#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Dictionary.h"
using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		cout << "Not enought arguments";
		return 0;
	}
	ofstream f(argv[4], ios_base::out);

	FullDict();
	string s;

	int white_balance = stoi(argv[3]);
	int scale = stoi(argv[2]);
	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);					//read image as grayscale
	if (!image.data)                           
		cout << "Could not open or find the image" << endl;
	else
	{

		for (int r = 0; r < image.rows - 5 * scale; r = r + 5 * scale)
		{
			for (int c = 0; c < image.cols - 5 * scale; c = c + 5 * scale)
			{
				int s = 0;											// for character encoding
				int k = 0;
				for (int i = r; i < r + 5 * scale; i = i + scale)
				{
					int rem = 0;									// for exact definition of "black" or "white" pixel
					for (int j = c; j < c + 5 * scale; j = j + scale)
					{
						k++;
						if (rem + int(image.at<uchar>(i, j)) > 127)
						{
							s = s + pow(2, k - 1);					//looking for number that encoded the whole block
							rem = rem - (white_balance*2 - int(image.at<uchar>(i, j)));
						}
						else
						{
							rem = rem + int(image.at<uchar>(i, j));
						}
					}
				}
				auto it = dict.find(s);								//looking for an appropriate number int the dictionary
				if (it != dict.end())								//an add a character to the text
					f << (*it).second << (*it).second;
				else
				{
					auto z1 = dict.lower_bound(s);
					auto z2 = dict.upper_bound(s);
					if ((*z2).first - s < s - (*z1).first)			//look for the nearest matching character
						f << (*z2).second << (*z2).second;
					else f << (*z1).second << (*z1).second;
				}
			}
			f << endl;
		}
		cout << "Open " << argv[4] << endl;
	}
	f.close();
	return 0;
}