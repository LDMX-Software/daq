#ifndef REFORMATBASE_BINDINGS_H_
#define REFORMATBASE_BINDINGS_H_

#include <boost/python.hpp>
#include "ReformatBase/RawDataFile.h"
#include "ReformatBase/Converter.h"

BOOST_PYTHON_MODULE("ReformatBase") {
  boost::python::class_<reformatbase::RawDataFile>("RawDataFile",boost::python::init<std::string>());

  boost::python::class_<reformatbase::Converter>("Converter")
    .def("insert",&reformatbase::Converter::insert);
}

#endif  // REFORMATBASE_BINDINGS_H_
