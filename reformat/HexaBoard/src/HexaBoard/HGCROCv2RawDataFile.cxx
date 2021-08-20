#include "HexaBoard/HGCROCv2RawDataFile.h"

#include <algorithm>
#include <iomanip>
#include <boost/crc.hpp>

/**
 * The number of readout channels is defined by the hardware
 * construction of a HGC ROC as well as our DAQ readout specs.
 *
 * We have defined a method for keeping track of zero suppression
 * along the DAQ path using a bit-map. Since we aren't using
 * zero suppression currently in the hexactrl-sw DAQ, this ends
 * up being a map of all ones.
 *
 * We have 38 channels that are always read out plus
 *  a header word at the top and a CRC checksum at the bottom
 */
#define N_READOUT_CHANNELS 40

namespace hexareformat {

/**
 * Generate bit masks at compile time.
 *
 * The template input defines how many of
 * the lowest bits will be masked for.
 *
 * Use like:
 *
 *  i & mask<N>::m
 *
 * To mask for the lowest N bits in i.
 *
 * Maximum mask is 63 bits because we are using
 * a 64-bit wide integer and so we can't do
 *  64 << 1
 * without an error being thrown during comiple-time.
 *
 * @tparam N number of lowest-order bits to mask
 */
template <uint64_t N>
struct mask {
  /// one stored in same width as mask
  static const uint64_t one{1};
  /// value of mask
  static const uint64_t m = (one << N) - one;
};

/**
 * @struct CRC
 *
 * The HGC ROC and FPGA use a CRC checksum to double check that the
 * data transfer has been done correctly. Boost has a CRC checksum
 * library that we can use to do this checking here as well.
 *
 * Idea for this helper struct was found on StackOverflow
 * https://stackoverflow.com/a/63237679
 * I've actually simplified it by limiting its use-case to our
 * type of data.
 */
struct CRC {
  // the object from Boost doing the summing
  boost::crc_32_type crc;
  // add a word to the sum
  void operator()(const uint32_t& w) {
    crc.process_bytes(&w, sizeof(w));
  }
  // get the checksum
  auto get() { return crc.checksum(); }
};

void HGCROCv2RawDataFile::Sample::stream(std::ostream& out) const {
  out << "event = " << std::dec << m_event << " "
      << "chip = " << std::dec << m_chip << std::endl;

  out << "first half :";
  for (auto d : m_data0)
    out << "  " << std::hex << std::setfill('0') << std::setw(8) << d;
  out << std::endl;
  out << "second half :";
  for (auto d : m_data1)
    out << "  " << std::hex << std::setfill('0') << std::setw(8) << d;
  out << std::dec << std::endl;
}

bool HGCROCv2RawDataFile::next(framework::Event& event) {
  static bool first_sample{true};

  try {
    std::vector<uint32_t> buffer;
    int current_event{the_sample_.event()};
    while (true) { //break out of loop if sample changes event numbers
      input_archive_ >> the_sample_;
      if (first_sample) {
        // on the first sample, we need to update
        // the current event after reading from the archive
        current_event = the_sample_.event();
        first_sample = false;
      }
      if (the_sample_.event() != current_event)
        break;
      // arbitrary ID values that are meaningless right now
      static const int fpga{42};
      static const int orbit{13};
      static const int roc{7};
      // current word we are using to help create buffer
      static uint64_t word;
    
      CRC fpga_crc;
    
      /** Insert new header here
       * In the DAQ specs, the header is separated into 32-bit words,
       * so we do the same here. Below, I've copied down the structure
       * that I've implemented for ease of reference.
       * The numbers in parentheses are the number of bits.
       *
       * VERSION (4) | FPGA (8) | NLINKS(6) | 0 | TOTAL_RO(12)
       * BX ID (12) | RREQ (10) | OR (10)
       *
       * We need to do some fancy footwork to extract the BX ID from the
       * ROC data because it is not decoded in hexactrl-sw by default.
       */
      word =
          ((1 & mask<4>::m) << 8 + 6 + 1 + 12) +  // 4 bit version number
          (
              (fpga & mask<8>::m)
              << 6 + 1 + 12) +  // 8 bit FPGA ID # (arbitrarily set to 9 here)
          ((2 & mask<6>::m) << 1 + 12) +  // 6 bit number of links ("halves" of ROC)
          ((0 & mask<1>::m) << 1) +       // Reserved 0 bit
          ((2 * N_READOUT_CHANNELS & mask<12>::m)
           << 0);  // 12 bit total number of readout channels
      buffer.push_back(word);
      fpga_crc(word);
    
      unsigned int bx_id{0};
      try {
        unsigned int bx_id_0{(the_sample_.data(0).at(0) >> 12) & 0xfff};
        unsigned int bx_id_1{(the_sample_.data(1).at(0) >> 12) & 0xfff};
        if (bx_id_0 == bx_id_1) bx_id = bx_id_0;
    
        /** Don't worry about this for now...
        if (debug_)
          std::cout << "BX IDs: " << bx_id_0 << " " << bx_id_1 << std::endl;
        else
          throw std::runtime_error("Received two different BX IDs at once.");
          */
      } catch (std::out_of_range&) {
        throw std::runtime_error("Received ROC data without a header.");
      }
    
      /*
      if (bx_id == 0)
        throw std::runtime_error("Unable to deduce BX ID.");
        */
    
      word =
          ((bx_id & mask<12>::m) << 10 + 10) +  // 12 bit bunch ID number
          ((current_event & mask<10>::m)
           << 10) +  // 10 bit read request ID number (what will be an event number)
          ((orbit & mask<10>::m) << 0);  // 10 bit bunch train/orbit counter
      buffer.push_back(word);
      fpga_crc(word);
    
      /** Insert link counters
       * We only have two links in this ROC,
       * so the first half of this word will be zeroes.
       *
       * And then, we aren't doing any zero-suppression,
       * so the number of channels readout will always
       * be the same for both links.
       * The numbers in parentheses are the number of bits.
       *
       * sixteen zeros
       *  | RID ok (1) | CRC ok (1) | LEN1 (6)
       *  | RID ok (1) | CRC ok (1) | LEN0 (6)
       */
      word = ((0 & mask<16>::m) << 16) + ((1 & mask<1>::m) << 6 + 1 + 1 + 6 + 1) +
             ((1 & mask<1>::m) << 6 + 1 + 1 + 6) +
             ((N_READOUT_CHANNELS & mask<6>::m) << 6 + 1 + 1) +
             ((1 & mask<1>::m) << 6 + 1) + ((1 & mask<1>::m) << 6) +
             ((N_READOUT_CHANNELS & mask<6>::m) << 0);
      buffer.push_back(word);
      fpga_crc(word);
    
      /** Go through both of our links
       * In our case, the two "half"s of the ROC are our two links.
       *
       * The hexactrl-sw does not insert the header for each link
       * because there is no zero-suppression or other ROCs to worry about,
       * so we need to insert an additional header here.
       *
       * ROC ID (16) | CRC ok (1) | 00000 | Readout Map [39:32]
       *
       * The numbers in parentheses are the number of bits.
       */
      for (int half{0}; half < 2; half++) {
        CRC link_crc;
        word = ((roc & mask<16>::m)
                << 8 + 5 + 1) +  // 16 bits for ROC ID ((arbitrary choice of 7)
               ((1 & mask<1>::m) << 8 + 5) +  // CRC OK bit
               ((0 & mask<5>::m) << 8) +      // 5 bits of zero reserved
               (mask<8>::m);  // last 8 bits of readout map (everything is being
                              // read out)
        buffer.push_back(word);
        fpga_crc(word);
        link_crc(word);
        // rest of readout map (everything is being readout)
        buffer.push_back(0xFFFFFFFF);
        fpga_crc(0xFFFFFFFF);
        link_crc(0xFFFFFFFF);
        /** header word from ROC
         * 0101 | BX ID (12) | RREQ (6) | OR (3) | HE (3) | 0101
         */
        word = ((0b0101) << 4 + 3 + 3 + 6 + 12) +          // 4 bits 0101
               ((bx_id & mask<12>::m) << 4 + 3 + 3 + 6) +  // 12 bits for BX ID
               ((current_event & mask<6>::m) << 4 + 3 + 3) +  // 6 bits for RREQ (event)
               ((orbit & mask<3>::m)
                << 4 + 3) +               // lower 3 bits of orbit (bunch train)
               ((0 & mask<3>::m) << 4) +  // any Hamming errors present?
               (0b0101);                  // 4 bits 0101
        buffer.push_back(word);
        fpga_crc(word);
        link_crc(word);
    
        // copy in _data_ words from hexactrl-sw
        //  (we already decoded the header to get the BX ID above)
        //  and we drop the four commas that are used by the ROC
        //  to signal the end of a group
        const std::vector<uint32_t>& link_data{the_sample_.data(half)};
        for (auto w_it{link_data.begin()+1}; w_it != link_data.end()-4; w_it++) {
          buffer.push_back(*w_it);
          fpga_crc(*w_it);
          link_crc(*w_it);
        }
    
        // ROC CRC Checksum
        buffer.push_back(link_crc.get());
        fpga_crc(link_crc.get());
      }
    
      /** CRC Checksum computed by FPGA
       * We don't compute one right now, so just an extra word of all ones)
       */
      buffer.push_back(fpga_crc.get());
    }

    // broken out of loop when done with current event samples
    // add the buffer to the event bus
    event.add("HgcrocRawData",buffer);
    return true;
  } catch (boost::archive::archive_exception&) {
    // nothing more from archive to read
    return false;
  }
}

}  // namespace hexareformat