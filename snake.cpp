#include "snake.h" // 包含snake头文件

// 从文件加载游戏数据
bool Snake::LoadPlayDataFromFile(const string &file) {
    std::ifstream fin(file); // 打开文件
    if (!fin) // 如果文件打开失败
    {
        std::cout << "can not open file " << file << endl; // 输出错误信息
        return false; // 返回false
    }
    auto result = m_control.LoadPlayDataFromFile(fin); // 从文件加载游戏数据
    return result; // 返回结果
}

// 开始游戏
bool Snake::Play(char direction) {
    if (!m_control.GoAhead(direction)) // 如果蛇不能向指定方向移动
    {
        std::cout << "Game Over!" << std::endl; // 输出游戏结束信息
        return true; // 返回true
    }
    return false; // 返回false
}

// 打印游戏面板
void Snake::PrintMatrix(QPainter &painter, int pictureSize) const {
    m_control.m_model.ShowGame(painter, pictureSize); // 显示游戏
}

// 蛇头向指定方向移动一步
bool Control::GoAhead(char userInputDirection)
{
    switch (userInputDirection) // 根据用户输入的方向
    {
        case 'w':
        case 'W':
            // 向上移动一行，列不变
            return GoAhead(/*row_step*/-1, /*column_step*/0);
        case 'a':
        case 'A':
            // 行不变，向左移动一列
            return GoAhead(0, -1);
        case 'd':
        case 'D':
            // 行不变，向右移动一列
            return GoAhead(0, +1);
        case 's':
        case 'S':
            // 向下移动一行，列不变
            return GoAhead(+1, 0);
        default:
            return true;
    }
}

// 从文件加载游戏数据
bool Control::LoadPlayDataFromFile(istream &fin)
{
    std::string line;
    std::getline(fin, line); // 读取一行
    std::istringstream iss(line); // 创建字符串流
    int row_count = 0, column_count = 0;
    // 从行中读取行数和列数
    iss >> row_count >> column_count;

    for (int row = 0; row < row_count; row++) // 对于每一行
    {
        std::vector<char> lineData;
        std::getline(fin, line); // 读取一行
        std::istringstream lineDataIss(line); // 创建字符串流
        for (int column = 0; column < column_count; column++) // 对于每一列
        {
            char element;
            // 读取一个元素
            lineDataIss >> element;
            lineData.push_back(element); // 将元素添加到行数据中
            // 蛇开始时没有身体，只有一个蛇头
            if (element == '1')
            {
                m_model.IncreaseOnlyBody(std::make_pair(row, column)); // 增加蛇身长度
            }
        }
        m_model.AppendToBoard(lineData); // 将行数据添加到游戏面板中
    }
    if (m_model.m_snakeBody.empty()) // 如果蛇身体为空
    {
        cout << "snake body is empty! init game failed." << endl; // 输出错误信息
        assert(false); // 断言失败
        return false; // 返回false
    }
    return true; // 返回true
}

// 蛇头向指定方向移动一步
bool Control::GoAhead(int row_step, int column_step)
{
    // nextPosition = currentPostion + (row_step, column_step)
    auto nextPosition = m_model.GetNextPosition(row_step, column_step); // 计算下一个位置
    if (m_model.IsGameOver(nextPosition.first, nextPosition.second)) // 如果游戏结束
    {
        return false; // 返回false
    }
    if (m_model.ExistFood(nextPosition.first, nextPosition.second)) // 如果存在食物
    {
        m_model.EatFood(nextPosition); // 吃食物
        m_model.CreateFood(); // 创建新的食物
    }
    else
    {
        m_model.MoveOneStepTo(nextPosition); // 向下一个位置移动一步
    }

    return true; // 返回true
}

// 吃食物
void Model::EatFood(pair<int, int> nextPosition)
{
    // 新的蛇头
    m_snakeBody.push_front(nextPosition); // 将新的蛇头添加到蛇身体中
    // 直接吃掉，不移动尾巴
    m_playBoard[nextPosition.first][nextPosition.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY); // 将新的蛇头添加到游戏面板中
}

