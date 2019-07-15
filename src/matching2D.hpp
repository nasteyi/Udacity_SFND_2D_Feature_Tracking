#ifndef matching2D_hpp
#define matching2D_hpp

#include <stdio.h>
#include <iostream>
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

void detKeypointsHarris(
    std::vector<cv::KeyPoint> &keypoints,
    const cv::Mat &img,
    bool bVis=false);

void detKeypointsShiTomasi(
    std::vector<cv::KeyPoint> &keypoints,
    const cv::Mat &img,
    bool bVis=false);

void detKeypointsModern(
    std::vector<cv::KeyPoint> &keypoints,
    const cv::Mat &img,
    const std::string& detectorType,
    bool bVis=false);

void descKeypoints(
    std::vector<cv::KeyPoint> &keypoints,
    const cv::Mat &img,
    cv::Mat &descriptors,
    const std::string& descriptorType);

void matchDescriptors(
    const std::vector<cv::KeyPoint> &kPtsSource,
    const std::vector<cv::KeyPoint> &kPtsRef,
    const cv::Mat &descSource,
    const cv::Mat &descRef,
    std::vector<cv::DMatch> &matches,
    const std::string& descriptorType,
    const std::string& matcherType,
    const std::string& selectorType);

#endif /* matching2D_hpp */
