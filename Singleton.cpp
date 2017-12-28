class Singleton
{
public:
    static Singleton& Instance(){ //静态成员函数,提供全局访问点
        static Singleton obj;
        return obj;
    }

private:
    Singleton();
    Singleton(Singleton &&) = default;
    Singleton(const Singleton &) = default;
    Singleton &operator=(Singleton &&) = default;
    Singleton &operator=(const Singleton &) = default;

};
