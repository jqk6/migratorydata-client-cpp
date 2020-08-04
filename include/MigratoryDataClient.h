#ifndef _MigratoryDataClient_h_included_
#define _MigratoryDataClient_h_included_

#include <vector>
#include <string>

#include "MigratoryDataLogLevel.h"
#include "MigratoryDataListener.h"

namespace migratorydata 
{

	/// @cond	
	class MigratoryDataLogListener;
	class PushClientImpl;
	/// @endcond

	/**
	* This class implements all the necessary operations for connecting to a cluster of one or more MigratoryData servers,
	* subscribing to subjects, getting real-time messages for the subscribed subjects, and publishing real-time messages.
	*/
	class MigratoryDataClient 
	{

	private :
		PushClientImpl* clientImpl;

	public :

		/**
		* A constant which indicates that the client successfully connected to a MigratoryData server.
		*/
		const std::string NOTIFY_SERVER_UP;

		/**
		* A constant which indicates that the client failed to connect to a MigratoryData server.
		*/
		const std::string NOTIFY_SERVER_DOWN;

		/**
		 * A constant which indicates that after a failover reconnection, the client successfully synchronized a subscribed
		 * subject with the latest retained message available for that subject, as well as with all messages made available
		 * during the failover period for that subject.
		 */
		const std::string NOTIFY_DATA_SYNC;

		/**
		 * A constant which indicates that after a failover reconnection, the client successfully synchronized a subscribed
		 * subject with the latest retained message available for that subject, but not with the potential messages made
		 * available during the failover period, therefore behaving as a new client.
		 */
		const std::string NOTIFY_DATA_RESYNC;

		/**
		 * A constant which indicates that the client was authorized to subscribe to a subject.
		 */
		const std::string NOTIFY_SUBSCRIBE_ALLOW;

		/**
		 * A constant which indicates that the client was not authorized to subscribe to a subject.
		 */
		const std::string NOTIFY_SUBSCRIBE_DENY;

		/**
		 * A constant which indicates that the client was unable to publish a message because it is not allowed by the
		 * entitlement system.
		 */
		const std::string NOTIFY_PUBLISH_DENIED;

		/**
		 * A constant which indicates that the client successfully published a message.
		 */
		const std::string NOTIFY_PUBLISH_OK;

		/**
		 * A constant which indicates that the client was unable to publish a message.
		 */
		const std::string NOTIFY_PUBLISH_FAILED;

		/**
		 * A constant which indicates that the client was unable to publish a message because the size of the message
		 * exceeds the message size limit allowed by the server (see the server parameter \c MAX_MESSAGE_SIZE).
		 */
		const std::string NOTIFY_MESSAGE_SIZE_LIMIT_EXCEEDED;

		/**
		* A constant which indicates that the reconnect rate threshold per 3-minute window has been reached.
		*
		* See \link MigratoryDataClient.notifyWhenReconnectRateExceedsThreshold() \endlink for more details about this policy.
		*/
		const std::string NOTIFY_RECONNECT_RATE_EXCEEDED;

		/**
		 * A constant used to define the reconnect policy.
		 *
		 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink for more details about this policy.
		 */
		const std::string CONSTANT_WINDOW_BACKOFF;

		/**
		 * A constant used to define the reconnect policy.
		 *
		 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink for more details about this policy.
		 */
		const std::string TRUNCATED_EXPONENTIAL_BACKOFF;

		/**
		 * A constant used to define the transport type.
		 *
		 * See \link MigratoryDataClient.setTransport() \endlink for more details about this policy.
		 */
		const std::string TRANSPORT_HTTP;

		/**
		 * A constant used to define the transport type.
		 *
		 * See \link MigratoryDataClient.setTransport() \endlink for more details about this policy.
		 */
		const std::string TRANSPORT_WEBSOCKET;


		/**
		* \brief Create a MigratoryDataClient object.
		*/
		MigratoryDataClient();

