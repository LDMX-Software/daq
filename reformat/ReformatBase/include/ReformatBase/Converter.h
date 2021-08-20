#ifndef REFORMAT_CORE_CONVERTER_H_
#define REFORMAT_CORE_CONVERTER_H_

#include "core/RawDataChannel.h"

namespace reformat {
namespace core {

/**
 * Class to convert the passed raw data channels into a
 * single Framework EventFile.
 */
class Converter {
 public:
  /// insert a new (default constructed) cahnnel
  template <typename ChannelType>
  bool insert(const std::string& channel_name);

  /// get a specific channel for pre/post processing
  template <typename ChannelType>
  ChannelType& get(const std::string& channel_name);

  /// actual run conversion
  void convert(int run, int start_event = 0, const std::string& pass = "raw");

 private:
  /// set of data channels and their associated names
  std::map<std::string, std::unique_ptr<RawDataChannel>> data_channels_;

};  // Converter

}  // namespace core
}  // namespace reformat

#endif  // REFORMAT_CORE_CONVERTER_H_
