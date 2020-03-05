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
	//DataManager();

	auto localit = localset.begin();
	auto dbit = dbset.begin();
	while (localit != localset.end() && dbit != dbset.end()) {
		if (*localit < *dbit) {		// �����У����ݿ�û�У����ݿ�����

			++localit;
		}
		else if (*localit > *dbit) {		// ����û�У����ݿ��У����ݿ�ɾ��

			++dbit;
		}
		else {		// ���غ����ݿ�һ�£����ݲ���
			++localit;
			++dbit;
		}
	}
	while (localit != localset.end()) {
		// ���ݿ�����
		++localit;
	}
	while (dbit != dbset.end()) {
		// ���ݿ�ɾ��
		++dbit;
	}
	// �ݹ�ȶ���Ŀ¼����
	for (const auto& subdirs : localdirs) {
		//Scan(subdirs);
	}
}