		/**
		 * Use this method to connect this client to one of the MigratoryData servers you specified with
		 * \link MigratoryDataClient.setServers() \endlink, and subscribe to the subjects you specified with
		 * \link MigratoryDataClient.subscribe() \endlink, if any.
		 */
		void connect();

		/**
		 * Disconnect from the connected MigratoryData server and dispose the resources used by the connection.
		 *
		 * This method should be called when the connection is no longer necessary.
		 */
		void disconnect();

		/**
		 * Attach a listener for handling log messages outputted by the library.
		 *
		 * It is advisable to configure this API call first if you want to log as much as possible.
		 *
		 * \param logListener   an implementation of the \link MigratoryDataLogListener \endlink interface
		 * \param logLevel      a particular \link MigratoryDataLogLevel \endlink configured as the logging threshold
		 */
		void setLogListener(MigratoryDataLogListener* logListener, MigratoryDataLogLevel logLevel);

		/**
		 * Attach a listener for handling the received real-time messages as well as the status notifications.
		 *
		 * \param listener   an implementation of the \link MigratoryDataListener \endlink interface
		 */
		void setListener(MigratoryDataListener* listener);

		/**
		 * Specify a cluster of one or more MigratoryData servers to which the client will connect to.
		 *
		 * For example, to connect to a cluster formed of two MigratoryData servers installed at the addresses
		 * \c p1.example.com and \c p2.example.com, and configured to accept clients on the standard HTTP port \c 80, the
		 * following code can be used:
		 *
		 * ```js
		 *	vector<string> servers;
		 *	servers.push_back("p1.example.com:80");
		 *	servers.push_back("p2.example.com:80");
		 *	client->setServers(servers);
		 * ```
		 *
		 * To achieve load-balancing, the API connects the client to a MigratoryData server chosen randomly from the
		 * \c servers list. In this way, the load is balanced among all the members of the cluster.
		 *
		 * Moreover, the API supports weighted load-balancing. This feature is especially useful if the MigratoryData
		 * servers of the cluster are installed on machines with different capacities. You can assign to each member of the
		 * cluster a \em weight ranging from \c 0 to \c 100. This weight assignment is a hint provided to the API to select
		 * with a higher probability a MigratoryData server with a higher weight either initially when the client connects
		 * to the cluster or later during a failover reconnection.
		 *
		 * Supposing the address \c p1.example.com corresponds to a machine that is twice more powerful than the machine
		 * having the address \c p2.example.com, then you can assign to \c p1.example.com a weight \c 100 and to
		 * \c p2.example.com a weight \c 50 by prefixing each address with the assigned weight as follows:
		 *
		 * ```js
		 *  vector<string> servers;
		 *	servers.push_back("100 p1.example.com:80");
		 *	servers.push_back("50 p2.example.com:80");
		 *	client->setServers(servers);
		 * ```
		 *
		 * The API assigns a default weight \c 100 to the addresses not prefixed with a specific weight.
		 *
		 * To achieve failover, if the connection between the client and a MigratoryData server is broken, then the API will
		 * automatically detect the failure and will select another MigratoryData server from the \c servers list. If the
		 * client fails to connect to the newly selected server, a status notification MigratoryDataClient.NOTIFY_SERVER_DOWN
		 * will be triggered, unless this is modified using \link MigratoryDataClient.notifyAfterFailedConnectionAttempts() \endlink),
		 * and a new MigratoryData server of the cluster will be selected again and again until the client will be able to connect to one of the MigratoryData servers of
		 * the cluster. When successfully connected, the API will trigger
		 * MigratoryDataClient.NOTIFY_SERVER_UP.
		 *
		 * Furthermore, if the Guaranteed Message Delivery feature is enabled for the MigratoryData cluster, then the messages
		 * potentialy published for a subscribed subject during the failover period will be automatically recovered from
		 * the cache of the MigratoryData server to which the client reconnects to and a status notification
		 * \link MigratoryDataClient.NOTIFY_DATA_SYNC \endlink will be triggered for that subject.
		 *
		 * If, for example, the failover period is abnormally long, and the client is not able to recover all the messages
		 * made available during the failover period for one of its subscribed subjects, then the API will retrieve only the
		 * most recent retained message available for that subject and will trigger a MigratoryDataClient.NOTIFY_DATA_RESYNC
		 * status notification for that subject, the client behaving as a new client.
		 *
		 * For a complete discussion about load balancing, failover, and guaranteed message delivery features see the
		 * <em>Architecture Guide</em>.
		 *
		 * \param servers   an array of strings where each string represents the network address (IP address or DNS domain
		 *                  name and its corresponding port) of a MigratoryData server, optionally prefixed by a weight
		 *                  ranging from \c 0 to \c 100; if the weight prefix is not provided to an address, then the API will
		 * 					automatically assign to that address a default weight \c 100
		 */
		void setServers(std::vector<std::string>& servers);

