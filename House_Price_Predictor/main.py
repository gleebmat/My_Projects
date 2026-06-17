from fastapi import FastAPI, Depends, HTTPException
from sqlalchemy.orm import Session
import logging
from app.database import engine, Base, get_db
from app.schemas import HouseRequest, save_to_database
from app.ml_logic import process_and_predict
from app.models import PredictionHistory

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(message)s",
    handlers=[logging.FileHandler("app.log"), logging.StreamHandler()],
)
logger = logging.getLogger(__name__)

Base.metadata.create_all(bind=engine)


app = FastAPI(title="Pro House Predictor")


@app.post("/predict")
def predict_price(request: HouseRequest, db: Session = Depends(get_db)):
    try:
        logger.info(f"Received prediction request for city: {request.city}")
        final_price = process_and_predict(request.model_dump(), request.city)
        save_to_database(request=request, final_price=final_price, db=db)
        logger.info("Successfully predicted and logged price.")
        return {
            "prediction": round(final_price, 2),
            "currency": "USD",
            "message": "Prediction logged to PostgreSQL",
        }
    except HTTPException as he:
        logger.warning(f"Validation or user fault: {he.detail}")
        raise he
    except Exception as e:
        logger.error(f"Unexpected prediction failure: {str(e)}", exc_info=True)
        raise HTTPException(status_code=500, detail=str(e))


@app.get("/history")
def get_prediction_history(limit: int = 10, db: Session = Depends(get_db)):
    try:
        logger.info(f"Fetching the last {limit} predictions form PostgreSQL.")

        records = (
            db.query(PredictionHistory)
            .order_by(PredictionHistory.timestamp.desc())
            .limit(limit)
            .all()
        )
        return [
            {
                "id": r.id,
                "timestamp": r.timestamp,
                "city": r.city,
                "sqft_living": r.sqft_living,
                "predicted_price": round(r.predicted_price, 2),
            }
            for r in records
        ]
    except Exception as e:
        logger.error(f"Database fetch failed: {str(e)}", exc_info=True)
        raise HTTPException(
            status_code=500, detail="Could not retrieve history records."
        )
