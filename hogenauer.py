from ctypes import cdll
import numpy.ctypeslib as npct
import ctypes as ct

import numpy as np
import numpy.fft as nfft
import numpy.random as ra
import scipy.signal as sig
import matplotlib.pyplot as plt

libhog = cdll.LoadLibrary("./libhogenauer.so")

class CICDecimator():
    """ I've realised that this structure doesn't suit the imperative structure
        of my simulations. Damn it.
    """
    r = 0

    def __init__(self,r,d,s):
        """ Initialise the class. The python class itself wraps the c++ class,
            which ideally.
        """
        self.r = r
        r_ct = ct.c_ulonglong(r)
        d_ct = ct.c_ulonglong(d)
        s_ct = ct.c_ulonglong(s)
        self.obj = libhog.CICDecimatorI(r_ct,d_ct, s_ct)

    def __del__(self):
        """Call the C++ object destructor"""
        libhog.CICDecimatorEnd(self.obj)

    def run_filter(self, steps, input):
        """Run the filter"""
        if type(input[0]) != np.int64:
            print("Warning: type error")

        n_samples_output = np.int64(len(input) / (self.r))

        steps_ct = ct.c_longlong(steps)

        input_ct = npct.as_ctypes(input)
        output_ct = npct.as_ctypes(np.zeros(n_samples_output,dtype=np.int64))

        libhog.CICDecimatorI64InOutSet(self.obj, input_ct, output_ct)
        libhog.CICDecimatorRunFilter(self.obj, steps_ct)

        output = npct.as_array(output_ct)
        output = output.astype(np.int64)
        return output


class CICInterpolator():
    """ I've realised that this structure doesn't suit the imperative structure
        of my simulations. Damn it.
    """
    r = 0

    def __init__(self,r,d,s):
        """ Initialise the class. The python class itself wraps the c++ class,
            which ideally.
        """
        self.r = r
        r_ct = ct.c_ulonglong(r)
        d_ct = ct.c_ulonglong(d)
        s_ct = ct.c_ulonglong(s)
        self.obj = libhog.CICInterpolatorI(r_ct,d_ct, s_ct)

    def __del__(self):
        """Call the C++ object destructor"""
        libhog.CICInterpolatorEnd(self.obj)

    def run_filter(self, steps, input):
        """Run the filter"""
        if type(input[0]) != np.int64:
            print("Warning: type error")

        n_samples_output = np.int64(len(input) * (self.r))

        steps_ct = ct.c_longlong(steps)

        input_ct = npct.as_ctypes(input)
        output_ct = npct.as_ctypes(np.zeros(n_samples_output,dtype=np.int64))

        libhog.CICInterpolatorI64InOutSet(self.obj, input_ct, output_ct)
        libhog.CICInterpolatorRunFilter(self.obj, steps_ct)

        output = npct.as_array(output_ct)
        output = output.astype(np.int64)
        return output
