#! /usr/bin/python

import numpy as np
import sys


DEFAULT_SIZE = 1000000
ZIPF_ALPH = 1.16

def usage():
    print('''
-n - normal distribution
-z - zipf distribution
-u - uniform distribution
''')


def zipf(alph, size):
    dist = np.random.zipf(alph, size)
    return dist

def normal(size):
    dist = np.random.normal(loc=(size / 2), scale=(size / 1000), size=size)
    dist = dist.round().astype(int)
    return dist

def uniform(size):
    dist = np.random.randint(0, size, size)
    return dist

def main(argv):
    if len(argv) == 0:
        usage()
        return
    
    if argv[0] == '-n':
        dist = normal(DEFAULT_SIZE)
    elif argv[0] == '-z':
        dist = zipf(ZIPF_ALPH, DEFAULT_SIZE)
    elif argv[0] == '-u':
        dist = uniform(DEFAULT_SIZE)
    else:
        usage()
        return

    for num in dist:
        print(num)


if __name__ == '__main__':
    main(sys.argv[1:])
