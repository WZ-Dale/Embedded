// ����ģ��
#include "DataManager.h"

void SqliteManager::Open(const string& path) {
	int ret = sqlite3_open(path.c_str(), &_db);
	if (ret == SQLITE_OK) {		// ����� �ɹ�
		TRACE_LOG("sqlite3_open success\n");
	}
	else {						// ����� ʧ��
		ERROE_LOG("sqlite3_open\n");
	}
}
void SqliteManager::Close() {
	int ret = sqlite3_close(_db);
	if (ret == SQLITE_OK) {		// ����ر� �ɹ�
		TRACE_LOG("sqlite3_close success\n");
	}
	else {						// ����ر� ʧ��
		ERROE_LOG("sqlite3_close\n");
	}
}
void SqliteManager::ExecuteSql(const string& sql) {
	char* errmsg;		// �洢������Ϣ
	int ret = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errmsg);
	if (ret == SQLITE_OK) {		// ���ִ�����ݿ���� �ɹ�
		TRACE_LOG("sqlite3_exec(%s) success\n", sql.c_str());
	}
	else {						// ���ִ�����ݿ���� ʧ��
		ERROE_LOG("sqlite3_exec(%s) errmsg:%s\n", sql.c_str(), errmsg);
	}
}
void SqliteManager::GetTable(const string& sql, int& row, int& col, char**& ppRet) {
	char* errmsg;
	int ret = sqlite3_get_table(_db, sql.c_str(), &ppRet, &row, &col, &errmsg);
	if (ret == SQLITE_OK) {		// ���ִ�����ݿ���� �ɹ�
		TRACE_LOG("sqlite3_get_table(%s) success\n", sql.c_str());
	}
	else {						// ���ִ�����ݿ���� ʧ��
		ERROE_LOG("sqlite3_get_table(%s) errmsg:%s\n", sql.c_str(), errmsg);
	}
}