		/**
		 *  Subscribe to one or more subjects.
		 *
		 *  The MigratoryData subjects are strings having a particular syntax. See the Chapter "Concepts" of the Architecture
		 *  Guide to learn about the syntax of the subjects.
		 *
		 *  As an example, supposing messages are market data updates having as subjects stock names. Then, to subscribe for
		 *  the messages having as subjects \c /stocks/NYSE/IBM and \c /stocks/Nasdaq/MSFT use:
		 *
		 * ```js
		 * 	vector<string> subjects;
		 * 	subjects.push_back("/stocks/NYSE/IBM");
		 * 	subjects.push_back("/stocks/Nasdaq/MSFT");
		 * 	client->subscribe(subjects);
		 * ```
		 *
		 *
		 * \param subjects   An array of strings representing subjects.
		 */
		void subscribe(std::vector<std::string>& subjects);

		/**
		 *  Subscribe to one or more subjects after getting historical messages for those subjects
		 *
		 *  The MigratoryData subjects are strings having a particular syntax. See the Chapter "Concepts" of the Architecture
		 *  Guide to learn about the syntax of the subjects.
		 *
		 *  Attempt to get the number of historical messages as defined by the argument \c numberOfHistoricalMessages,
		 *  for each subject in the argument \c subjects, then subscribe for real-time messages having as
		 *  subjects the strings provided in the \c subjects parameter.
		 *
		 *  When Guaranteed Message Delivery is enabled, each MigratoryData server in the cluster maintains an in-memory
		 *  cache with historical messages for each subject. The cache of each subject is available in all servers of the cluster.
		 *  The maximum number of messages held in cache is defined by the parameter \c MaxCachedMessagesPerSubject of the MigratoryData
		 *  server which defaults to 1,000 messages. The historical messages are continuously removed from the cache, but it is guaranteed that
		 *  they are available in the cache at least the number of seconds defined by the parameter \c CacheExpireTime which
		 *  defaults to 180 seconds.
		 *
		 *  If the value of \c numberOfHistoricalMessages is higher than the number of historical messages available in the cache, then
		 *  the client will receive only the messages available in the cache. As a consequence, if you use a value higher than the value of the
		 *  parameter \c MaxCachedMessagesPerSubject of the MigratoryData server (which defaults to 1000), then you will get the entire
		 *  cache before subscribing for real-time messages for the subjects specified with the API call.
		 *
		 *  If the value of \c numberOfHistoricalMessages is \c 0, then no historical messages have to be retrieved from the
		 *  cache and, in this case, this API method is equivalent to the API method  \link MigratoryDataClient.subscribe() \endlink.
		 *
		 * \param subjects An array of strings representing subjects.
		 * \param numberOfHistoricalMessages   the number of historical messages to be retrieved from the cache of the server
		 */
		void subscribeWithHistory(std::vector<std::string>& subjects, int numberOfHistoricalMessages);

