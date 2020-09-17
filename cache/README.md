# 2Q cache
To run test:
```bash
make
./test
```
To compare LRU and 2Q cache:
```bash
./compare <file with keys> (e.g. tools/zipf.txt)
```
To generate random keys with zipf distribution:
```bash
tools/generate.py
```
Use 2Q cache for test hits:
```bash
./main
```
