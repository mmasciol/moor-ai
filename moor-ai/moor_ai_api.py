from ctypes import (
    cdll,
    c_int
)
# import os
# import sys


class T(object):
    _lib = cdll.LoadLibrary('../bin/libmoor-ai.dylib')

    #_lib.api_hook.argtypes = [None]
    _lib.api_hook.restype = c_int

    def run(self) -> None:
        size = self._lib.api_hook()
        print(size)

