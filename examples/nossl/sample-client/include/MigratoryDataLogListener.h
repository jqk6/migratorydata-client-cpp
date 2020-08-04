#ifndef _MigratoryDataLogListener_h_included_
#define _MigratoryDataLogListener_h_included_

#include "MigratoryDataLogLevel.h"

#include <string>

namespace migratorydata {

    /**
    *
    * The implementation of this interface will handle the log messages produced by the library.
    *
    * Use the API method \link MigratoryDataClient.setLogListener() \endlink to register your log listener implementation.
    */
	class MigratoryDataLogListener {

	public :

    	/**
    	 * \brief This method handles the logs received from the API.
    	 *
    	 * \param log A string representing a log message. 
    	 */
		virtual void onLog(std::string& log, MigratoryDataLogLevel logLevel) = 0;
	};
	
}

#endif // _MigratoryDataLogListener_h_included_

