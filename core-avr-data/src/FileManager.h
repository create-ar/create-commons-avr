#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Streamer.h"
#include "File.h"
#include <Converter.h>
#include <Tuple.h>
#include <LinkedList.h>
#include <Logger.h>

/**
 * Number of bytes in header.
 */
#define FILEMANAGER_HEADER_SIZE 16

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
class FileManagerHeader
{
	#define IDENTIFIER_LENGTH 4

public:
	/**
	 * Identifier lets us know if the stream has a file manager header at all.
	 */
	char identifier[IDENTIFIER_LENGTH] = {'O', 'F', 'F', 'H'};

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

	/**
	 * TODO: GET RID OF UNIONS.
	 * 
	 * @brief      Reads header in.
	 *
	 * @param      stream  The stream to read with.
	 *
	 * @return     True if the header was read successfully.
	 */
	bool read(Streamer* stream)
	{
		char buffer[FILEMANAGER_HEADER_SIZE];

		// read header
		if (FILEMANAGER_HEADER_SIZE != stream->read(buffer, 0, FILEMANAGER_HEADER_SIZE))
		{
			return false;
		}

		// look for matching identifier
		for (int i = 0; i < IDENTIFIER_LENGTH; i++)
		{
			if (buffer[i] != identifier[i])
			{
				return false;
			}
		}
		
		// read in version
		ShortUnion converter;
		converter.charValue[0] = buffer[0];
		converter.charValue[1] = buffer[1];
		version = converter.shortValue;

		// read in number of files
		converter.charValue[0] = buffer[2];
		converter.charValue[1] = buffer[3];
		numFiles = converter.shortValue;

		// read in used/total bytes
		IntUnion intConverter;
		memcpy(intConverter.charValue, buffer + 4, 4);
		usedBytes = intConverter.intValue;

		memcpy(intConverter.charValue, buffer + 8, 4);
		totalBytes = intConverter.intValue;

		return true;
	}

	/**
	 * TODO: GET RID OF UNIONS.
	 * 
	 * @brief      Writes header to stream.
	 *
	 * @param[in]  stream  The stream to write with.
	 *
	 * @return     Returns true if successful.
	 */
	bool write(Streamer* stream)
	{
		// prepare buffer
		char buffer[FILEMANAGER_HEADER_SIZE];

		// id
		memcpy(buffer, identifier, IDENTIFIER_LENGTH);
		int index = IDENTIFIER_LENGTH;

		ShortUnion shortConverter;
		IntUnion intConverter;

		// version
		shortConverter.shortValue = version;
		memcpy(buffer + index, shortConverter.charValue, 2);
		index += 2;

		// numFiles
		shortConverter.shortValue = numFiles;
		memcpy(buffer + index, shortConverter.charValue, 2);
		index += 2;

		// used
		intConverter.intValue = usedBytes;
		memcpy(buffer + index, intConverter.charValue, 4);
		index += 4;

		// total
		intConverter.intValue = totalBytes;
		memcpy(buffer + index, intConverter.charValue, 4);

		return stream->write(buffer, 0, FILEMANAGER_HEADER_SIZE);
	}
};

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