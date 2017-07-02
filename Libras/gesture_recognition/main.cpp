#include "opencv2/opencv.hpp"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/video/background_segm.hpp"
#include "windows.h"

using namespace cv;
using namespace std;

int iLowH = 0;
int iHighH = 13;

int iLowS = 0;
int iHighS = 255;

int iLowV = 0;
int iHighV = 255;

Mat GetSkin(Mat const &src) {
    Mat imgHSV = src.clone();
    cvtColor(imgHSV, imgHSV, COLOR_BGR2HSV);
    Mat imgThresholded;
    inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
    return imgThresholded;
}

int main(int, char**)
{
    int hasParameters = 0;
    int option = 1;
    int configuration = 0;
    time_t start = time(0);

    VideoCapture capUm(0); // open the default camera
    capUm.set(CV_CAP_PROP_FRAME_WIDTH,600);
    capUm.set(CV_CAP_PROP_FRAME_HEIGHT,400);
    capUm.set(CV_CAP_PROP_FPS,10);
    //VideoCapture capUm("hand1.mov");

    /*if ( !capUm.isOpened() )  { // if not success, exit program
        cout << "Cannot open the video file" << endl;
        return -1;
    }*/

    //namedWindow("Original",1);
    namedWindow("Filtered",1);

    //Create trackbars in "Control" window
    createTrackbar("LowH", "Control", &iLowH, 255); //Hue (0 - 179)
    createTrackbar("HighH", "Control", &iHighH, 255);

    createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
    createTrackbar("HighS", "Control", &iHighS, 255);

    createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
    createTrackbar("HighV", "Control", &iHighV, 255);

    Mat frame, filtered_frame, original;

    while(1){

        capUm >> frame; // get a new frame from camera
        //frame = cv::imread("im01.jpg");

        if(frame.empty()==0) {
            //resize(frame, frame, Size(), 0.5, 0.5, INTER_LINEAR);

            //adjust frame
            /*Point2f src_center(frame.cols/2.0F, frame.rows/2.0F);
            Mat rot_mat = getRotationMatrix2D(src_center, 180, 1);
            warpAffine(frame, frame, rot_mat, frame.size());*/

            frame.copyTo(original);

            /*Size kSize;
            kSize.height = 3;
            kSize.width = 3;
            double sigma = 0.3*(3/2 - 1) + 0.8;
            GaussianBlur(frame,frame,kSize,sigma,0.0,4);
            medianBlur(frame,frame,11);*/

            //medianBlur(frame,frame,11);
            filtered_frame = GetSkin(frame);
            medianBlur(filtered_frame,filtered_frame,11);

            //morphological opening (removes small objects from the foreground)
            erode(filtered_frame, filtered_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( filtered_frame, filtered_frame, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

             //morphological closing (removes small holes from the foreground)
            dilate( filtered_frame, filtered_frame, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)) );
            erode(filtered_frame, filtered_frame, getStructuringElement(MORPH_ELLIPSE, Size(15, 15)) );

            //int Hmin=256, Hmax=0, Smin=256, Smax=0, Vmin=256, Vmax=0;
            if(hasParameters == 0) {

                double elapsedTime = difftime(time(0), start);
                if (elapsedTime == 3) {
                    option += 1;
                    start = time(0);
                    elapsedTime = 0;
                }

                char text[100];
                sprintf(text,"Qual destas configuracoes eh a melhor para ver sua mao?");
                putText(frame,text, Point(100,30) , FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0), 2, 8, false);

                if (configuration == 0) {
                    sprintf(text,"Option %d", option);
                    putText(frame,text, Point(120,60) , FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0), 2,8,false );

                    if (option == 1) {
                        iLowS = 0;
                    } else if (option == 2) {
                        iLowS = 40;
                    } else if (option == 3) {
                        iLowS = 80;
                    } else if (option == 4) {
                        iLowS = 120;
                    } else if (option >= 5) {
                        iLowS = 160;
                        if (option == 6) {
                            option = 1;
                        }
                    }

                    if( GetAsyncKeyState( '1' ) & 0x8000 ) {
                        cout << "Key 1 pressed" << std::endl;
                        iLowS = 0;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '2' ) & 0x8000 ) {
                        cout << "Key 2 pressed" << std::endl;
                        iLowS = 40;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '3' ) & 0x8000 ) {
                        cout << "Key 3 pressed" << std::endl;
                        iLowS = 80;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '4' ) & 0x8000 ) {
                        cout << "Key 4 pressed" << std::endl;
                        iLowS = 120;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '5' ) & 0x8000 ) {
                        cout << "Key 5 pressed" << std::endl;
                        iLowS = 160;
                        option = 1;
                        configuration += 1;
                    }
                } else if (configuration == 1) {
                    sprintf(text,"Option %d", option);
                    putText(frame,text, Point(120,60) , FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0), 2,8,false );

                    if (option == 1) {
                        iHighS = 250;
                    } else if (option == 2) {
                        iHighS = 210;
                    } else if (option == 3) {
                        iHighS = 170;
                    } else if (option == 4) {
                        iHighS = 130;
                    } else if (option >= 5) {
                        iHighS = 90;
                        if (option == 6) {
                            option = 1;
                        }
                    }

                    if( GetAsyncKeyState( '1' ) & 0x8000 ) {
                        cout << "Key 1 pressed" << std::endl;
                        iHighS = 250;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '2' ) & 0x8000 ) {
                        cout << "Key 2 pressed" << std::endl;
                        iHighS = 210;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '3' ) & 0x8000 ) {
                        cout << "Key 3 pressed" << std::endl;
                        iHighS = 170;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '4' ) & 0x8000 ) {
                        cout << "Key 4 pressed" << std::endl;
                        iHighS = 130;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '5' ) & 0x8000 ) {
                        cout << "Key 5 pressed" << std::endl;
                        iHighS = 90;
                        option = 1;
                        configuration += 1;
                    }
                } else if (configuration == 2) {
                    sprintf(text,"Option %d", option);
                    putText(frame,text, Point(120,60) , FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0), 2,8,false );

                    if (option == 1) {
                        iLowV = 0;
                    } else if (option == 2) {
                        iLowV = 40;
                    } else if (option == 3) {
                        iLowV = 80;
                    } else if (option == 4) {
                        iLowV = 120;
                    } else if (option >= 5) {
                        iLowV = 160;
                        if (option == 6) {
                            option = 1;
                        }
                    }

                    if( GetAsyncKeyState( '1' ) & 0x8000 ) {
                        cout << "Key 1 pressed" << std::endl;
                        iLowV = 0;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '2' ) & 0x8000 ) {
                        cout << "Key 2 pressed" << std::endl;
                        iLowV = 40;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '3' ) & 0x8000 ) {
                        cout << "Key 3 pressed" << std::endl;
                        iLowV = 80;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '4' ) & 0x8000 ) {
                        cout << "Key 4 pressed" << std::endl;
                        iLowV = 120;
                        option = 1;
                        configuration += 1;
                    } else if( GetAsyncKeyState( '5' ) & 0x8000 ) {
                        cout << "Key 5 pressed" << std::endl;
                        iLowV = 160;
                        option = 1;
                        configuration += 1;
                    }
                } else if (configuration == 3) {
                    sprintf(text,"Option %d", option);
                    putText(frame,text, Point(120,60) , FONT_HERSHEY_SIMPLEX, .5, Scalar(0,255,0), 2,8,false );

                    if (option == 1) {
                        iHighV = 250;
                    } else if (option == 2) {
                        iHighV = 210;
                    } else if (option == 3) {
                        iHighV = 170;
                    } else if (option == 4) {
                        iHighV = 130;
                    } else if (option >= 5) {
                        iHighV = 90;
                        if (option == 6) {
                            option = 1;
                        }
                    }

                    if( GetAsyncKeyState( '1' ) & 0x8000 ) {
                        cout << "Key 1 pressed" << std::endl;
                        iHighV = 250;
                        option = 1;
                        configuration += 1;
                        hasParameters = 1;
                    } else if( GetAsyncKeyState( '2' ) & 0x8000 ) {
                        cout << "Key 2 pressed" << std::endl;
                        iHighV = 210;
                        option = 1;
                        configuration += 1;
                        hasParameters = 1;
                    } else if( GetAsyncKeyState( '3' ) & 0x8000 ) {
                        cout << "Key 3 pressed" << std::endl;
                        iHighV = 170;
                        option = 1;
                        configuration += 1;
                        hasParameters = 1;
                    } else if( GetAsyncKeyState( '4' ) & 0x8000 ) {
                        cout << "Key 4 pressed" << std::endl;
                        iHighV = 130;
                        option = 1;
                        configuration += 1;
                        hasParameters = 1;
                    } else if( GetAsyncKeyState( '5' ) & 0x8000 ) {
                        cout << "Key 5 pressed" << std::endl;
                        iHighV = 90;
                        option = 1;
                        configuration += 1;
                        hasParameters = 1;
                    }
                }

            } else {
                /*Find contours*/
                vector<Vec4i> hierarchy;
                vector<vector<Point> > contours_hull;
                findContours(filtered_frame.clone(), contours_hull, hierarchy, CV_RETR_TREE, CV_CLOCKWISE, Point(0,0));
                vector<vector<Point> > hull(contours_hull.size());

                vector<vector<int> > hullsI(contours_hull.size());
                vector<vector<Vec4i> > defects(contours_hull.size() );

                for( int i = 0; i < contours_hull.size(); i++ ){
                    convexHull( Mat(contours_hull[i]), hull[i], false );
                    convexHull( Mat(contours_hull[i]), hullsI[i], false );
                    if(hullsI[i].size() > 3 )
                            convexityDefects(contours_hull[i],hullsI[i],defects[i]);
                }

                 int largest_index = 0;
                 double largest_contour = 0;
                 int fingers = 0;

                 for( int i = 0; i < contours_hull.size(); i++ ) {
                     //cout << "Tamanho: " << contourArea(contours_hull[i]) << endl;
                     double a = contourArea(contours_hull[i]);  //  Find the area of contour
                     if (a > largest_contour) {
                        largest_contour = a;
                        largest_index = i;
                     }
                 }


                 for( int i = 0; i < contours_hull.size(); i++ ) {

                     vector<Vec4i>::iterator d = defects[largest_index].begin();
                     while( d!=defects[largest_index].end() ) {
                        Vec4i& v=(*d);
                        if(largest_index == i) {
                            int startidx=v[0];
                            Point ptStart( contours_hull[i][startidx] ); // point of the contour where the defect begins
                            int endidx=v[1];
                            Point ptEnd( contours_hull[i][endidx] ); // point of the contour where the defect ends
                            int faridx=v[2];
                            Point ptFar( contours_hull[i][faridx] );// the farthest from the convex hull point within the defect
                            float depth = v[3] / 256; // distance between the farthest point and the convex hull

                            if(depth > 20 && depth < 150) {
                                line( frame, ptStart, ptFar, CV_RGB(0,255,0), 2 );
                                line( frame, ptEnd, ptFar, CV_RGB(0,255,0), 2 );
                                circle( frame, ptStart, 4, Scalar(100,0,255), 2 );
                                fingers += 1;
                            }
                        }
                        d++;
                     }

                     char name[30];
                     if (fingers != 0) {
                         if (fingers > 2) sprintf(name,"Mao aberta");
                         else sprintf(name,"Mao fechada");
                         putText(frame, name, Point(320,90) , FONT_HERSHEY_SIMPLEX, .8, Scalar(200,255,0), 2, 8, false);
                     }
                 }
                 drawContours( frame, contours_hull, largest_index, CV_RGB(255,0,0), 1, 8, vector<Vec4i>(), 0, Point() );
                 drawContours( frame, hull, largest_index, CV_RGB(0,255,0), 1, 8, vector<Vec4i>(), 0, Point() );
            }

            //imshow("Original", original);
            imshow("Resultado", frame);
            imshow("Filtered", filtered_frame);

            waitKey(30);
           /*if(waitKey(30) >= 0)
               break;*/

        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
