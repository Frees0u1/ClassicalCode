/*
* 互斥锁的C++封装，代码来自陈硕《Linux多线程服务端编程》
* 适当简化，保留核心代码
* Date: 2018/1/25
*/
#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

class MutexLock : boost::noncopyable {
public:
    MutexLock() {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~MutexLock() {
        pthread_mutex_destroy(&mutex_);
    }
    //以下函数仅供MutexLockGuard调用，严禁用户代码调用
    void lock() {
        pthread_mutex_lock(&mutex_);
    }

    void unlock() {
        pthread_mutex_unlock(&mutex_);
    }
   
private:
    pthread_mutex_t mutex_;
};

class MutexLockGuard : boost::noncopyable {
public:
    //创建时加锁
    explicit MutexLockGuard(MutexLock& mutex) : mutex_(mutex) {
        mutex_.lock();
    }
    //析构时解锁
    ~MutexLockGuard() {
        mutex_.unlock(); 
    }

private:
    MutexLock &mutex_;
};



//使用方法
MutexLock mutex_;
int main(){

    MutexLockGuard lock(mutex_);
    //Do somthing here
    //Would be thread safe

    return 0;
} //when leaves here, Deconstuctor would be work and auto unlock
