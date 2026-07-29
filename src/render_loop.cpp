#include <calculate.hpp>
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>

const int frequencyOfMapUpdate = 17;

void renderLoop(cv::Mat img,
                const std::string windowName,
                Node &ugv1,
                Node &ugv2,
                Draw &draw1)
{
    char pressedKey = cv::waitKey(frequencyOfMapUpdate);
    switch (pressedKey)
    {
    case 'a':
        ugv1.openCVCartesianCalculateAngle(cv::Point2d(ugv1.cartesian_x_y_point.x - 10, ugv1.cartesian_x_y_point.y));
        break;
    case 's':
        ugv1.openCVCartesianCalculateAngle(cv::Point2d(ugv1.cartesian_x_y_point.x, ugv1.cartesian_x_y_point.y - 10));
        break;
    case 'd':
        ugv1.openCVCartesianCalculateAngle(cv::Point2d(ugv1.cartesian_x_y_point.x + 10, ugv1.cartesian_x_y_point.y));
        break;
    case 'w':
        ugv1.openCVCartesianCalculateAngle(cv::Point2d(ugv1.cartesian_x_y_point.x, ugv1.cartesian_x_y_point.y + 10));
        break;
    case 'Q':
        ugv2.openCVCartesianCalculateAngle(cv::Point2d(ugv2.cartesian_x_y_point.x - 10, ugv2.cartesian_x_y_point.y));
        break;
    case 'T':
        ugv2.openCVCartesianCalculateAngle(cv::Point2d(ugv2.cartesian_x_y_point.x, ugv2.cartesian_x_y_point.y - 10));
        break;
    case 'S':
        ugv2.openCVCartesianCalculateAngle(cv::Point2d(ugv2.cartesian_x_y_point.x + 10, ugv2.cartesian_x_y_point.y));
        break;
    case 'R':
        ugv2.openCVCartesianCalculateAngle(cv::Point2d(ugv2.cartesian_x_y_point.x, ugv2.cartesian_x_y_point.y + 10));
        break;
    case '=':
        ugv1.setMeasurmentError(ugv1.getMeasurmentError() + 1);
        break;
    case '-':
        ugv1.setMeasurmentError(ugv1.getMeasurmentError() - 1);
        break;
    case ']':
        ugv1.setVehicleSize(ugv1.getVehicleSize() + 1);
        break;
    case '[':
        ugv1.setVehicleSize(ugv1.getVehicleSize() - 1);
        break;
    case '\'':
        ugv1.setInner(ugv1.getInner() + 1);
        break;
    case ';':
        ugv1.setInner(ugv1.getInner() - 1);
        break;
    case '1':
        break;
    case ',': // rotate left main node ugv1.cartesian_x_y_point = openCVPointToCartesianPoint(ugv1.opencv_x_y_point, cv::Point2d(1920 / 2, 1080 / 2));
        // ugv2.cartesian_x_y_point = openCVPointToCartesianPoint(ugv2.opencv_x_y_point);
        calculateNewPoints(ugv1, -1);

        break;
    case '.': // rotate right
        // ugv1.cartesian_x_y_point = openCVPointToCartesianPoint(ugv1.opencv_x_y_point);
        // ugv2.cartesian_x_y_point = openCVPointToCartesianPoint(ugv2.opencv_x_y_point);
        calculateNewPoints(ugv1, 1);
        break;
    default:
        break;
    }

    draw1.drawFrame(img, ugv1, ugv2);
    cv::imshow(windowName, img);
    cv::Point2d temp_opencv_point_x_y = cartesianPointToOpenCVPoint(ugv1.cartesian_x_y_point);
    // std::cout << "PressedKey: " << pressedKey << "\n";
    std::cout << "OpenCV (x,y) = " << "(" << temp_opencv_point_x_y.x << "," << temp_opencv_point_x_y.y << ")" << "\t";
    std::cout << "Cartesian (x,y) = " << "(" << ugv1.cartesian_x_y_point.x << "," << ugv1.cartesian_x_y_point.y << ")" << "\n";
}