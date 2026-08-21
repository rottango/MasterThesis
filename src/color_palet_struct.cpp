#include <color_palet_struct.hpp>

cv::Scalar colors[] = {
    cv::Scalar(255, 0, 0),     // #0000FF
    cv::Scalar(0, 0, 255),     // #FF0000
    cv::Scalar(254, 255, 1),   // #01FFFE
    cv::Scalar(254, 166, 255), // #FFA6FE
    cv::Scalar(102, 219, 255), // #FFDB66
    cv::Scalar(1, 100, 0),     // #006401
    cv::Scalar(58, 0, 149),    // #95003A
    cv::Scalar(181, 125, 0),   // #007DB5
    cv::Scalar(246, 0, 255),   // #FF00F6
    cv::Scalar(232, 238, 255), // #FFEEE8
    cv::Scalar(0, 77, 119),    // #774D00
    cv::Scalar(146, 251, 144), // #90FB92
    cv::Scalar(255, 118, 0),   // #0076FF
    cv::Scalar(0, 255, 213),   // #D5FF00
    cv::Scalar(126, 147, 255), // #FF937E
    cv::Scalar(108, 130, 106), // #6A826C
    cv::Scalar(157, 2, 255),   // #FF029D
    cv::Scalar(0, 137, 254),   // #FE8900
    cv::Scalar(130, 71, 122),  // #7A4782
    cv::Scalar(210, 45, 126),  // #7E2DD2
    cv::Scalar(0, 169, 133),   // #85A900
    cv::Scalar(86, 0, 255),    // #FF0056
    cv::Scalar(0, 36, 164),    // #A42400
    cv::Scalar(126, 174, 0),   // #00AE7E
    cv::Scalar(59, 61, 104),   // #683D3B
    cv::Scalar(255, 198, 189), // #BDC6FF
    cv::Scalar(147, 211, 189), // #BDD393
    cv::Scalar(23, 185, 0),    // #00B917
    cv::Scalar(142, 0, 158),   // #9E008E
    cv::Scalar(159, 140, 194), // #C28C9F
    cv::Scalar(163, 116, 255), // #FF74A3
    cv::Scalar(255, 208, 1),   // #01D0FF
    cv::Scalar(84, 71, 0),     // #004754
    cv::Scalar(254, 111, 229), // #E56FFE
    cv::Scalar(49, 130, 120),  // #788231
    cv::Scalar(161, 76, 14),   // #0E4CA1
    cv::Scalar(203, 208, 145), // #91D0CB
    cv::Scalar(112, 153, 190), // #BE9970
    cv::Scalar(232, 138, 150), // #968AE8
    cv::Scalar(0, 136, 187),   // #BB8800
    cv::Scalar(116, 255, 222), // #DEFF74
    cv::Scalar(198, 255, 0),   // #00FFC6
    cv::Scalar(2, 229, 255),   // #FFE502
    cv::Scalar(0, 14, 98),     // #620E00
    cv::Scalar(156, 143, 0),   // #008F9C
    cv::Scalar(82, 255, 152),  // #98FF52
    cv::Scalar(177, 68, 117),  // #7544B1
    cv::Scalar(255, 0, 181),   // #B500FF
    cv::Scalar(120, 255, 0),   // #00FF78
    cv::Scalar(65, 110, 255),  // #FF6E41
    cv::Scalar(57, 95, 0),     // #005F39
    cv::Scalar(130, 104, 107), // #6B6882
    cv::Scalar(78, 173, 95),   // #5FAD4E
    cv::Scalar(64, 87, 167),   // #A75740
    cv::Scalar(210, 255, 165), // #A5FFD2
    cv::Scalar(103, 177, 255), // #FFB167
    cv::Scalar(255, 155, 0),   // #009BFF
    cv::Scalar(190, 94, 232)   // #E85EBE
};

colorPalet generateColorPalet(int &color_positon)
{
    colorPalet generated_color_palet;

    cv::Scalar base_color{colors[color_positon++]};
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

    generated_color_palet.thickness = 2;
    generated_color_palet.lineType = 8;
    generated_color_palet.shift = 0;

    return generated_color_palet;
}
