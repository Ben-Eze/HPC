import numpy as np

def main():
    # Create a time array
    time = np.arange(0, 1000)

    # Create a signal
    signal = np.sin(2*np.pi * 0.01 * time) + np.sin(2*np.pi * 0.02 * time)

    # Save the signal to a file
    np.savetxt("Exercises/2.4/simple_signal.txt", signal)

if __name__ == "__main__":
    main()