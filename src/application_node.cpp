#include <application_node.hpp>
#include <color_palet_struct.hpp>

Application::Application() : draw_{graph_, img_}
{
    spdlog::info("Entering Application::Application()");
    spdlog::info("Exiting Application::Application()");
}

void Application::run()
{
    spdlog::info("Entering Application::run()");
    while (this->running_)
    {
        clearFrame();
        processInput();
        render();
        presentFrame();
    }
    end();
    spdlog::info("Exiting Application::run()");
}
void Application::initialUserInput()
{
    std::cout << "Provide Screen Width: ";
    std::cin >> this->screen_width_;
    std::cout << "\nProvide Screen Height: ";
    std::cin >> this->screen_height_;
}

bool Application::initialize()
{
    spdlog::info("Entering Application::initialize()");

    createNamedWindow();
    cv::Size windowSize{this->screen_width_, this->screen_height_};

    cv::Mat img_temp_{this->screen_height_,
                      this->screen_width_,
                      this->make_type_flag_,
                      this->background_color_};
    img_ = img_temp_;

    running_ = true;

    graph_.addNode(cv::Point2d(0, 0), 0, 45, 55, 65, ugv1ColorPalet);
    graph_.addNode(cv::Point2d(0, 0), 0, 45, 55, 65, ugv2ColorPalet);
    graph_.addNode(cv::Point2d(0, 0), 0, 45, 55, 65, ugv3ColorPalet);

    spdlog::info("Exiting Application::createNamedWindow()");
    return true;
}

void Application::clearFrame()
{
    spdlog::info("Entering Application::clearFrame()");

    this->img_.setTo(background_color_);
    spdlog::info("Exiting Application::clearFrame()");
}

void Application::start()
{
    spdlog::info("Entering Application::start()");

    initialUserInput();
    initialize();
    run();
    spdlog::info("Exiting Application::start()");
}

void Application::end()
{
    spdlog::info("Entering Application::end()");
    shutdown();
    spdlog::info("Exiting Application::end()");
}

void Application::update(char character)
{
    spdlog::info("Entering Application::update()");
    Node &node = graph_.findNodeByIdReadWrite(movable_node_id_);
    switch (character)
    {
    case 'a':
        node.changePosition(cv::Point2d(node.getXYPoint().x - position_step_size_, node.getXYPoint().y));
        break;
    case 's':
        node.changePosition(cv::Point2d(node.getXYPoint().x, node.getXYPoint().y - position_step_size_));
        break;
    case 'd':
        node.changePosition(cv::Point2d(node.getXYPoint().x + position_step_size_, node.getXYPoint().y));
        break;
    case 'w':
        node.changePosition(cv::Point2d(node.getXYPoint().x, node.getXYPoint().y + position_step_size_));
        break;
    case '[':
        node.rotateNodesAxis(-angle_step_size_);
        break;
    case ']':
        node.rotateNodesAxis(angle_step_size_);
        break;
    case 'x':
        min_difference_ = 255;
        node_id_of_min_difference = movable_node_id_;
        for (auto it = graph_.getNodes().begin(); it != graph_.getNodes().end(); it++)
        {
            int temp_result = it->second.getNodeId() - movable_node_id_;
            if (it->second.getNodeId() > movable_node_id_ &&
                temp_result < min_difference_)
            {
                min_difference_ = temp_result;
                node_id_of_min_difference = it->second.getNodeId();
            }
        };
        if (node_id_of_min_difference != movable_node_id_)
        {
            movable_node_id_ = node_id_of_min_difference;
            spdlog::info("Switched movable_node_id");

            break;
        }

        movable_node_id_ = 1;
        spdlog::info("movable_node_id=1");
    default:
        break;
    }
    spdlog::info("Exiting Application::update()");
}

void Application::render()
{
    spdlog::info("Entering Application::render()");
    draw_.drawFrame();
    spdlog::info("Exitng Application::render()");
}

void Application::presentFrame()
{
    spdlog::info("Entering Application::presentFrame()");
    cv::imshow(this->named_window_name_, this->img_);
    spdlog::info("Exiting Application::presentFrame()");
}

void Application::processInput()
{
    spdlog::info("Entering Application::processInput()");

    char pressedKey = cv::waitKey();
    switch (pressedKey)
    {
    case 'w':
        update(pressedKey);
        break;
    case 'a':
        update(pressedKey);
        break;
    case 's':
        update(pressedKey);
        break;
    case 'd':
        update(pressedKey);
        break;
    case '[':
        update(pressedKey);
        break;
    case ']':
        update(pressedKey);
        break;
    case 'x':
        update(pressedKey);
        break;
    case '.':
        running_ = false;
        break;
    default:
        break;
    }
    spdlog::info("Exiting Application::processInput()");
}

bool Application::shutdown()
{
    spdlog::info("Entering Application::shutdown()");

    cv::destroyWindow(this->named_window_name_);

    spdlog::info("Exiting Application::shutdown()");

    return true;
}

void Application::createNamedWindow()
{
    spdlog::info("Entering Application::createNamedWindow()");

    cv::namedWindow(this->named_window_name_, this->flag_);
    cv::resizeWindow(this->named_window_name_, cv::Size(this->screen_width_, this->screen_height_));
    spdlog::info("Exiting Application::createNamedWindow()");
}