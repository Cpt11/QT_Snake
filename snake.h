#pragma once // 防止头文件重复包含
#include <list> // 用于存储蛇身体的坐标
#include <utility> // 用于pair模板类
#include <fstream> // 文件流
#include <sstream> // 字符串流
#include <iostream>
#include <random> // 生成随机数
#include <chrono> // 时间库
#include <cassert>
using namespace std; // 使用标准命名空间

#include <QPainter> // Qt绘图类

const int P_SIZE = 50;
// 在任何位置，有以下三种可能：蛇身、食物、无（草地）
enum class MatrixValueEnum {
    NOTHING = '0', SNAKE_BODY = '1', FOOD = '2'
};

class Model {
public:
    size_t GetRow(void) const { return m_playBoard.size(); } // 获取游戏面板的行数
    size_t GetCol(void) const { return m_playBoard.at(0).size(); } // 获取游戏面板的列数
    void EatFood(pair<int, int> nextPosition); // 蛇吃食物
    bool PushFoodAt(int row, int col); // 在指定位置放置食物
    bool ExistFood(int row, int col) const; // 检查指定位置是否有食物
    void IncreaseOnlyBody(pair<int, int> nextPosition); // 增加蛇身长度
    void AppendToBoard(const vector<char>& lineData); // 向游戏面板添加一行
    // 如果蛇撞到自己的身体或者超出游戏面板，游戏结束
    bool IsGameOver(int row, int col) const;
    // 计算蛇头移动一次后的新坐标
    std::pair<int, int> GetNextPosition(int row_step, int column_step) const
    {
        auto old = GetCurrentPosition();
        auto newRow = old.first += row_step;
        auto newCol = old.second += column_step;
        return std::make_pair(newRow, newCol);
    }
    // 获取蛇头的坐标
    std::pair<int, int> GetCurrentPosition(void) const
    {
        auto front = m_snakeBody.front();
        return front;
    }
    void MoveOneStepTo(pair<int, int> nextPosition); // 蛇向指定位置移动一步
    void CreateFood(void); // 创建新的食物
    void ShowGame(QPainter& painter, int pictureSize) const; // 显示游戏
public:
    vector<vector<char>> m_playBoard; // 游戏面板
    list<pair<int, int>> m_snakeBody; // 蛇身体的坐标
};

class Control
{
public:
    size_t GetRow(void) const { return m_model.GetRow(); } // 获取游戏面板的行数
    size_t GetCol(void) const { return m_model.GetCol(); } // 获取游戏面板的列数
    // 用户输入一个字符（e / s / f / d），决定蛇头移动的方向
    bool GoAhead(char userInputDirection);
    bool LoadPlayDataFromFile(istream& fin); // 从文件加载游戏数据
    bool GoAhead(int row_step, int column_step); // 蛇头向指定方向移动一步
    Model m_model; // 游戏模型
};

class Snake {
public:
    size_t GetRow(void) const { return m_control.GetRow(); } // 获取游戏面板的行数
    size_t GetCol(void) const { return m_control.GetCol(); } // 获取游戏面板的列数
    // 从文件加载UI数据，存储在内部容器中，然后根据容器内容绘制UI
    bool LoadPlayDataFromFile(const std::string& file);
    // 开始游戏
    bool Play(char direction); // 如果游戏结束，返回true
    // 绘制贪吃蛇游戏，将UI和内存中的数据进行匹配
    // '_'  <== '0'
    // '$'  <== '2'
    // '#'  <== '1'
    // '@'  <== '1'
    void PrintMatrix(QPainter& painter, int pictureSize) const; // 打印游戏面板
private:
    Control m_control; // 游戏控制器
};
