from playground import lib as playlib

cdef public int del_py_agent "CyclusDelPyAgent"():
    some_num = playlib.libdel()
    PyErr_CheckSignals()
    return some_num