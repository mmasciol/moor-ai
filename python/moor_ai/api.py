#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import (
    cdll,
    c_int
)
import os
import platform
import sys


if platform.system() == 'Linux':
    ext = '.so'
elif platform.system() == 'Darwin':
    ext = '.dylib'
else:
    raise OSError('Unsupported operating system')


lib_name = 'libmoor-ai{}'.format(ext)


class Domain(object):
    try:
        _lib = cdll.LoadLibrary(os.path.join(sys.prefix, lib_name))
    except OSError:
        _lib = cdll.LoadLibrary(os.path.join('../bin/', lib_name))

    _lib.api_hook.restype = c_int

    def run(self) -> None:
        size = self._lib.api_hook()
        print(size)
