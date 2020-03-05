// ����ģ��
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <set>

#include <io.h>
#include "sqlite-amalgamation-3280000/sqlite3.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::set;

// Ŀ¼�о�
static void DirectoryList(const string& path, vector<string>& dirs, vector<string>& files) {
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

////////////////////////��־ģ�飨win��Linux�������ܵģ�/////////////////////////
////////////////////////  ���ڼ�¼���󣬴�ӡ������Ϣ��  /////////////////////////
static std::string GetFileName(const std::string& path)
{
	char ch = '/';
#ifdef _WIN32
	ch = '\\';
#endif
	size_t pos = path.rfind(ch);
	if (pos == std::string::npos)
		return path;
	else
		return path.substr(pos + 1);
}
//���ڵ���׷�ݵ�trace log
inline static void __TraceDebug(const char* filename, int line, const char* function, const
	char* format, ...)
{
#ifdef __TRACE__
	//������ú�������Ϣ
	fprintf(stdout, "[TRACE][%s:%d:%s]:", GetFileName(filename).c_str(), line, function);
	//����û����trace��Ϣ
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
	fprintf(stdout, "\n");
#endif
}

inline static void __ErrorDebug(const char* filename, int line, const char* function, const
	char* format, ...)
{
#ifdef __DEBUG__
	//������ú�������Ϣ
	fprintf(stdout, "[ERROR][%s:%d:%s]:", GetFileName(filename).c_str(), line, function);
	//����û����trace��Ϣ
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
	fprintf(stdout, " errmsg:%s, errno:%d\n", strerror(errno), errno);
#endif
}

// ��¼�ճ�׷����Ϣ���������ʾ�ɱ����
#define TRACE_LOG(...) \
 __TraceDebug(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);
// ��¼�ճ�������Ϣ
#define ERROE_LOG(...) \
 __ErrorDebug(__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__);
