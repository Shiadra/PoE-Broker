#include "stdafx.h"

#include "Settings.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <ostream>
#include <Shlobj.h>
#include <Shlwapi.h>
#include <iostream>

using namespace rapidxml;

namespace settings
{
	namespace
	{
		xml_document<wchar_t> *doc;
		std::wstring filePath;
		std::wstring dataPath;
		PWSTR appPath;
		std::vector<wchar_t> *m_data;
	}

	void init()
	{
		if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, NULL, &appPath)))
		{
			PathAppend(appPath, L"PoE Broker");
			if (SHCreateDirectoryEx(NULL, appPath, NULL) != ERROR_SUCCESS)
			{
				std::cout << "Error at creating Folder" << std::endl;
			}
		}
		else
		{
			std::cout << "Error at retrieving Folder Path" << std::endl;
		}
		filePath = std::wstring(appPath) + L"\\settings.xml";
		doc = new xml_document<wchar_t>();
		std::wifstream loadFile(filePath, std::ios::binary);
		if (loadFile)
		{
			m_data = new std::vector<wchar_t>();
			loadFile.unsetf(std::ios::skipws);
			loadFile.seekg(0, std::ios::end);
			size_t size = loadFile.tellg();
			loadFile.seekg(0);

			m_data->resize(size + 1);
			loadFile.read(&m_data->front(), static_cast<std::streamsize>(size));
			(*m_data)[size] = 0;
			doc->parse<rapidxml::parse_declaration_node>(m_data->data());
			loadFile.close();
		}
		else
		{
			default();
		}	
	}

	void default()
	{
		xml_node<wchar_t>* decl = doc->allocate_node(node_declaration);
		decl->append_attribute(doc->allocate_attribute(L"version", L"1.0"));
		decl->append_attribute(doc->allocate_attribute(L"encoding", L"UTF-16"));
		doc->append_node(decl);
		xml_node<wchar_t> *node = doc->allocate_node(node_element, L"settings");
		node->append_attribute(doc->allocate_attribute(L"river", L"0"));
		dataPath = std::wstring(appPath) + L"\\database.sqlite3";
		node->append_attribute(doc->allocate_attribute(L"database", dataPath.c_str()));
		doc->append_node(node);
	}

	void save()
	{
		std::wofstream saveFile;
		saveFile.open(filePath);
		saveFile << *doc;
		saveFile.close();
	}

	void remove()
	{
		delete doc;
		delete m_data;
	}

	const wchar_t* get(const wchar_t* key)
	{
		return doc->first_node(L"settings")->first_attribute(key)->value();
	}

	const char* get8(const wchar_t* key)
	{
		const wchar_t * val = get(key);
		size_t inputSize = wcslen(val);
		size_t outputSize = inputSize+1;
		char *outputString = new char[outputSize];
		size_t charsConverted = 0;
		wcstombs_s(&charsConverted, outputString, outputSize, val, inputSize);
		return outputString;
	}

	void set(const wchar_t* key, const wchar_t* value)
	{
		wchar_t* value_alloc = doc->allocate_string(value);
		doc->first_node(L"settings")->first_attribute(key)->value(value_alloc);
	}
}