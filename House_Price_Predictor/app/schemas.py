from pydantic import BaseModel, Field
from sqlalchemy.orm import Session
from app.models import PredictionHistory


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


def save_to_database(request: HouseRequest, final_price: float, db: Session):
    new_record = PredictionHistory(
        city=request.city,
        sqft_living=request.sqft_living,
        predicted_price=final_price,
    )
    db.add(new_record)
    db.commit()
