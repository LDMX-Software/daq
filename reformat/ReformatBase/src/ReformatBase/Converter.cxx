
#include "ReformatBase/Converter.h"

#include <ctime>

#include "Framework/EventFile.h"
#include "Framework/Event.h"
#include "Framework/EventHeader.h"
#include "Framework/RunHeader.h"
#include "TTimeStamp.h"

namespace reformatbase {

void Converter::configure(const framework::config::Parameters& cfg) {
  pass_ = cfg.getParameter<std::string>("pass_name");  // pass is a keyword in Python
  output_filename_ = cfg.getParameter<std::string>("output_filename");
  run_ = cfg.getParameter<int>("run");
  start_event_ = cfg.getParameter<int>("start_event");

  // Framework already has a library loading mechanism, no need to repeat ourselves
  auto libs{
      cfg.getParameter<std::vector<std::string>>("libraries", {})};
  std::for_each(libs.begin(), libs.end(), [](auto &lib) {
    RawDataFileFactory::getInstance().loadLibrary(lib);
  });

  auto input_files{
      cfg.getParameter<std::vector<framework::config::Parameters>>(
          "input_files", {})};
  if (input_files.empty()) {
    EXCEPTION_RAISE(
        "NoInputFiles",
        "No input files have been defined. What should I be doing?\n"
        "Use c.input_files to tell me what files to convert.");
  }
  for (auto f : input_files) {
    auto class_name{f.getParameter<std::string>("class_name")};
    input_files_.emplace_back(RawDataFileFactory::getInstance().create(class_name, f));
  }
}

void Converter::convert() {
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
    eh.setRun(run_);
    eh.setEventNumber(i_event++);
    eh.setTimestamp(TTimeStamp());

    for (auto& f : input_files_) {
      more_events = f->next(output_event);
    }
  }

  run_header.setRunEnd(std::time(nullptr));
  output_file.close();
}

}  // namespace reformatbase
