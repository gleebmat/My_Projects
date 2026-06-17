import reflex as rx
from game_dashboard.state import AppState, Turn

BG_CARD = "#141412"
BG_CARD2 = "#1a1917"
BG_TEAL_HEADER = "#0d1f1e"
BORDER = "#2a2927"
BORDER_TEAL = "#0f766e"
TEXT_PRIMARY = "#e8e7e4"
TEXT_MUTED = "#78776f"
TEXT_FAINT = "#4a4946"
TEAL = "#2dd4bf"
TEAL_DIM = "#134e4a"
BAR_BG = "#2a2927"


def hp_row(item: list) -> rx.Component:
    unit_key = item[0]
    hp_val = item[1]
    return rx.el.tr(
        rx.el.td(
            rx.text(
                unit_key,
                size="2",
                font_family="monospace",
                weight="bold",
                color=TEXT_PRIMARY,
            ),
            style={"padding": "0.55rem 1rem", "border_bottom": f"1px solid {BORDER}"},
        ),
        rx.el.td(
            rx.hstack(
                rx.box(
                    rx.box(
                        width=f"min(100%, calc({hp_val}px * 0.5))",
                        height="6px",
                        background=TEAL,
                        border_radius="999px",
                    ),
                    width="100px",
                    height="6px",
                    background=BAR_BG,
                    border_radius="999px",
                    overflow="hidden",
                ),
                rx.text(
                    hp_val.to_string(),
                    size="2",
                    font_family="monospace",
                    color=TEXT_MUTED,
                ),
                align="center",
                spacing="3",
            ),
            style={"padding": "0.55rem 1rem", "border_bottom": f"1px solid {BORDER}"},
        ),
    )


def turn_panel(turn: Turn) -> rx.Component:
    return rx.vstack(
        rx.hstack(
            rx.hstack(
                rx.icon("activity", size=13, color=TEAL),
                rx.text("Turn Record", size="2", weight="bold", color=TEXT_PRIMARY),
                spacing="2",
                align="center",
            ),
            rx.hstack(
                rx.box(
                    rx.hstack(
                        rx.text("Team:", size="1", color=TEXT_FAINT),
                        rx.text(
                            turn.team, size="1", color=TEAL, font_family="monospace"
                        ),
                        spacing="1",
                    ),
                    padding="2px 10px",
                    background=TEAL_DIM,
                    border="1px solid " + BORDER_TEAL,
                    border_radius="999px",
                ),
                rx.box(
                    rx.hstack(
                        rx.text("ID #", size="1", color=TEXT_FAINT),
                        rx.text(
                            turn.id.to_string(),
                            size="1",
                            color=TEXT_MUTED,
                            font_family="monospace",
                        ),
                        spacing="1",
                    ),
                    padding="2px 10px",
                    background=BG_CARD2,
                    border=f"1px solid {BORDER}",
                    border_radius="999px",
                ),
                spacing="2",
            ),
            justify="between",
            align="center",
            width="100%",
        ),
        rx.box(height="1px", width="100%", background=BORDER),
        rx.vstack(
            rx.text(
                "UNIT HP SNAPSHOT",
                size="1",
                weight="bold",
                color=TEXT_FAINT,
                letter_spacing="0.08em",
            ),
            rx.box(
                rx.el.table(
                    rx.el.thead(
                        rx.el.tr(
                            rx.el.th(
                                "Unit",
                                style={
                                    "text_align": "left",
                                    "padding": "0.5rem 1rem",
                                    "font_size": "11px",
                                    "color": TEXT_FAINT,
                                    "font_weight": "600",
                                    "letter_spacing": "0.06em",
                                    "border_bottom": f"1px solid {BORDER}",
                                    "background": BG_CARD,
                                },
                            ),
                            rx.el.th(
                                "HP",
                                style={
                                    "text_align": "left",
                                    "padding": "0.5rem 1rem",
                                    "font_size": "11px",
                                    "color": TEXT_FAINT,
                                    "font_weight": "600",
                                    "letter_spacing": "0.06em",
                                    "border_bottom": f"1px solid {BORDER}",
                                    "background": BG_CARD,
                                },
                            ),
                        ),
                    ),
                    rx.el.tbody(
                        rx.foreach(turn.hp_units.items(), hp_row),
                    ),
                    style={
                        "width": "100%",
                        "border_collapse": "collapse",
                        "font_family": "-apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif",
                    },
                ),
                border=f"1px solid {BORDER}",
                border_radius="8px",
                overflow="hidden",
                background=BG_CARD2,
                width="100%",
            ),
            spacing="2",
            width="100%",
            align="start",
        ),
        rx.box(height="1px", width="100%", background=BORDER),
        rx.vstack(
            rx.text(
                "AI EXPLANATION",
                size="1",
                weight="bold",
                color=TEXT_FAINT,
                letter_spacing="0.08em",
            ),
            rx.cond(
                turn.ai_explanation != "",
                rx.box(
                    rx.text(
                        turn.ai_explanation,
                        size="2",
                        color=TEXT_MUTED,
                        line_height="1.75",
                    ),
                    padding="1rem 1.1rem",
                    background=BG_CARD2,
                    border=f"1px solid {BORDER}",
                    border_radius="8px",
                    width="100%",
                ),
                rx.box(
                    rx.text(
                        "No explanation recorded.",
                        size="2",
                        color=TEXT_FAINT,
                        style={"font_style": "italic"},
                    ),
                    padding="1rem 1.1rem",
                    background=BG_CARD2,
                    border=f"1px solid {BORDER}",
                    border_radius="8px",
                    width="100%",
                ),
            ),
            spacing="2",
            width="100%",
            align="start",
        ),
        spacing="4",
        width="100%",
        padding="1.1rem",
        align="start",
    )


