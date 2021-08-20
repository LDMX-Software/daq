#ifndef REFORMATBASE_CONVERTER_H_
#define REFORMATBASE_CONVERTER_H_

#include "Framework/Exception/Exception.h"
#include "ReformatBase/RawDataChannel.h"

namespace reformatbase {

/**
 * Class to convert the passed raw data channels into a
 * single Framework EventFile.
 */
class Converter {
 public:
  /// insert a new (default constructed) cahnnel
  template <typename ChannelType>
  void insert(const std::string& channel_name) {
    if (data_channels_.find(channel_name) != data_channels_.end())
      EXCEPTION_RAISE("RepeatChannel", "Channel '" + channel_name +
                                           "' has already been inserted.");
    data_channels_[channel_name] = std::make_unique<ChannelType>();
  }

  /// get a specific channel for pre/post processing
  template <typename ChannelType>
  ChannelType& get(const std::string& channel_name) {
    try {
      return dynamic_cast<ChannelType&>(*data_channels_.at(channel_name));
    } catch (std::bad_cast&) {
      EXCEPTION_RAISE("ChannelType",
                      "Channel '" + channel_name +
                          "' has a different type than the one passed.");
    } catch (std::out_of_range&) {
      EXCEPTION_RAISE("ChannelDef",
                      "Channel '" + channel_name +
                          "' has not been inserted into the converter.");
    }
  }

  /// actual run conversion
  void convert(const std::string& output_filename, int run, int start_event = 0, const std::string& pass = "raw");

 private:
  /// set of data channels and their associated names
  std::map<std::string, std::unique_ptr<RawDataChannel>> data_channels_;

};  // Converter

}  // namespace reformatbase

#endif  // REFORMATBASE_CONVERTER_H_
