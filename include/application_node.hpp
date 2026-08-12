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

    bool initialize(int screen_width_,
                    int screen_height_);

    void clearFrame();

    void update();

    void render();

    void presentFrame();

    void processInput();

    bool shutdown();

    void createNamedWindow(std::string namedWindowName, int flag);
};