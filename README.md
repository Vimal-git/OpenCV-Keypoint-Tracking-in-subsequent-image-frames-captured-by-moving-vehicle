# OpenCV-Keypoint-Tracking-in-subsequent-image-frames-captured-by-moving-vehicle
* This project contains 10 time sequenced image frames (part of live video from a moving vehicle).
* The project uses the above frames to displays on monitor the performance of different keypoint detectors and descriptors supported by opencv for keypoint matching.
* User can choose the keypoint detectors and keypoint descriptors at runtime.
* This project is developed from the [link provided] as part of Udacity's Sensor Fusion Nano Degree program.

## Dependencies for running locally
1) cmake >= 2.8
* All OSes: [click here for installation instructions](https://cmake.org/install/)
2) make >= 4.1 (Linux, Mac), 3.81 (Windows)
* Linux: make is installed by default on most Linux distros
* Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
* Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
3) OpenCV >= 4.1
* All OSes: refer to the [official instructions](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html)
* This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON' cmake flag for testing the SIFT and SURF detectors. If using [homebrew](https://brew.sh/): ` $> brew install --build-from-source opencv ` will install required dependencies and compile opencv with the opencv_contrib module by default (no need to set -DOPENCV_ENABLE_NONFREE=ON manually).
* The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
4) gcc/g++ >= 5.4
* Linux: gcc / g++ is installed by default on most Linux distros
* Mac: same deal as make - install Xcode command line tools
* Windows: recommend using either MinGW-w64 or Microsoft's VCPKG, a C++ package manager. VCPKG maintains its own binary distributions of OpenCV and many other packages. To see what packages are available, type vcpkg search at the command prompt. For example, once you've VCPKG installed, you can install OpenCV 4.1 with the command:
```
c:\vcpkg> vcpkg install opencv4[nonfree,contrib]:x64-windows
```
Then, add C:_\vcpkg\installed\x64-windows\bin_ and C:_\vcpkg\installed\x64-windows\debug\bin_ to your user's PATH variable. Also, set the CMake Toolchain File to _c:\vcpkg\scripts\buildsystems\vcpkg.cmake_.

## Running the project
* Clone the repo in to your system
* images folder contains all the ten image frames used for keypoint matching.
* Open MidTermProject_Camera_Student.cpp and edit the assignment to `string dataPath` variable in line 28 to path of folder containing "images" folder in your PC.
* open terminal and change the directory to `Keypoint_Matching_OpenCV_UdacityProject/`
* run `mkdir build`
* run `cd build`
* run `cmake .. && make`
* run `./2D_feature_tracking `

## Acknowledgement
This project was developed from the resources provided as part of Udacity's Sensor Fusion Engineer Nano Degree program and [the starter code shared for this project is provided here](https://github.com/udacity/SFND_2D_Feature_Tracking).
