#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

 Mat src_gray;
int thresh = 100;
int max_thresh = 255;
int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;
RNG rng(12345);

/// Function header
void thresh_callback();
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
   string filename = "../shapes.mp4";
    VideoCapture capture(filename);
    Mat frame;

    if( !capture.isOpened() )
        throw "Error when reading video";
     for( ; ; )
    {
        capture >> frame;
        if(frame.empty())
            break;
         cvtColor( frame, src_gray, CV_BGR2GRAY );
  		 blur( src_gray, src_gray, Size(3,3) );

  		/// Create Window
		string source_window = "Source";
  		namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  		imshow( source_window, frame );
  		thresh_callback();
        waitKey(20); // waits to display frame
    }
    // releases and window destroy are automatic in C++ interface


  waitKey(0);
  return(0);
}

void thresh_callback()
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Point> anglescount;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
        approxPolyDP(contours[i],anglescount,0.01*arcLength(contours[i],true), true );
        cout<<"contours "<<anglescount.size()<<endl;
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       if(anglescount.size()>2 && anglescount.size() <10)
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}