import sys
import subprocess

ALGOS = ['rms', 'abs', 'localline', 'pv', 'skew']

if __name__ == '__main__':
  infile = sys.argv[1]
  
  window = 101
  if len(sys.argv) == 3:
    window = int(sys.argv[2])

  for alg in ALGOS:
    # execute rms
    rms_cmd = ['./rms', infile, alg + '.txt', alg, str(window)]
    result = subprocess.call(rms_cmd)
    # save matplot
    plot_cmd = ['python', 'viz/read_colored_scan.py', alg + '.txt', alg]
    result = subprocess.call(plot_cmd)
