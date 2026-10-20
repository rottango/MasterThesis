#include <cstdint>
#include <draw_class.hpp>
#include <graph_class.hpp>
#include <group_class.hpp>
#include <grouping_manager_class.hpp>
#include <node_class.hpp>

#include <opencv2/opencv.hpp>
#include <spdlog/spdlog.h>

/**
* @file application_class.hpp
* @author rottango
* @date 20.10.2026
* @see ‘‘ OpenCV2 ’’ 
*
* @brief Header file for the application class, thats the main coordinator of all tasks
*/

class Application
{
public:
    /**
     * @brief Construct a new Application object
     * 
     */
    Application();

    /**
     * @brief This function begins application, starting with initalization, and then calling the looped run function
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
     * @brief This function is responsible for handling each user input, and thus starting the cascade of all function calls, until the running flag is not false. 
     * 
     */
    void run();

    /**
     * @brief Get the size of the screen from the user
     * 
     */
    void initialUserInput();

    /**
     * @brief Start up the program, create the window and rise the running_ flag
     * 
     * @return true 
     * @return false 
     */
    bool initialize();

    /**
     * @brief Reset the image to a single solid color
     * 
     */
    void clearFrame();

    /**
     * @brief Call the shutdown function
     * 
     */
    void end();

    /**
     * @brief Based on the input from the processInput function, exectute differ functions in the run step
     * 
     * @param character 
     */
    void exectuteInput(char character);

    /**
     * @brief Call the draw's main function - drawFrame() for the currently active node
     * 
     */
    void render();

    /**
     * @brief Display the drawn image by the Draw object
     * 
     */
    void presentFrame();

    /**
     * @brief Based on the input, refer the program exectution to differ functions in the run step
     * 
     */
    void processInput();

    /**
     * @brief Call the graph's updateNodesAndEdges
     * 
     */
    void update();

    /**
     * @brief ToDo: Free all objects here
     * 
     * @return true 
     * @return false 
     */
    bool shutdown();

    /**
     * @brief Create a Named Window object and resize it to the user inputed screen width and height
     * 
     */
    void createNamedWindow();
};