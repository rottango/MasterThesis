#include <application_node.hpp>
#include <color_palet_struct.hpp>

Application::Application() : draw_{graph_, img_}
{
}

void Application::run()
{
    while (this->running_)
    {
        clearFrame();
        processInput();
        render();
        presentFrame();
    }
    shutdown();
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
    createNamedWindow();
    cv::Size windowSize{this->screen_width_, this->screen_height_};

    cv::Mat img_temp_{this->screen_height_,
                      this->screen_width_,
                      this->make_type_flag_,
                      this->background_color_};
    img_ = img_temp_;

    running_ = true;

    graph_.addNode(cv::Point2d(0, 0), 0, 45, 55, 65, ugv1ColorPalet);

    return true;
}

void Application::clearFrame()
{
    this->img_.setTo(background_color_);
}

void Application::start()
{
    initialUserInput();
    initialize();
    run();
}

void Application::end()
{
    shutdown();
}

void Application::update(char character)
{

    Node &node = graph_.findNodeByIdReadWrite(0);
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
    default:
        break;
    }
}

void Application::render()
{
    draw_.drawFrame();
}

void Application::presentFrame()
{
    cv::imshow(this->named_window_name_, this->img_);
}

void Application::processInput()
{
    char pressedKey = cv::pollKey();
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
    case '.':
        running_ = false;
        break;
    default:
        break;
    }
}

bool Application::shutdown()
{
    cv::destroyWindow(this->named_window_name_);

    return true;
}

void Application::createNamedWindow()
{
    cv::namedWindow(this->named_window_name_, this->flag_);
    cv::resizeWindow(this->named_window_name_, cv::Size(this->screen_width_, this->screen_height_));
}