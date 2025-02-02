"""
Plot a signal from an input file
"""

import numpy as np
import matplotlib.pyplot as plt

def main(filename):
    # Load COMPLEX frequencies from the input file
    freq = np.loadtxt(filename)

    # Create a time array
    time = np.arange(0, len(freq))

    print("boop")

    # Plot the freq
    plt.plot(time, freq[:, 0])
    plt.plot(time, freq[:, 1])
    plt.legend(["Real", " Imaginary"])
    plt.xlabel("Time")
    plt.ylabel("Amplitude")
    plt.title("Signal")
    

if __name__ == "__main__":
    main("Exercises/2.4/frequencies.txt")
    plt.show()