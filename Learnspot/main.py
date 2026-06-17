from fastapi import FastAPI
from databases.database import Base, engine
from fastapi_routing.translation_router_calls import router as translation_router
from fastapi_routing.users_router_calls import router as users_router
from fastapi_routing.reader_router_calls import router as reader_router
from fastapi_routing.chat_router_calls import router as chat_router
from fastapi_routing.practice_router_calls import router as practice_router

app = FastAPI()


app.include_router(translation_router, tags=["Your input translation"])
app.include_router(users_router, tags=["Users Manager"])
app.include_router(reader_router, tags=["AI-assistant for working with texts"])
app.include_router(chat_router, tags=["Learning German with talking to AI-Agents"])
app.include_router(practice_router, tags=["Practice your German!"])
Base.metadata.create_all(bind=engine)
