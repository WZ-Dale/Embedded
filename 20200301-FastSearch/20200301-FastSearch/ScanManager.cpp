// 扫描模块
#include "ScanManager.h"

void ScanManager::Scan(const string& path) {
	// 比对  本地文件 和 数据库
	vector<string> localdirs;
	vector<string> localfiles;
	DirectoryList(path, localdirs, localfiles);

	// 在集合里，即排序
	set<string> localset;
	localset.insert(localdirs.begin(), localdirs.end());
	localset.insert(localfiles.begin(), localfiles.end());

	set<string> dbset;
	DataManager::GetInstance()->GetDoc(path, dbset);		// 将数据库中的数据放到set中，为后序比对做准备

	// 开始比对
	auto localit = localset.begin();
	auto dbit = dbset.begin();
	while (localit != localset.end() && dbit != dbset.end()) {
		if (*localit < *dbit) {		// 本地有，数据库没有，数据库新增
			DataManager::GetInstance()->InsertDoc(path, *localit);
			++localit;
		}
		else if (*localit > *dbit) {		// 本地没有，数据库有，数据库删除
			DataManager::GetInstance()->DeleteDoc(path, *dbit);
			++dbit;
		}
		else {		// 本地和数据库一致，数据不变
			++localit;
			++dbit;
		}
	}
	while (localit != localset.end()) {
		DataManager::GetInstance()->InsertDoc(path, *localit);	// 数据库新增
		++localit;
	}
	while (dbit != dbset.end()) {
		DataManager::GetInstance()->DeleteDoc(path, *dbit);	// 数据库删除
		++dbit;
	}
	// 递归比对子目录数据
	for (const auto& subdirs : localdirs) {
		string subpath = path;
		subpath += '\\';
		subpath += subdirs;
		Scan(subpath);
	}
}

