#include <calculate.hpp>
#include <draw_on_screen.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>

const int frequencyOfMapUpdate = 17;

void renderLoop(cv::Mat img,
                const std::string windowName,
                Node &ugv1,
                Node &ugv2)
{
    char pressedKey = cv::waitKey(frequencyOfMapUpdate);
    switch (pressedKey)
    {
    case 'a':
        ugv1.changePositionXYZ(ugv1.x_position - 10, ugv1.y_position, ugv1.z_position);
        break;
    case 's':
        ugv1.changePositionXYZ(ugv1.x_position, ugv1.y_position + 10, ugv1.z_position);
        break;
    case 'd':
        ugv1.changePositionXYZ(ugv1.x_position + 10, ugv1.y_position, ugv1.z_position);
        break;
    case 'w':
        ugv1.changePositionXYZ(ugv1.x_position, ugv1.y_position - 10, ugv1.z_position);
        break;
    case 'Q':
        ugv2.changePositionXYZ(ugv2.x_position - 10, ugv2.y_position, ugv2.z_position);
        break;
    case 'T':
        ugv2.changePositionXYZ(ugv2.x_position, ugv2.y_position + 10, ugv2.z_position);
        break;
    case 'S':
        ugv2.changePositionXYZ(ugv2.x_position + 10, ugv2.y_position, ugv2.z_position);
        break;
    case 'R':
        ugv2.changePositionXYZ(ugv2.x_position, ugv2.y_position - 10, ugv2.z_position);
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
                ugv1.x_position = j;
                ugv1.y_position = i;
                ugv2.x_position = j - 100;
                ugv2.y_position = i - 100;

                char pressedKey = cv::waitKey(frequencyOfMapUpdate - frequencyOfMapUpdate + 2);

                ugv1.drawNode(tempImg);
                ugv2.drawNode(tempImg);
                drawConnectingLine(tempImg, ugv1, ugv2);
                drawTextOnScreen(tempImg, ugv1, ugv2);
                drawAxis(tempImg, ugv1);
                drawAxis(tempImg, ugv2);
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

    draw(img, ugv1, ugv2);
    cv::imshow(windowName, img);

    std::cout << "PressedKey: " << pressedKey << "\n";
}