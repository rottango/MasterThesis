#include <application_node.hpp>

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
    createNamedWindow("Visualization", cv::WindowFlags::WINDOW_NORMAL);
    cv::Size windowSize{this->screen_width_, this->screen_height_};

    cv::Mat img_temp_{this->screen_height_, this->screen_width_, this->make_type_flag_, this->background_color_};
    img_ = img_temp_;

    running_ = true;

    return true;
}

void Application::clearFrame()
{
    cv::Mat img_temp_{this->screen_height_,
                      this->screen_width_,
                      this->make_type_flag_,
                      this->background_color_};
    this->img_ = img_temp_;
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

void Application::update()
{
}

void Application::render()
{
    draw_.drawFrame();
}

void Application::presentFrame()
{
    cv::imshow(namedWindowName, img_);
}

void Application::processInput()
{
    char pressedKey = cv::pollKey();
    switch (pressedKey)
    {
    case 'w':
        update();
        break;
    case 'a':
        update();
        break;
    case 's':
        update();
        break;
    case 'd':
        update();
        break;
    case '[':
        update();
        break;
    case ']':
        update();
        break;
    default:
        break;
    }
}

bool Application::shutdown()
{
    cv::destroyWindow(namedWindowName);

    return true;
}

void Application::createNamedWindow(std::string namedWindowName, int flag)
{
    cv::namedWindow(namedWindowName, flag);
    cv::resizeWindow(namedWindowName, cv::Size(screen_width_, screen_height_));
}