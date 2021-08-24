#include <rogue/interfaces/stream/Frame.h>
#include <rogue/interfaces/stream/FrameIterator.h>
#include <rogue/utilities/fileio/StreamWriter.h>

namespace reformat {
namespace ldmx_rogue {

class EventWriter : public rogue::utilities::fileio::StreamWriter {
 protected:
  virtual void writeFile(
      uint8_t channel,
      std::shared_ptr<rogue::interfaces::stream::Frame> frame) {
    // Variables
    uint32_t value;
    uint32_t size;
    char buffer[100];

    // Release the python GIL to avoid deadlocks
    //rogue::GilRelease noGil;

    // Lock the access to the local file
    // When the writeFile method is called, a lock is already held on the Frame
    // instance
    std::unique_lock<std::mutex> lock(mtx_);

    // Get the payload size from the frame
    size = frame->getPayload();

    // Call a helper function to check the file size and do housekeeping on the
    // memory resident buffer. This will close and open a new file if we have
    // reached the max size and will flush the memory buffer to a file if we
    // have reached the requested burst size.
    checkSize(size);

    // Get an iterator to the frame data
    auto it = frame->begin();

    // First line is the size in 32-bit values
    sprintf(buffer, "0x%x\n", size / 4);

    // Call the underlying write functions
    intWrite(buffer, strlen(buffer));

    // Loop through the rest of the file
    do {
      fromFrame(it, 4, &value);
      sprintf(buffer, "0x%x\n", value);
      intWrite(buffer, strlen(buffer));
    } while (++it != frame->end());

    // Update the frame count
    frameCount_++;

    // This helps update the class state
    cond_.notify_all();
  }
};

// Smart pointer alias for our custom class
typedef std::shared_ptr<EventWriter> EventWriterPtr;
    
}
}
