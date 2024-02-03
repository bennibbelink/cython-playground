#include "Python.h"
#include "pyhooks.h"
#include "pymodule.h"
#include <iostream>

int PY_INTERP_COUNT = 0;
bool PY_INTERP_INIT = false;


void PyImportCallInit(void) {
    std::cout << "In PyImportCallInit()\n";
    PyInit_pymodule();
    PyImport_ImportModule("pymodule");
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
    PyImport_ImportModule("pymodule");
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