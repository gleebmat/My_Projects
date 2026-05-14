import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

df = pd.read_csv("data/data.csv")

df.info()

df.head()

df.describe()
numeric_df = df.select_dtypes(include=["float64", "int64"])

correlation_matrix = numeric_df.corr()


plt.figure(figsize=(12, 10))

sns.heatmap(correlation_matrix, annot=True, cmap="coolwarm", fmt=".2f", linewidths=0.5)
plt.show()

plt.figure(figsize=(10, 6))

sns.regplot(
    data=df,
    x="sqft_living",
    y="price",
    scatter_kws={"alpha": 0.2, "s": 10},
    line_kws={"color": "yellow"},
)

df = df.dropna()
df.info()
df = df.drop(columns=["street", "statezip", "country", "city"])
df.info()
df["price"] = df["price"].replace(0, np.nan)

initial = len(df)
df = df.dropna()
final = len(df) - initial

sale_year = pd.to_datetime(df["date"]).dt.year

df["years_since_renovation"] = sale_year - np.maximum(
    df["yr_built"], df["yr_renovated"]
)

df.drop("yr_renovated", axis=1, inplace=True)
df = df.drop(columns="date")
df.to_csv("data/data_processed.csv", index=False)
df.to_parquet("data/data_processed.parquet", index=False)
