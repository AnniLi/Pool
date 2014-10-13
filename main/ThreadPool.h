template<typename func_type> class ThreadsPool
{
	std::multimap <int, std::function<func_type()> > functionMap;
	int threadCount = 0;
	int poolSize = 2;
	void Handler();
	void Start(int size );

public:
	std::mutex taskLock;
	int getPoolSize();
	void setPoolSize(int);
	void push_back(std::function<func_type()> , int priority = 0);
	int GetThreadCount();
	const ThreadsPool<func_type>& operator+=(std::function<func_type()> f);
	const ThreadsPool<func_type>& operator+(std::function<func_type()> f);
	ThreadsPool();
};



template<typename func_type>
void ThreadsPool<func_type>::Handler()
{
	while (true)
	{
		taskLock.lock();
		auto functionIt = functionMap.begin();
		if (functionIt == functionMap.end())
		{
			taskLock.unlock();
			return;
		}
		auto functionPtr = functionIt->second;
		functionMap.erase(functionIt);
		threadCount++;
		taskLock.unlock();
		functionPtr();
		threadCount--;
	}
}

template<typename func_type>
void ThreadsPool<func_type>::Start(int size)
{
	for (int i = 0; i < size; i++)
	boost::thread t1(&ThreadsPool<func_type>::Handler, this);
}

template<typename func_type>
int ThreadsPool<func_type>::getPoolSize()
{
	return poolSize;
}

template<typename func_type>
void ThreadsPool<func_type>::setPoolSize(int size)
{
	taskLock.lock();
	Start(size-poolSize)
	poolSize = size;
	taskLock.unlock();
}

template<typename func_type>
void ThreadsPool<func_type>::push_back(std::function<func_type()> f, int priority = 0)
{
	taskLock.lock();
	functionMap.insert(std::make_pair(-priority, f));
	taskLock.unlock();
}

template<typename func_type>
int ThreadsPool<func_type>::GetThreadCount()
{
	return threadCount;
}

template<typename func_type>
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+=(std::function<func_type()> f)
{
	push_back(f);
	return *this;
}

template<typename func_type>
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+(std::function<func_type()> f)
{
	push_back(f);
	return *this;
}

template<typename func_type>
ThreadsPool<func_type>::ThreadsPool()
{
	Start(poolSize);
}


