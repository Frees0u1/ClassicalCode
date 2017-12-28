class Singleton
{
public:
    static Singleton& Instance(){ //静态成员函数,提供全局访问点
        static Singleton obj;
        return obj;
    }

private: //构造 析构 拷贝 赋值 移动构造函数均设置为私有
    Singleton();
    Singleton(Singleton &&) = default;
    Singleton(const Singleton &) = default;
    Singleton &operator=(Singleton &&) = default;
    Singleton &operator=(const Singleton &) = default;
};
