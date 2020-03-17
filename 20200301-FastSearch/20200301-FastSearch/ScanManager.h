#pragma once

#include "Common.h"
#include "DataManager.h"

//��������ֻ��Ҫһ��ɨ��ģ��,��˽�ScanManager��Ƴɵ���
class ScanManager 	//ɨ�����Ϣ,�ŵ����ݿ���
{
public:
	void Scan(const string& path);
	void StartScan() {
		while (1) {
			Scan("E:\\Projects\\20200301-FastSearch\\20200301-FastSearch\\Test");
			std::this_thread::sleep_for(std::chrono::seconds(5));	// ÿ��5sɨ��һ��
		}
	}
	static ScanManager* CreateInstance() {
		static ScanManager scanmgr;
		static std::thread thd(&StartScan, &scanmgr);	// ��scanmgr�����StartScan����
		thd.detach();		// �̷߳���һ��
		return &scanmgr;
	}
private:
	ScanManager() {
		//_datamgr.Init();
	}
	ScanManager(const ScanManager&);
	//DataManager _datamgr;
};
