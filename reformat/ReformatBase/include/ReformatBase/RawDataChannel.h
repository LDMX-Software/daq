#ifndef REFORMATBASE_RAWDATACHANNEL_H_
#define REFORMATBASE_RAWDATACHANNEL_H_

#include "Framework/Event.h"

namespace reformatbase {

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
   * @note next will continue to be called until all raw data channels
   * return false. This means your implementation of this function needs
   * to continue to return false after it is done processing data.
   *
   * @return true if we have more data, false if we are done
   */
  virtual bool next(framework::Event& event) = 0;
};  // RawDataChannel

}  // reformatbase

#endif  // REFORMATBASE_RAWDATACHANNEL_H_
