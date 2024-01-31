cdef extern from "run_playground.h":
    cdef void run_playground()

cdef extern from "pyhooks.h":
    cdef void PyImportCallInit()
    cdef void PyStart()
