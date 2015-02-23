import numpy as np
import matplotlib.pyplot as plt

import sys

SCAN_SIZE = 800
# Surfae roughness scores
V_MAX = 0.15
V_MIN = 0.0
DEFAULT_MIN_MAX = (V_MIN, V_MAX)
SCORE_MAP = {'localline':(0,0.03),
             'pv': DEFAULT_MIN_MAX }
TITLE_MAP = {'localline':'Surface Roughness by Local RMS',
             'pv': 'Surface Roughness by Peak-Valley'}

# Color stuff
C_MIN = (0, 0, 1) # Blue
C_MAX = (1, 0, 0) # Red

def display_data(x, y, c):
  plt.scatter(x, y, c=c, lw=0)#, cmap=plt.cm.gray)
  plt.show()

def save_figure(x,y,c,filename):
  plt.scatter(x, y, c=c, lw=0)
  plt.ylabel('Vertical Displacement from Center Line (mm)')
  plt.xlabel('Horizontal Displacement (mm)')
  if filename in TITLE_MAP:
    plt.title(TITLE_MAP[filename])
  print('Saving figure %s' % filename)
  plt.savefig(filename)
  plt.close()

def interp_color(v):
  d = V_MAX - V_MIN
  r = (v - V_MIN) / d
  b = (V_MAX - v) / d
  return (r, 0, b)

def to_color(v, minimum = V_MIN, maximum = V_MAX):
  if v > maximum:
    return C_MAX
  elif v < minimum:
    return C_MIN
  else:
    return interp_color(v)

def read_data(fh, limit, mn, mx):
  xs = []
  ys = []
  cs = []
  n = 0
  for line in fh:
    x,y,c = line.split()
    xs.append(float(x))
    ys.append(float(y))
    c2 = to_color(abs(float(c)), mn, mx)
    cs.append(c2)
    # cs.append(abs(float(c)))
    n += 1
    if n >= limit:
      break
  
  return xs,ys,cs

def read_and_display(filename, save=False, outfile=""):
  with open(filename, 'r') as fh:
    # read color score ranges
    mn, mx = DEFAULT_MIN_MAX
    if outfile in SCORE_MAP:
      pair = SCORE_MAP[outfile]
      print 'Using', pair, 'for', outfile
      mn, mx = pair
    # read data from file
    x,y,c = read_data(fh, SCAN_SIZE, mn, mx)
    # Either save to file or just display till user kills
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
