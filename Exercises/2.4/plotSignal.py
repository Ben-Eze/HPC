"""
Plot a signal from an input file
"""

import numpy as np
import matplotlib.pyplot as plt

def main(filename):
    # Load the signal from the input file
    signal = np.loadtxt(filename)

    # Create a time array
    time = np.arange(0, len(signal))

    print("boop")

    # Plot the signal
    plt.plot(time, signal)
    plt.xlabel("Time")
    plt.ylabel("Amplitude")
    plt.title("Signal")

if __name__ == "__main__":
    main("Exercises/2.4/signal.txt")
    main("Exercises/2.4/reconstructed_signal.txt")
    plt.legend(["Original signal", "Reconstructed signal"])
    plt.show()