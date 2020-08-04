#pragma once
namespace migratorydata {

	/**
	 * Return a string representation of the message.
	 */
	enum class MessageType {

		/**
		 * the message from the server is snapshot type
		 */
		SNAPSHOT = 1,

		/**
		 * the message from the server is update type
		 */
		UPDATE,

		/**
		 * the message from the server is recovered type
		 */
		RECOVERED,

		/**
		 * the message from the server is historical type
		 */
		HISTORICAL

	};

}