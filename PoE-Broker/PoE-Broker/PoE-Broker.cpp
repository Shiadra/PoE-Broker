#include "stdafx.h"
#include "Resource.h"

#include "PoE-Broker.h"
#include "BrokerController.h"
#include "BrokerModel.h"
#include "BrokerView.h"
#include "Settings.h"

#include <stdio.h>

FILE *g_ic_file_cout_stream; FILE *g_ic_file_cin_stream;

bool InitConsole();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	//Console for Debugging purposes
	InitConsole();
	settings::init();
	BrokerModel *model = new BrokerModel();
	BrokerController *controller = new BrokerController(model);
	BrokerView *view = new BrokerView(model, controller);
	controller->setView(view);
	int exit =  view->init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	delete view;
	delete controller;
	delete model;
	settings::save();
	settings::remove();
	return exit;
}

bool InitConsole()
{
	if (!AllocConsole()) { return false; }
	if (freopen_s(&g_ic_file_cout_stream, "CONOUT$", "w", stdout) != 0) { return false; } // For std::cout 
	if (freopen_s(&g_ic_file_cin_stream, "CONIN$", "w+", stdin) != 0) { return false; } // For std::cin
	return true;
}
