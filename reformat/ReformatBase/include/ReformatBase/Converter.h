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
  /// un-interesting default constructor
  Converter() = default;
  /// un-interested default destructor
  ~Converter() = default;

  /**
   * Configure our converter based off the configuration parameters
   * decoded from the passed python script
   */
  void configure(const framework::config::Parameters& configuration);

  /// actual run conversion
  void convert();

 private:
  /// set of data files and their associated names
  std::map<std::string, std::unique_ptr<RawDataFile>> data_files_;
  /// pass name to use for output event tree
  std::string pass_;
  /// output file name to write data to
  std::string output_filename_;
  /// run number to use for output event tree
  int run_;
  /// starting event number
  int start_event_;

};  // Converter

}  // namespace reformatbase

#endif  // REFORMATBASE_CONVERTER_H_
