#ifndef PACKING_HEXAREFORMAT_HGCROCV2RAWDATA
#define PACKING_HEXAREFORMAT_HGCROCV2RAWDATA

#include <iostream>
#include <deque>
#include <fstream>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/vector.hpp>

#include "ReformatBase/RawDataFile.h"

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
 * This HGCROCv2RawData class is copied almost exactly from 
 * the hexactrl-sw borrowed from CMS. I have deleted the parts
 * of it that are used to write the raw data coming from the HGC ROC
 * in-order-to cleanup the code.
 *
 * Each instance of this class represents an individual sample 
 * from each channel on both halves of the ROC.
 */
class HGCROCv2RawDataSample {
 public:
  HGCROCv2RawDataSample() {}

  int event() const { return m_event; }

  int chip() const { return m_chip; }

  const std::vector<uint32_t>& data(int chiphalf) const {
    return chiphalf == 0 ? m_data0 : m_data1;
  }

  friend std::ostream& operator<<(std::ostream& out, const HGCROCv2RawDataSample& h);

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
};  // HGCROCv2RawDataSample

/**
 * This is the full raw data channel.
 */
class HGCROCv2RawData : public reformatbase::RawDataFile {
  public:
   HGCROCv2RawData(const std::string& input_file) : input_stream_{input_file}, input_archive_{input_stream_}, reformatbase::RawDataFile(input_file) {}
   ~HGCROCv2RawData() = default;

   /// read in the data for the next event and put it on the bus
   bool next(framework::Event& event);

  private:
   /// the input file stream
   std::ifstream input_stream_;
   /// the archive we are reading in
   boost::archive::binary_iarchive input_archive_;
   /// the sample we are using for reading
   HGCROCv2RawDataSample the_sample_;

};  // HGCROCv2RawData

}  // hexareformat

#endif
