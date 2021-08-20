#ifndef REFORMAT_CORE_RAWDATACHANNEL_H_
#define REFORMAT_CORE_RAWDATACHANNEL_H_

#include "Framework/Event.h"

namespace reformat {
namespace core {

/**
 * @class RawDataChannel
 *
 * A single channel of raw data. One raw data channel is translated
 * into one event bus object.
 */
class RawDataChannel {
 public:
  /**
   * Save the next event from this data channel into the passed bus.
   *
   * @return true if we have more data, false if we are done
   */
  virtual bool next(framework::Event& event) = 0;
};  // RawDataChannel

}  // core
}  // reformat

#endif  // REFORMAT_CORE_RAWDATACHANNEL_H_
