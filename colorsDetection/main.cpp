#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
 
int main(int argc, const char **argv) {
	Mat cameraFrame;
	int idcam=0;
	VideoCapture camera;   
	 if(argc>1)
	 	idcam=atoi(argv[1]);
	 camera.open(idcam);
	if (!camera.isOpened()) { 
			cout << "cannot open camera";
	}
	
	while (true) {
		camera.read(cameraFrame);
		imshow("cam", cameraFrame);
		if (waitKey(30) >= 0)
			break;
	}
	return 0;
}