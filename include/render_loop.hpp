#pragma once

#include <extern_variables.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

void renderLoop(cv::Mat img,
                const std::string windowName,
                Node &ugv1,
                Node &ugv2,
                Draw &draw1);