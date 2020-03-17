// ����ģ��
#include "DataManager.h"

// DDL ���ݶ������ԣ�����ά���洢���ݵĽṹ����ָ�create��drop��alter
// DML ���ݲ������ԣ����������ݽ��в�������ָ�insert��delete��update
//     DML���ֵ�������һ��DQL�����ݲ�ѯ���ԣ�����ָ�select
// DCL ���ݿ������ԣ���Ҫ����Ȩ�޹�����������ָ�grant��revoke��commit

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
	assert(_db);
	char* errmsg;		// �洢������Ϣ
	int ret = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errmsg);
	if (ret == SQLITE_OK) {		// ���ִ�����ݿ���� �ɹ�
		TRACE_LOG("sqlite3_exec(%s) success\n", sql.c_str());
	}
	else {						// ���ִ�����ݿ���� ʧ��
		ERROE_LOG("sqlite3_exec(%s) errmsg:%s\n", sql.c_str(), errmsg);
		sqlite3_free(errmsg);
	}
}
void SqliteManager::GetTable(const string& sql, int& row, int& col, char**& ppRet) {
	assert(_db);
	char* errmsg;		// �洢������Ϣ
	int ret = sqlite3_get_table(_db, sql.c_str(), &ppRet, &row, &col, &errmsg);
	if (ret == SQLITE_OK) {		// ���ִ�����ݿ���� �ɹ�
		TRACE_LOG("sqlite3_get_table(%s) success\n", sql.c_str());
	}
	else {						// ���ִ�����ݿ���� ʧ��
		ERROE_LOG("sqlite3_get_table(%s) errmsg:%s\n", sql.c_str(), errmsg);
		sqlite3_free(errmsg);
	}
}
////////////////////////////////////////////////////////
void DataManager::Init() {
	_dbmgr.Open(DB_NAME);
	char createtb_sql[256];
	sprintf(createtb_sql, "create table if not exists %s (id integer primary key, path text, name text, name_pinyin text, name_initials text)", TB_NAME);	// �����ؽ���
	_dbmgr.ExecuteSql(createtb_sql);
}
void DataManager::GetDoc(const string& path, set<string>& dbset) {
	char query_sql[256];
	sprintf(query_sql, "select name from %s where path = '%s'", TB_NAME, path.c_str());
	int row, col;
	char** ppRet;
	AutoGetTable agt(_dbmgr, query_sql, row, col, ppRet);
	for (int i = 1; i <= row; ++i) {
		for (int j = 0; j < col; ++j) {
			dbset.insert(ppRet[i * col + j]);
		}
	}
}
void DataManager::InsertDoc(const string& path, const string& name) {
	char insert_sql[256];
	string pinyin = ChineseConvertPinYinAllSpell(name);
	string initials = ChineseConvertPinYinInitials(name);
	sprintf(insert_sql, "insert into %s (path, name, name_pinyin, name_initials) values('%s', '%s', '%s', '%s')", TB_NAME, path.c_str(), name.c_str(), pinyin.c_str(), initials.c_str());
	_dbmgr.ExecuteSql(insert_sql);
}
void DataManager::DeleteDoc(const string& path, const string& name) {
	char delete_sql[256];
	sprintf(delete_sql, "delete from %s where path = '%s' and name = '%s'", TB_NAME, path.c_str(), name.c_str());
	_dbmgr.ExecuteSql(delete_sql);
	// ע�⣺�˴����ļ�ϵͳ��ɾ����Ŀ¼�����¼��ļ������ݿ���Ҳ��Ҫ���¼��ļ�ɾ��
	string path_ = path;
	path_ += '\\';
	path_ += name;
	sprintf(delete_sql, "delete from %s where path like '%s%%'", TB_NAME, path_.c_str());
	_dbmgr.ExecuteSql(delete_sql);
}
void DataManager::Search(const string& key, vector<std::pair<string, string>>& docinfos) {
	/*
	char search_sql[256];
	sprintf(search_sql, "select name, path from %s where name like '%%%s%%'", TB_NAME, key.c_str());
	int row, col;
	char** ppRet;
	AutoGetTable agt(_dbmgr, search_sql, row, col, ppRet);
	for (int i = 1; i <= row; ++i) {
		docinfos.push_back(std::make_pair(ppRet[i * col], ppRet[i * col + 1]));
	}
	*/
	char search_sql[256];
	string key_pinyin = ChineseConvertPinYinAllSpell(key);
	string key_initials = ChineseConvertPinYinInitials(key);
	sprintf(search_sql, "select name, path from %s where name_pinyin like '%%%s%%' or name_initials like '%%%s%%'", TB_NAME, key_pinyin.c_str(), key_initials.c_str());
	int row, col;
	char** ppRet;
	AutoGetTable agt(_dbmgr, search_sql, row, col, ppRet);
	for (int i = 1; i <= row; ++i) {
		docinfos.push_back(std::make_pair(ppRet[i * col], ppRet[i * col + 1]));
	}
}
void DataManager::SplitHighLight(const string& key, const string& name, string& prefix, string& highlight, string& suffix) {
	//1.key�Ǻ���->������Ӧ����
	{
		size_t pos = name.find(key);
		if (pos != string::npos) {
			prefix = name.substr(0, pos);
			highlight = key;
			suffix = name.substr(pos + key.size(), string::npos);

			return;
		}
	}
	//2.key��ƴ��->������Ӧ���֣��������Ӣ�Ļ�����⣩
	//{
	//	string key_pinyin = ChineseConvertPinYinAllSpell(key);
	//	string name_pinyin = ChineseConvertPinYinAllSpell(name);
	//	size_t pos = name_pinyin.find(key_pinyin);
	//	if (pos != string::npos) {
	//		size_t name_i = 0, name_j = 0, py_i = 0;
	//		while (py_i < pos) {
	//			if (name[name_i] >= 0 && name[name_i] <= 127) {	//�����ASCII�ַ�
	//				++name_i;
	//				++py_i;
	//			}
	//			else {
	//				char chinese[3] = { 0 };
	//				chinese[0] = name[name_i];
	//				chinese[1] = name[name_i + 1];
	//				string ch_pinyin = ChineseConvertPinYinAllSpell(chinese);
	//				py_i += ch_pinyin.size();
	//				name_i += 2;
	//			}
	//		}
	//		prefix = name.substr(0, name_i);		// ��һ��
	//		name_j = name_i;
	//		while (py_i < pos + key_pinyin.size()) {
	//			if (name[name_j] >= 0 && name[name_j] <= 127) {	//�����ASCII�ַ�
	//				++name_j;
	//				++py_i;
	//			}
	//			else {
	//				char chinese[3] = { 0 };
	//				chinese[0] = name[name_j];
	//				chinese[1] = name[name_j + 1];
	//				string ch_pinyin = ChineseConvertPinYinAllSpell(chinese);
	//				py_i += ch_pinyin.size();
	//				name_j += 2;
	//			}
	//		}
	//		highlight = name.substr(name_i, name_j - name_i);		// ƥ���
	//		suffix = name.substr(name_j, string::npos);		// ������
	
	//		return;
	//	}
	//}
	// ��������while���߼��󲿷����ƣ����Ժϲ�����while
	{
		string key_ap = ChineseConvertPinYinAllSpell(key);	//keyתƴ��
		string name_ap = ChineseConvertPinYinAllSpell(name);	//ԭ��תƴ��
		size_t ap_start = name_ap.find(key_ap);	//�ҵ�ƴ��ƥ��λ��
		size_t ap_end = ap_start + key_ap.size();
		size_t ap_index = 0;	//ԭ��ת��ƴ���е�ָ�루������ָ�룬ֻ��Ϊ�˷����ʾ���ѣ�
		size_t ht_index = 0;	//ԭ�������е�ָ��
		size_t ht_start = 0, ht_len = 0;		//��������
		if (ap_start != string::npos) {
			while (ap_index < ap_end) {
				if (ap_index == ap_start) {		// ��ƴ��ƥ��ʱ��ԭ��ƥ�䣬���ҵ��˸����Ŀ�ʼ
					ht_start = ht_index;
				}
				if (name[ht_index] >= 0 && name[ht_index] <= 127) {	//�����ASCII�ַ�
					++ht_index;
					++ap_index;
				}
				else {
					char chinese[3] = { '\0' };
					chinese[0] = name[ht_index];
					chinese[1] = name[ht_index + 1];
					string py_str = ChineseConvertPinYinAllSpell(chinese);
					ap_index += py_str.size();	//�����ú���ƴ���ĳ���
					ht_index += 2;	//gbk���������ַ�
				}
			}
			ht_len = ht_index - ht_start;

			prefix = name.substr(0, ht_start);
			highlight = name.substr(ht_start, ht_len);
			suffix = name.substr(ht_start + ht_len, string::npos);

			return;
		}
	}
	//3.key��ƴ������ĸ->������Ӧ���֣��������Ӣ�Ļ�����⣩
	//{
	//	string key_py_initials = ChineseConvertPinYinInitials(key);
	//	string name_py_initials = ChineseConvertPinYinInitials(name);
	//	size_t pos = name_py_initials.find(key_py_initials);
	//	if (pos != string::npos) {
	//		size_t name_i = 0, name_j = 0, py_i = 0;
	//		while (py_i < pos) {
	//			if (name[name_i] >= 0 && name[name_i] <= 127) {	//�����ASCII�ַ�
	//				++name_i;
	//				++py_i;
	//			}
	//			else {
	//				char chinese[3] = { 0 };
	//				chinese[0] = name[name_i];
	//				chinese[1] = name[name_i + 1];
	//				string ch_py_initials = ChineseConvertPinYinInitials(chinese);
	//				py_i += ch_py_initials.size();
	//				name_i += 2;
	//			}
	//		}
	//		prefix = name.substr(0, name_i);		// ��һ��
	//		name_j = name_i;
	//		while (py_i < pos + key_py_initials.size()) {
	//			if (name[name_i] >= 0 && name[name_i] <= 127) {	//�����ASCII�ַ�
	//				++name_i;
	//				++py_i;
	//			}
	//			else {
	//				char chinese[3] = { 0 };
	//				chinese[0] = name[name_j];
	//				chinese[1] = name[name_j + 1];
	//				string ch_py_initials = ChineseConvertPinYinInitials(chinese);
	//				py_i += ch_py_initials.size();
	//				name_j += 2;
	//			}
	//		}
	//		highlight = name.substr(name_i, name_j - name_i);		// ƥ���
	//		suffix = name.substr(name_j, string::npos);		// ������

	//		return;
	//	}
	//}
	{
		string key_it = ChineseConvertPinYinInitials(key);	//keyת����ĸ
		string name_it = ChineseConvertPinYinInitials(name);	//ԭ��ת����ĸ
		size_t it_start = name_it.find(key_it);
		size_t it_end = it_start + key_it.size();
		size_t it_index = 0;	//ԭ��ת������ĸ�е�ָ�루������ָ�룬ֻ��Ϊ�˷����ʾ���ѣ�
		size_t ht_index = 0;	//ԭ�������е�ָ��
		size_t ht_start = 0, ht_len = 0;		//��������
		if (it_start != string::npos) {
			while (it_index < it_end) {
				if (it_index == it_start) {
					ht_start = ht_index;
				}
				if (name[ht_index] >= 0 && name[ht_index] <= 127) {	//�����ASCII�ַ�
					++ht_index;
					++it_index;
				}
				else {
					++it_index;	//�����ú�������ĸ
					ht_index += 2;	//gbk���������ַ�
				}
			}
			ht_len = ht_index - ht_start;

			prefix = name.substr(0, ht_start);
			highlight = name.substr(ht_start, ht_len);
			suffix = name.substr(ht_start + ht_len, string::npos);

			return;
		}
	}
	// �������û��ƥ�䵽����ԭ������һ�Σ��м�κ͵�����Ϊ�վͺ�
	TRACE_LOG("Split highlight no match. name: %s, key: %s\n", name.c_str(), key.c_str());
	prefix = name;
}
