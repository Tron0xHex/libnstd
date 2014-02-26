
#pragma once

#include <nstd/String.h>

class File
{
public:
  enum Flags
  {
    readFlag = 0x0001,
    writeFlag = 0x0002,
    appendFlag = 0x0004,
  };

  struct Times
  {
    timestamp_t writeTime;
    timestamp_t accessTime;
    timestamp_t creationTime;
  };

  File();
  ~File();

  bool_t open(const String& file, uint_t flags = readFlag);
  void_t close();
  bool_t isOpen() const;

  /**
  * Read a data block from the file at the current read position.
  *
  * The file has to be opened with Flags::readFlag. If successful, the read position changes to after 
  * the block that was read.
  *
  * @param  [in] buffer A buffer where the data should be stored. It has to be large 
  *                     enough to hold \c length bytes.
  * @param  [in] length The count of the bytes to read.
  *
  * @return The amount of bytes that was read. This could be equal 0 or less than \c length when the end of the
  *         file was reached. In case of an error -1 is returned.
  */
  ssize_t read(void_t* buffer, size_t length);

  ssize_t write(const void_t* buffer, size_t length);

  bool_t write(const String& data);

  bool_t flush();

  static String dirname(const String& file);
  static String basename(const String& file, const String& extension = String());
  static String extension(const String& file);
  static String simplifyPath(const String& path);
  static bool_t isAbsolutePath(const String& path);

  static bool_t times(const String& file, Times& time);

  static bool_t exists(const String& file);
  static bool_t unlink(const String& file);

private:
  void_t* fp;

  File(const File&);
  File& operator=(const File&);
};
