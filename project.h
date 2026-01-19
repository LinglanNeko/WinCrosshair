#pragma once
#include "project.h"
#include <Windows.h>
#include <string>
#define VERSION "0.1"

//menu
const std::string star3 = " === ";
const std::string star5 = " ===== ";

//log.cpp
const std::string level_INFO = "INFO";
const std::string level_WARNING = "WARNING";


//函数声明
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain1(HINSTANCE hInstance, HINSTANCE, LPSTR, int); int WINAPI WinMain1(HINSTANCE hInstance, HINSTANCE, LPSTR, int);
void CenterMouse();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void printLogs();
void showMenu();
void DrawCrosshair();
void clearScreen();
void printLog(const std::string& level, const std::string& message);
