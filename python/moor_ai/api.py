#!/usr/bin/env python
# -*- coding: utf-8 -*-
from ctypes import (
    byref,
    c_char_p,
    cdll,
    c_int,
    POINTER,
    Structure
)
import os
import platform
import sys


if platform.system() == 'Linux':
    ext = '.so'
elif platform.system() == 'Darwin':
    ext = '.dylib'
else:
    raise OSError(
        'Unsupported operating system')


lib_name = 'libmoor-ai{}'.format(ext)


class Domain(Structure):
    def __init__(self, obj, name=''):
        self.obj = obj
    _fields_ = [
        ('label', POINTER(c_char_p))]


class Interface(object):
    domain = (POINTER(Domain) * 1)()
    msg = (c_char_p * 1)()

    try:
        _lib = cdll.LoadLibrary(os.path.join(sys.prefix, lib_name))
    except OSError:
        lpath_default: str = os.path.join('./bin/', lib_name)
        if os.path.exists(lpath_default):
            _lib = cdll.LoadLibrary(lpath_default)
        else:
            _lib = cdll.LoadLibrary(os.path.join('../bin/', lib_name))

    _lib.api_allocate_domain.restype = c_int
    _lib.api_free_domain.restype = c_int
    _lib.api_flush_msg.restype = c_int

    _lib.api_allocate_domain.argtype = [  # type: ignore
        POINTER(Domain), c_char_p]
    _lib.api_flush_msg.argtype = [c_char_p]  # type: ignore
    _lib.api_free_domain.argtype = [POINTER(Domain), c_char_p]  # type: ignore

    def _check_err(self, ierr: int) -> None:
        if ierr != 0 and self.msg[0]:
            print(self.msg[0].decode())  # type: ignore

    def allocate(self) -> None:
        ierr = self._lib.api_allocate_domain(byref(self.domain), self.msg)
        self._check_err(ierr)

    def free(self) -> None:
        ierr = self._lib.api_free_domain(byref(self.domain), self.msg)
        self._check_err(ierr)

    def flush_message(self) -> None:
        ierr = self._lib.api_flush_msg(self.msg)
        self._check_err(ierr)
