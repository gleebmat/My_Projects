import joblib
import numpy as np
import pandas as pd
from fastapi import HTTPException


model = joblib.load("data/models/xgboost.joblib")
scaler = joblib.load("data/models/scaler.joblib")
model_columns = joblib.load("data/models/model_columns.joblib")


def process_and_predict(request_dict: dict, city_name: str) -> float:
    input_data = pd.DataFrame([request_dict])

    for col in model_columns:
        if col.startswith("city_"):
            input_data[col] = 0

    city_col = f"city_{city_name}"
    if city_col in model_columns:
        input_data[city_col] = 1
    else:
        raise HTTPException(status_code=400, detail=f"City {city_name} not supported")

    input_data = input_data[model_columns]
    input_data = input_data[model_columns]

    # DIAGNOSTIC PRINTS
    print("--- DOCKER ML DIAGNOSTICS ---")
    print(f"Columns being sent to scaler: {list(input_data.columns)}")
    print(f"Raw input row values: {input_data.values}")

    scaled_features = scaler.transform(input_data)
    log_pred = model.predict(scaled_features)

    print(f"Raw model prediction output: {log_pred[0]}")

    final_price = float(np.expm1(log_pred)[0])
    return final_price

    scaled_features = scaler.transform(input_data)
    log_pred = model.predict(scaled_features)

    final_price = float(np.expm1(log_pred)[0])
    return final_price
