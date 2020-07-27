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



def test():
    """ Basic testing function! """

    #data = np.zeros(4096,dtype=np.int64)
    #data += np.int64(10*np.sin(3*np.pi*np.arange(0, 2*np.pi, (2*np.pi/4096))))
    #data += np.int64(10*np.sin(513*np.arange(0, 2*np.pi, (2*np.pi/4096))))
    data = np.int64(np.round(64*ra.randn(4096)))
    #data = np.int64(16*np.array([1,-1,1,-1,1,-1,1,-1]))

    rate = 4096
    deci = CICDecimator(rate,1,3)
    interp = CICInterpolator(rate,1,1)
    up = interp.run_filter(4096,data)
    updown = deci.run_filter(4096, up)

    plt.figure()
    plt.plot(10*np.log10(1e-20+np.abs(nfft.fft(data[1:]/updown[:-1]))))
    plt.figure()
    plt.plot(np.arange(0,4096),data, label="data")
    #plt.plot(np.arange(0,4096,1/rate), up, label="up")
    plt.plot(np.arange(0,4096), updown*1e-9, label="updown")
    plt.legend()
    plt.figure()
    plt.plot(10*np.log10(1e-10+np.abs(nfft.fft(up))), label="up")
    plt.plot(10*np.log10(1e-10+np.abs(nfft.fft(data))), label="data")
    plt.plot(10*np.log10(1e-10+np.abs(nfft.fft(updown*1e-10))), label="updown")
    plt.legend()
    plt.show()

    while (True):
        pass

test()
