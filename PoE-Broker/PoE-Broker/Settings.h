#pragma once


namespace settings
{
	void init();
	void default();
	void save();
	void remove();
	const wchar_t* get(const wchar_t* key);
	const char* get8(const wchar_t* key);
	void set(const wchar_t* key, const wchar_t* value);
}