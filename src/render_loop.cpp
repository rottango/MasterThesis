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
        ugv1.changePositionXYZ(cv::Point2d(ugv1.opencv_x_y_point.x - 10, ugv1.opencv_x_y_point.y), ugv1.opencv_z_position);
        break;
    case 's':
        ugv1.changePositionXYZ(cv::Point2d(ugv1.opencv_x_y_point.x, ugv1.opencv_x_y_point.y + 10), ugv1.opencv_z_position);
        break;
    case 'd':
        ugv1.changePositionXYZ(cv::Point2d(ugv1.opencv_x_y_point.x + 10, ugv1.opencv_x_y_point.y), ugv1.opencv_z_position);
        break;
    case 'w':
        ugv1.changePositionXYZ(cv::Point2d(ugv1.opencv_x_y_point.x, ugv1.opencv_x_y_point.y - 10), ugv1.opencv_z_position);
        break;
    case 'Q':
        ugv2.changePositionXYZ(cv::Point2d(ugv2.opencv_x_y_point.x - 10, ugv2.opencv_x_y_point.y), ugv2.opencv_z_position);
        break;
    case 'T':
        ugv2.changePositionXYZ(cv::Point2d(ugv2.opencv_x_y_point.x, ugv2.opencv_x_y_point.y + 10), ugv2.opencv_z_position);
        break;
    case 'S':
        ugv2.changePositionXYZ(cv::Point2d(ugv2.opencv_x_y_point.x + 10, ugv2.opencv_x_y_point.y), ugv2.opencv_z_position);
        break;
    case 'R':
        ugv2.changePositionXYZ(cv::Point2d(ugv2.opencv_x_y_point.x, ugv2.opencv_x_y_point.y - 10), ugv2.opencv_z_position);
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

        for (int i = 100; i < 1080; i += 5)
        {
            for (int j = 100; j < 1920; j += 5)
            {
                cv::Mat tempImg = img.clone();
                ugv1.opencv_x_y_point.x = j;
                ugv1.opencv_x_y_point.y = i;
                ugv2.opencv_x_y_point.x = j - 100;
                ugv2.opencv_x_y_point.y = i - 100;

                char pressedKey = cv::waitKey(frequencyOfMapUpdate - frequencyOfMapUpdate + 2);

                ugv1.drawNode(tempImg);
                ugv2.drawNode(tempImg);
                draw1.drawConnectingLine(tempImg, ugv1, ugv2);
                draw1.drawTextOnScreen(tempImg, ugv1, ugv2);
                draw1.drawAxis(tempImg, ugv1);
                draw1.drawAxis(tempImg, ugv2);
                cv::imshow(windowName, tempImg);
            }
        }
    case ',': // rotate left main node
        calculateNewPoints(ugv1, -1);

        break;
    case '.': // rotate right
        calculateNewPoints(ugv1, 1);

        break;
    default:
        break;
    }

    draw1.drawFrame(img, ugv1, ugv2);
    cv::imshow(windowName, img);

    // std::cout << "PressedKey: " << pressedKey << "\n";
    std::cout << "OpenCV (x,y) = " << "(" << ugv1.opencv_x_y_point.x << "," << ugv1.opencv_x_y_point.y << ")" << "\t";
    cv::Point2d cartesianPoint = openCVPointToCartesianPoint(cv::Point2d(ugv1.opencv_x_y_point.x, ugv1.opencv_x_y_point.y), cv::Point2d(draw1.centerOfScreen.x, draw1.centerOfScreen.y));
    std::cout << "Carthesian (x,y) = " << "(" << cartesianPoint.x << "," << cartesianPoint.y << ")" << "\n";
}