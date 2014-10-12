template<typename func_type> class ThreadsPool
{
	//std::map <int,std::shared_ptr<boost::thread>> m_treads;
	std::multimap <int, std::function<func_type()> > functionVector;
	int treadCount = 0;
	int poolSize = 2;
	void Handler(std::function<func_type()>,int k);
	void Start();

public:
	std::mutex taskLock;
	int getPoolSize();
	void setPoolSize(int);
	void push_back(std::function<func_type()> , int priority = 0);
	void Wait();
	void GetThreadCount();
	const ThreadsPool<func_type>& operator+=(std::function<func_type()> f);
	const ThreadsPool<func_type>& operator+(std::function<func_type()> f);
	ThreadsPool();
};


template<typename func_type>
void ThreadsPool<func_type>::Handler(std::function<func_type()> ptr, int k)
{
	ptr();
	taskLock.lock();
	treadCount--;
	taskLock.unlock();
}

template<typename func_type>
void ThreadsPool<func_type>::Start()
{
	while (true)
	{
		while (!functionVector.empty())
		{
			taskLock.lock();
			if ((treadCount < poolSize))
			{
				std::function<func_type()> ptr;
				std::multimap <int, std::function<func_type()>>::iterator it;
				it = functionVector.begin();
				ptr = (*it).second;
				functionVector.erase(it);
				treadCount++;
				auto tread = std::make_shared<boost::thread>(&ThreadsPool::Handler, this, ptr, treadCount);
				taskLock.unlock();
			}
			else taskLock.unlock();
		}
	}
}

template<typename func_type>
int ThreadsPool<func_type>::getPoolSize()
{
	std::cout << "Pool size is " << poolSize << std::endl;
	return poolSize;
}

template<typename func_type>
void ThreadsPool<func_type>::setPoolSize(int k)
{
	taskLock.lock();
	poolSize = k;
	taskLock.unlock();
}

template<typename func_type>
void ThreadsPool<func_type>::push_back(std::function<func_type()> f, int priority = 0)
{
	taskLock.lock();
	functionVector.insert(std::make_pair(-priority, f));
	taskLock.unlock();
}

template<typename func_type>
void ThreadsPool<func_type>::Wait()
{
	while (!functionVector.empty() || treadCount);
}

template<typename func_type>
void ThreadsPool<func_type>::GetThreadCount()
{
	std::cout << std::endl;
	std::cout << treadCount << " thread(s) are running now" << std::endl;
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
	auto tread = std::make_shared<boost::thread>(&ThreadsPool::Start, this);
}


