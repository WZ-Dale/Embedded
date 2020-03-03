// ����ģ��
#pragma once
#include <iostream>
#include <string>
#include <vector>

#include <io.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Ŀ¼�о�
void DirectoryList(const string& path, vector<string>& docs) {
	_finddata_t file;	//	�ļ���Ϣ�ṹ��
	const string path_ = path + "\\*.*";	// ��Ŀ¼�µ������ļ�
	intptr_t handle = _findfirst(path_.c_str(), &file);
	if (handle == -1) {
		cout << "_findfirst:" << path << "error" << endl;
		return;
	}
	do {
		docs.push_back(file.name);
	} while (_findnext(handle, &file) == 0);	//	���ֵ�
}