		/**
		 * Unsubscribe from one or more subjects.
		 *
		 * \param subjects   subjects to unsubscribe
		 */
		void unsubscribe(std::vector<std::string>& subjects);

		/**
		 *  Publish a message.
		 *
		 *  If the message includes a closure data, then a status notification will be provided via
		 *  \link MigratoryDataListener.onStatus() \endlink to inform whether the message publication
		 *  has been successful or failed.
		 *
		 * \param message A MigratoryDataMessage message
		 */
		void publish(MigratoryDataMessage& message);

		/**
		 * Assign an entitlement token to the client.
		 *
		 * To define which users of your application have access to which subjects, you will first have to configure the
		 * parameter ```Entitlement```, see the <em>Configuration Guide</em>. If you set this parameter on
		 * \c Custom, then you can use the <em>MigratoryData Extension SDK for Entitlement</em> to build an extension plugin
		 * for the MigratoryData server to allow or deny certain users to subscribe to or publish on certain subjects.
		 *
		 * \param token  a string representing an entitlement token
		 */
		void setEntitlementToken(std::string& token);

		/**
		 * Return the list of subscribed subjects.
		 *
		 * \return The list of strings representing the subscribed subjects.
		 */
		void getSubjects(std::vector<std::string>& subjects);

		/**
		 *  Define the number of failed attempts to connect to one or more MigratoryData servers before triggering a status
		 *  notification MigratoryDataClient.NOTIFY_SERVER_DOWN.
		 *
		 * \param retries   the number of the failed attempts to connect to one or more MigratoryData servers before
		 *                  triggering a status notification MigratoryDataClient.NOTIFY_SERVER_DOWN; the default is \c 1
		 */
		void notifyAfterFailedConnectionAttempts(int n);

		/**
		*  Define the number of reconnect attempts to one or more MigratoryData servers per 3-minute window
		*  before triggering a status notification \link NOTIFY_RECONNECT_RATE_EXCEEDED \endlink.
		*
		* \param n The number of reconnect attempts to one or more MigratoryData servers per 3-minute window
		*          before triggering a status notification
		*          \link NOTIFY_RECONNECT_RATE_EXCEEDED \endlink; default value is <code>15</code>.
		*/
		void notifyWhenReconnectRateExceedsThreshold(int n);

#if !defined (SSL_DISABLED)

		/**
		 * Configure whether to use SSL/TLS encryption when connecting to a MigratoryData server.
		 *
		 * When using encryption you should connect to the ports of the MigratoryData server that are configured with the
		 * parameter \c ListenEncrypted to listen for encrypted connections.
		 *
		 * \param encrypted   indicate whether or not to use an encrypted SSL/TLS connection to communicate with the server
		 */
		void setEncryption(bool encryption);
#endif

