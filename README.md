# CPythonOMPOffload

This is an attempt to build a CPython extension using OpenMP offloading to GPUs at NERSC.  Thus far we have not been successful.

Information on NERSC GPUs:
* https://docs-dev.nersc.gov/cgpu/software/

## Enviroment setup for clang

```
module load gcc/7.3.0 cuda/9.2.148 llvm/10.0.0-git_20190828 python
module load esslurm
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
```
When submitting the job you will likely need to change the -A flag in the submit_*.sh scripts to match your account.

## Build straight executable and test
```
clang -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda myomp.cc mymain.cc -o mymain
sbatch submit_mymain.sh
```


## Try exe with shared lib
```
clang -fPIC -shared -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda myomp.cc -o libmyomp.so
clang -c mymain.cc
clang mymain.o -L. -lmyomp -o mymain2
sbatch submit_mymain2.sh
```


## Linking to this shared library works with gcc as well (also on gpu-002)
The following links and runs correctly.  If we copy libmyomp.so to gpu-002 the same also works properly.
```
g++ -c mymain.cc
g++ mymain.o -L. -lmyomp -o mymain3
sbatch submit_mymain3.sh
```


## Build AddTwo module with setuptools.  Running segfaults
```
python setup.py build_ext --inplace
submit_python.sh
```
Running also fails:
```
python run.py
```
