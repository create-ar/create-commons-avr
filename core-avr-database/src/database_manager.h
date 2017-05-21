#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "AvrStream.h"
#include "Database.h"

#include <Tuple.h>
#include <LinkedList.h>
#include <Logger.h>
#include <stdio.h>

#define IDENTIFIER_LENGTH 4

/**
 * @brief      Configuration object fo initializing DatabaseManager.
 */
struct DatabaseManagerConfig
{
	/**
	 * Total size, in bytes. Defaults to 2MB.
	 */
	int totalBytes = 2097152;
};

/**
 * @brief      Header stored at beginning of stream.
 */
struct DatabaseManagerHeader
{
	/**
	 * Identifier lets us know if the stream has a file manager header at all.
	 */
	char identifier[IDENTIFIER_LENGTH];

	/**
	 * DatabaseManager header version.
	 */
	short version;

	/**
	 * Total number of files stored.
	 */
	short numDatabases;

	/**
	 * Total number of bytes being used by file system, excluding the header.
	 */
	int usedBytes;

	/**
	 * Total number of bytes this file system can use, excluding the header.
	 */
	int totalBytes;
};

/**
 * Number of bytes in header.
 */
#define DATABASEMANAGER_HEADER_SIZE sizeof(DatabaseManagerHeader)

/**
 * @brief      The DatabaseManager class exposes a fixed-size file manipulation API, based on URI.
 */
class DatabaseManager
{
	private:
		/**
		 * Logger.
		 */
		Logger* logger_;

		/**
		 * Clock implementation to use.
		 */
		AvrClock* clock_;

		/**
		 * The DatabaseManager is the owner of the EEPROMStream abstraction.
		 */
		AvrStream* stream_;

		/**
		 * Header information for file system.
		 */
		DatabaseManagerHeader header_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param      clock   The clock implementation to use.
		 * @param      stream  The stream to read/write data with.
		 */
		DatabaseManager(
			AvrClock* clock,
			AvrStream* stream);

		/**
		 * @brief      Destructor.
		 */
		~DatabaseManager();

		/**
		 * @brief      Attempts to load existing filesystem.
		 *
		 * @return     Returns true if everything is good to go.
		 */
		bool load(DatabaseManagerConfig config);

		/**
		 * @brief      Initializes a new filesystem.
		 *
		 * @return     Returns true if everything is good to go.
		 */
		bool init(DatabaseManagerConfig config);

		/**
		 * @brief      Creates a Database of a specific size, linked to a URI.
		 *
		 * @param[in]  uri   The uri this Database can be addressed at.
		 * @param[in]  uri   The number of values that should be stored in a
		 * single record.
		 * @param[in]  size  The size of the file.
		 *
		 * @return     If there was room for the file and it was successfully created, returns the Database. If not, nullptr.
		 */
		Database* create(
			const char* uri,
			const int size,
			const char valuesPerRecord);

		/**
		 * @brief      Retrieves a file by uri.
		 *
		 * @param[in]  uri   The uri to retrieve the file with.
		 *
		 * @return     If the Database was found, the file. Otherwise, nullptr.
		 */
		Database* get(const char* uri);

		/**
		 * @brief      Writes the file. This is the equivalent to calling Database::flush().
		 *
		 * @param[in]  file  The file to write to disk.
		 *
		 * @return     Returns true if the Database was successfully saved.
		 */
		bool set(Database* file);
};

#endif