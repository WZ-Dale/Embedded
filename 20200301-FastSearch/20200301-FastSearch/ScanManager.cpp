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
	DataManager::GetInstance()->GetDoc(path, dbset);		// �����ݿ��е����ݷŵ�set�У�Ϊ����ȶ���׼��

	// ��ʼ�ȶ�
	auto localit = localset.begin();
	auto dbit = dbset.begin();
	while (localit != localset.end() && dbit != dbset.end()) {
		if (*localit < *dbit) {		// �����У����ݿ�û�У����ݿ�����
			DataManager::GetInstance()->InsertDoc(path, *localit);
			++localit;
		}
		else if (*localit > *dbit) {		// ����û�У����ݿ��У����ݿ�ɾ��
			DataManager::GetInstance()->DeleteDoc(path, *dbit);
			++dbit;
		}
		else {		// ���غ����ݿ�һ�£����ݲ���
			++localit;
			++dbit;
		}
	}
	while (localit != localset.end()) {
		DataManager::GetInstance()->InsertDoc(path, *localit);	// ���ݿ�����
		++localit;
	}
	while (dbit != dbset.end()) {
		DataManager::GetInstance()->DeleteDoc(path, *dbit);	// ���ݿ�ɾ��
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

