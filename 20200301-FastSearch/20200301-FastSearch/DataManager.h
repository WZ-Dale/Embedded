#pragma once

#include "Common.h"

// SqliteManager�Ƕ�Sqlite�Ľӿڽ���һ��򵥵ķ�װ��
class SqliteManager
{
public:
	SqliteManager()
		:_db(nullptr)
	{}
	~SqliteManager()
	{
		Close();
	}
	void Open(const string& path);
	void Close();
	void ExecuteSql(const string& sql);
	void GetTable(const string& sql, int& row, int& col, char**& ppRet);

	SqliteManager(const SqliteManager&) = delete;
	SqliteManager& operator=(const SqliteManager&) = delete;
private:
	sqlite3* _db;	// ���ݿ����
};
// RAII
class AutoGetTable
{
public:
	AutoGetTable(SqliteManager& sm, const string& sql, int& row, int& col, char**& ppRet) {
		sm.GetTable(sql, row, col, ppRet);
		_ppRet = ppRet;
	}
	~AutoGetTable() {
		sqlite3_free_table(_ppRet);
	}
	AutoGetTable(const AutoGetTable&) = delete;
	AutoGetTable& operator=(const AutoGetTable&) = delete;
private:
	char** _ppRet;
};

//////////////////////////////////////////////////////////
// ���ݹ���ģ��
#define DB_NAME "doc.db"
#define TB_NAME "tb_doc"

class DataManager
{
public:
	void Init();	// ���������ݿ�
	void GetDoc(const string& path, set<string>& dbset);	// ����path�µ��������ĵ�
	void InsertDoc(const string& path, const string& name);
	void DeleteDoc(const string& path, const string& name);
private:
	SqliteManager _dbmgr;
};
