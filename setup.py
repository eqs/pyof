# -*- coding: utf-8 -*-
import io
import os
import re
import sys
import glob
import platform
import subprocess

from setuptools import setup, Extension, find_packages
from setuptools.command.build_ext import build_ext


class OFExtension(Extension):
    def __init__(self, name, sln_path=''):
        Extension.__init__(self, name, sources=[])
        self.sln_path = os.path.abspath(sln_path)


class OFBuild(build_ext):
    def run(self):
        for ext in self.extensions:
            self.build_extension(ext)

    def build_extension(self, ext):
        # subprocess.check_call([
        #     'msbuild', ext.sln_path, '/t:build', '/p:Configuration=Release;Platform="x64"'
        # ])
        subprocess.check_call(['build.bat'])


def read(filename):
    filename = os.path.join(os.path.dirname(__file__), filename)
    text_type = type(u"")
    with io.open(filename, mode="r", encoding='utf-8') as fd:
        return re.sub(text_type(r':[a-z]+:`~?(.*?)`'), text_type(r'``\1``'), fd.read())


setup(
    name="pyof",
    version="0.0.1",
    url="https://github.com/eqs/pyof",
    license='BSD',

    author="eqs",
    author_email="murashige.satoshi.mi1 [at] gmail.com",

    description="Python binding of openFrameworks",
    long_description=read("README.md"),

    packages=find_packages(exclude=('tests',)),

    install_requires=[],
    cmdclass={'build_ext': OFBuild},
    ext_modules=[OFExtension('pyof.lib.pyoflib', 'pyoflib/pyoflib.sln')],
    zip_safe=False,

    include_package_data=True,

    classifiers=[
        'Development Status :: 2 - Pre-Alpha',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9'
    ],
)

