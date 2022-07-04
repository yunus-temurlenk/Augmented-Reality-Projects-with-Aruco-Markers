#include <opencv2/aruco.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main()
{
    cv::Mat imgIn,imgOut;
    cv::Ptr<cv::aruco::Dictionary> dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    cv::namedWindow("Out",0);

    cv::VideoCapture capIn("/ur/camera/stream/video/path.mp4");//or your camera id
    cv::VideoCapture capOut("/ur/video/to/paste/a.mp4");


    while(1)
    {
        capIn>>imgIn;
        capOut>>imgOut;

        cv::Mat frame = imgIn.clone();

        std::vector<std::vector<cv::Point2f>> corners;
        std::vector<int> ids;

        cv::aruco::detectMarkers(imgIn,dict,corners,ids);
        std::vector<cv::Point2f> ptsOut(4);

        int cnt = 0;

        for(int i=0; i<(int)ids.size(); i++)
        {
            if(ids[i] == 0)
            {
                cnt++;
                int x=(corners[i][0].x+corners[i][2].x)/2;
                int y=(corners[i][0].y+corners[i][2].y)/2;

                ptsOut[0] = (cv::Point2f(x,y));
            }
            else if(ids[i] == 34)
            {
                cnt++;

                int x=(corners[i][0].x+corners[i][2].x)/2;
                int y=(corners[i][0].y+corners[i][2].y)/2;

                ptsOut[1] = (cv::Point2f(x,y));
            }
            else if(ids[i] == 30)
            {
                cnt++;

                int x=(corners[i][0].x+corners[i][2].x)/2;
                int y=(corners[i][0].y+corners[i][2].y)/2;

                ptsOut[2] = (cv::Point2f(x,y));
            }
            else if(ids[i] == 4)
            {
                cnt++;

                int x=(corners[i][0].x+corners[i][2].x)/2;
                int y=(corners[i][0].y+corners[i][2].y)/2;

                ptsOut[3] = (cv::Point2f(x,y));
            }
        }

        //input point
        cv::Point2f inPoints[4];
        inPoints[0] = cv::Point2f(0,0);
        inPoints[1] = cv::Point2f(imgOut.cols,0);
        inPoints[2] = cv::Point2f(0,imgOut.rows);
        inPoints[3] = cv::Point2f(imgOut.cols,imgOut.rows);

        //destination points
        cv::Point2f outPoints[4];
        outPoints[0] = ptsOut[0];
        outPoints[1] = ptsOut[1];
        outPoints[2] = ptsOut[2];
        outPoints[3] = ptsOut[3];

        cv::Mat matrix = cv::getPerspectiveTransform(inPoints,outPoints);
        cv::warpPerspective(imgOut,imgIn,matrix,imgIn.size());
        if(cnt == 4)
        {
            for(int i=0; i<imgIn.cols; i++)
            {
                for(int j=0; j<imgIn.rows; j++)
                {
                    if(imgIn.at<cv::Vec3b>(cv::Point(i,j))[0] <= 5
                            && imgIn.at<cv::Vec3b>(cv::Point(i,j))[1] <= 5
                            && imgIn.at<cv::Vec3b>(cv::Point(i,j))[2] <= 5)
                        imgIn.at<cv::Vec3b>(cv::Point(i,j)) = frame.at<cv::Vec3b>(cv::Point(i,j));
                }
            }


            cv::imshow("Out",imgIn);
            cv::waitKey(1);
        }
    }r

}






















