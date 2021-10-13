#include "UMNTestStand/HGCROCv2RawDataFile.h"

#include <iomanip>
#include <bitset>

#include "Reformat/Utility/Mask.h"

namespace reformat {
namespace umnteststand {

bool HGCROCv2RawDataFile::next(framework::Event& event) {
  static uint32_t w;

  /** Decode Bunch Header
   * We have a few words of header material before the actual data.
   * This header material is assumed to be encoded as in Table 3
   * of the DAQ specs.
   *
   * <name> (bits)
   *
   * VERSION (4) | FPGA_ID (8) | NLINKS (6) | 0 | LEN (12)
   * BX ID (12) | RREQ (10) | OR (10)
   * RID ok (1) | CDC ok (1) | LEN3 (6) |
   *  RID ok (1) | CDC ok (1) | LEN2 (6) |
   *  RID ok (1) | CDC ok (1) | LEN1 (6) |
   *  RID ok (1) | CDC ok (1) | LEN0 (6)
   * ... other listing of links ...
   */
  reader_ >> w;
  std::cout << std::bitset<32>(w) << " : ";
  uint32_t version =
      (w >> 12 + 1 + 6 + 8) & reformat::utility::mask<4>;
  std::cout << "version " << version << std::flush;
  uint32_t one{1};
  if (version != one)
    EXCEPTION_RAISE("VersMis", "HcalRawDecoder only knows version 1 of DAQ format.");

  uint32_t fpga = (w >> 12 + 1 + 6) & reformat::utility::mask<8>;
  uint32_t nlinks = (w >> 12 + 1) & reformat::utility::mask<6>;
  uint32_t len = w & reformat::utility::mask<12>;

  std::cout << ", fpga: " << fpga << ", nlinks: " << nlinks
            << ", len: " << len << std::endl;

  std::vector<uint32_t> buffer(len+1);
  buffer[0] = w;
  for (int i{1}; i < len+1; i++) {
    reader_ >> buffer[i];
    if (!reader_) {
      EXCEPTION_RAISE("Malform","Expected a word when there wasn't one.");
    }
  }

  // broken out of loop when done because either
  //    reached EOF of archive OR
  //    new event ID has been read in
  // add the buffer to the event bus
  event.add(buffer_name_, buffer);

  // we are done if reader is in an EoF state
  return !reader_;
}

} 
}  // namespace reformat

DECLARE_RAW_DATA_FILE(reformat::umnteststand, HGCROCv2RawDataFile)
