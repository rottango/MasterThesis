#include <extern_variables.hpp>

void setExternValues(int new_screen_width_pixels,
                     int new_screen_height_pixels,
                     cv::Point2d new_opencv_screen_center)
{
    screen_width_pixels = new_screen_width_pixels;
    screen_height_pixels = new_screen_height_pixels;
    opencv_screen_center = new_opencv_screen_center;
}