#include <Python.h>
#include "client.h"
#include "server.h"

// client initializer
static PyObject* client(PyObject* self, PyObject* args) {
    //initialize port number for localhost
    int port_num;
    if(!PyArg_ParseTuple(args, "i", &port_num))
        return NULL;
    // return client_fd
    return Py_BuildValue("i", init_client(port_num));
}

//send client request
static PyObject* request(PyObject* self, PyObject* args) {
        //initialize port number for localhost
    int client_fd;
    if(!PyArg_ParseTuple(args, "i", &client_fd))
        return NULL;
    // send client request
    request_server(client_fd);
    return Py_None;
}

// server initializer
static PyObject* server(PyObject* self, PyObject* args) {
    //initialize port number for localhost
    int port_num;
    if(!PyArg_ParseTuple(args, "i", &port_num))
        return NULL;
    // return server_fd
    return Py_BuildValue("i", init_server(port_num));
}

// server starter
static PyObject* startServer(PyObject* self, PyObject* args) {
    //initialize port number for localhost
    int server_fd;
    if(!PyArg_ParseTuple(args, "i", &server_fd))
        return NULL;
    // start
    start_server(server_fd);
    return Py_None;
}
// Our Module's Function Definition struct
// We require this `NULL` to signal the end of our method
// definition
static PyMethodDef cliServ[] = {
    { "client", client, METH_VARARGS, "initialize client" },
    { "server", server, METH_VARARGS, "initialize server" },
    { "request", request, METH_VARARGS, "send client's request" },
    { "startServer", startServer, METH_VARARGS, "start the server" },
    { NULL, NULL, 0, NULL }
};

// Our Module Definition struct
static struct PyModuleDef clieServModule = {
    PyModuleDef_HEAD_INIT,
    "clieServModule",
    "Test Module",
    -1,
    cliServ
};

// Initializes our module using our above struct
PyMODINIT_FUNC PyInit_clieServModule(void)
{
    return PyModule_Create(&clieServModule);
}