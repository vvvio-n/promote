#include "Assistance.h"
#include "SeqQueue.h"
#include "SeqStack.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <algorithm>  // 包含 std::random_shuffle
#include <functional> // 包含 std::function

int main(void) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "T-shaped Railway Scheduling System");

    // 设置字体
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font file arial.ttf" << std::endl;
        return -1;
    }

    // 创建菜单文本
    sf::Text menuText("T-shaped Railway Scheduling System\n", font, 24);
    menuText.setPosition(200, 100);
    sf::Text option1("1. Scheduling System (Input/Output)\n", font, 24);
    option1.setPosition(250, 150);
    sf::Text option2("2. Random Sequence Generation\n", font, 24);
    option2.setPosition(250, 200);
    sf::Text option5("5. Exit Program\n", font, 24);
    option5.setPosition(250, 250);

    // 创建次级菜单文本
    sf::Text stackOptionText("1. Use Stack as Assist Track\n", font, 24);
    stackOptionText.setPosition(250, 150);
    sf::Text queueOptionText("2. Use Queue as Assist Track\n", font, 24);
    queueOptionText.setPosition(250, 200);

    // 创建输入提示文本
    sf::Text inputText("Enter the number of carriages (order from right to left): ", font, 24);
    inputText.setPosition(100, 100);
    sf::Text inputOrderText("Enter the order of carriages entering the stack: ", font, 24);
    inputOrderText.setPosition(100, 150);
    sf::Text inputEText("Enter e (e = 0 to exit): ", font, 24);
    inputEText.setPosition(100, 200);

    // 创建轨道状态文本
    sf::Text mainTrackText("Main Track:", font, 24);
    mainTrackText.setPosition(100, 450);
    sf::Text assistStackText("Assist Track:", font, 24);
    assistStackText.setPosition(100, 500);
    sf::Text rightTrackText("Right Track:", font, 24);
    rightTrackText.setPosition(100, 550);

    // 创建变量
    SeqQueue<int> qa;     // 创建一个整型的队列 qa，表示主轨道
    SeqQueue<int> qc;     // 创建一个整型的队列 qc，表示右侧轨道
    SeqStack<int> qb;     // 创建一个整型的栈 qb，表示辅轨道
    SeqQueue<int> qd;     // 创建一个整型的队列 qd，用于替代栈作为辅轨道
    int n = 0, x = 0, d = 0, No = 0;      // 定义整型变量 n, x, d, No
    int inst = 0;          // 初始化入栈次数为0 
    int outst = 0;         // 初始化出栈次数为0
    int outqu = 0;       // 初始化出队列次数为0
    int inqu = 0;       // 初始化入队列次数为0
    int maxlen = 0;     // 初始化辅轨道最大长度为0

    // 用于存储用户输入的车厢编号
    std::vector<int> inputCarriages;

    int choice = 0;
    int secondaryChoice = 0; // 用于存储栈或队列的选择
    bool inputCompleted = false;
    bool showMenu = true;
    bool showSecondaryMenu = false; // 新增用于显示次级菜单的标志

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Num1 && showMenu) {
                    choice = 1;
                    showMenu = false;
                    showSecondaryMenu = true; // 显示次级菜单
                }
                else if (event.key.code == sf::Keyboard::Num2 && showMenu) {
                    choice = 2;
                    showMenu = false;
                }
                else if (event.key.code == sf::Keyboard::Num5 && showMenu) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Num1 && showSecondaryMenu) { // 选择栈作为辅轨道
                    secondaryChoice = 1;
                    showSecondaryMenu = false;
                }
                else if (event.key.code == sf::Keyboard::Num2 && showSecondaryMenu) { // 选择队列作为辅轨道
                    secondaryChoice = 2;
                    showSecondaryMenu = false;
                }
                else if (event.key.code == sf::Keyboard::Enter && !showMenu && !showSecondaryMenu) {
                    if (x == 0) {
                        inputCompleted = true;
                    }
                    else {
                        inputCarriages.push_back(x);
                    }
                    x = 0;
                }
                else if (event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 && !showMenu && !showSecondaryMenu) {
                    x = x * 10 + (event.key.code - sf::Keyboard::Num0);
                }
                else if (event.key.code == sf::Keyboard::BackSpace && !showMenu && !showSecondaryMenu) {
                    // 删除最后一位输入的数字
                    if (x > 0) {
                        x /= 10; // 去掉最后一位
                    }
                }

            }
        }

        window.clear(sf::Color::Black); // 将背景颜色改为黑色

        if (showMenu) {
            window.draw(menuText);
            window.draw(option1);
            window.draw(option2);
            window.draw(option5);
        }
        else if (showSecondaryMenu) { // 新增次级菜单选择
            window.draw(stackOptionText);
            window.draw(queueOptionText);
        }
        else if (!inputCompleted && choice == 1) { // 只在选择1时显示输入提示
           
            // 显示输入提示
            window.draw(inputText);
            window.draw(inputOrderText);
            window.draw(inputEText);

            // 显示当前输入的车厢编号
            std::string carriagesStr = "Current input:";
            for (int carriage : inputCarriages) {
                carriagesStr += std::to_string(carriage) + " ";
            }
            sf::Text carriagesText(carriagesStr, font, 24);
            carriagesText.setPosition(450, 350);
            window.draw(carriagesText);

            // 显示当前输入的临时变量
            sf::Text tempText(std::to_string(x), font, 24);
            tempText.setPosition(450, 400);
            window.draw(tempText);
        }
        else {
            // 处理调度逻辑
            if (choice == 1) {
                n = inputCarriages.size();
                No = 1;
                for (int carriage : inputCarriages) {
                    qa.EnQueue(carriage);
                }

                // 从 1 到 n 进行调度操作
                for (int i = 1; i <= n; i++) {
                    if (secondaryChoice == 1) { // 使用栈作为辅助轨道
                        // 先检查辅轨道
                        if (!qb.IsEmpty()) {
                            qb.Top(d);
                            if ((d != No) && (qa.IsEmpty())) {
                                break;
                            }
                            else if (d == No) {
                                std::cout << "Carriage " << d << " from assist stack enters right track." << std::endl;
                                outst++; inqu++;
                                qc.EnQueue(d);
                                qb.Pop(d);
                                No++;
                            }
                        }
                        // 再检查主轨道
                        if (!qa.IsEmpty()) {
                            qa.GetHead(x);
                            if (No == x) {
                                std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                                outqu++; inqu++;
                                qc.EnQueue(x);
                                qa.DelQueue(x);
                                No++;
                            }
                            else if (No != x) {
                                while (No != x && !(qa.IsEmpty())) {
                                    std::cout << "Carriage " << x << " from left main track enters assist stack." << std::endl;
                                    d = x;
                                    qb.Push(d);
                                    qa.DelQueue(x);
                                    qa.GetHead(x);
                                    outqu++; inst++;
                                    if (qb.GetLength() > maxlen) maxlen = qb.GetLength();
                                }
                                if (No == x) {
                                    std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                                    outqu++; inqu++;
                                    qc.EnQueue(x);
                                    qa.DelQueue(x);
                                    No++;
                                    continue;
                                }
                            }
                        }
                    }
                    else if (secondaryChoice == 2) { // 使用队列作为辅助轨道
                        // 先检查辅轨道
                        if (!qd.IsEmpty()) { 
                            qd.GetHead(d);  
                            
                            if ((d != No) && (qa.IsEmpty())) {
                                break;
                            }
                            else if (d == No) {
                                std::cout << "Carriage " << d << " from assist queue enters right track." << std::endl;
                                outst++; inqu++; 
                                qc.EnQueue(d); 
                                qd.DelQueue(d);
                                No++;

                            }
                        }
                        // 再检查主轨道
                        if (!qa.IsEmpty()) {
                            qa.GetHead(x); 
                        
                            if (No == x) {
                                std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                                outqu++; inqu++;
                                qc.EnQueue(x); 
                                qa.DelQueue(x);
                                No++;  

                            }
                            // 如果队头元素不是当前需要调度的车厢
                            else if (No != x) {
                               
                                while (No != x && !(qa.IsEmpty())) {
                                    std::cout << "Carriage " << x << " from left main track enters assist queue." << std::endl;
                                    d = x;    
                                    qd.EnQueue(x);   
                                    qa.DelQueue(x); 
                                    qa.GetHead(x);  
                                    outqu++; inst++; 
                                    if (qd.GetLength() > maxlen) maxlen = qd.GetLength();


                                }
                                // 如果队头元素是当前需要调度的车厢
                                if (No == x) {
                                    std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                                    outqu++; inqu++; 
                                    qc.EnQueue(x);  
                                    qa.DelQueue(x);

                                    No++;      
                                    continue;   
                                }
                            }
                        }
                    }
                }

                // 显示调度结果
                if (qc.GetLength() == n) {
                    std::cout << "Scheduling completed." << std::endl;
                    std::cout << "Total number of push operations: " << inst << std::endl;
                    std::cout << "Total number of pop operations: " << outst << std::endl;
                    std::cout << "Total number of enqueue operations: " << outqu << std::endl;
                    std::cout << "Total number of dequeue operations: " << inqu << std::endl;
                    std::cout << "Maximum length of assist track: " << maxlen << std::endl;
                }
                else {
                    std::cout << "Scheduling cannot be completed." << std::endl;
                }
            }
            else if (choice == 2) {
                No = 1;
                int maxcarriage = 100;  // 将 maxcarriage 改为 100
                std::vector<int> nums(maxcarriage);

                // 生成 1 到 100 的车厢编号
                for (int k = 0; k < maxcarriage; k++) {
                    nums[k] = k + 1;
                }

                // 随机打乱车厢编号
                std::random_shuffle(nums.begin(), nums.end());

                // 将车厢编号依次入队到左侧主轨道 (qa)
                for (int j = 0; j < maxcarriage; j++) {
                    qa.EnQueue(nums[j]);
                }

                // 从 1 到 maxcarriage 进行调度操作
                for (int j = 1; j <= maxcarriage; j++) {
                    // 先检查辅轨道
                    if (!qb.IsEmpty()) {
                        qb.Top(d);
                        if ((d != No) && (qa.IsEmpty())) {
                            break;
                        }
                        else if (d == No) {
                            std::cout << "Carriage " << d << " from assist stack enters right track." << std::endl;
                            outst++; inqu++;
                            qc.EnQueue(d);
                            qb.Pop(d);
                            No++;
                        }
                    }
                    // 再检查主轨道
                    if (!qa.IsEmpty()) {
                        qa.GetHead(x);
                        if (No == x) {
                            std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                            outqu++; inqu++;
                            qc.EnQueue(x);
                            qa.DelQueue(x);
                            No++;
                        }
                        else if (No != x) {
                            while (No != x && !(qa.IsEmpty())) {
                                std::cout << "Carriage " << x << " from left main track enters assist stack." << std::endl;
                                d = x;
                                qb.Push(d);
                                qa.DelQueue(x);
                                qa.GetHead(x);
                                outqu++; inst++;
                                if (qb.GetLength() > maxlen) maxlen = qb.GetLength();
                            }
                            if (No == x) {
                                std::cout << "Carriage " << x << " from left main track enters right main track." << std::endl;
                                outqu++; inqu++;
                                qc.EnQueue(x);
                                qa.DelQueue(x);
                                No++;
                                continue;
                            }
                        }
                    }
                }

                // 显示调度结果
                if (qc.GetLength() == maxcarriage) {
                    std::cout << "Scheduling completed." << std::endl;
                    std::cout << "Total number of push operations: " << inst << std::endl;
                    std::cout << "Total number of pop operations: " << outst << std::endl;
                    std::cout << "Total number of enqueue operations: " << outqu << std::endl;
                    std::cout << "Total number of dequeue operations: " << inqu << std::endl;
                    std::cout << "Maximum length of assist stack: " << maxlen << std::endl;
                }
                else {
                    std::cout << "Scheduling cannot be completed." << std::endl;
                }
}


            // 显示当前轨道的状态
            std::string mainTrackStr = "Main Track:";
            qa.Traverse([&](int data) {
                mainTrackStr += std::to_string(data) + " ";
                });
            sf::Text mainTrack(mainTrackStr, font, 24);
            mainTrack.setPosition(100, 450);
            window.draw(mainTrack);

            std::string assistTrackStr = "Assist Track:";
            if (secondaryChoice == 1) {
                qb.Traverse([&](int data) {
                    assistTrackStr += std::to_string(data) + " ";
                    });
            }
            else if (secondaryChoice == 2) {
                qd.Traverse([&](int data) {
                    assistTrackStr += std::to_string(data) + " ";
                    });
            }
            sf::Text assistTrack(assistTrackStr, font, 24);
            assistTrack.setPosition(100, 500);
            window.draw(assistTrack);

            std::string rightTrackStr = "Right Track:";
            qc.Traverse([&](int data) {
                rightTrackStr += std::to_string(data) + " ";
                });
            sf::Text rightTrack(rightTrackStr, font, 24);
            rightTrack.setPosition(100, 550);
            window.draw(rightTrack);

            // 重置输入状态
            inputCarriages.clear();
            inputCompleted = false;
            showMenu = true;
            showSecondaryMenu = false; // 重置次级菜单显示标志
            qa.Clear();
            qc.Clear();
            qb.Clear();
            qd.Clear();
            inst = 0;
            outst = 0;
            outqu = 0;
            inqu = 0;
            maxlen = 0;

            // 暂停以显示结果
            sf::sleep(sf::seconds(2));
        }

        window.display();
    }

    return 0;
}
