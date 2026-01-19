#include <iostream>
#include <Windows.h>
#include "project.h"

DWORD WINAPI CrosshairThread(LPVOID lpParam) 
{
	HINSTANCE hInstance = GetModuleHandle(NULL); 
	WinMain(hInstance, NULL, NULL, SW_SHOW);
	return 0; 
}

void printUI();

int main()
{
	printLog(level_INFO, "User-initiated program.");

	printLog(level_INFO, "欢迎使用本程序，祝您使用愉快。");

	printUI();
	
	system("pause");
	return 0;
}

void printUI()
{
	while(true)
	{
		printLog(level_INFO, "Display the main menu.");
		int numCin = 0;

		clearScreen();
		printLogs();
	
		std::cout << star3 << "准星助手" << star3 << std::endl;
		std::cout << star5 << "0.退出程序" << star5 << std::endl;
		std::cout << star5 << "1.让鼠标回到屏幕中心" << star5 << std::endl;
		std::cout << star5 << "2.绘制中心准星(test)" << star5 << std::endl;
		std::cout << star5 << "3.控制台打印日志功能" << star5 << std::endl;

		std::cin >> numCin;

		//检测输入是否正确
		if (std::cin.fail())	
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			printLog(level_WARNING, "请输入整数！");
			continue;
		}
		/*
			cin.fail 是一个输入流对象，负责从控制台读取数据,用 cin >> num; 时，C++会尝试把输入类型转为 int。
			这时候输入的内容不能转换(比如输错了字母)，cin就会进入错误状态，这时 cin.fail() 会返回 true ，表示上一次输入操作失败了。

			C++ 的流对象有几个常见的状态函数：
	
			cin.good() → 一切正常，没有错误。

			cin.fail() → 最近一次输入失败（比如类型不匹配）。

			cin.eof() → 到达输入结束（End Of File）。

			cin.bad() → 出现严重错误（比如硬件问题）。
		*/

		switch (numCin)
		{
		case 0:
			printLog(level_INFO, "用户退出程序");
			return;
		case 1:
			CenterMouse();
			break;

		case 2:
			CreateThread(NULL, 0, CrosshairThread, NULL, 0, NULL);
		
			break;

		case 3:
			showMenu();
			break;

		default:
			std::cout << ">>>" << "请输入正确的数字选项" << std::endl;
			system("pause");
			break;
		}
	}

}