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
     * @brief Draw a circle representing the vehicle size with its center at the node's center
     * 
     * @param node 
     */
    void drawNodeVehicleSize(const Node &node);

    /**
     * @brief Draw the X and Y axis of the node
     * 
     * @param node 
     */
    void drawNodeAxis(const Node &node);

    /**
     * @brief Draw a circle representing the measurment error with its center at the node's center
     * 
     * @param node 
     */
    void drawNodeMeasurmentError(const Node &node);

    /**
     * @brief Draw a circle representing the "Inner" with its center at the node's center
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
     * @brief draw the lines from observer to target that represent the relationship of "being observer" that is the same as when two UWBs measure one another.
     * 
     * Each of the rules has to be followed:
     * 
     * 1. Each observer can have only one line with one specific target
     * 
     * 2. Each observer can have unlimited lines from him
     * 
     * 3. Each target can have unlimited lines to him
     * 
     * @param edge 
     */
    void drawEdgeConnectingLine(const Edge &edge);

    /**
     * @brief draw a part of a circle on top of the observer node, that represents the angle between the X-Axis of the observer node axis and one connecting line between an observer an target.
     * 
     * 1. The circle isn't ever more then a semi circle <-180; 180)
     * 
     * @param edge 
     * @param radius 
     */
    void drawEdgeAngleElipseToTarget(const Edge &edge, int radius); // single edge from observer to target is drawn

    /**
     * @brief call generateText and decideMaxSizeOfNodeAndEdgeText
     * 
     * @param movable_node_id_ 
     */
    void drawText(const int movable_node_id_);

    /**
     * @brief call generateNodeText and generateEdgesText on the currently controlled node
     * 
     * @param movable_node_id_ 
     */
    void generateText(const int movable_node_id_);

    /**
     * @brief Generate text based on the node's basic parameters:
     * 
     * 1. node id
     * 
     * 2. cartesian xy point
     * 
     * 3. vehicle size
     * 
     * 4. inner 
     * 
     * 5. measurment error
     * 
     * 6. theta rotation
     * 
     * @param node 
     */
    void generateNodeText(const Node &node);

    /**
     * @brief Call generateEdgeText for all observer's edges
     * 
     * @param movable_node_id_ 
     */
    void generateEdgesText(const int movable_node_id_);

    /**
     * @brief Generate text based on the observer's edge basic parameters: 
     * 
     * 1. edge id
     * 
     * 2. observer id
     * 
     * 3. target id
     * 
     * 4. distance between nodes
     * 
     * 5. angle between nodes
     * 
     * 6. temp timestamps
     * 
     * 7. distance between nodes error
     * 
     * 8. angle between nodes error
     * 
     * @param edge 
     */
    void generateEdgeText(const Edge &edge);

    /**
     * @brief layoutNodeAndEdgeText, Then call drawGeneratedText.
     * @param movable_node_id_ 
     */
    void decideMaxSizeOfNodeAndEdgeText(const int movable_node_id_);

    /**
     * @brief Draw the generated text of the current node while maintaining the correct sizing and offseting.
     * 
     * @param origin_point 
     * @param generated_text 
     * @param movable_node_id 
     */
    void drawGeneratedText(const cv::Point2d origin_point, std::vector<std::string> generated_text, int movable_node_id);

    /**
     * @brief Based on the ammount of rows of text to print from a std::vector , calculate the cummulative sum of gap
     * 
     * @param generated_text 
     * @return int 
     */
    int textGapSum(std::vector<cv::String> generated_text);

    /**
     * @brief Calculate the rectange width and height in which the text from std::vector fits
     * 
     * @param generated_text 
     * @return cv::Size 
     */
    cv::Size rectangleOfTextSize(std::vector<cv::String> generated_text);

    /**
     * @brief Check if the calculated minimum rectangle in which the text of std::vector fits, also fits on the screen. // i think this shit does NOT work, because it prob should throw false if it extends outisde screen, which it doesnt rn...
     * 
     * @param rectangle 
     * @return true 
     * @return false 
     */
    bool doesTextFitOnScreen(cv::Size rectangle);

    /**
     * @brief Find the location and the size of a rectangle, in which every text will fit. Looping text to not be off screen is not supported right now.
     * 
     * @param rectangleNodeText 
     * @param rectangleEdgeText 
     * @return std::pair<cv::Point2d, cv::Point2d> 
     */
    std::pair<cv::Point2d, cv::Point2d> layoutNodeAndEdgeText(cv::Size rectangleNodeText, cv::Size rectangleEdgeText);

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