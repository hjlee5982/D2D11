#pragma once

class TimerManager : public Singleton<TimerManager>
{
public:
	void Update();
public:
	void AddTimer(const string& key, sptr<class JTimer> timer);
public:
	sptr<class JTimer> GetTimer(const string& key);
private:
	Dictionary<string, sptr<class JTimer>> _timers;
};

