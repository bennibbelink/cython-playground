# distutils: language=c++
from playground import lib as playlib
from cpython.exc cimport PyErr_CheckSignals

cdef public int del_py_agent "CyclusDelPyAgent"():
    some_num = playlib.libdel()
    PyErr_CheckSignals()
    return some_num