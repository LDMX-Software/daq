"""HexaBoard.hgcroc Python module"""

from Reformat import reformatcfg

class HGCROCv2RawDataFile(reformatcfg.RawDataFile) :
    """Configuration for HGCROC v2 raw data file"""
    def __init__(self, filepath) :
        super().__init__('HexaBoard','hexareformat::HGCROCv2RawDataFile')
        self.input_file = filepath