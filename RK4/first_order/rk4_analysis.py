#!/usr/bin/env python3
# script to plot and compare first order RK4 results

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# purely cosmetic
import seaborn as sns
sns.set()


def main():
    # create dataframe from C++ outfile
    df = pd.read_csv("RK4.csv", header=0);
    x = df.iloc[:, 0].tolist();
    y2 = df.iloc[:, 1].tolist();

    # create numpy arrays to compare to
    y = np.exp(x);

    # create canvas
    fig = plt.figure();
    ax = plt.axes();

    # plot lines
    line = ax.plot(x, y, label=r"Analytic Solution $e^x$", color='r')
    line2 = ax.scatter(x, y2, label=r"RK4 Solution", s=10, alpha = 0.7, color='b');

    # set preferences
    plt.xlabel("x");
    plt.ylabel("y");
    plt.title("Runge-Kutta Solution of $y' = y$");
    plt.legend();

    # show
    plt.grid(True);
    # plt.show();
    plt.savefig("exp.svg")
    return 0;


main();
