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

#ifndef QUANTSYSTEM_COMMON_COMPRESSION_H_
#define QUANTSYSTEM_COMMON_COMPRESSION_H_

#include <iostream>  // NOLINT
using std::istream;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::map;

namespace quantsystem {
/**
 * Compression class manages the opening and extraction of compressed
 * files (zip, tar, tar.gz).
 *
 * Data library is stored in zip format locally on the hard drive.
 */
namespace compression {
/**
 * Create a zip file of the supplied file names and string data source.
 * @param zip_path Output location to save the file
 * @param filename_and_data File names and data in a dictionary format
 * @return True on successfully creating the zip file
 */
bool ZipData(const string& zip_path,
             const map<string, string>& filename_and_data);

/**
 * Uncompress zip data byte array into a dictionary string array
 * of filename-contents.
 * @param zip_data String data of zip compressed information
 * @return Uncompressed dictionary string-sting of files in the zip
 */
map<string, string> UnzipData(const string& zip_data);

/**
 * Compress a given file and delete the original file.
 * Automatically rename the file to name.zip.
 * @param text_path Path of the original file
 * @param delete_original Boolean flag to delete the original file
 * after completion
 * @return String path for the new zip file
*/
string Zip(const string& text_path, bool delete_original = true);

/**
 * Unzip a local file and return its contents via istream.
 * @param file_name Location of the original zip file.
 * @return Istream of the first file contents in the zip file
 */
istream* Unzip(const string& file_name);

/**
 * Create the file_name with the data and zip it into the file_name.zip.
 * @param file_name Location of the create file
 * @param data Content of the file
 */
bool ZipFromString(const string& path, const string& data);

/**
 * Unzip a local file and return its contents as string.
 * @param file_name Location of the original zip file.
 * @return string of the first file contents in the zip file
 */
string UnzipToString(const string& file_name);

/**
 * Unzip a local file to the same the folder of zip file.
 * @param zip_file Location of the zip
 * @return Vector of unzipped file names
 */
vector<string> UnzipToFolder(const string& zip_file);

/**
 * Extracts all file from a Tar archive and copies them to a destination folder.
 * @param zip_file Location of the zip
 * @param destination The destination folder to extract the file to
 */
void UnZipFiles(const string& zip_file, const string& destination);

}  // namespace compression
}  // namespace quantsystem
#endif  // QUANTSYSTEM_COMMON_COMPRESSION_H_
