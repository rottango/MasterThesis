#include <cstdint>
#include <draw_class.hpp>
#include <node_class.hpp>

class Application
{
public:
    Application();

private:
    uint8_t application_id_;
    uint8_t graph_id_;
    cv::Mat img;
    uint8_t window_loop;
};