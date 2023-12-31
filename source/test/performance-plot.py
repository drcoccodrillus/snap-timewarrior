#!/usr/bin/env python3

import os

import argparse
import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser(description='Display performance plots.')
parser.add_argument('output_dir', help='directory containing the measurement files')
parser.add_argument('commands', nargs='*', type=str)

args = parser.parse_args()

output_directory = args.output_dir
commands = args.commands

plt.axes([0.1, 0.1, 0.6, 0.75])
plt.xlabel("# database entries")
plt.ylabel("time [s]")
plt.title(output_directory)

for filename in os.listdir(output_directory):
    if filename.endswith(".log"):
        cmd = "-".join(filename.split('-')[1:-1])
    else:
        continue

    if len(commands) == 0 or cmd in commands:
        try:
            x, y = np.loadtxt(os.path.join(output_directory, filename),
                              delimiter='\t',
                              usecols=(1, 2),
                              unpack=True)
            plt.plot(x, y, label=cmd, marker=".", linestyle='-')
        except ValueError as e:
            print("Invalid file: {} {}".format(filename, e))

plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left', borderaxespad=0., ncol=2)
plt.show()
