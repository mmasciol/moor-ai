#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import (
    cdll,
    c_int
)
import os
import sys


sys.prefix

class T(object):
    _lib = cdll.LoadLibrary(os.path.join(sys.prefix, 'libmoor-ai.dylib'))

    #_lib.api_hook.argtypes = [None]
    _lib.api_hook.restype = c_int

    def run(self) -> None:
        size = self._lib.api_hook()
        print(size)

