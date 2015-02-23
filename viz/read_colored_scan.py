import numpy as np
import matplotlib.pyplot as plt

import sys

SCAN_SIZE = 800

def display_data(x, y, c):
  plt.scatter(x, y, c=c, lw=0)#, cmap=plt.cm.gray)
  plt.show()

def save_figure(x,y,c,filename):
  plt.scatter(x, y, c=c, lw=0)
  print('Saving figure %s' % filename)
  plt.savefig(filename)
  plt.close()

V_MAX = 0.15
V_MIN = 0.0

def to_color(v):
  if v > V_MAX:
    return (1.0, 0.0, 0.0)
  elif v < 0.0:
    return (0, 0.0, 0.0)
  else:
    return (v / (V_MAX-V_MIN), 0, 0)

def read_data(fh, limit=SCAN_SIZE):
  xs = []
  ys = []
  cs = []
  n = 0
  for line in fh:
    x,y,c = line.split()
    xs.append(float(x))
    ys.append(float(y))
    #c2 = to_color(abs(float(c)))
    #cs.append(c2)
    cs.append(abs(float(c)))
    n += 1
    if n >= limit:
      break
  
  return xs,ys,cs

def read_and_display(filename, save=False, outfile=""):
  with open(filename, 'r') as fh:
    x,y,c = read_data(fh)
    if not save:
      display_data(x,y,c)
    else:
      save_figure(x,y,c,outfile)

if __name__ == '__main__':
  if len(sys.argv) == 2:
    read_and_display(sys.argv[1])
  elif len(sys.argv) == 3:
    read_and_display(sys.argv[1], True, sys.argv[2])
  else:
    print('Usage: python read_scan.py <filename>')
