#include "filter.h"

bool createMask(const vector<vector<string>>& mask, Mat& realMask, float& sum, float& maskSum);
void readFilterText(vector<vector<string>>& mask, const string filterPath);

int main(int argc, char **argv) {
	path imagesFolderPath(argv[1]);
	path filterTextPath(argv[2]);
	path outputFolderPath(argv[3]);

	string filterPath = filterTextPath.string();
	vector<vector<string>> mask;
	readFilterText(mask, filterPath);

	Mat realMask = Mat::zeros(Size(stoi(mask[0][1]), stoi(mask[0][0])), CV_32FC1);
	float lowPassMaskSum = 0.0;
	float highPassMaskSum = 0.0;
	bool passFilter = createMask(mask, realMask, lowPassMaskSum, highPassMaskSum);


	directory_iterator end_itr;
	directory_iterator itr(imagesFolderPath);
	for (directory_iterator itr(imagesFolderPath); itr != end_itr; ++itr) {
		string bmpCheck = itr->path().extension().string();
		if (bmpCheck == ".bmp" || bmpCheck == ".BMP") {
			//cout << itr->path().filename().string() << endl;

			Mat image = imread(itr->path().string(), IMREAD_GRAYSCALE);
			Mat filterImage = Mat::zeros(Size(image.cols, image.rows), CV_32FC1);
			Filter filter;
			filter.computeFilter(image, realMask, filterImage, passFilter, lowPassMaskSum, highPassMaskSum);

			string outputFile = outputFolderPath.string();
			outputFile.append("/");
			outputFile.append(itr->path().filename().string());
			//cout << outputFile << endl;
			imwrite(outputFile, filterImage);
		}
	}
	return 0;
}


bool createMask(const vector<vector<string>>& mask, Mat& realMask, float& lowPassMaskSum, float& highPassMaskSum) {
	bool passFilter;
	if (mask[1][0] == "L") { passFilter = true; }
	else { passFilter = false; }

	for (int i = 0; i < stoi(mask[0][0]); i++) {
		for (int j = 0; j < stoi(mask[0][1]); j++) {
			realMask.at<float>(i, j) = (float)(stoi(mask[2 + i][j]));
			lowPassMaskSum += realMask.at<float>(i, j);
			if (realMask.at<float>(i, j) > 0) {
				highPassMaskSum += realMask.at<float>(i, j);
			}
		}
	}
	return passFilter;
}

void readFilterText(vector<vector<string>>& mask, const string filterPath) {
	boost::filesystem::fstream filter;
	filter.open(filterPath);
	string line;

	while (getline(filter, line)) {
		istringstream is(line);
		mask.push_back(
			vector<string>(istream_iterator<string>(is),
				istream_iterator<string>()));
	}
	filter.close();
}