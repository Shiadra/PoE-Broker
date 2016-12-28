#include "stdafx.h"

#include "sqlite3\sqlite3.h"

#include "Database.h"
#include "Settings.h"

#include <iostream>

Database::Database()
{
	int rc;
	const wchar_t *dataFile = settings::get(L"database");
	
	rc = sqlite3_open16(dataFile, &db);
	if (rc) {
		std::cout << "Can't open database" << std::endl;
		sqlite3_close(db);
	}
	else
	{
		std::cout << "Success" << std::endl;
	}
}