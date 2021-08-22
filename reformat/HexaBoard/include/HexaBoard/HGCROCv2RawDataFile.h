#ifndef PACKING_HEXAREFORMAT_HGCROCV2RAWDATAFILE
#define PACKING_HEXAREFORMAT_HGCROCV2RAWDATAFILE

#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <deque>
#include <fstream>
#include <iostream>

#include "Reformat/RawDataFile.h"

/**
 * The HGCROC Data buffer size is fixed by the construction of the hardware.
 * 36 channels + 2 common mode gathered together + 1 calib + 1 header
 *  + 4 iddles in trailer per half
 */
#define HGCROC_DATA_BUF_SIZE 43

/**
 * @namespace hexareformat
 *
 * Helper classes for interfacing with raw data.
 * The code in this namespace is not expected to be around long.
 */
namespace hexareformat {

/**
 * This raw data file wraps the Boost.Serialization output
 * of the hexactrl-sw being used to test the HGC ROC board
 * and its connection to a hexa-board in CMS.
 */
class HGCROCv2RawDataFile : public reformat::RawDataFile {
 public:
  /// open up boost binary archive from input file
  HGCROCv2RawDataFile(const framework::config::Parameters& ps)
      : input_stream_{ps.getParameter<std::string>("input_file")},
        input_archive_{input_stream_},
        reformat::RawDataFile(ps) {}
 
  /// default destructor, closes up boost archive and input stream
  ~HGCROCv2RawDataFile() = default;

  /// read in the data for the next event and put it on the bus
  bool next(framework::Event& event);

 private:
  /// the input file stream
  std::ifstream input_stream_;
  /// the archive we are reading in
  boost::archive::binary_iarchive input_archive_;
  /**
   * This class is copied almost exactly from
   * the hexactrl-sw borrowed from CMS. I have deleted the parts
   * of it that are used to write the raw data coming from the HGC ROC
   * in-order-to cleanup the code.
   *
   * Each instance of this class represents an individual sample
   * from each channel on both halves of the ROC.
   */
  class Sample {
   public:
    Sample() {}

    int event() const { return m_event; }

    int chip() const { return m_chip; }

    const std::vector<uint32_t>& data(int chiphalf) const {
      return chiphalf == 0 ? m_data0 : m_data1;
    }

    /**
     * Stream the sample class to an output stream
     *
     * Helpful for debugging
     */
    void stream(std::ostream& out) const;

    /// output stream operator
    friend std::ostream& operator<<(std::ostream& out,
                                    const HGCROCv2RawDataFile::Sample& h) {
      h.stream(out);
      return out;
    }

   private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar& m_event;
      ar& m_chip;
      ar& m_data0;
      ar& m_data1;
    }

   private:
    int m_event{-1};
    int m_chip;
    std::vector<uint32_t> m_data0;
    std::vector<uint32_t> m_data1;
  } the_sample_;  // Sample

};  // HGCROCv2RawDataFile

}  // namespace hexareformat

#endif
