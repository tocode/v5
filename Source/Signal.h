#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <string>
#include <functional>

class Connection
{
public:
	Connection()
	{
		content = shared_ptr<Content>(new Content());
		content->connected = true;
	}
	bool IsConnected()
	{
		return content->connected;
	}
	void Disconnect()
	{
		if (content->connected)
			content->connected = false;
	}
	bool operator==(const Connection& con) const
	{
		return this->content == con.content;
	}
private:
	struct Content
	{
		bool connected;
	};
	shared_ptr<Content> content;
};

template<typename T>
class Signal
{
public:
	vector<Connection> connections;
	vector<std::function<T>> functions;
public:
	Connection Connect(std::function<T> fun)
	{
		Connection con;
		connections.push_back(con);
		functions.push_back(fun);
		return con; 
	}
	~Signal()
	{
		DisconnectAll();
	}
	void DisconnectAll()
	{
		for (auto i=0; i<connections.size(); i++)
			connections[i].Disconnect();
	}
};

#define EMIT(SIG,ARGS)\
	for (auto i=0; i<SIG.connections.size(); i++)\
		if (SIG.connections[i].IsConnected())\
			SIG.functions[i] ARGS;

class ConnectionHolder
{
public:
	void HoldConnection(Connection& c)
	{
		connections.push_back(c);
	}
	~ConnectionHolder()
	{
		DisconnectAll();
	}
	void DisconnectAll()
	{
		for (auto i=0; i<connections.size(); i++)
			connections[i].Disconnect();
	}
private:
	std::vector<Connection> connections;
};

#define CONNECT(SIG,OBJ,FUN)\
	OBJ.HoldConnection(SIG.Connect(FUN));

//#define CONNECT(SIG,FUN)\
	//SIG.Connect(FUN);

#endif