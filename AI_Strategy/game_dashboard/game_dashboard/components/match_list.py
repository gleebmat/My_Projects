import reflex as rx
from game_dashboard.state import AppState, Match

BG_CARD = "#171715"
BG_CARD_HOVER = "#1e1d1b"
BG_CARD_ACTIVE = "#1a2e2c"
BORDER = "#2a2927"
BORDER_ACTIVE = "#0f766e"
TEXT_PRIMARY = "#e8e7e4"
TEXT_MUTED = "#78776f"
TEXT_FAINT = "#4a4946"
TEAL = "#2dd4bf"
TEAL_DIM = "#134e4a"


def match_card(match: Match) -> rx.Component:
    turn_count = match.turns.length()
    team_label = rx.cond(match.turns.length() > 0, match.turns[0].team, "—")
    is_selected = AppState.selected_match.id == match.id

    return rx.box(
        rx.hstack(
            rx.vstack(
                rx.hstack(
                    rx.text(
                        rx.el.span("Match #", style={"color": TEXT_FAINT}),
                        rx.el.span(match.id.to_string(), style={"color": TEXT_PRIMARY}),
                        size="3",
                        weight="bold",
                        font_family="monospace",
                    ),
                    rx.box(
                        rx.cond(turn_count > 0, "✓ data", "empty"),
                        padding="1px 7px",
                        border_radius="999px",
                        font_size="11px",
                        background=rx.cond(turn_count > 0, TEAL_DIM, "#2a2927"),
                        color=rx.cond(turn_count > 0, TEAL, TEXT_MUTED),
                        border=rx.cond(
                            turn_count > 0,
                            f"1px solid {BORDER_ACTIVE}",
                            f"1px solid {BORDER}",
                        ),
                    ),
                    align="center",
                    spacing="2",
                ),
                rx.hstack(
                    rx.text("Team:", size="1", color=TEXT_FAINT),
                    rx.text(
                        team_label, size="1", color=TEXT_MUTED, font_family="monospace"
                    ),
                    rx.text("·", size="1", color=TEXT_FAINT),
                    rx.text(
                        turn_count.to_string(),
                        size="1",
                        color=TEXT_MUTED,
                        font_family="monospace",
                    ),
                    rx.text(
                        rx.cond(turn_count == 1, "turn", "turns"),
                        size="1",
                        color=TEXT_FAINT,
                    ),
                    spacing="1",
                    align="center",
                ),
                spacing="1",
                align="start",
            ),
            rx.icon("chevron-right", size=15, color=TEXT_FAINT),
            justify="between",
            align="center",
            width="100%",
        ),
        padding="0.8rem 1rem",
        border_radius="8px",
        background=rx.cond(is_selected, BG_CARD_ACTIVE, BG_CARD),
        border=rx.cond(
            is_selected, f"1px solid {BORDER_ACTIVE}", f"1px solid {BORDER}"
        ),
        cursor="pointer",
        transition="all 140ms ease",
        _hover={
            "background": rx.cond(is_selected, BG_CARD_ACTIVE, BG_CARD_HOVER),
            "border_color": BORDER_ACTIVE,
        },
        on_click=AppState.select_match(match.id),
        width="100%",
    )


def match_list() -> rx.Component:
    return rx.vstack(
        rx.hstack(
            rx.hstack(
                rx.icon("database", size=14, color=TEAL),
                rx.text("Matches", size="2", weight="bold", color=TEXT_PRIMARY),
                spacing="2",
                align="center",
            ),
            rx.box(
                AppState.matches.length().to_string(),
                padding="1px 8px",
                border_radius="999px",
                font_size="11px",
                background=TEAL_DIM,
                color=TEAL,
                font_weight="600",
            ),
            justify="between",
            align="center",
            width="100%",
            padding_bottom="0.75rem",
            border_bottom=f"1px solid {BORDER}",
        ),
        rx.cond(
            AppState.loading,
            rx.vstack(
                rx.foreach(
                    rx.Var.range(5),
                    lambda _: rx.box(
                        height="58px",
                        width="100%",
                        border_radius="8px",
                        background="#1a1917",
                    ),
                ),
                spacing="2",
                width="100%",
            ),
            rx.cond(
                AppState.matches.length() == 0,
                rx.vstack(
                    rx.icon("inbox", size=30, color=TEXT_FAINT),
                    rx.text("No matches yet", size="2", color=TEXT_MUTED),
                    rx.text(
                        "Run the AI pipeline to populate data.",
                        size="1",
                        color=TEXT_FAINT,
                    ),
                    align="center",
                    padding_y="2rem",
                    width="100%",
                    spacing="1",
                ),
                rx.vstack(
                    rx.foreach(AppState.matches, match_card),
                    spacing="2",
                    width="100%",
                ),
            ),
        ),
        spacing="3",
        width="100%",
        padding="1rem",
    )
