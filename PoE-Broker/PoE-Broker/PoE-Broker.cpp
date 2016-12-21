#include "stdafx.h"
#include "Resource.h"

#include "PoE-Broker.h"
#include "BrokerController.h"
#include "BrokerModel.h"
#include "BrokerView.h"

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
	BrokerModel model;
	BrokerController controller(&model);
	BrokerView view(&model, &controller);
	controller.setView(&view);
	return view.init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

bool InitConsole()
{
	if (!AllocConsole()) { return false; }
	if (freopen_s(&g_ic_file_cout_stream, "CONOUT$", "w", stdout) != 0) { return false; } // For std::cout 
	if (freopen_s(&g_ic_file_cin_stream, "CONIN$", "w+", stdin) != 0) { return false; } // For std::cin
	return true;
}
