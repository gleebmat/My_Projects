import datetime
from sqlalchemy import Column, Integer, Float, String, DateTime
from app.database import Base


class PredictionHistory(Base):
    __tablename__ = "predictions"
    id = Column(Integer, primary_key=True, index=True)
    timestamp = Column(DateTime, default=datetime.datetime.now)
    city = Column(String)
    sqft_living = Column(Float)
    predicted_price = Column(Float)
