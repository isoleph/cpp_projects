#!/usr/bin/env python3
# script to plot and compare RK4 results

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns;

sns.set();


def main():
    # create dataframe from C++ outfile
    df = pd.read_csv("RK4.csv", header=0);
    x = df.iloc[:, 0].tolist();
    y = df.iloc[:, 1].tolist();

    # create numpy arrays to compare to
    x2 = np.linspace(0, 5, 50);
    y2 = 1 / 3 * x2**3;

    # create canvas
    fig = plt.figure();
    ax = plt.axes();

    # plot lines
    line = ax.scatter(x, y, label=r"RK Solution of $\frac{1}{3} x^3$",
                      linestyle="--", alpha=0.7, linewidth=0.5);
    line2 = ax.scatter(x2, y2, label=r"Actual Solution of $\frac{1}{3} x^3$",
                       alpha=0.7, linewidth=0.5);

    # set preferences
    plt.xlabel("x");
    plt.ylabel("y");
    plt.title("Runge-Kutta Solution of $y' = x^2$");
    plt.legend();

    # show
    plt.grid(True);
    plt.show();
    return 0;


main();
