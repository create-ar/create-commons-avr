#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Stream.h"
#include "File.h"
#include <Converter.h>
#include <Tuple.h>
#include <LinkedList.h>
#include <Logger.h>

/**
 * Number of bytes in header.
 */
#define FILEMANAGER_HEADER_SIZE 12

/**
 * @brief      Configuration object fo initializing FileManager.
 */
struct FileManagerConfig
{
	/**
	 * Specifies the data out pin, from the EEPROM.
	 */
	int pinDataOut = 11;

	/**
	 * Specifies the data in pin, from the EEPROM.
	 */
	int pinDataIn = 12;

	/**
	 * Specifies the pin that controls the SPI clock.
	 */
	int pinSpiClock = 13;

	/**
	 * Specifies the pin for slave selection.
	 */
	int pinSlaveSelect = 10;

	/**
	 * Number of pages in memory.
	 */
	int numPages = 128;

	/**
	 * Number of bytes per page of memory.
	 */
	int bytesPerPage = 128;
};

/**
 * @brief      Header stored at beginning of EEPROM.
 */
class FileManagerHeader
{
	#define IDENTIFIER_LENGTH 4

public:
	/**
	 * Identifier lets us know if the EEPROM has a file manager header at all.
	 */
	char identifier[IDENTIFIER_LENGTH] = {'O', 'F', 'F', 'H'};

	/**
	 * FileManager header version.
	 */
	short version;

	/**
	 * Total number of files.
	 */
	short numFiles;

	/**
	 * Bytes used by all files, not including this header.
	 */
	int totalBytes;

	/**
	 * @brief      Reads header in.
	 *
	 * @param      stream  The stream to read with.
	 *
	 * @return     True if the header was read successfully.
	 */
	bool read(Stream* stream)
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

		// read in total bytes used
		IntUnion intConverter;
		memcpy(intConverter.charValue, buffer + 4, 4);
		totalBytes = intConverter.intValue;

		return true;
	}

	/**
	 * @brief      Writes header to stream.
	 *
	 * @param[in]  stream  The stream to write with.
	 *
	 * @return     Returns true if successful.
	 */
	bool write(Stream* stream)
	{
		// prepare buffer
		char buffer[FILEMANAGER_HEADER_SIZE];

		// copy in identifier
		memcpy(buffer, identifier, IDENTIFIER_LENGTH);

		int index = IDENTIFIER_LENGTH;

		ShortUnion shortConverter;
		IntUnion intConverter;

		shortConverter.shortValue = version;
		memcpy(buffer + index, shortConverter.charValue, 2);
		index += 2;

		shortConverter.shortValue = numFiles;
		memcpy(buffer + index, shortConverter.charValue, 2);
		index += 2;

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
		Stream* _stream;

		/**
		 * Tracks files.
		 */
		LinkedList<Tuple<char*, File>> _files;

		/**
		 * Header information for file system.
		 */
		FileManagerHeader _header;

		/**
		 * Total size of filesystem. Calculated value from config.
		 */
		int _totalSize;

	public:
		/**
		 * @brief      Constructor.
		 */
		FileManager(Stream* stream);

		/**
		 * @brief      Destructor.
		 */
		~FileManager();

		/**
		 * @brief      Initializes the system.
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
		bool set(const File* file);
};

#endif