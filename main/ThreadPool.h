template<typename func_type> class ThreadsPool
{
	std::map <int,std::shared_ptr<boost::thread>> m_treads;
	std::multimap <int, std::function<func_type()> > functionVector;
	int treadCount = 0;
	int poolSize = 2;
	void Handler(std::function<func_type()>,int k);
	
public:
	std::mutex taskLock;


	void setPoolSize();
	void getPoolSize();
	void Start();
	void Wait();
	void GetThreadCount();
	const ThreadsPool<func_type>& operator+=(std::function<func_type()> f);
	const ThreadsPool<func_type>& operator+(std::function<func_type()> f);

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



template<typename func_type>
void ThreadsPool<func_type>::Start()
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
			taskLock.unlock();
			auto tread = std::make_shared<boost::thread>(&ThreadsPool::Handler, this, ptr, treadCount);
			m_treads[treadCount] = tread;
		}
		else taskLock.unlock();
	}
}

template<typename func_type>
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
	return *this;
}

template<typename func_type>
const ThreadsPool<func_type>& ThreadsPool<func_type>::operator+=(std::function<func_type()> f)
{
	functionVector.insert(std::make_pair(0,f));
	Start();
	return *this;
}

