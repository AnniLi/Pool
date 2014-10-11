template<typename func_type> class ThreadsPool
{
<<<<<<< HEAD
	//std::map <int,std::shared_ptr<boost::thread>> m_treads;
=======
	std::map <int,std::shared_ptr<boost::thread>> m_treads;
>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
	std::multimap <int, std::function<func_type()> > functionVector;
	int treadCount = 0;
	int poolSize = 2;
	void Handler(std::function<func_type()>,int k);
<<<<<<< HEAD
	void Start();

public:
	std::mutex taskLock;

	int getPoolSize();
	void setPoolSize(int);
	void push_back(std::function<func_type()> , int priority = 0);
=======
	
public:
	std::mutex taskLock;


	void setPoolSize();
	void getPoolSize();
	void Start();
>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
	void Wait();
	void GetThreadCount();
	const ThreadsPool<func_type>& operator+=(std::function<func_type()> f);
	const ThreadsPool<func_type>& operator+(std::function<func_type()> f);
<<<<<<< HEAD
};


template<typename func_type>
void ThreadsPool<func_type>::Handler(std::function<func_type()> ptr, int k)
{
	ptr();
	taskLock.lock();
	treadCount--;
	taskLock.unlock();
}

=======

};



template<typename func_type>
void ThreadsPool<func_type>::GetThreadCount()
{
	std::cout << std::endl;
	std::cout << m_treads.size() << " thread(s) are running now" << std::endl;
}

template<typename func_type>
void ThreadsPool<func_type>::Wait()
{
	while (!functionVector.empty() || treadCount)
	{
		auto it = m_treads.begin();
		(*it).second->join();


	}

}



>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
template<typename func_type>
void ThreadsPool<func_type>::Start()
{
	while (!functionVector.empty())
	{
		taskLock.lock();
		if ((treadCount < poolSize))
<<<<<<< HEAD
		{
=======
		{	
>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
			std::function<func_type()> ptr;
			std::multimap <int, std::function<func_type()>>::iterator it;
			it = functionVector.begin();
			ptr = (*it).second;
			functionVector.erase(it);
			treadCount++;
<<<<<<< HEAD
			auto tread = std::make_shared<boost::thread>(&ThreadsPool::Handler, this, ptr, treadCount);
			taskLock.unlock();
=======
			taskLock.unlock();
			auto tread = std::make_shared<boost::thread>(&ThreadsPool::Handler, this, ptr, treadCount);
			m_treads[treadCount] = tread;
>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
		}
		else taskLock.unlock();
	}
}

template<typename func_type>
<<<<<<< HEAD
int ThreadsPool<func_type>::getPoolSize()
{
	std::cout << "Pool size is " << poolSize << std::endl;
	return poolSize;
}

template<typename func_type>
void ThreadsPool<func_type>::setPoolSize(int k)
{
	poolSize = k;
}

template<typename func_type>
void ThreadsPool<func_type>::push_back(std::function<func_type()> f, int priority = 0)
{
	taskLock.lock();
	functionVector.insert(std::make_pair(priority, f));
	taskLock.unlock();
	Start();
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
	std::cout << m_treads.size() << " thread(s) are running now" << std::endl;
}

template<typename func_type>
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+=(std::function<func_type()> f)
{
	push_back(f);
=======
void ThreadsPool<func_type>::Handler(std::function<func_type()> ptr, int k)
{
	ptr();
	std::map<int, std::shared_ptr<boost::thread>>::iterator it;
	while ((it = m_treads.find(k)) == m_treads.end());
	taskLock.lock();
	it = m_treads.find(k);
	m_treads.erase(m_treads.find(k));
	treadCount--;
	taskLock.unlock();
	
}

template<typename func_type>
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+(std::function<func_type()> f)
{
	functionVector.insert(std::make_pair(0, f));
	Start();
>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
	return *this;
}

template<typename func_type>
<<<<<<< HEAD
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+(std::function<func_type()> f)
{
	push_back(f);
	return *this;
}



=======
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+=(std::function<func_type()> f)
{
	functionVector.insert(std::make_pair(0,f));
	Start();
	return *this;
}

>>>>>>> fb87ec89746c490ba2374ec5de78bf7d07ddd108