		/**
		 * Define the number of seconds to wait before attempting to reconnect to the cluster after a connection failure is detected.
		 *
		 * <h5>Connection Failure Detection</h5>
		 *
		 * Connection failure is detected immediately for almost all users. For a few users which are subject to temporary, atypical network conditions,
		 * connection failure is detected after 30-40 seconds.
		 *
		 * <h5>Reconnection Phases and Policies</h5>
		 *
		 * When a connection failure is detected, the API will attempt to reconnect to the servers of the MigratoryData cluster as follows:
		 * First, it will attempt to reconnect up to a number of times as defined by \link MigratoryDataClient.setQuickReconnectMaxRetries() \endlink
		 * using small delays between retries (Quick Reconnection Phase). If the connection cannot be established after the Quick Reconnection Phase,
		 * then the API will attempt to reconnect less frequently according to the policy defined by \link MigratoryDataClient.setReconnectPolicy() \endlink.
		 *
		 * The delays between retries are computed according to the following algorithm where the values of the variables involved are defined by the API methods having substantially the same names:
		 *
		 * ```
		 *    Quick Reconnect Phase (retries <= quickReconnectMaxRetries)
		 *    -----------------------------------------------------------
		 *
		 *       (retries starts with 1 and increment by 1 at each quick reconnect)
		 *
		 *       reconnectDelay = quickReconnectInitialDelay * retries - random(0, quickReconnectInitialDelay)
		 *
		 *    After Quick Reconnect Phase (retries > quickReconnectMaxRetries)
		 *    ----------------------------------------------------------------
		 *
		 *       (reset retries to start with 1 and increment by 1 at each reconnect)
		 *
		 *       If reconnectPolicy is CONSTANT_WINDOW_BACKOFF, then
		 *
		 *          reconnectDelay = reconnectTimeInterval
		 *
		 *       else if reconnectPolicy is TRUNCATED_EXPONENTIAL_BACKOFF, then
		 *
		 *          reconnectDelay = min(reconnectTimeInterval * (2 ^ retries) - random(0, reconnectTimeInterval * retries), reconnectMaxDelay)
		 * ```
		 *
		 * For a few users which are subject to temporary, atypical network conditions, if <code>reconnectDelay</code> computed
		 * with the algorithm above is less than 10 seconds, then it is rounded to 10 seconds.
		 *
		 * \param seconds The number of seconds to wait before attempting to reconnect to the cluster; default value is <code>5</code> seconds.
		 */
		void setQuickReconnectInitialDelay(int seconds);

		/**
		 * Define the maximum number of retries for the Quick Reconnect phase
		 * 
		 * \param retries The maximum number of quick reconnect retries; default value is <code>3</code>. 
		*/
		void setQuickReconnectMaxRetries(int retries);

		/**
		 * Define the reconnect policy to be used after the Quick Reconnect phase.
		 *
		 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn about the Quick Reconnect phase
		 * and the reconnect schedule for the policy defined by this method.
		 *
		 * \param  policy   the reconnect policy to be used after the Quick Reconnect phase; the possible values are:
		 *                  \link MigratoryDataClient.CONSTANT_WINDOW_BACKOFF \endlink and
		 *                  \link MigratoryDataClient.TRUNCATED_EXPONENTIAL_BACKOFF \endlink; the default value is
		 *					\link MigratoryDataClient.TRUNCATED_EXPONENTIAL_BACKOFF \endlink;
		 */
		void setReconnectPolicy(std::string policy);

		/**
		 * Define the time interval used for the reconnect schedule after the Quick Reconnect phase.
		 *
		 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn about the Quick Reconnect phase
		 * and the reconnect schedule for the policy defined by this method.
		 *
		 * \param seconds A time interval expressed in seconds used for reconnect schedule; default is <code>20</code> seconds.
		 */
		void setReconnectTimeInterval(int seconds);

		/**
		 * Define the maximum reconnect delay for the MigratoryDataClient.TRUNCATED_EXPONENTIAL_BACKOFF policy.
		 *
		 * See \link MigratoryDataClient.setQuickReconnectInitialDelay() \endlink to learn how the value defined by this
		 * method is used.
		 *
		 * \param seconds The maximum reconnect delay when the policy \link MigratoryDataClient.TRUNCATED_EXPONENTIAL_BACKOFF \endlink is used; default value is 360 seconds.
		 */
		void setReconnectMaxDelay(int seconds);

		/**
		 * Define the transport type used by the client to communicate with the MigratoryData cluster.
		 *
		 * \param  type   the possible values are:
		 *                MigratoryDataClient.TRANSPORT_HTTP and
		 *                MigratoryDataClient.TRANSPORT_WEBSOCKET;
		 * 				  the default transport used by the API is MigratoryDataClient.TRANSPORT_WEBSOCKET
		 */
		void setTransport(std::string transport);

		// @cond
		void pause();
		void resume();
		// @endcond

		/**
		* \brief Destructor.
		*/
		virtual ~MigratoryDataClient();
	};

}

#endif // _MigratoryDataClient_h_included_
