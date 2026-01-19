#include <iostream>
#include <vector>
#include "project.h"



//日志打印功能
bool flag = true;

//日志容器
std::vector<std::string> logs;

std::string getTimeStr()	//获取时间函数
{
	time_t now = time(0);	
	
	/*
		time(0) 返回当前时间的时间戳 (从1970年1月1日到现在的秒数)
		time_t 是 C/C++ 标准库里定义的一种时间类型 用来表示“从 1970 年 1 月 1 日 00:00:00 UTC 到现在所经过的秒数”
	*/

	tm localtm;
	localtime_s(&localtm, &now);

	/*
		把时间戳转换本地时间
		tm 是一个结构体，里面有 tm_year,tm_mon,tm_mday,tm_hour 等字段。
	*/

	char buf[80];	//数组 用于存放格式化后的时间字符串
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &localtm);	//把 tm 结构体里的时间信息格式化成字符串

	return std::string(buf);	//返回时间字符串
}

void printLog(const std::string& level, const std::string& message)
{
	if (flag)
	{ 
		std::string logEntry = "[" + getTimeStr() + "]" + "[" + level + "]" + message;

		logs.push_back(logEntry);

		/*
			logs:
				这就是一个 std::vector<std::string> 类型的容器
				它就像一个动态数组，用来存放多条日志字符串

			push_back(...):
				这是 std::vector 的成员函数
				作用:把括号里的元素追加到容器的末尾
		*/

		std::cout << logEntry << std::endl;
	}
}

void printLogs()
{
	if (flag)
	{
		std::cout << "\n--- 日志 ---\n";

		for (const auto& log : logs)
		{
			std::cout << log << '\n';
		}

		std::cout << "\n\n\n";

		/*
			const auto& log
			auto:编译器自动推到类型，这里就是 std::string
			&:引用，避免拷贝，提高效率，直接引用容器里的元素
			const:只读，保证循环体里不会修改日志内容
		*/
	}

}

void showMenu()
{
	printLog(level_INFO, "Display Log Menu.");
	while (true)
	{
		clearScreen();
		printLogs();

		std::cout << star3 << "准星助手" << star3 << std::endl;
		std::cout << star5 << "0.退出页面" << star5 << std::endl;
		std::cout << star5 << "1.开启日志功能" << star5 << std::endl;
		std::cout << star5 << "2.关闭日志功能" << star5 << std::endl;



		int numCin = 0;

		std::cin >> numCin;

		//检测输入是否正确
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			printLog(level_WARNING, "请输入整数！");
			continue;
		}

		switch (numCin)
		{
		case 0:
			return;
		case 1:
			flag = true;
			printLog(level_INFO,"日志功能已开启");
			return;
		case 2:
			flag = false;
			printLog(level_INFO, "日志功能已关闭");
			return;
		default:
			std::cout << ">>>" << "请输入正确的数字选项" << std::endl;
			system("pause");
			break;
		}
	}

}

//清屏函数
void clearScreen()
{
	system("cls");
}