def detail_panel() -> rx.Component:
    return rx.box(
        rx.cond(
            AppState.selected_match.id == 0,
            # Empty state
            rx.center(
                rx.vstack(
                    rx.icon("mouse-pointer-click", size=36, color=TEXT_FAINT),
                    rx.text(
                        "Select a match", size="3", weight="bold", color=TEXT_MUTED
                    ),
                    rx.text(
                        "Click any match on the left to inspect its data.",
                        size="2",
                        color=TEXT_FAINT,
                    ),
                    spacing="2",
                    align="center",
                ),
                height="100%",
                width="100%",
                padding="4rem",
            ),
            # Match detail
            rx.box(
                rx.box(
                    rx.hstack(
                        rx.hstack(
                            rx.icon("swords", size=15, color=TEAL),
                            rx.text(
                                "Match #",
                                rx.el.span(
                                    AppState.selected_match.id.to_string(),
                                    style={"font_family": "monospace"},
                                ),
                                size="4",
                                weight="bold",
                                color=TEXT_PRIMARY,
                            ),
                            spacing="2",
                            align="center",
                        ),
                        rx.box(
                            AppState.selected_match.turns.length().to_string(),
                            rx.cond(
                                AppState.selected_match.turns.length() == 1,
                                " turn",
                                " turns",
                            ),
                            padding="3px 10px",
                            background=TEAL_DIM,
                            color=TEAL,
                            border=f"1px solid {BORDER_TEAL}",
                            border_radius="999px",
                            font_size="12px",
                            font_weight="600",
                        ),
                        justify="between",
                        align="center",
                        width="100%",
                    ),
                    padding="1rem 1.25rem",
                    background=BG_TEAL_HEADER,
                    border_bottom=f"1px solid {BORDER_TEAL}",
                    border_radius="10px 10px 0 0",
                ),
                rx.cond(
                    AppState.selected_match.turns.length() == 0,
                    rx.center(
                        rx.vstack(
                            rx.icon("inbox", size=26, color=TEXT_FAINT),
                            rx.text(
                                "No turns in this match.", size="2", color=TEXT_MUTED
                            ),
                            align="center",
                            spacing="1",
                        ),
                        padding="2.5rem",
                        width="100%",
                    ),
                    rx.foreach(AppState.selected_match.turns, turn_panel),
                ),
                border=f"1px solid {BORDER}",
                border_radius="10px",
                overflow="hidden",
                background=BG_CARD,
                width="100%",
            ),
        ),
        padding="1.25rem",
        width="100%",
    )
