#!/usr/bin/env python3
# script to plot and compare second order RK4 results

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# purely cosmetic
import seaborn as sns
sns.set();


def main():
    # create dataframe from C++ outfile
    df = pd.read_csv("RK42O.csv", header=0);
    x = df.iloc[:, 0].tolist();
    y2 = df.iloc[:, 1].tolist();

    # create numpy arrays to compare to
    y = np.sin(x);

    # create canvas
    fig = plt.figure();
    ax = plt.axes();

    # plot lines
    line = ax.plot(x, y, label=r"Analytic Solution of $\sin(x)$", color='r', zorder=1)
    line2 = ax.scatter(x, y2, label=r"RK Solution", s=1, color='b', alpha=0.7, zorder=5)
                  

    # set preferences
    plt.xlabel("x");
    plt.ylabel("y");
    plt.title("Runge-Kutta Solution of $y'' = -y$");
    plt.legend();

    # show
    plt.grid(True);
    plt.savefig("sho.svg");
    # plt.show();
    return 0;


main();
