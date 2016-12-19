#pragma once

#include "BrokerModel.h"

class BrokerController;

class BrokerView
{
public:
	BrokerView(BrokerModel *model, BrokerController *controller);
	int init(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	BrokerModel *model;
	BrokerController *controller;
};