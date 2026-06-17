from typing import Generator
from fastapi import Depends, HTTPException
from fastapi.security import HTTPBearer
from sqlalchemy.orm import Session
from fastapi.security import HTTPBearer
from fastapi.security import HTTPAuthorizationCredentials
from databases.database import SessionLocal
from fastapi.security import HTTPAuthorizationCredentials
from databases.models.models import User


def get_db() -> Generator[Session, None, None]:
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()


security = HTTPBearer()


def get_current_user(
    credentials: HTTPAuthorizationCredentials = Depends(security),
    db: Session = Depends(get_db),
) -> User:
    login = credentials.credentials

    user = db.query(User).filter(User.login == login).scalar()

    if not user:
        raise HTTPException(status_code=401, detail="Unauthorized user")
    return user
