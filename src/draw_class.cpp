
#include <draw_class.hpp>
#include <node_class.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>

Draw::Draw(const Graph &graph,
           cv::Mat &img) : graph_(graph), img_(img)
{
    this->screen_width_ = img_.cols;
    this->screen_height_ = img_.rows;
    this->size_ = img_.size();
    this->type_ = img_.type();
}

// frame

void Draw::drawFrame(const int movable_node_id_)
{
    this->screen_width_ = img_.cols;
    this->screen_height_ = img_.rows;
    this->size_ = img_.size();
    this->type_ = img_.type();
    drawGraph(movable_node_id_);
}

// graph

void Draw::drawGraph(const int movable_node_id_)
{
    drawNodes();

    drawEdges();

    drawText(movable_node_id_);
}
// node

void Draw::drawNodes()
{
    for (auto it = graph_.getNodes().begin(); it != graph_.getNodes().end(); it++)
    {
        drawNode(it->second);
    }
}

void Draw::drawNode(const Node &node)
{
    drawNodeVehicleSize(node);
    drawNodeInner(node);
    drawNodeMeasurmentError(node);
    drawNodeAxis(node);
}

void Draw::drawNodeVehicleSize(const Node &node)
{
    uint8_t radius = node.getVehicleSize();
    int thickness = node.getColorPalet().thickness;
    int shift = node.getColorPalet().shift;
    if (radius < 0)
    {
        spdlog::warn("radius of cv::circle is out of range, value = {}", radius);
        radius = 55;
    }
    if (thickness > 32767) // MAX_THICKNESS from drawing.cpp source file.
    {
        spdlog::warn("thickness of cv::ellipse is too big, value = {}", thickness);
        thickness = 2;
    }
    if (shift < 0 || shift > 16) // XY_SHIFT from drawing.cpp source file.
    {
        spdlog::warn("shift of cv::ellipse is out of range, value = {}", shift);
        shift = 0;
    }
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               radius,
               node.getColorPalet().vehicle_color,
               thickness,
               node.getColorPalet().lineType,
               shift);
}

void Draw::drawNodeAxis(const Node &node)
{
    // no assertions used here, so no error handling required
    cv::arrowedLine(img_,
                    cartesianPointToOpenCVPoint(node.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    cartesianPointToOpenCVPoint(node.getXAxisPoint(),
                                                screen_width_,
                                                screen_height_),
                    x_axis_color_,
                    axis_arrow_thickness_);

    cv::arrowedLine(img_,
                    cartesianPointToOpenCVPoint(node.getXYPoint(),
                                                screen_width_,
                                                screen_height_),
                    cartesianPointToOpenCVPoint(node.getYAxisPoint(),
                                                screen_width_,
                                                screen_height_),
                    y_axis_color_,
                    axis_arrow_thickness_);
}

void Draw::drawNodeMeasurmentError(const Node &node)
{
    uint8_t radius = node.getMeasurmentError();
    int thickness = node.getColorPalet().thickness;
    int shift = node.getColorPalet().shift;
    if (radius < 0)
    {
        spdlog::warn("radius of cv::circle is out of range, value = {}", radius);
        radius = 77;
    }
    if (thickness > 32767) // MAX_THICKNESS from drawing.cpp source file.
    {
        spdlog::warn("thickness of cv::ellipse is too big, value = {}", thickness);
        thickness = 2;
    }
    if (shift < 0 || shift > 16) // XY_SHIFT from drawing.cpp source file.
    {
        spdlog::warn("shift of cv::ellipse is out of range, value = {}", shift);
        shift = 0;
    }
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               radius,
               node.getColorPalet().measurment_error_color,
               thickness,
               node.getColorPalet().lineType,
               shift);
}

