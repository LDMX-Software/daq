
#include "ReformatBase/Converter.h"

#include <ctime>

#include "Framework/EventFile.h"
#include "Framework/Event.h"
#include "Framework/EventHeader.h"
#include "Framework/RunHeader.h"
#include "TTimeStamp.h"

namespace reformatbase {

void Converter::convert(const std::string& output_filename, int run, int start_event, const std::string& pass) {
  framework::Event output_event(pass);
  framework::EventFile output_file({}, output_filename, nullptr, true, true,
                                   false);
  output_file.setupEvent(&output_event);

  ldmx::RunHeader run_header(run);
  run_header.setRunStart(std::time(nullptr));
  output_file.writeRunHeader(run_header);

  bool more_events{true};
  int i_event{start_event};
  while (more_events) {
    ldmx::EventHeader& eh = output_event.getEventHeader();
    eh.setRun(run);
    eh.setEventNumber(i_event++);
    eh.setTimestamp(TTimeStamp());

    for (auto& [name, channel] : data_channels_) {
      more_events = channel->next(output_event);
    }
  }

  run_header.setRunEnd(std::time(nullptr));
  output_file.close();
}

}  // namespace reformatbase
