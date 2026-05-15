import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.metrics import mean_absolute_error, r2_score
import joblib
import torch
from xgboost import XGBRegressor
import numpy as np
from sklearn.preprocessing import StandardScaler
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader, TensorDataset


scaler = StandardScaler()

df = pd.read_csv("data/data_processed.csv")
df
# rf_params = {
#     "n_estimators": [1100],
#     "max_depth": [100],
#     "min_samples_split": [40],
# }
xgb_params = {
    "n_estimators": [1100],
    "learning_rate": [0.1],
    "max_depth": [2],
}
X = df.drop(columns=["price", "price_log"])
y = df["price_log"]

X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)
X_train
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)
X_test_scaled
model = [("XGBoost", XGBRegressor(random_state=42), xgb_params)]
for name, model, params in model:
    print(f"Training {name}")
    grid = GridSearchCV(
        model, params, cv=7, scoring="neg_mean_absolute_error", n_jobs=-1, verbose=3
    )
    grid.fit(X_train_scaled, y_train)

    best_m = grid.best_estimator_
    print(grid.best_params_)

    log_preds = best_m.predict(X_test_scaled)
    real_preds = np.expm1(log_preds)
    real_y_test = np.expm1(y_test)
    mae = mean_absolute_error(real_y_test, real_preds)
    r2 = r2_score(y_test, log_preds)  # r2 on the log values is standart!!

    print(f"{name} Real World Error (MAE): ${mae:,.2f}")
    print(f"{name} R-squared: {r2:.4f}")
df.describe()

joblib.dump(best_m, "data/models/xgboost.joblib")
joblib.dump(scaler, "data/models/scaler.joblib")


# -----------------------------

X_train_t = torch.tensor(X_train_scaled, dtype=torch.float32)
y_train_t = torch.tensor(y_train.values, dtype=torch.float32).view(-1, 1)
X_test_t = torch.tensor(X_test_scaled, dtype=torch.float32)


class HousePriceModel(nn.Module):
    def __init__(self, input_size):
        super(HousePriceModel, self).__init__()
        self.layer1 = nn.Linear(input_size, 64)
        self.layer2 = nn.Linear(64, 32)
        self.output = nn.Linear(32, 1)
        self.relu = nn.ReLU()

    def forward(self, x):
        x = self.relu(self.layer1(x))
        x = self.relu(self.layer2(x))
        return self.output(x)


model_pt = HousePriceModel(X_train_t.shape[1])
criterion = nn.MSELoss()
optimizer = optim.Adam(model_pt.parameters(), lr=0.0005)
train_data = TensorDataset(X_train_t, y_train_t)
train_loader = DataLoader(dataset=train_data, batch_size=16, shuffle=True)

print("\n--- Training PyTorch Neural Network ---")
for epoch in range(400):
    model_pt.train()
    epoch_loss = 0
    for batch_X, batch_y in train_loader:
        optimizer.zero_grad()

        predictions = model_pt(batch_X)
        loss = criterion(predictions, batch_y)

        loss.backward()
        torch.nn.utils.clip_grad_norm_(model_pt.parameters(), max_norm=1.0)

        optimizer.step()
        epoch_loss += loss.item()
    if (epoch + 1) % 20 == 0:
        avg_loss = epoch_loss / len(train_loader)
        print(f"Epoch [{epoch + 1}/400], Loss: {avg_loss:.4f}")

# 4. Evaluation
model_pt.eval()
with torch.no_grad():
    pt_log_preds = model_pt(X_test_t).numpy()
    pt_log_preds = np.clip(pt_log_preds, 10, 18)
    pt_real_preds = np.expm1(pt_log_preds)
    real_y_test = np.expm1(y_test.values).reshape(-1, 1)

    mae_pt = mean_absolute_error(real_y_test, pt_real_preds)
    print(f"\nPyTorch Real World Error (MAE): ${mae_pt:,.2f}")
# ----WAS PRETTY BAD...