void Draw::drawNodeInner(const Node &node)
{
    uint8_t radius = node.getInner();
    int thickness = node.getColorPalet().thickness;
    int shift = node.getColorPalet().shift;
    if (radius < 0)
    {
        spdlog::warn("radius of cv::circle is out of range, value = {}", radius);
        radius = 66;
    }
    if (thickness > 32767) // MAX_THICKNESS from drawing.cpp source file.
    {
        spdlog::warn("thickness of cv::ellipse is too big, value = {}", thickness);
        thickness = 2;
    }
    if (shift < 0 || shift > 16) // XY_SHIFT from drawing.cpp source file.
    {
        spdlog::warn("shift of cv::ellipse is out of range, value = {}", shift);
        shift = 0;
    }
    cv::circle(this->img_,
               cartesianPointToOpenCVPoint(node.getXYPoint(),
                                           screen_width_,
                                           screen_height_),
               radius,
               node.getColorPalet().inner__color,
               thickness,
               node.getColorPalet().lineType,
               shift);
}

// edge

void Draw::drawEdges() // correct
{
    std::unordered_map<uint8_t, uint8_t> number_of_elipses_per_observer_id;
    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        uint8_t observer_id = it->second.getObserverId();
        uint8_t &counter = number_of_elipses_per_observer_id[observer_id];
        int radius = base_angle_elipse_size_ + counter * base_angle_elipse_spacing_;
        drawEdge(it->second, radius);
        counter++;
    }
}

void Draw::drawEdge(const Edge &edge, int radius)
{
    drawEdgeConnectingLine(edge);
    drawEdgeAngleElipseToTarget(edge, radius);
}

void Draw::drawEdgeConnectingLine(const Edge &edge)
{
    const Node &observer = graph_.findNodeByIdReadOnly(edge.getObserverId());
    const Node &target = graph_.findNodeByIdReadOnly(edge.getTargetId());
    double tip_length = desired_tip_length_ / distanceBetweenTwoPoints(observer.getXYPoint(), target.getXYPoint());
    if (tip_length <= 0.0 || tip_length > 1.0)
    {
        spdlog::warn("tip_length of cv::arrowedLine is out of range, value = {}", tip_length);
        tip_length = 0.5;
    }
    try
    {
        cv::arrowedLine(img_,
                        cartesianPointToOpenCVPoint(observer.getXYPoint(),
                                                    screen_width_,
                                                    screen_height_),
                        cartesianPointToOpenCVPoint(target.getXYPoint(),
                                                    screen_width_,
                                                    screen_height_),
                        observer.getColorPalet().text_color,
                        axis_arrow_thickness_,
                        8,
                        0,
                        tip_length);
    }
    catch (cv::Exception &e)
    {
        spdlog::warn("{}", e.what());
    }
}

void Draw::drawEdgeAngleElipseToTarget(const Edge &edge, int radius)
{
    const Node &observer = graph_.findNodeByIdReadOnly(edge.getObserverId());
    double angle = 0;
    double start_angle = -observer.getThetaRotationDegrees();
    double normalized_angle = edge.getAngleBetweenNodesDegrees();
    double end_angle = start_angle - normalized_angle;
    int thickness = 1;
    int line_type = 8;
    int shift = 0;
    if (radius < 0)
    {
        spdlog::warn("radius of cv::ellipse is negative, value = {}", radius);
        radius = 100;
    }
    if (thickness > 32767) // MAX_THICKNESS from drawing.cpp source file.
    {
        spdlog::warn("thickness of cv::ellipse is too big, value = {}", thickness);
        thickness = 2;
    }
    if (shift < 0 || shift > 16) // XY_SHIFT from drawing.cpp source file.
    {
        spdlog::warn("shift of cv::ellipse is out of range, value = {}", shift);
        shift = 0;
    }
    try
    {
        cv::ellipse(img_, // cv::InputOutputArray img,
                    cartesianPointToOpenCVPoint(observer.getXYPoint(),
                                                screen_width_,
                                                screen_height_), // cv::Point center
                    cv::Size2d(radius,
                               radius),                  // cv::Size axes
                    angle,                               // double angle STAYS 0, then its like i want it to be
                    start_angle,                         // double startAngle
                    end_angle,                           // double endAngle
                    observer.getColorPalet().text_color, // const cv::Scalar &color
                    1,                                   // int thickness
                    8,                                   // int lineType = 8
                    0);                                  // int shift = 0
    }
    catch (cv::Exception &e)
    {
        spdlog::warn("{}", e.what());
    }
}

// text

void Draw::drawText(const int movable_node_id_)
{
    generateText(movable_node_id_);

    decideMaxSizeOfNodeAndEdgeText(movable_node_id_);
}

void Draw::generateText(const int movable_node_id_)
{
    generateNodeText(graph_.findNodeByIdReadOnly(movable_node_id_));
    generateEdgesText(movable_node_id_);
}

void Draw::generateNodeText(const Node &node)
{
    generated_text_node.clear();

    generated_text_node.push_back(node_id_text_ + std::to_string(node.getNodeId()));
    generated_text_node.push_back(cartesian_x_y_point_text_ + "(" + std::to_string(node.getXYPoint().x) +
                                  "," + std::to_string(node.getXYPoint().y) + ")");
    generated_text_node.push_back(vehicle_size_text_ + std::to_string(node.getVehicleSize()));
    generated_text_node.push_back(inner_text_ + std::to_string(node.getInner()));
    generated_text_node.push_back(measurment_error_cm_text_ + std::to_string(node.getMeasurmentError()));
    generated_text_node.push_back(theta_rotation_degrees_text_ + std::to_string(node.getThetaRotationDegrees()));
    generated_text_node.push_back("===================");
}

void Draw::generateEdgesText(const int movable_node_id_)
{
    generated_text_edge.clear();
    for (auto it = graph_.getEdges().begin(); it != graph_.getEdges().end(); it++)
    {
        if (it->second.getObserverId() == movable_node_id_)
        {
            generateEdgeText(it->second);
        }
    }
}

void Draw::generateEdgeText(const Edge &edge)
{
    generated_text_edge.push_back(edge_id_ + std::to_string(edge.getEdgeId()));
    generated_text_edge.push_back(observer_id + std::to_string(edge.getObserverId()));
    generated_text_edge.push_back(target_id_ + std::to_string(edge.getTargetId()));
    generated_text_edge.push_back(distance_between_nodes_meters_ + std::to_string(edge.getDistanceBetweenNodesMeters()));
    generated_text_edge.push_back(angle_between_nodes_degrees_ + std::to_string(edge.getAngleBetweenNodesDegrees()));
    generated_text_edge.push_back(temp_timestamp_ + std::to_string(edge.getTempTimestamp()));
    generated_text_edge.push_back(distance_between_nodes_meters_error_ + std::to_string(edge.getDistanceBetweenNodesMetersError()));
    generated_text_edge.push_back(angle_between_nodes_degrees_error_ + std::to_string(edge.getAngleBetweenNodesDegreesError()));
    generated_text_edge.push_back("===================");
}

// all of this stuff shouldnt really be inside this fucntion, it should be handled probably in differnect funcitons,because names dont resemble resposibility here
void Draw::decideMaxSizeOfNodeAndEdgeText(const int movable_node_id_)
{
    const Node &node = graph_.findNodeByIdReadOnly(movable_node_id_);

    int node_info_rectangle_width_ = 0;
    int node_info_rectangle_height_ = 0;
    int edge_info_rectangle_width_ = 0;
    int edge_info_rectangle_height_ = 0;

    int node_text_gap = textGapSum(generated_text_node);
    int edge_text_gap = textGapSum(generated_text_edge);

    cv::Size rectangleNodeText = rectangleOfTextSize(generated_text_node);
    cv::Size rectangleEdgeText = rectangleOfTextSize(generated_text_edge);

    // now a function needed to decide the localization of where the text is to be drawn BEFORE drawGeneratedText()
    // it needs to return the org pos

    // also the function of the layout generated text function is now:
    //-getMaxSizeofText()
    // Its no longer laying out generated text.

    // the next fucnton i want to call, which would get the origin pos of text
    //  is the laoutGeneratedText, and THEN i call draw generatedTExt();

    std::pair<cv::Point2d, cv::Point2d> textOriginPoints = layoutNodeAndEdgeText(rectangleNodeText, rectangleEdgeText);

    drawGeneratedText(textOriginPoints.first, generated_text_node, movable_node_id_);
    drawGeneratedText(textOriginPoints.second, generated_text_edge, movable_node_id_);
}

// recieve origin point, then in this function i decide
// the logic of drawing on each level differnet vector of generated_edge_text/node positions.

void Draw::drawGeneratedText(cv::Point2d origin_point,
                             std::vector<std::string> generated_text,
                             int movable_node_id_)
{
    for (auto it = generated_text.rbegin(); it != generated_text.rend(); it++)
    {
        spdlog::warn("Origin point of drawnText ({},{})  ", origin_point.x, origin_point.y);

        if ((*it).length() == 0)
        {
            spdlog::warn("text of generated_text is empty");
            *it == "ERROR, NO TEXT";
        }
        if (font_face_ == 0)
        {
            spdlog::warn("font_face_ of class is equal to zero");
            font_face_ = cv::FONT_HERSHEY_PLAIN;
        }
        cv::Size text_size = cv::getTextSize(*it,
                                             font_face_,
                                             font_scale_,
                                             font_thickness_,
                                             &baseline_);

        cv::putText(img_,
                    *it,
                    origin_point,
                    font_face_,
                    font_scale_,
                    graph_.findNodeByIdReadOnly(movable_node_id_).getColorPalet().text_color,
                    font_thickness_);

        spdlog::warn("text_size.height ({}), gap_size_pixels_ ({}), baseline_ ({})  ", text_size.height, gap_size_pixels_, baseline_);

        origin_point.y -= (text_size.height + gap_size_pixels_ + baseline_);
    }
}

int Draw::textGapSum(std::vector<cv::String> generated_text)
{
    if (generated_text.size() < 1)
    {
        return 0;
    }
    else
    {
        return ((generated_text.size() - 1) * gap_size_pixels_);
    }
}

cv::Size Draw::rectangleOfTextSize(std::vector<cv::String> generated_text)
{
    int rectangle_width_ = 0;
    int rectangle_height_ = 0;
    // calculate the rectangle of the node
    for (auto it = generated_text.begin(); it != generated_text.end(); it++)
    {
        if ((*it).length() == 0)
        {
            spdlog::warn("text of generated_text is empty");
            *it == "ERROR, NO TEXT";
        }
        if (font_face_ == 0)
        {
            spdlog::warn("font_face_ of class is equal to zero");
            font_face_ = cv::FONT_HERSHEY_PLAIN;
        }

        cv::Size text_size = cv::getTextSize(*it,
                                             font_face_,
                                             font_scale_,
                                             font_thickness_,
                                             &baseline_);
        if (text_size.width > rectangle_width_)
        {
            rectangle_width_ = text_size.width;
        }
        rectangle_height_ += text_size.height + baseline_ + gap_size_pixels_;
    }
    return cv::Size(rectangle_width_, rectangle_height_);
}

bool Draw::doesTextFitOnScreen(cv::Size rectangle)
{
    if (rectangle.height > screen_height_ ||
        rectangle.width > screen_width_)
    {
        spdlog::warn("The text of size ({},{})  will not fit on the screen without additional formating", rectangle.width, rectangle.height);
        return false;
    }

    return true;
}

std::pair<cv::Point2d, cv::Point2d> Draw::layoutNodeAndEdgeText(cv::Size rectangleNodeText,
                                                                cv::Size rectangleEdgeText)
{
    spdlog::warn("screen_width_ ({}), screen_height_({})", screen_width_, screen_height_);
    spdlog::warn("1rectangle_width_ ({}), rectangle_height_({})", rectangleNodeText.width, rectangleNodeText.height);
    spdlog::warn("2rectangle_width_ ({}), rectangle_height_({})", rectangleEdgeText.width, rectangleEdgeText.height);
    cv::Point2d node_text_origin_point;
    cv::Point2d edge_text_origin_point;

    if (!doesTextFitOnScreen(rectangleNodeText))
    {
        // do formatting algorithm and return something
    }
    if (!doesTextFitOnScreen(rectangleEdgeText))
    {
        // do formatting algorithm and return something
    }

    node_text_origin_point.x = margin_from_edge_;
    node_text_origin_point.y = margin_from_edge_ + rectangleNodeText.height;

    edge_text_origin_point.x = screen_width_ - margin_from_edge_ - rectangleEdgeText.width;
    edge_text_origin_point.y = margin_from_edge_ + rectangleEdgeText.height;

    return std::pair<cv::Point2d, cv::Point2d>(node_text_origin_point, edge_text_origin_point);
}
