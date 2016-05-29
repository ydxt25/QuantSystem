/*
 * \copyright Copyright 2015 All Rights Reserved.
 * \license @{
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @}
 */

#include <glog/logging.h>
#include <sstream>
using std::istringstream;
#include "miniz.c"
#include "quantsystem/common/util/file.h"
#include "quantsystem/compression/compression.h"
namespace quantsystem {
namespace compression {
bool ZipData(const string& zip_path,
             const map<string, string>& filename_and_data) {
  // TODO (Shi)
}

map<string, string> UnzipData(const string& zip_data) {
  // TODO (Shi)
}

string Zip(const string& text_path, bool delete_original) {
  // TODO (Shi)
}

istream* Unzip(const string& file_name) {
  string first_file_data = UnzipToString(file_name);
  istream* is = new istringstream(first_file_data);
  return is;
}

bool ZipFromString(const string& path, const string& data) {
  string zip_path = path + ".zip";
  if (File::Exists(zip_path)) {
    File::Delete(zip_path);
  }
  string base_name = File::Basename(path).as_string();
  mz_bool status = mz_zip_add_mem_to_archive_file_in_place(
      zip_path.c_str(), base_name.c_str(), data.c_str(), data.size(), "", 0 ,
      MZ_BEST_COMPRESSION);
  if (!status) {
    LOG(ERROR) << "mz_zip_add_mem_to_archive_file_in_place failed!";
    return false;
  }
  return true;
}

string UnzipToString(const string& file_name) {
  mz_zip_archive zip_archive;
  mz_bool status;
  memset(&zip_archive, 0, sizeof(zip_archive));
  if (!File::Exists(file_name)) {
    LOG(ERROR) << file_name << "doesnot exist!";
    return "";
  }

  status = mz_zip_reader_init_file(&zip_archive, file_name.c_str(), 0);
  if (!status) {
    LOG(ERROR) << "mz_zip_reader_init_file() failed!";
    return "";
  }
  if ((int)mz_zip_reader_get_num_files(&zip_archive) < 1) {
    LOG(ERROR) << "mz_zip_reader_get_num_files() no file!";
    return "";
  }
  mz_zip_archive_file_stat file_stat;
  if (!mz_zip_reader_file_stat(&zip_archive, 0, &file_stat)) {
    LOG(ERROR) << "mz_zip_reader_file_stat() failed!";
    mz_zip_reader_end(&zip_archive);
    return "";
  }
  std::size_t size;
  char* data = static_cast<char *>(mz_zip_reader_extract_file_to_heap(
      &zip_archive, file_stat.m_filename, &size, 0));
  if (data == NULL) {
    mz_zip_reader_end(&zip_archive);
    LOG(ERROR) << "mz_zip_reader_extract_file_to_heap() fail()!";
    return "";
  }
  string extracted(data, data + size);
  mz_free(data);
  mz_zip_reader_end(&zip_archive);
  return extracted;
}

vector<string> UnzipToFolder(const string& zip_file) {
  // TODO (Shi)
}

void UnZipFiles(const string& zip_file, const string& destination) {
  // TODO (Shi)
}

}  // namespace compression
}  // namespace quantsystem
