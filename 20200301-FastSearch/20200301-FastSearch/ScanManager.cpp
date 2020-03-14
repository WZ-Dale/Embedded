// ɨ��ģ��
#include "ScanManager.h"

void ScanManager::Scan(const string& path) {
	// �ȶ�  �����ļ� �� ���ݿ�
	vector<string> localdirs;
	vector<string> localfiles;
	DirectoryList(path, localdirs, localfiles);

	// �ڼ����������
	set<string> localset;
	localset.insert(localdirs.begin(), localdirs.end());
	localset.insert(localfiles.begin(), localfiles.end());

	set<string> dbset;
	_datamgr.GetDoc(path, dbset);

	// ��ʼ�ȶ�
	auto localit = localset.begin();
	auto dbit = dbset.begin();
	while (localit != localset.end() && dbit != dbset.end()) {
		if (*localit < *dbit) {		// �����У����ݿ�û�У����ݿ�����
			_datamgr.InsertDoc(path, *localit);
			++localit;
		}
		else if (*localit > *dbit) {		// ����û�У����ݿ��У����ݿ�ɾ��
			_datamgr.DeleteDoc(path, *dbit);
			++dbit;
		}
		else {		// ���غ����ݿ�һ�£����ݲ���
			++localit;
			++dbit;
		}
	}
	while (localit != localset.end()) {
		_datamgr.InsertDoc(path, *localit);	// ���ݿ�����
		++localit;
	}
	while (dbit != dbset.end()) {
		_datamgr.DeleteDoc(path, *dbit);	// ���ݿ�ɾ��
		++dbit;
	}
	// �ݹ�ȶ���Ŀ¼����
	for (const auto& subdirs : localdirs) {
		string subpath = path;
		subpath += '\\';
		subpath += subdirs;
		Scan(subpath);
	}
}

