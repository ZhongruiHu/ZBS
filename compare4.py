#!/usr/bin/python
# Requires Python 2.6 or above

from string import *
from math import *
import os
import signal

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
	for n in [1000, 2000, 3000]:
		for k in range(5, 55, 5):	# k neighbors
			if sh.signaled:
				break

			r = sqrt((k)/(n*pi))
			if os.name == 'nt':
				os.system('p %f %d' % (r, n))
			else:
				os.system('./p %f %d' % (r, n))

# vim:ts=2:sw=2:

