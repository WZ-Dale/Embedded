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
void DirectoryList(const string& path, vector<string>& dirs, vector<string>& files) {
	_finddata_t file;	//	�ļ���Ϣ�ṹ��
	const string path_ = path + "\\*.*";	// ��Ŀ¼�µ������ļ�
	intptr_t handle = _findfirst(path_.c_str(), &file);
	if (handle == -1) {
		cout << "_findfirst:" << path << "error" << endl;
		return;
	}
	do {
		if (file.attrib & _A_SUBDIR) {		// �����ǰ�ļ���һ��Ŀ¼
			if ((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0)) {
				string subpath = path + "\\" + file.name;
				dirs.push_back(file.name);
			}
		}
		else {		// ��ǰ�ļ���һ�����ļ�
			files.push_back(file.name);
		}
	} while (_findnext(handle, &file) == 0);	//	���ֵ�
}
