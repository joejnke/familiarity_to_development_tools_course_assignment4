#from distutils.core import setup, Extension
from setuptools import setup, find_packages, Extension
py_binder = Extension('clieServModule',
                    define_macros = [('MAJOR_VERSION', '1'),
                                     ('MINOR_VERSION', '0')],
                    include_dirs = ['/usr/local/include'],
                    libraries = ['client', 'server'],
                    library_dirs = ['/usr/local/lib'],
                    sources = ['py_binder.c'])

setup (name='clieServModule',
       version='1.0',
       author='Kirubel Kassaye',
       author_email='joejnke@gmail.com',
       description='python c extension for socket based server client library',
       ext_modules = [py_binder])