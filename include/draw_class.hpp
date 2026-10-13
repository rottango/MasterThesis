#pragma once

#include <graph_class.hpp>
#include <opencv2/opencv.hpp>
#include <reusable_calculations.hpp>

class Draw
{
public:

    /**
     * @brief Construct a new Draw object
     * 
     * @param Graph 
     * @param img 
     */
    Draw(const Graph &Graph, cv::Mat &img);

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void drawFrame(const int movable_node_id_);

private:

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void drawGraph(const int movable_node_id_);

    /**
     * @brief 
     * 
     */
    void drawNodes();

    /**
     * @brief 
     * 
     * @param node 
     */
    void drawNode(const Node &node);

    /**
     * @brief 
     * 
     * @param node 
     */
    void drawNodeVehicleSize(const Node &node);

    /**
     * @brief 
     * 
     * @param node 
     */
    void drawNodeAxis(const Node &node);

    /**
     * @brief 
     * 
     * @param node 
     */
    void drawNodeMeasurmentError(const Node &node);

    /**
     * @brief 
     * 
     * @param node 
     */
    void drawNodeInner(const Node &node);

    /**
     * @brief 
     * 
     */
    void drawEdges();

    /**
     * @brief 
     * 
     * @param edge 
     * @param radius 
     */
    void drawEdge(const Edge &edge, int radius); // this is the same as drawConnectingLine i believe

    /**
     * @brief 
     * 
     * @param edge 
     */
    void drawEdgeConnectingLine(const Edge &edge);

    /**
     * @brief 
     * 
     * @param edge 
     */
    void drawEdgeAngleElipse(const Edge &edge); // every edge from observer to targets are drawn

    /**
     * @brief 
     * 
     * @param edge 
     * @param radius 
     */
    void drawEdgeAngleElipseToTarget(const Edge &edge, int radius); // single edge from observer to target is drawn

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void drawText(const int movable_node_id_);

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void generateText(const int movable_node_id_);

    /**
     * @brief 
     * 
     * @param node 
     */
    void generateNodeText(const Node &node);

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void generateEdgesText(const int movable_node_id_);

    /**
     * @brief 
     * 
     * @param edge 
     */
    void generateEdgeText(const Edge &edge);

    /**
     * @brief 
     * 
     * @param movable_node_id_ 
     */
    void decideMaxSizeOfNodeAndEdgeText(const int movable_node_id_);

    /**
     * @brief 
     * 
     * @param origin_point 
     * @param generated_text 
     * @param movable_node_id 
     */
    void drawGeneratedText(const cv::Point2d origin_point, std::vector<std::string> generated_text, int movable_node_id);

    /**
     * @brief 
     * 
     * @param generated_text 
     * @return int 
     */
    int textGapSum(std::vector<cv::String> generated_text);

    /**
     * @brief 
     * 
     * @param generated_text 
     * @return cv::Size 
     */
    cv::Size rectangleOfTextSize(std::vector<cv::String> generated_text);

    /**
     * @brief 
     * 
     * @param rectangle 
     * @return true 
     * @return false 
     */
    bool doesTextFitOnScreen(cv::Size rectangle);

    /**
     * @brief 
     * 
     * @param rectangleNodeText 
     * @param rectangleEdgeText 
     * @return std::pair<cv::Point2d, cv::Point2d> 
     */
    std::pair<cv::Point2d, cv::Point2d> layoutNodeAndEdgeText(cv::Size rectangleNodeText, cv::Size rectangleEdgeText);

    /**
     * @brief 
     * 
     * @param origin_point 
     * @param generated_text_node 
     */
    void drawGeneratedText(cv::Point2d origin_point, std::vector<std::string> generated_text_node);

    const Graph &graph_;
    cv::Mat &img_;

    int screen_width_;
    int screen_height_;
    cv::Size size_;
    int type_;

    cv::Scalar x_axis_color_{0, 0, 255};
    cv::Scalar y_axis_color_{255, 0, 0};
    int axis_arrow_thickness_ = 3;
    int angle_elipse_size_ = 100;

    int font_face_ = cv::FONT_HERSHEY_PLAIN;
    double font_scale_ = 1;
    int font_thickness_ = 1;
    int baseline_;

    int base_angle_elipse_size_ = 75;
    int base_angle_elipse_spacing_ = 25;

    int gap_size_pixels_ = 5;
    int margin_from_edge_ = 10;

    double desired_tip_length_ = 30;

    std::vector<std::string> generated_text_node;
    std::vector<std::string> generated_text_edge;

    // node
    std::string node_id_text_ = "Node ID: ";
    std::string cartesian_x_y_point_text_ = "Location (x,y): ";
    std::string vehicle_size_text_ = "bgr_vehicle_color size: ";
    std::string inner_text_ = "Inner size: ";
    std::string measurment_error_cm_text_ = "Measurment error [cm]: ";
    std::string theta_rotation_degrees_text_ = "Theta rotation [degrees]: ";

    // edge
    std::string edge_id_ = "Edge ID: ";
    std::string observer_id = "Observer ID: ";
    std::string target_id_ = "Target ID: ";
    std::string distance_between_nodes_meters_ = "Distance [m]: ";
    std::string angle_between_nodes_degrees_ = "Angle [degrees]: ";
    std::string temp_timestamp_ = "Timestamp: ";
    std::string distance_between_nodes_meters_error_ = "Distance error [m]: ";
    std::string angle_between_nodes_degrees_error_ = "Angle error [degrees]: ";
};