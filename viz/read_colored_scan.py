import numpy as np
import matplotlib.pyplot as plt

import sys

SCAN_SIZE = 800

def display_data(x, y, c):
  plt.scatter(x, y, c=c, lw=0)#, cmap=plt.cm.gray)
  plt.show()

def read_data(fh, limit=SCAN_SIZE):
  xs = []
  ys = []
  cs = []
  n = 0
  for line in fh:
    x,y,c = line.split()
    xs.append(float(x))
    ys.append(float(y))
    cs.append(float(c))
    n += 1
    if n >= limit:
      break
  
  return xs,ys,cs

def read_and_display(filename):
  with open(filename, 'r') as fh:
    x,y,c = read_data(fh)
    display_data(x,y,c)

if __name__ == '__main__':
  if len(sys.argv) > 1:
    read_and_display(sys.argv[1])
  else:
    print('Usage: python read_scan.py <filename>')