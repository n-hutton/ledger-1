//------------------------------------------------------------------------------
//
//   Copyright 2018-2020 Fetch.AI Limited
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.
//
//------------------------------------------------------------------------------

#include "storage/single_object_store.hpp"
#include "storage/storage_exception.hpp"

static constexpr char const *LOGGING_NAME = "SingleObjectStore";

namespace fetch {

namespace platform {
enum
{
  LITTLE_ENDIAN_MAGIC = 2337
};
}

namespace storage {

struct FileMetadata
{
  uint16_t magic;
  uint16_t version;
  uint64_t object_size;

  bool Valid() const
  {
    return magic == platform::LITTLE_ENDIAN_MAGIC;
  }

  void Initialise(uint16_t version_to_set)
  {
    magic   = platform::LITTLE_ENDIAN_MAGIC;
    version = version_to_set;
  }
};

bool SingleObjectStore::Load(std::string const &file_name)
{
  file_name_ = file_name;

  file_handle_.open(file_name, std::fstream::in | std::fstream::out | std::fstream::binary);

  // If does not exist
  if (!file_handle_)
  {
    file_handle_.open(file_name, std::fstream::in | std::fstream::out | std::fstream::binary |
                                     std::fstream::trunc);
  }

  if (!(file_handle_ && file_handle_.is_open()))
  {
    FETCH_LOG_WARN(LOGGING_NAME, "Failed to open: ", file_name);
    return false;
  }

  file_handle_.seekg(0, std::fstream::end);
  uint64_t file_size = static_cast<uint64_t>(file_handle_.tellg());

  // To remain POD, this must be initialized rather than constructed
  FileMetadata meta{};
  meta.Initialise(version_);
  static_assert(std::is_pod<FileMetadata>::value, "FileMetadata must be POD");

  // Check it is either empty or non-corrupted
  if (file_size == 0)
  {
    // Write metadata to new file
    file_handle_.write(reinterpret_cast<char const *>(&meta), sizeof(meta));
    file_handle_.flush();
    return true;
  }

  if (file_size < sizeof(meta))
  {
    FETCH_LOG_WARN(
        LOGGING_NAME,
        "Attempted to open a file that had nonzero size but less than expected metadata");
    return false;
  }

  // Read the metadata
  file_handle_.seekg(0, std::fstream::beg);
  file_handle_.read(reinterpret_cast<char *>(&meta), sizeof(meta));

  if (meta.version != version_)
  {
    FETCH_LOG_WARN(LOGGING_NAME, "Found version: ", meta.version, " when expecting: ", version_);
    return false;
  }

  if (!meta.Valid())
  {
    FETCH_LOG_INFO(LOGGING_NAME, "After opening, file metadata was invalid!");
    return false;
  }

  if ((meta.object_size + sizeof(meta)) != file_size)
  {
    FETCH_LOG_ERROR(LOGGING_NAME,
                    "mismatch in file sizes. Expected: ", (meta.object_size + sizeof(meta)),
                    " got: ", file_size, " note: metadata is ", sizeof(meta), " while filesize is ",
                    meta.object_size);
    return false;
  }

  return true;
}

void SingleObjectStore::GetRaw(ByteArray &data) const
{
  FileMetadata meta{};

  if (!file_handle_)
  {
    throw StorageException("Attempted to Get before loading");
  }

  file_handle_.seekg(0, std::fstream::beg);
  file_handle_.read(reinterpret_cast<char *>(&meta), sizeof(meta));

  if (meta.object_size == 0)
  {
    FETCH_LOG_WARN(LOGGING_NAME, "Attempted to get an object of size 0");
    throw StorageException("Attempt to get zero length object is invalid");
    return;
  }

  data.Resize(meta.object_size);

  file_handle_.read(data.char_pointer(), static_cast<int64_t>(meta.object_size));

  if (!file_handle_)
  {
    FETCH_LOG_ERROR(LOGGING_NAME, "Only able to read ", file_handle_.gcount(), " when expecting ",
                    meta.object_size);
    throw StorageException("After reading from file, the stream could not provide enough data");
  }
}

void SingleObjectStore::SetRaw(ByteArray &data)
{
  FileMetadata meta{};
  meta.Initialise(version_);
  meta.object_size = data.size();

  if (!file_handle_)
  {
    throw StorageException("Attempted to Set before loading");
  }

  // Wipe the file since there is no easy way to truncate/resize
  Clear();

  file_handle_.seekg(0, std::fstream::beg);
  file_handle_.write(reinterpret_cast<char *>(&meta), sizeof(meta));
  file_handle_.write(data.char_pointer(), static_cast<int64_t>(data.size()));
  file_handle_.flush();
}

SingleObjectStore::~SingleObjectStore()
{
  if (file_handle_.is_open())
  {
    file_handle_.close();
  }
}

void SingleObjectStore::Close()
{
  file_handle_.close();
}

uint16_t SingleObjectStore::Version() const
{
  return version_;
}

void SingleObjectStore::Clear()
{
  file_handle_.close();
  file_handle_.open(file_name_, std::fstream::in | std::fstream::out | std::fstream::binary |
                                    std::fstream::trunc);
}

}  // namespace storage
}  // namespace fetch