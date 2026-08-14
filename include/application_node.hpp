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

    void run();

private:
    cv::Mat img_;
    Graph graph_;
    Draw draw_;
    bool running_;
    std::string namedWindowName;
    int screen_width_;
    int screen_height_;
    int make_type_flag_ = CV_8UC3;
    cv::Scalar background_color_{87, 80, 73};

    void initialUserInput();

    bool initialize();

    void clearFrame();

    void start();

    void end();

    void update();

    void render();

    void presentFrame();

    void processInput();

    bool shutdown();

    void createNamedWindow(std::string namedWindowName, int flag);
};