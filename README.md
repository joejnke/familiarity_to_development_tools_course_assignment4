# familiarity_to_development_tools_course_assignment4
Python c extension to write client server programs using python. The client server programs are rewritten as c libraries 
which will be installed as shared libraries. Then there is a python binder that will make this libraries avalilable
for use with python codes.
### Installation
#### building the c shared libraries
`cd c_client_server/`

`mkdir build`

`cd build`

`cmake ../`

`cmake --build .`

`cmake --install .` *here we assume that the default installation directory of cmake, which is `/usr/local`*

`cd ../../`

#### building the python binder as whl
`cd py_binder`

`python setup.py bdist_wheel`

`cd ../`

#### installing the python binder
`python -m pip install py_binder/dist/clieServModule-1.0-cp37-cp37m-linux_x86_64.whl`

#### testing 
`python server.py`

open another terminal and `python client.py`

type in file name in the client terminal, and the server will send back the contents(text) of the file.
