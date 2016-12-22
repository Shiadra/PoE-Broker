#include "stdafx.h"
#include "BrokerModel.h"

#include<Shlobj.h>

#include "DataManager.h"

BrokerModel::BrokerModel(void)
{
	PWSTR wszPath;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, NULL, &wszPath)))
	{
		printf("SHGetKnownFolderPath FOLDERID_Documents = %S\n", wszPath);
	}
	DataManager *manager = new DataManager();
}