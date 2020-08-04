#ifndef _MigratoryDataLogLevel_h_included_
#define _MigratoryDataLogLevel_h_included_

#include <string>

namespace migratorydata
{

	/**
	 * This class enumerates the MigratoryData logging levels.
	 *
	 * The available log levels ordered by verbosity are:
	 * <ul>
	 *  <li>LOG_ERROR (less verbose)</li>
	 *  <li>LOG_INFO</li>
	 *  <li>LOG_DEBUG</li>
	 *  <li>LOG_TRACE (most verbose)</li>
	 * </ul>
	 */
	typedef enum {

		/**
		 * The <code>LOG_ERROR</code> level turns on the error logs of the API.
		 */
		LOG_ERROR,

		/**
		 * The <code>LOG_INFO</code> level turns on the info, warning, and error logs of the API.
		 */
		LOG_INFO,

		/**
		 * The <code>LOG_DEBUG</code> level turns on the debug, info, warning, and error logs of the API.
		 */
		LOG_DEBUG,

		/**
		 * The <code>LOG_TRACE</code> level turns on all the logs of the API.
		 */
		LOG_TRACE

	} MigratoryDataLogLevel;

}

#endif // _MigratoryDataGlobals_h_included_
