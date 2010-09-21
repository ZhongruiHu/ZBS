#!/usr/bin/python
# Requires Python 2.6 or above

from string import *
from math import *
import os
import signal

# constants
n = 2000

class SigHandler:
	def __init__(self):
		self.signaled = 0
		self.sn = None
	def __call__(self, sn, sf):
		self.sn = sn 
		self.signaled += 1

sh = SigHandler()

if __name__ == "__main__":
	signal.signal(signal.SIGINT, sh)
	signal.signal(signal.SIGBREAK, sh)

	os.environ['NUM_RUNS'] = '10'
	for k in range(1, 61):	# k neighbors
		if sh.signaled:
			break

		if os.name == 'nt':
			os.system('p %d %d' % (k, n))
		else:
			os.system('./p %d %d' % (k, n))

# vim:ts=2:sw=2:
