import datetime
import os
import joblib
import numpy as np
import pandas as pd
from fastapi import FastAPI, Depends, HTTPException
from pydantic import BaseModel, Field
from sqlalchemy import Column, Integer, Float, String, DateTime, create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, Session

from dotenv import load_dotenv


load_dotenv()

DATABASE_URL = (
    f"postgresql://postgres:{os.getenv('POSTGRESQL_PASS')}@localhost:5432/house_db"
)
engine = create_engine(DATABASE_URL)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()


class PredictionHistory(Base):
    __tablename__ = "predictions"
    id = Column(Integer, primary_key=True, index=True)
    timestamp = Column(DateTime, default=datetime.datetime.utcnow)
    city = Column(String)
    sqft_living = Column(Float)
    bedrooms = Column(Integer)
    predicted_price = Column(Float)


Base.metadata.create_all(bind=engine)


model = joblib.load("data/models/xgboost.joblib")
scaler = joblib.load("data/models/scaler.joblib")
model_columns = joblib.load("data/models/model_columns.joblib")


app = FastAPI(title="Pro House Predictor")


def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


class HouseRequest(BaseModel):
    bedrooms: int = Field(..., gt=0)
    bathrooms: float = Field(..., gt=0)
    sqft_living: float = Field(..., gt=0)
    sqft_lot: float = Field(..., gt=0)
    floors: float = Field(..., gt=0)
    waterfront: int = Field(..., ge=0, le=1)
    view: int = Field(..., ge=0, le=4)
    condition: int = Field(..., ge=1, le=5)
    sqft_above: float = Field(..., gt=0)
    sqft_basement: float = Field(..., ge=0)
    yr_built: int = Field(..., gt=1750)
    city: str
    years_since_renovation: float = Field(..., ge=0)


@app.post("/predict")
def predict_price(request: HouseRequest, db: Session = Depends(get_db)):
    try:
        input_data = pd.DataFrame([request.dict()])

        for col in model_columns:
            if col.startswith("city_"):
                input_data[col] = 0

        city_col = f"city_{request.city}"
        if city_col in model_columns:
            input_data[city_col] = 1
        else:
            raise HTTPException(
                status_code=400, detail=f"City {request.city} not supported"
            )

        input_data = input_data[model_columns]

        scaled_features = scaler.transform(input_data)
        log_pred = model.predict(scaled_features)
        final_price = float(np.expm1(log_pred)[0])

        new_record = PredictionHistory(
            city=request.city,
            sqft_living=request.sqft_living,
            bedrooms=request.bedrooms,
            predicted_price=final_price,
        )
        db.add(new_record)
        db.commit()
        return {
            "prediction": round(final_price, 2),
            "currency": "USD",
            "message": "Prediction logged to PostgreSQL",
        }
    except Exception as e:
        raise HTTPException(status_code=500, detail=str(e))
