#include "stdafx.h"

#include "Settings.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include <ostream>
#include <Shlobj.h>
#include <iostream>

using namespace rapidxml;

namespace settings
{
	namespace
	{
		xml_document<wchar_t> *doc;
		std::wstring filePath;
		std::vector<wchar_t> *m_data;
	}

	void init()
	{
		PWSTR appPath;
		SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, NULL, &appPath);
		filePath = std::wstring(appPath) + L"\\PoEBroker-settings.xml";
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
			std::wcout << m_data->data() << std::endl;
			doc->parse<rapidxml::parse_declaration_node>(m_data->data());
			std::wcout << *doc << std::endl;
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

	void set(const wchar_t* key, const wchar_t* value)
	{
		wchar_t* value_alloc = doc->allocate_string(value);
		doc->first_node(L"settings")->first_attribute(key)->value(value_alloc);
	}
}