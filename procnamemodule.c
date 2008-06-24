#include <Python.h>
#include <sys/prctl.h>

PyDoc_STRVAR(procname__doc__, "Module for setting/getting process name");

static PyObject *
procname_check(PyObject *self, PyObject *args) {	return Py_BuildValue("i", 1);
};


static PyObject *
procname_getprocname(PyObject *self, PyObject *args) {	int argc;
	char **argv;
	Py_GetArgcArgv(&argc, &argv);
	return Py_BuildValue("s", argv[0]);
};


static PyObject *
procname_setprocname(PyObject *self, PyObject *args) {	int argc;
	char **argv;
	char *name;
	if (!PyArg_ParseTuple(args, "s", &name))
		return NULL;
	Py_GetArgcArgv(&argc, &argv);
	strncpy(argv[0], name , strlen(name));
	memset(&argv[0][strlen(name)], '\0', strlen(&argv[0][strlen(name)]));
	prctl (15 /* PR_SET_NAME */, name, 0, 0, 0);
	Py_INCREF(Py_None);
	return Py_None;
};


static PyMethodDef procname_methods[] = {	{"check", procname_check, METH_VARARGS, "Test func"},
	{"getprocname", procname_getprocname, METH_VARARGS,
		"Get procname.\nReturns name (string)"},
	{"setprocname", procname_setprocname, METH_VARARGS,
		"Set procname.\n  name (string) -> new process name.\nReturns None."},
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initprocname(void) {	(void) Py_InitModule3("procname", procname_methods, procname__doc__);
}

