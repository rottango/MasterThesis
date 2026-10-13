#include <cstdint>
#include <draw_class.hpp>
#include <graph_class.hpp>
#include <group_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

class Application
{
public:
    /**
     * @brief Construct a new Application object
     * 
     */
    Application();

    /**
     * @brief 
     * 
     */
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

    int color_positon_ = 0;

    int movable_node_id_ = 1;
    int node_id_of_min_difference = 1;
    int min_difference_;

    std::vector<uint8_t> node_id_list_;
    std::vector<uint8_t> edge_id_list_;

    /**
     * @brief 
     * 
     */
    void run();

    /**
     * @brief 
     * 
     */
    void initialUserInput();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool initialize();

    /**
     * @brief 
     * 
     */
    void clearFrame();

    /**
     * @brief 
     * 
     */
    void end();

    /**
     * @brief 
     * 
     * @param character 
     */
    void exectuteInput(char character);

    /**
     * @brief 
     * 
     */
    void render();

    /**
     * @brief 
     * 
     */
    void presentFrame();

    /**
     * @brief 
     * 
     */
    void processInput();

    /**
     * @brief 
     * 
     */
    void update();

    /**
     * @brief 
     * 
     * @return true 
     * @return false 
     */
    bool shutdown();

    /**
     * @brief Create a Named Window object
     * 
     */
    void createNamedWindow();
};