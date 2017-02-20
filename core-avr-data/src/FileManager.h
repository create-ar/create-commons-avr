#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Streamer.h"
#include "File.h"

#include <Tuple.h>
#include <LinkedList.h>
#include <Logger.h>
#include <stdio.h>

#define IDENTIFIER_LENGTH 4

static char VALID_IDENTIFIER[IDENTIFIER_LENGTH] = {'O', 'F', 'F', 'H'};

/**
 * @brief      Configuration object fo initializing FileManager.
 */
struct FileManagerConfig
{
	/**
	 * Total size, in bytes. Defaults to 2MB.
	 */
	int totalBytes = 2097152;
};

/**
 * @brief      Header stored at beginning of stream.
 */
struct FileManagerHeader
{
	/**
	 * Identifier lets us know if the stream has a file manager header at all.
	 */
	char identifier[IDENTIFIER_LENGTH];

	/**
	 * FileManager header version.
	 */
	short version;

	/**
	 * Total number of files stored.
	 */
	short numFiles;

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
#define FILEMANAGER_HEADER_SIZE sizeof(FileManagerHeader)

/**
 * @brief      The FileManager class exposes a fixed-size file manipulation API, based on URI.
 */
class FileManager
{
	private:
		/**
		 * Logger.
		 */
		Logger* _logger;

		/**
		 * The FileManager is the owner of the EEPROMStream abstraction.
		 */
		Streamer* _stream;

		/**
		 * Header information for file system.
		 */
		FileManagerHeader _header;

	public:
		/**
		 * @brief      Constructor.
		 */
		FileManager(Streamer* stream);

		/**
		 * @brief      Destructor.
		 */
		~FileManager();

		/**
		 * @brief      Attempts to load existing filesystem.
		 *
		 * @return     Returns true if everything is good to go.
		 */
		bool load(FileManagerConfig config);

		/**
		 * @brief      Initializes a new filesystem.
		 *
		 * @return     Returns true if everything is good to go.
		 */
		bool init(FileManagerConfig config);

		/**
		 * @brief      Creates a File of a specific size, linked to a URI.
		 *
		 * @param[in]  uri   The uri this File can be addressed at.
		 * @param[in]  size  The size of the file.
		 *
		 * @return     If there was room for the file and it was successfully created, returns the File. If not, nullptr.
		 */
		File* create(const char* uri, const int size);

		/**
		 * @brief      Retrieves a file by uri.
		 *
		 * @param[in]  uri   The uri to retrieve the file with.
		 *
		 * @return     If the File was found, the file. Otherwise, nullptr.
		 */
		File* get(const char* uri);

		/**
		 * @brief      Writes the file. This is the equivalent to calling File::flush().
		 *
		 * @param[in]  file  The file to write to disk.
		 *
		 * @return     Returns true if the File was successfully saved.
		 */
		bool set(File* file);
};

#endif