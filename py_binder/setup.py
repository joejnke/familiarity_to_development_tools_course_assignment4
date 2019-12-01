from setuptools import setup, find_packages
setup(name='pathology',
      version='0.1',
      url='https://github.com/joejnke/',
      license='MIT',
      author='Kirubel Kassaye',
      author_email='joejnke@gmail.com',
      description='python c extension for socket based server client library',
      packages=find_packa(),
      long_description=open('README.md').read(),
      zip_safe=False)