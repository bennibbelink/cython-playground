#include "pyhooks.h"
#include "Python.h"
#include "pymodule.h"

int PY_INTERP_COUNT = 0;
bool PY_INTERP_INIT = false;


void PyImportCallInit(void) {
    PyInit_pymodule();
}

void PyStart(void) {
    if (!PY_INTERP_INIT) {
    PyImport_AppendInittab("_cyclus_pymodule", PyInit_pymodule);
    Py_Initialize();
    PyImport_ImportModule("_cyclus_pymodule");
    atexit(PyStop);
    PY_INTERP_INIT = true;
  };
  PY_INTERP_COUNT++;
}

void PyStop(void) {
  PY_INTERP_COUNT--;

  // PY_INTERP_COUNT should only be negative when called atexit()
  if (PY_INTERP_INIT && PY_INTERP_COUNT < 0) {
    Py_Finalize();
  };
};

int DelPyAgent(void) { return CyclusDelPyAgent(); };