// 在指定位置放置食物
bool Model::PushFoodAt(int row, int col)
{
    bool result = false;
    if (m_playBoard[row][col] == static_cast<char>(MatrixValueEnum::NOTHING)) // 如果指定位置为空
    {
        m_playBoard[row][col] = static_cast<char>(MatrixValueEnum::FOOD); // 在指定位置放置食物
        result = true; // 返回true
    }
    return result; // 返回结果
}

// 检查指定位置是否有食物
bool Model::ExistFood(int row, int col) const
{
    // 坐标(i, j)是否是蛇食物
    return m_playBoard[row][col] == static_cast<int>(MatrixValueEnum::FOOD); // 返回结果
}

// 增加蛇身长度
void Model::IncreaseOnlyBody(pair<int, int> nextPosition)
{
    m_snakeBody.push_front(nextPosition); // 将新的蛇头添加到蛇身体中
}

// 向游戏面板添加一行
void Model::AppendToBoard(const vector<char> &lineData)
{
    m_playBoard.push_back(lineData); // 将行数据添加到游戏面板中
}
// 判断游戏是否结束
bool Model::IsGameOver(int row, int col) const
{
    // 如果蛇头打算去的位置会导致游戏结束，例如索引超出范围或者目标位置是蛇身体，则游戏结束
    return (row < 0
            || row >= m_playBoard.size()
            || col < 0
            || col >= m_playBoard[0].size()
            || (m_playBoard[row][col] == static_cast<int>(MatrixValueEnum::SNAKE_BODY))
            );
}

// 蛇向指定位置移动一步
void Model::MoveOneStepTo(pair<int, int> nextPosition)
{
    // 蛇尾移动到蛇新的头部
    auto head = nextPosition;
    auto tail = m_snakeBody.back();
    m_playBoard[tail.first][tail.second] = static_cast<char>(MatrixValueEnum::NOTHING); // 蛇尾变为空
    m_playBoard[head.first][head.second] = static_cast<char>(MatrixValueEnum::SNAKE_BODY); // 新的蛇头
    m_snakeBody.push_front(head); // 将新的蛇头添加到蛇身体中
    m_snakeBody.pop_back(); // 移除蛇尾
}

// 创建新的食物
void Model::CreateFood()
{
    // 随机生成一个新的位置，但这个位置可能已经是蛇的身体
    // 所以，创建食物需要在新生成的随机位置重复，直到成功
    do
    {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 g(seed);  // mt19937是一个标准的梅森旋转引擎
        // 生成新的随机坐标
        int row = g() % GetRow();
        int col = g() % GetCol();
        // 一旦放置成功，记得退出循环，让程序继续
        bool pushSuccess = PushFoodAt(row, col);
        if (pushSuccess)
        {
            break;
        }
    } while (true);
}

// 显示游戏
void Model::ShowGame(QPainter &painter, int pictureSize) const {
    auto headPosition = m_snakeBody.front();
    for (size_t row = 0; row < m_playBoard.size(); row++) {
        for (size_t col = 0; col < m_playBoard[row].size(); col++)
        {
            auto element = m_playBoard[row][col];
            QPixmap pixmap;
            bool load_result = false;
            if (row == headPosition.first && col == headPosition.second)
            {
                if(pixmap.load("snake_head.png")){
                     load_result = true;
                }
            }
            else if (element == static_cast<char>(MatrixValueEnum::FOOD))
            {
                if(pixmap.load("food-apple.png")){
                     load_result = true;
                }
            }
            else if (element == static_cast<char>(MatrixValueEnum::NOTHING))
            {
                if(pixmap.load("grass.png")){
                     load_result = true;
                }
            }
            // 蛇身体
            else if(element == static_cast<char>(MatrixValueEnum::SNAKE_BODY))
            {
                if(pixmap.load("body.png")){
                     load_result = true;
                }
            }
            else {
                assert(false);
            }
            assert(load_result);
            int x = col * pictureSize;
            int y = row * pictureSize;
            QRect rect(x, y, pictureSize, pictureSize);
            painter.drawPixmap(rect, pixmap);
        }
    }
}
