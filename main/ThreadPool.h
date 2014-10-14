template<typename FuncType> class ThreadPool
{
public:
    ThreadPool();

    int GetPoolSize();
    void SetPoolSize(int);
    int GetThreadCount();

    void PushBack(std::function<FuncType()>, int priority = 0);
    const ThreadPool<FuncType>& operator += (std::function<FuncType()> f);
    const ThreadPool<FuncType>& operator + (std::function<FuncType()> f);

private:
    void Handler();
    void Start(int size);

    std::multimap <int, std::function<FuncType()> > functionMap;
    std::mutex taskLock;
    int RunningThreadCount = 0;
    int poolSize = 2;
};

#pragma region Constructor
template<typename FuncType>
ThreadPool<FuncType>::ThreadPool()
{
    Start(poolSize);
}
#pragma endregion Constructor

#pragma region Get And Set Methods
template<typename FuncType>
int ThreadPool<FuncType>::GetPoolSize()
{
    return poolSize;
}

template<typename FuncType>
void ThreadPool<FuncType>::SetPoolSize(int size)
{
    taskLock.lock();
    Start(size - poolSize);
    poolSize = size;
    taskLock.unlock();
}

template<typename FuncType>
int ThreadPool<FuncType>::GetThreadCount()
{
    return RunningThreadCount;
}
#pragma endregion Get And Set Methods

#pragma region Public Methods
template<typename FuncType>
void ThreadPool<FuncType>::PushBack(std::function<FuncType()> f, int priority = 0)
{
    taskLock.lock();
    functionMap.insert(std::make_pair(-priority, f));
    taskLock.unlock();
}
#pragma endregion Public Methods

#pragma region Operators
template<typename FuncType>
const ThreadPool<FuncType>& ThreadPool<FuncType>::operator+=(std::function<FuncType()> f)
{
    PushBack(f);
    return *this;
}

template<typename FuncType>
const ThreadPool<FuncType>& ThreadPool<FuncType>::operator+(std::function<FuncType()> f)
{
    PushBack(f);
    return *this;
}
#pragma endregion Operators

#pragma region Private Methods
template<typename FuncType>
void ThreadPool<FuncType>::Handler()
{
    while (true)
    {
        taskLock.lock();
        auto functionIt = functionMap.begin();
        if (functionIt == functionMap.end())
        {
            taskLock.unlock();
            break;
        }
        auto functionPtr = functionIt->second;
        functionMap.erase(functionIt);
        RunningThreadCount++;
        taskLock.unlock();
        functionPtr();
        RunningThreadCount--;
    }
}

template<typename FuncType>
void ThreadPool<FuncType>::Start(int size)
{
    for (int i = 0; i < size; i++)
    {
        std::thread t1(&ThreadPool<FuncType>::Handler, this);
        // WARNING
    }
}
#pragma endregion Private Methods
