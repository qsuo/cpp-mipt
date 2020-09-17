#! /usr/bin/python

import numpy as np

dist = np.random.zipf(1.16, 1000000)
for num in dist:
    print(num)
