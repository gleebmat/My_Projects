import reflex as rx
import httpx
from typing import List
from dataclasses import dataclass, field


@dataclass
class Turn:
    id: int = 0
    team: str = ""
    hp_units: dict = field(default_factory=dict)
    ai_explanation: str = ""


@dataclass
class Match:
    id: int = 0
    turns: List[Turn] = field(default_factory=list)


class AppState(rx.State):
    matches: List[Match] = []
    selected_match: Match = Match()
    loading: bool = False
    error: str = ""

    @rx.event
    async def load_matches(self):
        self.loading = True
        self.error = ""
        self.selected_match = Match()
        yield
        try:
            async with httpx.AsyncClient(timeout=10.0) as client:
                resp = await client.get("http://127.0.0.1:8000/turns")
                resp.raise_for_status()
                data = resp.json()
                self.matches = [
                    Match(
                        id=m["id"],
                        turns=[
                            Turn(
                                id=t["id"],
                                team=str(t.get("team", "")),
                                hp_units=t.get("hp_units", {}),
                                ai_explanation=t.get("ai_explanation") or "",
                            )
                            for t in m.get("turns", [])
                        ],
                    )
                    for m in data
                ]
        except Exception as e:
            self.error = f"Could not reach API: {e}"
        finally:
            self.loading = False

    @rx.event
    async def select_match(self, match_id: int):
        self.loading = True
        self.error = ""
        yield
        try:
            async with httpx.AsyncClient(timeout=10.0) as client:
                resp = await client.get(f"http://127.0.0.1:8000/turn/{match_id}")
                resp.raise_for_status()
                m = resp.json()
                self.selected_match = Match(
                    id=m["id"],
                    turns=[
                        Turn(
                            id=t["id"],
                            team=str(t.get("team", "")),
                            hp_units=t.get("hp_units", {}),
                            ai_explanation=t.get("ai_explanation") or "",
                        )
                        for t in m.get("turns", [])
                    ],
                )
        except Exception as e:
            self.error = f"Could not load match #{match_id}: {e}"
        finally:
            self.loading = False
