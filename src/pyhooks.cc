#include "Python.h"
#include "pyhooks.h"
#include "pymodule.h"
#include <iostream>

int PY_INTERP_COUNT = 0;
bool PY_INTERP_INIT = false;


void PyImportCallInit(void) {
    std::cout << "In PyImportCallInit()\n";
}

void PyStart(void) {
  std::cout << "In PyStart()\n";
  if (!PY_INTERP_INIT) {
    std::cout << "Actually doing things in PyStart()\n";
    if (PyImport_AppendInittab("pymodule", PyInit_pymodule) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }
    std::cout << "Call Py_Initialize()\n";
    Py_Initialize();
    PySys_SetPath(L"/playground/build:/playground/build/src");

    // Get the Python path
    PyObject *pPathList = PySys_GetObject("path");
    
    if (pPathList && PyList_Check(pPathList)) {
        Py_ssize_t listSize = PyList_Size(pPathList);

        // Iterate through the sys.path list and print each item
        for (Py_ssize_t i = 0; i < listSize; ++i) {
            PyObject *pItem = PyList_GetItem(pPathList, i);
            if (pItem) {
                // Assuming the items in the list are strings
                const char *pathItem = PyUnicode_AsUTF8(pItem);
                printf("Item %zd: %s\n", i, pathItem);
            }
        }
    } else {
        PyErr_Print();  // Print any Python exception if occurred
    }
    

    PyObject *pmodule = PyImport_ImportModule("pymodule");
    if (!pmodule) {
        PyErr_Print();
        fprintf(stderr, "Error: could not import module 'pymodule'\n");
        exit(1);
    }
    atexit(PyStop);
    PY_INTERP_INIT = true;
  };
  PY_INTERP_COUNT++;
}

void PyStop(void) {
  std::cout << "In PyStop()\n";
  PY_INTERP_COUNT--;

  // PY_INTERP_COUNT should only be negative when called atexit()
  if (PY_INTERP_INIT && PY_INTERP_COUNT < 0) {
    Py_Finalize();
  };
};

int DelPyAgent(void) { 
  std::cout << "In DelPyAgent()\n";
  return CyclusDelPyAgent(); 
};