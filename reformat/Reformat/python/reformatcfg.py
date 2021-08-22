"""Base module for configuring a reformat of raw data files"""

class Converter :
    """Core converter class which handles converting input raw data files
    into an output Framework EventFile

    Attributes
    ----------
    lastConverter : Converter
        Holds the converter that was last constructed
    libraries : list[str]
        List of libraries to load
    input_files : list[RawDataFile]
        RawDataFile instances to use as input files for conversion
    run : int
        Run number to put into output EventFile
    start_event : int
        Starting event ID
    output_filename : str
        Output EventFile path
    pass_name : str
        Pass name in output EventFile
    """

    lastConverter = None

    def __init__(self, output_file) :
        Converter.lastConverter = self
        self.libraries = []
        self.input_files = []
        self.run = 1
        self.start_event = 0
        self.output_filename = output_file
        self.pass_name = 'raw'

    def addLibrary(lib) :
        if Converter.lastConverter is None :
            raise Exception('Must define a Converter object before adding another library.')

        Converter.lastConverter.libraries.append(lib)

    def addModule(m) :
        if not m.startswith('lib') :
            m = 'lib'+m

        if not m.endswith('.so') :
            m += '.so'

        Converter.addLibrary(m)

class RawDataFile :
    """Base class for configuring other raw data files

    Parameters
    ----------
    module : str
        Name of module to load
    class_name : str
        Full class name (including namespace) of data file
    """

    def __init__(self, module, class_name) :
        Converter.addModule(module)
        self.class_name = class_name
