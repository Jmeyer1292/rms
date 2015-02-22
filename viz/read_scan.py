import numpy as np
import matplotlib.pyplot as plt

import sys

SCAN_SIZE = 800

def display_data(x, y):
  plt.scatter(x, y) #, s=500)
  plt.show()

def read_data(fh, limit=SCAN_SIZE):
  xs = []
  ys = []
  n = 0
  for line in fh:
    x,y = line.split()
    xs.append(float(x))
    ys.append(float(y))
    n += 1
    if n >= limit:
      break
  
  return xs,ys

def read_and_display(filename):
  with open(filename, 'r') as fh:
    x,y = read_data(fh)
    display_data(x,y)

if __name__ == '__main__':
  if len(sys.argv) > 1:
    read_and_display(sys.argv[1])
  else:
    print('Usage: python read_scan.py <filename>')