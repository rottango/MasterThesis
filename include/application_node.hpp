#include <cstdint>
#include <draw_class.hpp>
#include <graph_class.hpp>
#include <group_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>

#include <opencv2/opencv.hpp>

class Application
{
public:
    Application();

    void start();

private:
    cv::Mat img_;
    Graph graph_;
    Draw draw_;
    bool running_;
    std::string named_window_name_ = "Visualization";
    int screen_width_;
    int screen_height_;
    int make_type_flag_ = CV_8UC3;
    int flag_ = cv::WindowFlags::WINDOW_NORMAL;
    cv::Scalar background_color_{87, 80, 73};
    double position_step_size_ = 10;
    double angle_step_size_ = 1;

    void run();

    void initialUserInput();

    bool initialize();

    void clearFrame();

    void end();

    void update(char character);

    void render();

    void presentFrame();

    void processInput();

    bool shutdown();

    void createNamedWindow();
};