#include "hello.h"

#include<iostream>
#include<string>
#include<stdexcept>

void runTests();

class Executor
{
    private:
       int x, y; // 车的位置
       char heading; // 车的朝向

       // 改变顺序为 东 西 南 北
       const int move_x[4] = {0, -1, 0, 1};
       const int move_y[4] = {1, 0, -1, 0};
       const char directions[4] = {'N', 'W', 'S', 'E'};

    public:
       Executor(int x = 0, int y = 0, char heading = 'N') : x(x), y(y), heading(heading)
       {
            if(heading != 'E' && heading != 'W' && heading != 'S' && heading != 'N')
            {
                throw std::invalid_argument("Invalid heading direction");
            }
       }

       void executeCommand(char command)
       {
            switch(command)
            {
                case 'M':
                    move();
                    break;
                case 'L':
                    turnLeft();
                    break;
                case 'R':
                    turnRight();
                    break;
                default:
                    std::cerr << "Unknown command!" << std::endl;
                    break;
            }
       }

       void executeCommands(const std::string& commands)
       {
           for (char command : commands)
           {
                executeCommand(command);
           }
       }

       void getPositionAndHeading(int& x_out, int& y_out, char& heading_out) const
       {
            x_out = x;
            y_out = y;
            heading_out = heading;
       }

    private:
        void move()
        {
            if (heading == 'N')
            {
                y += 1;
            }
            else if (heading == 'S')
            {
                y -= 1;
            }
            else if (heading == 'E')
            {
                x += 1;
            }
            else if (heading == 'W')
            {
                x -= 1;
            }
        }

        void turnLeft()
        {
            for (int i = 0; i < 4; i++)
            {
                if (heading == directions[i])
                {
                    heading = directions[(i + 3) % 4];
                    break;
                }
            }
        }

        void turnRight()
        {
            for (int i = 0; i < 4; i++)
            {
                if (heading == directions[i])
                {
                    heading = directions[(i + 1) % 4];
                    break;
                }
            }
        }
};

void runTests()
{
    Executor executor;

    int x, y;
    char heading;
    executor.getPositionAndHeading(x, y, heading);
    std::cout << "Initial Position: (" << x << "," << y << "), heading: " << heading << std::endl;

    // 测试前进指令
    executor.executeCommand('M');
    executor.getPositionAndHeading(x, y, heading);
    std::cout << "After 'M' Command: (" << x << "," << y << "), heading: " << heading << std::endl;

    // 测试左转指令
    executor.executeCommand('L');
    executor.getPositionAndHeading(x, y, heading);
    std::cout << "After 'L' Command: (" << x << "," << y << "), heading: " << heading << std::endl;

    // 测试右转指令
    executor.executeCommand('R');
    executor.getPositionAndHeading(x, y, heading);
    std::cout << "After 'R' Command: (" << x << "," << y << "), heading: " << heading << std::endl;

    // 批量测试指令
    executor.executeCommands("MLMR");
    executor.getPositionAndHeading(x, y, heading);
    std::cout << "After 'MLMR' Commands: (" << x << ", " << y << "), Heading: " << heading << std::endl;
}


int test()
{
    runTests();
    return 0;
}
