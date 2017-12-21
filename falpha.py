#!/usr/bin/python

import sys
import re

print "ALPHA architecture feature extractor\n"
inp = open(sys.argv[1], "r");
out = open("inst.txt", "w");
pat_inst = re.compile(r'   [0-9a-f]+:\s+([0-9a-f][0-9a-f] ){4}\t');

for line in inp:
	if(pat_inst.search(line) != None):
		line = pat_inst.sub("", line)
		inst = line.split();
		inst = inst[0].split('/');
		out.write(inst[0] + '\n')

out.close()

