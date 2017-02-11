#include "EEPROMStream.h"
#include "File.h"

/**
 * @brief      The FileManager class exposes a fixed-size file manipulation API, based on URI.
 */
class FileManager
{
	private:
		/**
		 * The FileManager is the owner of the EEPROMStream abstraction.
		 */
		EEPROMStream _stream;

	public:
		/**
		 * @brief      Constructor.
		 */
		FileManager();

		/**
		 * @brief      Initializes the system.
		 *
		 * @return     Returns true if everything is good to go.
		 */
		bool init();

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