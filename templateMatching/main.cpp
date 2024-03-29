#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv)
{
  cv::Mat ref = cv::imread(argv[1], 1);
  cv::Mat tpl = cv::imread(argv[2], 1);
  if (ref.empty() || tpl.empty())
    return -1;

  cv::Mat gref, gtpl;
  cv::cvtColor(ref, gref, CV_BGR2GRAY);
  cv::cvtColor(tpl, gtpl, CV_BGR2GRAY);

  cv::Mat res(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
  cv::matchTemplate(gref, gtpl, res, CV_TM_CCOEFF_NORMED);
  cv::threshold(res, res, 0.8, 1., CV_THRESH_TOZERO);

  while (true)
  {
    double minval, maxval, threshold = 0.8;
    cv::Point minloc, maxloc;
    cv::minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

    if (maxval >= threshold)
    {
      cv::rectangle(
        ref,
        maxloc,
        cv::Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows),
        CV_RGB(0, 255, 0), 2
      );
      line(ref, cv::Point(0,maxloc.y+tpl.rows), cv::Point(ref.cols, maxloc.y+tpl.rows) ,CV_RGB(255, 0, 0));
      line(ref, cv::Point(0,maxloc.y), cv::Point(ref.cols, maxloc.y) ,CV_RGB(255, 0, 0));
      cv::floodFill(res, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));
    }
    else
      break;
  }

  cv::imshow("reference", ref);
  cv::waitKey();
  return 0;
}