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
			//cout << "**************************��ʼɨ��****************************" << endl;
			Scan("E:\\Projects\\ATK-LORA-01");
			//Scan("E:\\Projects\\20200301-FastSearch\\20200301-FastSearch\\Test");
			//cout << "���������������������������� �� 5 �롢��������������������������" << endl;
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

class Singleton {
public:
	static Singleton* GetInstance() {
		static Singleton m_instance;
		return &m_instance;
	}
	void Cout() {
		cout << "��������" << a++ << endl;
	}
private:
	// ���캯��˽��
	Singleton() {};
	// C++98 ������
	//Singleton(Singleton const&);
	//Singleton& operator=(Singleton const&);
	// or
	// C++11
	Singleton(Singleton const&) = delete;
	Singleton& operator=(Singleton const&) = delete;
	int a = 0;
};

