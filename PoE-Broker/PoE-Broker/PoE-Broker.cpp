#include "stdafx.h"

#include "PoE-Broker.h"
#include "BrokerController.h"
#include "BrokerModel.h"
#include "BrokerView.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	BrokerModel model;
	BrokerController controller(&model);
	BrokerView view(&model, &controller);
	controller.setView(&view);
	return view.init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
