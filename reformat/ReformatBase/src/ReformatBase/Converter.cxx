
#include "ReformatBase/Converter.h"

#include <ctime>

#include "Framework/EventFile.h"
#include "Framework/Event.h"
#include "Framework/EventHeader.h"
#include "Framework/RunHeader.h"
#include "TTimeStamp.h"

namespace reformatbase {

void Converter::configure(const framework::config::Parameters& cfg) {
  pass_ = cfg.getParameter<std::string>("pass"); 
  output_filename_ = cfg.getParameter<std::string>("output_filename");
  run_ = cfg.getParameter<int>("run");
  start_event_ = cfg.getParameter<int>("start_event");
}

void Converter::convert()
  framework::Event output_event(pass_);
  framework::EventFile output_file({}, output_filename_, nullptr, true, true,
                                   false);
  output_file.setupEvent(&output_event);

  ldmx::RunHeader run_header(run_);
  run_header.setRunStart(std::time(nullptr));
  output_file.writeRunHeader(run_header);

  bool more_events{true};
  int i_event{start_event_};
  while (more_events) {
    ldmx::EventHeader& eh = output_event.getEventHeader();
    eh.setRun(run);
    eh.setEventNumber(i_event++);
    eh.setTimestamp(TTimeStamp());

    for (auto& [name, file] : data_files_) {
      more_events = file->next(output_event);
    }
  }

  run_header.setRunEnd(std::time(nullptr));
  output_file.close();
}

}  // namespace reformatbase