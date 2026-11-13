#include <application_class.hpp>
#include <libserialport_sequence.hpp>
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
        update();
        if(graph_.numerOfNodes()==0){
            spdlog::warn("There is no nodes in the graph");
        }
        else{
            render();
        }
        presentFrame();
    }
    end();
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

    // rows = height
    // cols = width

    cv::Mat img_temp_{this->screen_height_,
                      this->screen_width_,
                      this->make_type_flag_,
                      this->background_color_};
    img_ = img_temp_;

    movable_node_id_ = graph_.addNode(openCVPointToCartesianPoint(cv::Point2d(screen_width_ / 6), screen_width_, screen_height_ * 1 / 3), 0, 45, 55, 65, generateColorPalet(color_positon_));

    running_ = true;

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

    uwb_running_ = true;
    std::thread uwbThread([this]() {
        UwbDeviceProcess(*this);
    });

    run();

    uwb_running_ = false;
    uwbThread.join();
}

void Application::end()
{
    shutdown();
}

void Application::exectuteInput(char character)
{
    Node *node = nullptr;
    bool doesAnyNodeExist;
    
    if(graph_.numerOfNodes()==0){
        doesAnyNodeExist = false;  
    }else{
        doesAnyNodeExist = true;
        node = &graph_.findNodeByIdReadWrite(movable_node_id_);
    }

    switch (character)
    {
    case 'a':
        if(doesAnyNodeExist==false){
            break;
        }
        node->changePosition(cv::Point2d(node->getXYPoint().x - position_step_size_, node->getXYPoint().y));
        break;
    case 's':
        if(!doesAnyNodeExist)
            break;
        node->changePosition(cv::Point2d(node->getXYPoint().x, node->getXYPoint().y - position_step_size_));
        break;
    case 'd':
        if(!doesAnyNodeExist)
            break;
        node->changePosition(cv::Point2d(node->getXYPoint().x + position_step_size_, node->getXYPoint().y));
        break;
    case 'w':
        if(!doesAnyNodeExist)
            break;
        node->changePosition(cv::Point2d(node->getXYPoint().x, node->getXYPoint().y + position_step_size_));
        break;
    case 'l':
        if(!doesAnyNodeExist)
            break;
        node->rotateNodesAxis(-angle_step_size_);
        break;
    case 'r':
        if(!doesAnyNodeExist)
            break;
        node->rotateNodesAxis(angle_step_size_);
        break;
    case 'x':
        if(!doesAnyNodeExist)
            break;
        
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
        }

        if (node_id_of_min_difference != movable_node_id_)
        {
            movable_node_id_ = node_id_of_min_difference;

            spdlog::info("Switched movable_node_id");
            break;
        }

        movable_node_id_ = 1;
        spdlog::info("movable_node_id=1");
        break;
    case '=':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setMeasurmentErrorCm(node->getMeasurmentError() + 1);
        break;
    case '-':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setMeasurmentErrorCm(node->getMeasurmentError() - 1);
        break;
    case ']':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setVehicleSize(node->getVehicleSize() + 1);
        break;
    case '[':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setVehicleSize(node->getVehicleSize() - 1);
        break;
    case '\'':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setInner(node->getInner() + 1);
        break;
    case ';':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        node->setInner(node->getInner() - 1);
        break;
    case 'e':
        if(!doesAnyNodeExist){
            spdlog::warn("There is no nodes in the graph");
            break;
        }
        int target_id_temp;

        std::cout << "Provide target_id: ";
        std::cin >> target_id_temp;

        edge_id_list_.push_back(graph_.addEdge(movable_node_id_, static_cast<uint8_t>(target_id_temp)));
        break;
    case 'n':
        node_id_list_.push_back(graph_.addNode(openCVPointToCartesianPoint(cv::Point2d(screen_width_ / 6), screen_width_, screen_height_ * 1 / 3), 0, 45, 55, 65, generateColorPalet(color_positon_)));
        break;
    case 'o':
        int32_t x, y;
        this->getUwbPosition(x,y);
        node->changePosition(cv::Point2d(x/10, y/10));
    default:
        break;
    }
}

void Application::render()
{
    draw_.drawFrame(movable_node_id_);
}

void Application::presentFrame()
{
    cv::imshow(this->named_window_name_, this->img_);
}

void Application::processInput()
{
    char pressedKey = cv::waitKey(40);
    switch (pressedKey)
    {
    case 'w':
        exectuteInput(pressedKey);
        break;
    case 'a':
        exectuteInput(pressedKey);
        break;
    case 's':
        exectuteInput(pressedKey);
        break;
    case 'd':
        exectuteInput(pressedKey);
        break;
    case 'l':
        exectuteInput(pressedKey);
        break;
    case 'r':
        exectuteInput(pressedKey);
        break;
    case 'x':
        exectuteInput(pressedKey);
        break;
    case '.':
        running_ = false;
        break;
    case '=':
        exectuteInput(pressedKey);
        break;
    case '-':
        exectuteInput(pressedKey);
        break;
    case ']':
        exectuteInput(pressedKey);
        break;
    case '[':
        exectuteInput(pressedKey);
        break;
    case '\'':
        exectuteInput(pressedKey);
        break;
    case ';':
        exectuteInput(pressedKey);
        break;
    case 'e':
        exectuteInput(pressedKey);
        break;
    case 'n':
        exectuteInput(pressedKey);
        break;
    case 'o':
        //miliseconds=40;
        exectuteInput(pressedKey);
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

void Application::update()
{
    int32_t x, y;
    getUwbPosition(x, y);
    Node &node = graph_.findNodeByIdReadWrite(movable_node_id_);
    node.changePosition(cv::Point2d(x / 10.0, y / 10.0));

    graph_.updateNodesAndEdges();
}

void Application::createNamedWindow()
{
    cv::namedWindow(this->named_window_name_, this->flag_);
    cv::resizeWindow(this->named_window_name_, cv::Size(this->screen_width_, this->screen_height_));
}

void Application::setUwbPosition(int32_t x, int32_t y)
{
    std::lock_guard<std::mutex> lock(uwb_mutex_);

    uwb_x_ = x;
    uwb_y_ = y;
}

void Application::getUwbPosition(int32_t &x, int32_t &y)
{
    std::lock_guard<std::mutex> lock(uwb_mutex_);

    x = uwb_x_;
    y = uwb_y_;
}

