#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "MigratoryDataLogLevel.h"
#include "MigratoryDataListener.h"
#include "MigratoryDataClient.h"
#include "MigratoryDataLogListener.h"
#include "MigratoryDataLogLevel.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace migratorydata;

class MLogListener : public MigratoryDataLogListener
{

public:
	void onLog(string& log, MigratoryDataLogLevel logLevel)
	{
		cout << "Got Log: " << log << endl;
	}

};

class MListener : public MigratoryDataListener
{

public:
	void onMessage(const MigratoryDataMessage& message)
	{
		cout << "Got message: " << endl;
		cout << message.toString() << endl;
	}

	void onStatus(const string& status, string& info)
	{
		cout << "Got status: " << status << " " << info << endl;
	}
};

void start()
{
	MigratoryDataClient* client = new MigratoryDataClient();

	// configure the logging
	MigratoryDataLogListener* myLogListener = new MLogListener();
	client->setLogListener(myLogListener, LOG_TRACE);

	// attach the entitlement information
	string entitlementToken = "some-token";
	client->setEntitlementToken(entitlementToken);

#if !defined (SSL_DISABLED)
	// connect via https encrypted connection
	client->setEncryption(true);
#endif

	// define the listener for messages and notifications
	MigratoryDataListener* myListener = new MListener();
	client->setListener(myListener);

	// connect to the MigratoryData server
	vector<string> servers;
	//servers.push_back("127.0.0.1:7700");
	// servers.push_back("127.0.0.1:8800");
	// servers.push_back("127.0.0.1:9900");
#if !defined (SSL_DISABLED)
	servers.push_back("127.0.0.1:443");
#else
	servers.push_back("127.0.0.1:8800");
#endif
	client->setServers(servers);

	// subscribe
	vector<string> subjects;
	subjects.push_back("/server/status");
	client->subscribe(subjects);
	client->connect();

	// publish a message every 5 seconds
	int count = 0;
	while (count++ < 100)
	{
		ostringstream content;
		content << "some-content-" << count;

		ostringstream closure;
		closure << "some-closure-" << count;

		MigratoryDataMessage message("/server/status", content.str(), closure.str());

		client->publish(message);

#ifdef WIN32
		Sleep(5000);
#else
		sleep(5);
#endif
	}

	client->disconnect();

	delete myLogListener;
	delete myListener;
	delete client;
}

int main(int argc, char* argv[])
{
	start();

	return 0;
}
