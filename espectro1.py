import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import plotly.express as px

# Cargar el archivo CSV con el delimitador correcto
df = pd.read_csv("datoss.csv", sep=';')

# Imprimir los nombres de las columnas
print("Nombres de las columnas:", df.columns)

# Eliminar espacios en blanco alrededor de los nombres de las columnas
df.columns = df.columns.str.strip()

# Verificar si las columnas 'Energia' e 'Intensidad' están presentes
if 'energia' in df.columns and 'intensidad' in df.columns:
    # Reemplazar comas por puntos en las columnas 'Energia' e 'Intensidad'
    df['energia'] = df['energia'].str.replace(',', '.', regex=False)
    df['intensidad'] = df['intensidad'].str.replace(',', '.', regex=False)
    
    # Convertir las columnas a tipo numérico
    df[['energia', 'intensidad']] = df[['energia', 'intensidad']].apply(pd.to_numeric, errors='coerce')
else:
    print("Las columnas 'energia' e 'intensidad' no se encontraron en el DataFrame.")
# Imprimir las primeras filas del DataFrame
print(df.head())
# Verificar si hay valores nulos
print("Valores nulos en 'energia':", df['energia'].isnull().sum())
print("Valores nulos en 'intensidad':", df['intensidad'].isnull().sum())

df = df.dropna(subset=['energia', 'intensidad'])

df[['energia', 'intensidad']].to_csv("236Pu.dat", sep='\t', index=False, header=True)



# Graficar
plt.figure(figsize=(8, 5))  # tamaño de la figura
plt.plot(df['energia'], df['intensidad'], marker='o', color='blue', linestyle='')
plt.yscale("log")
plt.title("Espectro de Energia")
plt.xlabel("Energia")
plt.ylabel("Intensidad")
plt.grid(True)
plt.tight_layout()
plt.show()
fig = px.scatter(df, x='energia', y='intensidad', title='Gráfico Energy vs Intensity', log_y=True)
fig.show()