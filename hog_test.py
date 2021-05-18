import numpy as np
import numpy.fft as nfft
import numpy.random as ra
import scipy.signal as sig
import matplotlib.pyplot as plt
import hogenauer as hog

def autoscale(input, rate, to_power_per_hertz):
    """
    Automatically scales the input to the power of to_power, and returns
      the result. Bandwidth is used to ensure that the right power/bw is chosen
    A convenience function for display - used to see relative variations in
      amplitude across frequency.
    At the Time I wrote this I didn't understand noise temperature!

    """
    input_power = np.mean(input**2)
    expected_power = to_power_per_hertz * rate
    ratio = expected_power / input_power
    output = input * ratio**(1/2)
    return output

def test_autoscale():
    """
        Test function for our autoscaling convenience function.
    """

    sigsig = ra.randn(100000) * 74
    print(np.var(sigsig))
    sigsig = autoscale(sigsig, 100000, 0.2345)
    print(np.mean(sigsig**2))


def test():
    """ Basic testing function! (to see if it works!) """

    #data = np.zeros(4096,dtype=np.int64)
    #data += np.int64(10*np.sin(3*np.pi*np.arange(0, 2*np.pi, (2*np.pi/4096))))
    #data += np.int64(10*np.sin(513*np.arange(0, 2*np.pi, (2*np.pi/4096))))

    #data = np.int64(np.round(4*ra.randn(4096)))
    #data += np.int64(np.round(1024*np.sin(2*np.pi*1/64*np.arange(4096))))
    #data = np.abs(data) * 512

    n_samples = 4096*16
    data = np.int64(np.zeros(n_samples))
    data[0] = 1024
    #data = np.int64(16*np.array([1,-1,1,-1,1,-1,1,-1]))

    rate = 1024
    #Remember, these are defined  R D S
    deci = hog.CICDecimator(rate,2,2)
    interp = hog.CICInterpolator(rate,2,2)
    up = interp.run_filter(n_samples,data)
    updown = deci.run_filter(n_samples, np.roll(up,1024+256+128) )

    #data = autoscale(data, rate, 1)
    #updown = autoscale(updown, rate, 1)
    print(np.mean((data - updown)**2))

    #Plot the relative difference
    plt.figure()
    plt.plot(20*np.log10(1e-20 + np.abs(nfft.fft(updown[:-1])) / np.abs(nfft.fft(data[:-1])) ),label="data,end")
    #plt.plot(10*np.log10(1e-20 + np.abs(nfft.fft(data[1:])) / np.abs(nfft.fft(updown[:-1])) ),label="updown,end")
    plt.title("Relative Difference")
    plt.xlabel("Frequency (unnormalised)")
    plt.ylabel("original/filtered (dB, power)")

    plt.figure()
    plt.plot(np.arange(0,n_samples),10*np.log10(data + 1e-10), marker='o', label="data")
    #plt.plot(np.arange(0,n_samples,1/rate), up, marker='o', label="up")
    plt.plot(np.arange(0,n_samples), 10*np.log10(updown + 1e-10), marker='o', label="updown")
    plt.legend(loc="upper right")
    plt.title("Before and After (Impulse Response)")
    plt.xlabel("Sample")
    plt.ylabel("Amplitude (dB)")

    plt.figure()
    #plt.plot(np.angle(nfft.fft( autoscale(up, 4096*rate, 1)  )), label="up")
    plt.plot(np.angle(nfft.fft( autoscale(data, n_samples, 1)  )), label="data")
    plt.plot(np.angle(nfft.fft( autoscale(updown*1.01 , n_samples, 1) )), label="updown")
    plt.legend(loc="upper right")
    plt.title("Phase")
    plt.xlabel("Frequency (unnormalised)")
    plt.ylabel("arg (radians)")
    plt.show()

    while (True):
        pass

test()
