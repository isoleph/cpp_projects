#!/usr/bin/env python3
# script to plot and compare RK4 results

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns;

sns.set();


def main():
    # create dataframe from C++ outfile
    df = pd.read_csv("RK42O.csv", header=0);
    x = df.iloc[:, 0].tolist();
    y = df.iloc[:, 1].tolist();

    # create numpy arrays to compare to
    x2 = np.linspace(0, 2 * np.pi, 500);
    y2 = np.sin(x);

    # create canvas
    fig = plt.figure();
    ax = plt.axes();

    # plot lines
    line = ax.plot(x, y, label=r"RK Solution of $y '' = -y$")
    line2 = ax.plot(x2, y2, label=r"Actual Solution of $y '' = -y$")
                  

    # set preferences
    plt.xlabel("x");
    plt.ylabel("y");
    plt.title("Runge-Kutta Integration of $y'' = -y$");
    plt.legend();

    # show
    plt.grid(True);
    plt.show();
    return 0;


main();
