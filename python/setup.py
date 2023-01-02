#!/usr/bin/env python
# -*- coding: utf-8 -*-
from codecs import open  # To use a consistent encoding
from os import path
import platform
from setuptools import setup, find_packages


if platform.system() == 'Linux':
    ext = '.so'
elif platform.system() == 'Darwin':
    ext = '.dylib'
else:
    raise OSError('Unsupported operating system')


lib_path = './moor_ai/libmoor-ai{}'.format(ext)
here = path.abspath(path.dirname(__file__))


# Get the long description from the relevant file
with open(path.join(here, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()


setup(
    name='moor_ai',
    packages=find_packages(),
    version='0.2.0',
    description='',
    long_description=long_description,
    author='mdm',
    author_email='marco.masciola@gmail.com',
    url='',
    download_url='',
    keywords=[],
    classifiers=[
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
    ],
    install_requires=[''],
    # include_package_data=True,
    # package_data={'':['../bin/*.dylib']}
    # datas=[('../bin/libmoor-ai.dylib', '.')]
    data_files=[('', [lib_path])]
)
