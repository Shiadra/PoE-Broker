#pragma once

#include "sqlite3\sqlite3.h"

class Database
{
public:
	Database();
private:
	sqlite3 *db;
};