"""Test core functionality by running dummy test file(s)"""

from Reformat import reformat

import argparse, sys

parser = argparse.ArgumentParser(f'ldmx reformat {sys.argv[0]}')

parser.add_argument('input_file')
parser.add_argument('--pause',action='store_true')
parser.add_argument('--output',default='reformatted_hgcroc.root')

arg = parser.parse_args()

c = reformat.Converter(arg.output)

from Reformat import hgcroc
c.input_files = [ hgcroc.HGCROCv2RawDataFile(arg.input_file) ]

if arg.pause :
    c.pause()
