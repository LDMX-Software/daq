"""Test core functionality by running dummy test file(s)"""

from Reformat import reformatcfg

class TestFile(reformatcfg.RawDataFile) :
    def __init__(self, n) :
        super().__init__('ReformatBase','reformatbase::test::TestFile')
        self.num = n

import argparse, sys

parser = argparse.ArgumentParser(f'ldmx reformat {sys.argv[0]}')

parser.add_argument('input_cfg',choices=['single','multi','misalign'])

arg = parser.parse_args()

c = reformatcfg.Converter('test_output.root')

if arg.input_cfg == 'single' :
    c.input_files = [TestFile(5)]
elif arg.input_cfg == 'multi' :
    c.input_files = [TestFile(5), TestFile(5)]
elif arg.input_cfg == 'misalign' :
    c.input_files = [TestFile(3), TestFile(5)]
