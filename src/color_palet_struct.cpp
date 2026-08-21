#include <color_palet_struct.hpp>

colorPalet generateColorPalet(uint8_t node_id)
{
    colorPalet generated_color_palet;
    cv::Scalar choosen_base_color = colors[node_id - 1];
    cv::Mat temp(cv::Size(1, 1), CV_8UC3, choosen_base_color);
    cv::Mat dst;
    cv::cvtColor(temp, dst, cv::COLOR_BGR2HSV);

    cv::Vec3b hsv = dst.at<cv::Vec3b>(0, 0);

    uint8_t h = hsv[0];
    uint8_t s = hsv[1];
    uint8_t v = hsv[2];

    cv::Scalar hsv_vehicle_color(h, s, v);
    cv::Scalar hsv_inner_color(h, s * 0.95, v * 0.95);
    cv::Scalar hsv_measurment_error_color(h, s * 1.05, v * 1.05);
    cv::Scalar hsv_observer_line_color(h, s * 0.95, v * 0.75);
    cv::Scalar hsv_text_color(h, s, v);

    cv::Mat hsv_vehicle_mat(1, 1, CV_8UC3, hsv_vehicle_color);
    cv::Mat hsv_inner_mat(1, 1, CV_8UC3, hsv_inner_color);
    cv::Mat hsv_measurment_error_mat(1, 1, CV_8UC3, hsv_measurment_error_color);
    cv::Mat hsv_observer_line_mat(1, 1, CV_8UC3, hsv_observer_line_color);
    cv::Mat hsv_text_mat(1, 1, CV_8UC3, hsv_text_color);

    cv::Mat dst_vehicle_mat;
    cv::Mat dst_inner_mat;
    cv::Mat dst_measurment_error_mat;
    cv::Mat dst_observer_line_mat;
    cv::Mat dst_text_mat;

    cv::cvtColor(hsv_vehicle_mat, dst_vehicle_mat, cv::COLOR_HSV2BGR);
    cv::cvtColor(hsv_inner_mat, dst_inner_mat, cv::COLOR_HSV2BGR);
    cv::cvtColor(hsv_measurment_error_mat, dst_measurment_error_mat, cv::COLOR_HSV2BGR);
    cv::cvtColor(hsv_observer_line_mat, dst_observer_line_mat, cv::COLOR_HSV2BGR);
    cv::cvtColor(hsv_text_mat, dst_text_mat, cv::COLOR_HSV2BGR);

    cv::Vec3b vehicle_bgr = dst_vehicle_mat.at<cv::Vec3b>(0, 0);
    cv::Vec3b inner_bgr = dst_inner_mat.at<cv::Vec3b>(0, 0);
    cv::Vec3b measurment_error_bgr = dst_measurment_error_mat.at<cv::Vec3b>(0, 0);
    cv::Vec3b observer_line_bgr = dst_observer_line_mat.at<cv::Vec3b>(0, 0);
    cv::Vec3b text_bgr = dst_text_mat.at<cv::Vec3b>(0, 0);

    generated_color_palet.vehicle_color = cv::Scalar(vehicle_bgr[0], vehicle_bgr[1], vehicle_bgr[2]);
    generated_color_palet.inner__color = cv::Scalar(inner_bgr[0], inner_bgr[1], inner_bgr[2]);
    generated_color_palet.measurment_error_color = cv::Scalar(measurment_error_bgr[0], measurment_error_bgr[1], measurment_error_bgr[2]);
    generated_color_palet.observer_line_color = cv::Scalar(observer_line_bgr[0], observer_line_bgr[1], observer_line_bgr[2]);
    generated_color_palet.text_color = cv::Scalar(text_bgr[0], text_bgr[1], text_bgr[2]);
}
