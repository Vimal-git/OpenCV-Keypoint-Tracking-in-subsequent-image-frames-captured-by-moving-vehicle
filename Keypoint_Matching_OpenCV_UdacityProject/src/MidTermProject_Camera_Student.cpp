/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{

    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    string dataPath = "../"; // Once downloaded change this to path of folder containing "images" folder

    // camera
    string imgBasePath = dataPath + "images/";
    string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = true;            // visualize results
    bool choiceEntered=false;// flag to allow all image frames to be processed by a single choice of keypoint detector and descriptor
    char allowDetectorChange='N';//This variable if set to 'Y' allow 
    string detectorType="SHITOMASI";//default detector type
    string descriptorType="BRISK";//default descriptor type
    /* MAIN LOOP OVER ALL IMAGES */

    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
    {
        /* LOAD IMAGE INTO BUFFER */

        // assemble filenames for current index
        ostringstream imgNumber;
        imgNumber << setfill('0') << setw(imgFillWidth) << imgStartIndex + imgIndex;
        string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

        // load image from file and convert to grayscale
        cv::Mat img, imgGray;
        img = cv::imread(imgFullFilename);
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        //// STUDENT ASSIGNMENT
        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

        // push image into data frame buffer
        DataFrame frame;
      	vector<DataFrame>::iterator it;
      	frame.cameraImg = imgGray;
      	if(dataBuffer.size()>=dataBufferSize)
        {
          it = dataBuffer.begin();
          dataBuffer.erase(it);
        }
        dataBuffer.push_back(frame);
      	

        //// EOF STUDENT ASSIGNMENT
        cout << "#1 : LOAD IMAGE INTO BUFFER done" << endl;

        /* DETECT IMAGE KEYPOINTS */

        // extract 2D keypoints from current image
        vector<cv::KeyPoint> keypoints; // create empty feature list for current image
        //string detectorType = "SHITOMASI";

        //// STUDENT ASSIGNMENT
        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
        //// -> HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
    if(!choiceEntered)
    {
      cout<<"Choose the keypoint DETECTOR by the serial number of detector: \n";
      cout<<"1) HARRIS \n";
      cout<<"2) FAST \n";
      cout<<"3) BRISK \n";
      cout<<"4) ORB \n";
      cout<<"5) AKAZE \n";
      cout<<"6) SIFT \n";
      cout<<"7) SHITOMASI \n";
      
      int detectorChoice=7;//Default for SHITOMASI
      cin>>detectorChoice;

      switch(detectorChoice){
        case 1:
          detectorType = "HARRIS";
          break;
      	case 2:
          detectorType = "FAST";
          break;
      	case 3:
          detectorType = "BRISK";
          break;
      	case 4:
          detectorType = "ORB";
          break;
      	case 5:
          detectorType = "AKAZE";
          break;
      	case 6:
          detectorType = "SIFT";
          break;
        case 7:
          detectorType = "SHITOMASI";
          break;
        default:
          detectorType = "SHITOMASI";
      }
      
      int descriptorChoice=1;//default for BRISK DESCRIPTOR
      cout<<"Choose the keypoint DESCRIPTOR by the serial number of DESCRIPTOR: \n";
      cout<<"1) BRISK \n";
      cout<<"2) ORB \n";
      cout<<"3) FREAK \n";
      cout<<"4) SIFT \n";
      cout<<"5) BRIEF \n";
      if(detectorType.compare("AKAZE")==0)
      {
        cout<<"6) AKAZE \n";
      }
      
      cin>>descriptorChoice;

      
      switch(descriptorChoice){
        case 1:
          descriptorType = "BRISK";
          break;
      	case 2:
          descriptorType = "ORB";
          break;
      	case 3:
          descriptorType = "FREAK";
          break;
      	case 4:
          descriptorType = "SIFT";
          break;
      	case 5:
          descriptorType = "BRIEF";
          break;
      	case 6:
          descriptorType = "AKAZE";
          break;
        default:
		  descriptorType = "BRISK";
      }
      cout<<"Do you prefer to use different choices over subsequent frame pairs? enter Y/N \n";
      cin>>allowDetectorChange;
      
      if(allowDetectorChange!='Y')
      {
        choiceEntered=true;
        cout<<"Initial Choice to be used for matching keypoints of all the 10 subsequent frames \n";
      }
    }
		 //detectorType = "HARRIS";
      	 //detectorType = "FAST";
      	 //detectorType = "BRISK";
      	 //detectorType = "ORB";
      	 //detectorType = "AKAZE";
      	 //detectorType = "SIFT";
         //detectorType = "SHITOMASI";
        if (detectorType.compare("SHITOMASI") == 0)
        {
            detKeypointsShiTomasi(keypoints, imgGray, false);
          	//detKeypointsShiTomasi(keypoints, imgGray, true);
        }
        else 
        {
            //...
          if(detectorType.compare("HARRIS") == 0)
          {
          	detKeypointsHarris(keypoints, imgGray, false);
            //detKeypointsHarris(keypoints, imgGray, true);
          }
          else if(detectorType.compare("FAST") == 0)
          {
          	detKeypointsFast(keypoints, imgGray, false);
            //detKeypointsFast(keypoints, imgGray, true);
          }
          else if(detectorType.compare("BRISK") == 0)
          {
          	detKeypointsBrisk(keypoints, imgGray, false);
            //detKeypointsBrisk(keypoints, imgGray, true);
          }
          else if(detectorType.compare("ORB") == 0)
          {
          	detKeypointsOrb(keypoints, imgGray, false);
            //detKeypointsOrb(keypoints, imgGray, true);
          }
          else if(detectorType.compare("AKAZE") == 0)
          {
          	detKeypointsAkaze(keypoints, imgGray, false);
            //detKeypointsAkaze(keypoints, imgGray, true);
          }
          else if(detectorType.compare("SIFT") == 0)
          {
          	detKeypointsSift(keypoints, imgGray, false);
            //detKeypointsSift(keypoints, imgGray, true);
          }
        }
        //// EOF STUDENT ASSIGNMENT

        //// STUDENT ASSIGNMENT
        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

       // only keep keypoints on the preceding vehicle
        bool bFocusOnVehicle = true;
      	//bool bFocusOnVehicle = false;
        cv::Rect vehicleRect(535, 180, 180, 150);
        if (bFocusOnVehicle)
        {
            // ...
          
          for(auto it=keypoints.begin();it!=keypoints.end();++it)
          {
            if(vehicleRect.contains((*it).pt))
              continue;
            else
            {
              keypoints.erase(it);
              --it;//compensate for erasing an entry
            }
          }  
        }

        //// EOF STUDENT ASSIGNMENT

        // optional : limit number of keypoints (helpful for debugging and learning)
        bool bLimitKpts = true;
        if (bLimitKpts)
        {
            int maxKeypoints = 50;

            if (detectorType.compare("SHITOMASI") == 0)
            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
            }
            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
            cout << " NOTE: Keypoints have been limited!" << endl;
        }

        // push keypoints and descriptor for current frame to end of data buffer
        (dataBuffer.end() - 1)->keypoints = keypoints;
        cout << "#2 : DETECT KEYPOINTS done" << endl;

        /* EXTRACT KEYPOINT DESCRIPTORS */

        //// STUDENT ASSIGNMENT
        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT

        cv::Mat descriptors;
        //string descriptorType = "BRISK"; // BRIEF, ORB, FREAK, AKAZE, SIFT
      	//string descriptorType = "BRIEF";
      	//string descriptorType = "ORB";
      	//string descriptorType = "FREAK";
      	//string descriptorType = "AKAZE";//only with AKAZE detector
      	//string descriptorType = "SIFT";
        descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
        //// EOF STUDENT ASSIGNMENT
		cout<<"out of descKeypoints "<<endl;
        // push descriptors for current frame to end of data buffer
        (dataBuffer.end() - 1)->descriptors = descriptors;

        cout << "#3 : EXTRACT DESCRIPTORS done" << endl;

        if (dataBuffer.size() > 1) // wait until at least two images have been processed
        {

            /* MATCH KEYPOINT DESCRIPTORS */

            vector<cv::DMatch> matches;
            string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
          	//string matcherType = "MAT_FLANN"; 
            string descriptorType = "DES_BINARY"; // DES_BINARY, DES_HOG
            //string selectorType = "SEL_NN";       // SEL_NN, SEL_KNN
			string selectorType = "SEL_KNN";
            //// STUDENT ASSIGNMENT
            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp

            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                             (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                             matches, descriptorType, matcherType, selectorType);

            //// EOF STUDENT ASSIGNMENT

            // store matches in current data frame
            (dataBuffer.end() - 1)->kptMatches = matches;

            cout << "#4 : MATCH KEYPOINT DESCRIPTORS done" << endl;

            // visualize matches between current and previous image
            
            if (bVis)
            {
                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                matches, matchImg,
                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                string windowName = "Matching keypoints between two camera images";
                cv::namedWindow(windowName, 7);
                cv::imshow(windowName, matchImg);
                cout << "Press key to continue to next image" << endl;
                cv::waitKey(0); // wait for key to be pressed
            }
            
        }

    } // eof loop over all images

    return 0;
}
