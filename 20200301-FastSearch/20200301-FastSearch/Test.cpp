#include "Common.h"
#include "DataManager.h"

void TestDirectoryList() {
	vector<string> dirs, files;
	DirectoryList("E:\\Projects\\20200301-FastSearch", dirs, files);
	for (const auto& e : dirs) {
		cout << e << endl;
	}
	for (const auto& e : files) {
		cout << e << endl;
	}
}

void TestSqlite() {
	// �����ݿ�
	SqliteManager sq;
	sq.Open("E:\\Projects\\20200301-FastSearch\\20200301-FastSearch\\test.db");

	// ������
	//string exists_sql = "select count(*)  from sqlite_master where type='table' and name = 'tb_doc'"
	string createtb_sql = "create table tb_doc(id integer primary key autoincrement, doc_path text, doc_name int)";
	sq.ExecuteSql(createtb_sql);
	
	// ��������
	string insert_sql = "insert into tb_doc values(NULL, '·��', 'name')";
	sq.ExecuteSql(insert_sql);
	insert_sql = "insert into tb_doc values(NULL, '22', 'qq')";
	sq.ExecuteSql(insert_sql);
	insert_sql = "insert into tb_doc values(NULL, '33', 'ww')";
	sq.ExecuteSql(insert_sql);
	insert_sql = "insert into tb_doc values(NULL, '44', 'ee')";
	sq.ExecuteSql(insert_sql);

	// ��������
	string query_sql = "select * from tb_doc where doc_path = '33'";
	int row, col;
	char** ppRet;
	sq.GetTable(query_sql, row, col, ppRet);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			cout << ppRet[i * col + j] << "\t";		// ���ڸ����ݿ�����ڴ��а�һά�����ŵ�
		}
		cout << endl;
	}
}

int main() {
	//TestDirectoryList();
	TestSqlite();
	return 0;
}