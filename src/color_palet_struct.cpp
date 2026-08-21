#include <color_palet_struct.hpp>

colorPalet generateColorPalet()
{
    colorPalet generated_color_palet;

    cv::Scalar base_color{colors[color_positon_++]};
    cv::Mat src = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat dst;
    cv::cvtColor(src, dst, cv::COLOR_BGR2HSV, 0);

    cv::Vec3b hsv = dst.at<cv::Vec3b>(0, 0);
    uchar h = hsv.val[0];
    uchar s = hsv.val[1];
    uchar v = hsv.val[2];

    cv::Vec3b hsv_vec_vehicle_color{h, static_cast<uchar>(s * 0.95), v};
    cv::Vec3b hsv_vec_inner__color{h, s, static_cast<uchar>(v * 0.95)};
    cv::Vec3b hsv_vec_measurment_error_color{static_cast<uchar>(h * 0.90), s, v};
    cv::Vec3b hsv_vec_observer_line_color{h, s, static_cast<uchar>(v * 0.90)};
    cv::Vec3b hsv_vec_text_color{h, static_cast<uchar>(s * 0.85), v};

    cv::Mat hsv_mat_vehicle_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat hsv_mat_inner__color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat hsv_mat_measurment_error_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat hsv_mat_observer_line_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat hsv_mat_text_color = cv::Mat(1, 1, CV_8UC3, base_color);

    hsv_mat_vehicle_color.at<cv::Vec3b>(0, 0) = hsv_vec_vehicle_color;
    hsv_mat_inner__color.at<cv::Vec3b>(0, 0) = hsv_vec_inner__color;
    hsv_mat_measurment_error_color.at<cv::Vec3b>(0, 0) = hsv_vec_measurment_error_color;
    hsv_mat_observer_line_color.at<cv::Vec3b>(0, 0) = hsv_vec_observer_line_color;
    hsv_mat_text_color.at<cv::Vec3b>(0, 0) = hsv_vec_text_color;

    cv::Mat bgr_vehicle_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat bgr_inner_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat bgr_measurment_error_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat bgr_observer_line_color = cv::Mat(1, 1, CV_8UC3, base_color);
    cv::Mat bgr_text_color = cv::Mat(1, 1, CV_8UC3, base_color);

    cv::cvtColor(hsv_mat_vehicle_color, bgr_vehicle_color, cv::COLOR_HSV2BGR, 0);
    cv::cvtColor(hsv_mat_inner__color, bgr_inner_color, cv::COLOR_HSV2BGR, 0);
    cv::cvtColor(hsv_mat_measurment_error_color, bgr_measurment_error_color, cv::COLOR_HSV2BGR, 0);
    cv::cvtColor(hsv_mat_observer_line_color, bgr_observer_line_color, cv::COLOR_HSV2BGR, 0);
    cv::cvtColor(hsv_mat_text_color, bgr_text_color, cv::COLOR_HSV2BGR, 0);

    cv::Vec3b bgr_vec_vehicle = bgr_vehicle_color.at<cv::Vec3b>(0, 0);
    cv::Vec3b bgr_vec_inner = bgr_inner_color.at<cv::Vec3b>(0, 0);
    cv::Vec3b bgr_vec_measurment_error = bgr_measurment_error_color.at<cv::Vec3b>(0, 0);
    cv::Vec3b bgr_vec_observer_line = bgr_observer_line_color.at<cv::Vec3b>(0, 0);
    cv::Vec3b bgr_vec_text = bgr_text_color.at<cv::Vec3b>(0, 0);

    generated_color_palet.vehicle_color = cv::Scalar(bgr_vec_vehicle.val[0], bgr_vec_vehicle.val[1], bgr_vec_vehicle.val[2]);
    generated_color_palet.inner__color = cv::Scalar(bgr_vec_inner.val[0], bgr_vec_inner.val[1], bgr_vec_inner.val[2]);
    generated_color_palet.measurment_error_color = cv::Scalar(bgr_vec_measurment_error.val[0], bgr_vec_measurment_error.val[1], bgr_vec_measurment_error.val[2]);
    generated_color_palet.observer_line_color = cv::Scalar(bgr_vec_observer_line.val[0], bgr_vec_observer_line.val[1], bgr_vec_observer_line.val[2]);
    generated_color_palet.text_color = cv::Scalar(bgr_vec_text.val[0], bgr_vec_text.val[1], bgr_vec_text.val[2]);

    return generated_color_palet;
}
