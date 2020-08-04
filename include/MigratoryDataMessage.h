#pragma once

#include "MigratoryDataMessageType.h"
#include "MigratoryDataQoS.h"

#include <vector>
#include <string>

namespace migratorydata
{

	/**
	 * Represent a message.
	 */
	class MigratoryDataMessage
	{

	private :
		std::string subject;
		std::string content;
		std::string closure;
		std::string replySubject;

		bool retained;
		QoS qos;

	protected:
		int seq;
		int epoch;
		MessageType messageType;
		bool compressed;

	public :

		/**
		 * Default constructor.
		 */
		MigratoryDataMessage();

		/**
		 * Copy constructor.
		 * 
		 * \param message A MigratoryDataMessage object
		 */
		MigratoryDataMessage(const MigratoryDataMessage& message);

		/**
	    * Create a MigratoryDataMessage object
 		*
 		* \param subject The subject of the message
 		* \param content The content of the message
 		*/
		MigratoryDataMessage(const std::string& subject, const std::string& content);
		
	   /**
 		* Create a MigratoryDataMessage object
 		*
 		* \param subject The subject of the message
 		* \param content The content of the message
 		* \param closure The closure of the message (OPTIONAL)
 		*/		
		MigratoryDataMessage(const std::string& subject, const std::string& content, const std::string& closure);

		/**
		 * Create a MigratoryDataMessage object
		 *
		 * If a reply subject is attached to a message, the message acts as a request message. The clients which receive a
		 * request message will be able to reply by sending back one or more messages having as subject the reply subject.
		 *
		 * <p>
		 *     Note: If the reply subject is not already subscribed, it will be subscribed by the library implicitly, and it
		 *     can be reused for request/reply interactions (and even for receiving multiple replies to one request). When
		 *     it is not needed anymore, it should be unsubscribed explicitly.
		 * </p>
		 *
		 * \param subject The subject of the message
		 * \param content The content of the message
		 * \param closure The closure of the message (OPTIONAL)
		 * \param qos       the QoS level of the message; the default is <code>QoS.GUARANTEED</code> (OPTIONAL)
		 * \param retained  indicate whether or not the message should be/was retained by the server; the default is <code>true</code> (OPTIONAL)
		 * \param replySubject   the reply subject of the message (OPTIONAL)
		 *
		 */
		MigratoryDataMessage(const std::string& subject, const std::string& content, const std::string& closure, QoS qos, bool retained, const std::string& replySubject);

	   /**
 		* Get the subject of the message
 		*
 		* \return A string representing the subject of the message
		*/
		std::string getSubject() const;
		
	   /**
 		* Get the content of the message
 		*
 		* \return A string representing the content of the message
		*/
		std::string getContent() const;
		
	   /**
 		* Get the closure of the message
 		*
 		* \return The closure data of the message
 		*/	
		std::string getClosure() const;

		/**
		 * Indicate whether or not the message should be/was retained by the server.
		 *
		 * \return  true if the message should be, or was, retained by the server
		 */
		bool isRetained() const;

		/**
		 * Get the subject to be used to reply to this message.
		 *
		 * A client which receives a message containing a reply subject should interpret the message
		 * as a request. It has the option to use the reply subject - extracted from the message with
		 * this method - to send a reply.
		 *
		 * \return The subject to be used to reply to this message.
		 */
		std::string getReplySubject() const;
		
		/**
		 * Get the QoS level of the message.
		 *
		 * \return the QoS level of the message
		 */
		QoS getQos() const;

		/**
		 * Get the MessageType of the message.
		 *
		 * \return the message type of the message
		 */
		MessageType getMessageType() const;

		/**
		 * Set whether to compress the content of the message or not.
		 *
		 *  <p>
		 *      Note: If compression is enabled with this method but the size of the content of the message is smaller than
		 *      the size of compressed content, then the message will be sent uncompressed to save bandwidth and CPU cycles
		 *      with the decompression on the receiver side.
		 *  </p>
		 *
		 * @param compressed if \c true, the content of the message will be published in ZLIB-compressed format; if \c false
		 *                  no compression format will be used; the default value is \c false.
		 */
		void setCompressed(bool compressed);

		/**
		 * Indicate whether or not the message should be/was compressed.
		 *
		 * @return Return whether or not the message should be/was compressed. If the received message was compressed, the
		 * library automatically decompresses its content without any additional code.
		 */
		bool isCompressed() const;

		/**
		 * Return a string representation of the message.
		 */
		std::string toString() const;

		/**
		 * \brief Destructor.
		 */ 
		virtual ~MigratoryDataMessage();
		
		/// @cond
		int getSeq() const;

		int getEpoch() const;
		/// @endcond
	};
}