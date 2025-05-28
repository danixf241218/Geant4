import pandas as pd
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import plotly.express as px

# Cargar el archivo CSV
nombre_columnas = ["energy", "intensity"]
df = pd.read_csv("livechart.csv")
df[['energy', 'intensity']] = df[['energy', 'intensity']].apply(pd.to_numeric, errors = 'coerce')

#generar archivo salida.csv
df[['energy', 'intensity']].to_csv("salida.csv", index = False)
df[['energy', 'intensity']].to_csv("salida.dat", sep='\t', index=False, header=False)
df = df.dropna(subset=['energy', 'intensity'])


#graficar
plt.figure(figsize=(8, 5)) #tamaño de la figura
plt.plot(df['energy'], df['intensity'], marker='o', color='blue', linestyle = '--')
plt.yscale("log")
plt.title("Espectro de Energia")
plt.xlabel("Energia")
plt.ylabel("Intensidad")
plt.grid(True)
plt.tight_layout()
plt.show()

fig = px.scatter(df, x='energy', y='intensity', title='Gráfico Energy vs Intensity', log_y=True)
fig.show()
