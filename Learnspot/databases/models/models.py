from sqlalchemy.orm import Mapped, mapped_column, relationship
from databases.database import Base
from sqlalchemy import ForeignKey
from sqlalchemy import JSON
from typing import Optional, List


# class User(Base):
#     __tablename__ = "user"

#     id: Mapped[int] = mapped_column(primary_key=True)
#     login: Mapped[str] = mapped_column(unique=True)


class Translation(Base):
    __tablename__ = "translation"

    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("user.id"), nullable=False)
    charachteristics: Mapped[str]

    translated_words: Mapped[list[str]] = mapped_column(JSON)


class User(Base):
    __tablename__ = "user"
    id: Mapped[int] = mapped_column(primary_key=True)
    login: Mapped[str] = mapped_column(unique=True)


class Texts(Base):
    __tablename__ = "texts"

    id: Mapped[int] = mapped_column(primary_key=True)

    user_id: Mapped[int] = mapped_column(ForeignKey("user.id"), nullable=False)

    characteristics: Mapped[Optional[str]] = mapped_column(nullable=True)
    original_text: Mapped[Optional[str]] = mapped_column(nullable=True)
    mistakes_solutions: Mapped[list[str]] = mapped_column(JSON)
    improved_text: Mapped[Optional[str]] = mapped_column(nullable=True)


class Conversation(Base):
    __tablename__ = "conversations"
    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("user.id"))
    messages: Mapped[List["ChatMessage"]] = relationship(
        back_populates="conversation", cascade="all, delete-orphan"
    )


class ChatMessage(Base):
    __tablename__ = "chat_messages"
    id: Mapped[int] = mapped_column(primary_key=True)
    conversation_id: Mapped[int] = mapped_column(ForeignKey("conversations.id"))
    role: Mapped[str] = mapped_column()
    content: Mapped[str] = mapped_column()
    conversation: Mapped["Conversation"] = relationship(
        back_populates="messages",
    )


class Words_to_practice(Base):
    __tablename__ = "words_to_practice"
    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("user.id"))
    words: Mapped[list[str]] = mapped_column(JSON)


class Words_to_practice_ai(Base):
    __tablename__ = "words_to_practice_ai"
    id: Mapped[int] = mapped_column(primary_key=True)
    user_id: Mapped[int] = mapped_column(ForeignKey("user.id"))
    words: Mapped[list[str]] = mapped_column(JSON)
