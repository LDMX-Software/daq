#ifndef REFORMATBASE_RAWDATAFILE_H_
#define REFORMATBASE_RAWDATAFILE_H_

#include "Framework/Event.h"

namespace reformatbase {

/**
 * @class RawDataFile
 *
 * A single file of raw data. 
 */
class RawDataFile {
 public:
  /**
   * Constructor of a raw data file with a filename
   */
  RawDataFile(const std::string& filename) {}

  /// virtual and default destructor
  virtual ~RawDataFile() = default;

  /**
   * Save the next event from this data file into the passed bus.
   *
   * @note next will continue to be called until all raw data files
   * return false. This means your implementation of this function needs
   * to continue to return false after it is done processing data.
   *
   * @return true if we have more data, false if we are done
   */
  virtual bool next(framework::Event& event) = 0;
};  // RawDataFile

}  // reformatbase

#endif  // REFORMATBASE_RAWDATAFILE_H_
