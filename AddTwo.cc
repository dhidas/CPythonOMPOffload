#include "AddTwo.h"

#include "myomp.h"

PyObject* AddTwo_Offload (PyObject*, PyObject* args)
{



  float myreturn = (float) Offload();
  return Py_BuildValue("f", myreturn);
}















float AddTwo (float A, float B)
{
  return A + B;
}




PyObject* AddTwo_AddTwo(PyObject*, PyObject* args)
{
  float A = 0;
  float B = 0;
  if (!PyArg_ParseTuple(args, "ff", &A, &B)) {
    PyErr_SetString(PyExc_ValueError, "input not correct (A, B)");
    return NULL;
  }


  return Py_BuildValue("f", AddTwo(A, B));
}





static PyMethodDef methodtable[] = {
  {"offload", AddTwo_Offload, METH_VARARGS, "float ()"},
  {"AddTwo", AddTwo_AddTwo, METH_VARARGS, "float AddTwo(float, float)"},
  {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3
static PyModuleDef AddTwomodule = {
  PyModuleDef_HEAD_INIT,
  "AddTwo",
  "Documentation",
  -1,
  methodtable,
  NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC PyInit_AddTwo (void) {
    PyModule_Create(&AddTwomodule);
}
#else
PyMODINIT_FUNC initAddTwo(void)
{
  Py_InitModule("AddTwo", methodtable);
}
#endif
