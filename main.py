import numpy as np
import seaborn as sns
import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import pandas as pd
import subprocess
from scipy.stats import linregress
import time

FILENAME1 = "data1.txt"
FILENAME2 = "data2.txt"
FILENAME3 = "data3.txt"

EXEC = "program"

def make_graphs(data, regression_type, name):
    df = pd.DataFrame(data, columns=["Tempo", "Conjunto", "Tamanho"])
    df["Conjunto_label"] = df["Conjunto"].astype(int).apply(lambda x: f"Conjunto {chr(ord('A') + x - 1)}")
          
    fig = plt.figure(figsize=(10, 6))
    palette = sns.color_palette("Set1", n_colors=len(df["Conjunto"].unique()))
    sns_plot = sns.scatterplot(x="Tamanho", y="Tempo", data=df, hue='Conjunto_label', style='Conjunto_label', palette=palette, s=100)
    
    regression_lines = []
    
    for idx, conjunto in enumerate(sorted(df["Conjunto"].unique())):
        subset = df[df["Conjunto"] == conjunto]
        x = subset["Tamanho"].values
        y = subset["Tempo"].values

        if regression_type == 1:
            X_fit = x ** 2  
        elif regression_type == 2:
            X_fit = x * np.log2(x)  
        else:
            continue

        slope, intercept, r_value, _, _ = linregress(X_fit, y)

        y_pred = slope * X_fit + intercept

        line, = plt.plot(x, y_pred, color=palette[idx], linestyle='-')
        regression_lines.append((line, f"Ajuste {subset['Conjunto_label'].iloc[0]} (R²={r_value**2:.3f})"))
            
    plt.title(f"Algoritmo {name}")
    plt.xlabel("Tamanho do Conjunto")
    plt.ylabel("Tempo de Execução (s)")
    
    scatter_handles, scatter_labels = sns_plot.get_legend_handles_labels()
    
    regression_handles = [line for line, _ in regression_lines]
    regression_labels = [label for _, label in regression_lines]
    
    all_handles = scatter_handles + regression_handles
    all_labels = scatter_labels + regression_labels
    
    plt.legend(handles=all_handles, labels=all_labels, title="Conjunto", loc="upper left")
    plt.grid(True)
    
    plt.show(block=False)
    plt.pause(0.5)
    
def main():
    # Run 3 processes, 1 for each algorithm 
    process1 = subprocess.Popen([f"./{EXEC}", "1"])
    process2 = subprocess.Popen([f"./{EXEC}", "2"])
    process3 = subprocess.Popen([f"./{EXEC}", "3"])

    processes = [(process1, FILENAME1), (process2, FILENAME2), (process3, FILENAME3)]

    while processes:
        for i, (process, filename) in enumerate(processes):
            retcode = process.poll()
            # Check if the process has finished
            if retcode is not None:
                with open(filename, "r") as file:
                    if filename == "data1.txt":
                        data = np.loadtxt(file)
                        make_graphs(data, 1, "Insertion Sort")
                    else:
                        data = np.loadtxt(file)
                        if filename == "data2.txt": make_graphs(data, 2, "Heap Sort")
                        else: make_graphs(data, 2, "Quick Sort")
                
                print(f"Process finished. Data read from {filename}.")

                processes.pop(i)
                break 
        time.sleep(1)
    
    input("Press Enter to exit...")
        
if __name__ == "__main__":
    main()
