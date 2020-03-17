#pragma once

#include "Common.h"

//////////////////////////////////////////////////////////
// SqliteManager �Ƕ� Sqlite�Ľӿ� ����һ��򵥵ķ�װ
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
	void Open(const string& path);		// �����ݿ�
	void Close();						// �ر����ݿ�
	void ExecuteSql(const string& sql);		// ִ�����ݿ����
	void GetTable(const string& sql, int& row, int& col, char**& ppRet);	// ��ȡ���ݿ����б���Ϣ

	SqliteManager(const SqliteManager&) = delete;		// ���ο�������͸�ֵ����
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
//Ϊ�˷������,��Ƴɵ���ģʽ
//һ��ʹ�ö���ģʽ,���ÿ����̰߳�ȫ����Ŷ
class DataManager
{
public:
	static DataManager* GetInstance() {
		static DataManager datamgr;
		datamgr.Init();
		return &datamgr;
	}

	void Init();	// ���ݿ��ʼ���������ݿ⣬����
	void GetDoc(const string& path, set<string>& dbset);	// ����path�µ��������ĵ����ŵ�set�����ڱȶ�
	void InsertDoc(const string& path, const string& name);		// ���뵽���ݿ�
	void DeleteDoc(const string& path, const string& name);		// ɾ�����ݿ�������
	void Search(const string& key, vector<std::pair<string, string>>& docinfos);	// ��������
	void SplitHighLight(const string& key, const string& name, string& prefix, string& highlight, string& suffix);	// ����Ҫ�����ķָ����
private:
	DataManager() {}
	SqliteManager _dbmgr;
};
