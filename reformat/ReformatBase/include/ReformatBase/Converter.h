#ifndef REFORMATBASE_CONVERTER_H_
#define REFORMATBASE_CONVERTER_H_

#include "Framework/Exception/Exception.h"
#include "ReformatBase/RawDataFile.h"

namespace reformatbase {

/**
 * Class to convert the passed raw data files into a
 * single Framework EventFile.
 */
class Converter {
 public:
  /// insert a new (default constructed) cahnnel
  template <typename FileType>
  void insert(const std::string& file_name, const std::string& filename) {
    if (data_files_.find(file_name) != data_files_.end())
      EXCEPTION_RAISE("RepeatFile", "File '" + file_name +
                                           "' has already been inserted.");

    data_files_[file_name] = std::make_unique<FileType>(filename);
  }

  /// get a specific file for pre/post processing
  template <typename FileType>
  FileType& get(const std::string& file_name) {
    try {
      return dynamic_cast<FileType&>(*data_files_.at(file_name));
    } catch (std::bad_cast&) {
      EXCEPTION_RAISE("FileType",
                      "File '" + file_name +
                          "' has a different type than the one passed.");
    } catch (std::out_of_range&) {
      EXCEPTION_RAISE("FileDef",
                      "File '" + file_name +
                          "' has not been inserted into the converter.");
    }
  }

  /// actual run conversion
  void convert(const std::string& output_filename, int run, int start_event = 0, const std::string& pass = "raw");

 private:
  /// set of data files and their associated names
  std::map<std::string, std::unique_ptr<RawDataFile>> data_files_;

};  // Converter

}  // namespace reformatbase

#endif  // REFORMATBASE_CONVERTER_H_
