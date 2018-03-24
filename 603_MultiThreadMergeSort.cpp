#include <iostream>
#include <random>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <atomic>
#include <assert.h>
#include <chrono>

using namespace std;
using namespace chrono;
string curPath = "F:\\Coding\\Interview\\MultiThreadMergeSort\\";

vector<vector<int>> g_data(10, vector<int>());
queue<int> sortedQue;
mutex que_mutex;
condition_variable cond;
std::atomic<int> mergeCnt;

void threadFunc(int id) {
	string filename = curPath + "data" + to_string(id) + ".dat";
	ifstream fstrm(filename);
	int x;
	while (fstrm >> x) {
		g_data[id].push_back(x);
	}
	sort(g_data[id].begin(), g_data[id].end());
	{
		lock_guard<mutex> locker(que_mutex);
		sortedQue.push(id); //already sorted
		if (sortedQue.size() > 1) cond.notify_one();
	}
	return;
}


class MergeThreadPool {
public:
	MergeThreadPool()  {
		mergeCnt = 0;
	}
	~MergeThreadPool() {
		
	}

	void setThreadNum(int num) {
		numThread_ = num;
	}

	void start() {
		for (int i = 0; i < numThread_; i++) {
			Pool_.push_back(std::thread(std::bind(&MergeThreadPool::mergeThreadFunc, this) ));
		}
		// 等待所有线程终止
		for (int i = 0; i < numThread_; i++)
			Pool_[i].join();
		
		
		// 全部归并完成
		assert(sortedQue.size() == 1);
		ofstream fout(curPath + "sortedData.dat");
		int outId = sortedQue.front();
		for (int i = 0; i < g_data[outId].size(); i++) {
			fout << g_data[outId][i] << "\n";
		}

		cout << "Everything is done!" << endl;

	}
	
private:

	int numThread_;
	vector<thread> Pool_;
	void merge(int idA, int idB) {
		// g_data[idA] 和 g_data[idB]的两个数组进行归并，并将新数据写到数据A的后面
		vector<int> A(g_data[idA].begin(), g_data[idA].end());
		g_data[idA].clear();
		int i = 0, j = 0;
		while (i < A.size() && j < g_data[idB].size()) {
			if (A[i] < g_data[idB][j]) {
				g_data[idA].push_back(A[i++]);
			}
			else {
				g_data[idA].push_back(g_data[idB][j++]);
			}
		}
		while (i < A.size())
			g_data[idA].push_back(A[i++]);
		while (j < g_data[idB].size())
			g_data[idA].push_back(g_data[idB][j++]);

		return;
	}

	void mergeThreadFunc() {
		while (mergeCnt < 9) { //FIXME:　k-merge should merge k - 1 times
			int idA, idB;
			{
				std::unique_lock<mutex> locker(que_mutex);
				cond.wait(locker, []() {
					return mergeCnt >= 9 || sortedQue.size() > 1;
				}); //等待条件满足
				if (mergeCnt >= 9) break; //刚才wait阻塞的这段时间,其他线程已经把活干完了
				idA = sortedQue.front(); sortedQue.pop();
				idB = sortedQue.front(); sortedQue.pop();
			}
			merge(idA, idB);
			{
				std::unique_lock<mutex> locker(que_mutex);
				sortedQue.push(idA);
				if (sortedQue.size() > 1) cond.notify_one();
			}
			
			if ((++mergeCnt) >= 9) cond.notify_all(); //如果有某一个线程把活干完了，要告诉所有的线程
			cout << mergeCnt << endl;
		}
		return;
	}
};



int main() {
	 //step1: generate 10 files with random data
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10000);
	

	for (int fileid = 0; fileid < 10; fileid++) {
		string filename = curPath + "data" + to_string(fileid) + ".dat";
		{
			ofstream fstrm(filename); //离开作用域自动关闭文件

			for (int i = 0; i < 100000; i++) {
				fstrm << dis(gen) << "\n";
			}
		}
	}

	auto start = system_clock::now();

	// 起10个线程，分别进行排序
	for (int id = 0; id < 10; id++) {
		std::thread thr(threadFunc, id);
		thr.detach();
	}
	MergeThreadPool mergePool;
	int threadNum = 8;
	mergePool.setThreadNum(threadNum);
	mergePool.start();


	auto end = system_clock::now();
	auto duration = duration_cast<microseconds> (end - start);

	cout << "merge Thread Num: " << threadNum << endl;
	cout << "Time cost: " << double(duration.count()) / 1000 << "ms" << endl;

	system("pause");
	return 0;
}


/*
	测试结果：每个文件100000个数，共1000000个数
	ThreadNum	TimeCost(ms)
		1			10905.1
		2			9634.51
		3			9311.86
		4			9087.17
		8			9206.77

*/
